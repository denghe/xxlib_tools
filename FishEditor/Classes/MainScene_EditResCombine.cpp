#include "MainScene.h"

void MainScene::EditResCombine(std::shared_ptr<FishManage::ResCombine> const& resCombine, int const& pageIndex) {
	removeAllChildren();

	// 背景
	CreateBG(this);

	// 创建 / 编辑组合鱼

	// 初始化 editBoxs 引用容器. 准备数据保存函数
	editBoxs.clear();

	// 先创建 item 容器，再创建 design area. 确保拖拽时的显示层级正确
	auto itemNode = cocos2d::Node::create();
	addChild(itemNode);

	// design area
	auto drawNode = cocos2d::DrawNode::create();
	drawNode->setPosition(W_2 + 250, H_2);
	drawNode->drawPoint({ 0,0 }, 2, cocos2d::Color4F::BLUE);
	drawNode->drawRect({ -DW_2, -DH_2 }, { DW_2, DH_2 }, cocos2d::Color4F::BLUE);
	addChild(drawNode);

	// 读 items 并绘制
	for (auto&& o : resCombine->items) {
		
		auto dr = DraggingRes::create();
		dr->scene = this;
		dr->item = CreateResPreview({ 0,0 }, { 0,0 }, o.res.lock(), dr);
		dr->setPosition({ o.offsetX,o.offsetY });
		dr->setScale(o.baseScale);
		dr->setRotation(o.baseAngle);
		dr->setUserData(&*o.res.lock());
		drawNode->addChild(dr);
	}

	auto&& SaveDataToRes = [this, resCombine, drawNode] {
		resCombine->name = editBoxs[0]->getText();
		// todo: 扫 drawNode 的成员, 同步 resCombine->items
		// 从 drawNode 过滤出所有 DraggingRes 节点
		std::vector<DraggingRes*> rs;
		for (auto&& n : drawNode->getChildren()) {
			if (auto&& o = dynamic_cast<DraggingRes*>(n)) {
				rs.push_back(o);
			}
		}
		// 存储数据
		resCombine->items.clear();
		for (auto&& r : rs) {
			auto&& p = r->getPosition();
			auto&& o = resCombine->items.emplace_back();
			o.offsetX = p.x;
			o.offsetY = p.y;
			o.baseAngle = r->getRotation();
			o.baseScale = r->getScale();
			o.res = xx::As<FishManage::ResBase>(((FishManage::ResBase*)r->getUserData())->shared_from_this());
		}
	};


	// res name: [________________]
	cocos2d::Vec2 p(margin, H - lineHeight / 2);
	{
		auto tName = CreateLabel(p, "res name: ");
		p.x += GetWidth(tName);
		auto eName = CreateEditBox(p, { lineHeight * 10, fontSize * 1.1f }, resCombine->name, "");
		editBoxs.push_back(eName);
	}

	p.x = margin;
	p.y -= lineHeight;
	CreateLabel(p, "please drag some res into right side place.");

	// 左边分页显示所有资源列表( 如果用 scroll view 横着拖有点麻烦 ), 右边显示布景框
	// 从左边拖拽已有资源到布景框。拖拽时 按实际大小 创建并跟随鼠标 / touch 移动， touch up 时判断如果落在 布景框则 保留 否则 杀掉
	// 同时同步所有数据结构. 利用 setUserData 来对应数据, 最后扫描这些节点 填充到数据

	// 每条 item 长相：
/*
+-------+ name: resName
|preview|
+-------+ type: 2d? spine? 3d? combine?
	*/

	// item 高度
	auto itemHeight = lineHeight * 2;

	// 列表可用显示高度
	auto avaliableHeight = H - lineHeight * 4 - margin;
	
	// 每页能显示多少条
	auto pageSize = (int)floor(avaliableHeight / (itemHeight + margin));

	// 成员总数
	decltype(data.ress) ress;
	for (auto&& o : data.ress) {
		if (!xx::Is<FishManage::ResCombine>(o)) ress.emplace_back(o);
	}
	auto itemCount = (int)ress.size();

	// 总页数
	auto pageCount = itemCount / pageSize;
	if (pageCount * pageSize < itemCount) {
		++pageCount;
	}

	// 当前页 item 起始下标
	auto beginRowIndex = pageSize * pageIndex;

	// 结束下标
	auto endRowIndex = beginRowIndex + pageSize;
	if (endRowIndex >= itemCount) {
		endRowIndex = itemCount - 1;
	}

	// [<---] ? / ??? [--->]

	p.x = lineHeight * 8;
	p.y = lineHeight / 2;
	auto bPrev = CreateButton(p, "[<---]", [this, resCombine, pageIndex, SaveDataToRes](auto) {
		if (pageIndex == 0) return;
		SaveDataToRes();
		EditResCombine(resCombine, pageIndex - 1);
	});

	p.x += GetWidth(bPrev) + margin;
	auto tIndex = CreateLabel(p, xx::ToString(pageIndex + 1));

	p.x += GetWidth(tIndex);
	auto tSplit = CreateLabel(p, " / ");
	tSplit->setColor(yellow);

	p.x += GetWidth(tSplit);
	auto tCount = CreateLabel(p, xx::ToString(pageCount));

	p.x += GetWidth(tCount) + margin;
	auto bNext = CreateButton(p, "[--->]", [this, resCombine, pageIndex, pageCount, SaveDataToRes](auto) {
		if (pageIndex + 1 == pageCount) return;
		SaveDataToRes();
		EditResCombine(resCombine, pageIndex + 1);
	});


	// items
	for (int i = beginRowIndex; i <= endRowIndex; ++i) {
		auto&& res = ress[i];

		//cocos2d::Vec2 pos
		// 计算起始坐标

		// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
		cocos2d::Vec2 pos(margin, H - lineHeight * 2 - margin - (itemHeight + margin) * (i - beginRowIndex));

		// bg( can drag )
		{
			auto&& img = cocos2d::ui::ImageView::create("green_edit.png");
			img->setScale9Enabled(true);
			img->setPosition(pos);
			img->setContentSize({ 500, itemHeight });
			img->setAnchorPoint({0, 1});
			itemNode->addChild(img);

			auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
			touchListener->setSwallowTouches(true);
			touchListener->onTouchBegan = [this, img, res, drawNode](cocos2d::Touch* t, cocos2d::Event* e) {
				auto&& tL = t->getLocation();
				auto&& p = img->convertToNodeSpace(tL);
				auto&& cs = img->getContentSize();
				// 如果点击在img范围内
				if (p.x>=0 && p.x<=cs.width && p.y>=0 && p.y<=cs.height) {
					touching = true;
					currDraggingRes = DraggingRes::create();
					currDraggingRes->scene = this;
					currDraggingRes->item = CreateResPreview({0,0}, { 0,0 }, res, currDraggingRes);
					currDraggingRes->setPosition(drawNode->convertToNodeSpace(tL));
					currDraggingRes->setUserData(&*res);
					drawNode->addChild(currDraggingRes);
					lastPos = tL;
					return true;
				}
				return false;
			};
			touchListener->onTouchMoved = [this, img](cocos2d::Touch* t, cocos2d::Event* e) {
				if (!touching) return false;
				auto&& tL = t->getLocation();
				auto&& diff = tL - lastPos;
				lastPos = tL;
				currDraggingRes->setPosition(currDraggingRes->getPosition() + diff);
				return true;
			};
			touchListener->onTouchEnded = [this](cocos2d::Touch* t, cocos2d::Event* e) {
				if (!touching) return false;
				// 如果拖拽到蓝框外，就自杀
				touching = false;
				auto&& p = currDraggingRes->getPosition();
				if (p.x < -DW_2 || p.x > DW_2 || p.y < -DH_2 || p.y > DH_2) {
					currDraggingRes->removeFromParentAndCleanup(true);
				}
				currDraggingRes = nullptr;
				return true;
			};
			touchListener->onTouchCancelled = touchListener->onTouchEnded;
			cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, img);
		}

		p.x = pos.x + itemHeight / 2;
		p.y = pos.y - itemHeight / 2;
		CreateResPreview(p, { itemHeight ,itemHeight }, res, itemNode);

		// name
		{
			p.x = pos.x + itemHeight + margin;
			p.y = pos.y - lineHeight / 2;
			CreateLabelPair(p, "name: ", xx::ToString(res->name), itemNode);
		}

		// type
		{
			p.y -= lineHeight;
			std::string typeName;
			if (xx::Is<FishManage::Res2d>(res)) {
				typeName = "2D Sprite Frame";
			}
			else if (xx::Is<FishManage::ResSpine>(res)) {
				typeName = "2D Spine";
			}
			else if (xx::Is<FishManage::Res3d>(res)) {
				typeName = "3D c3b Model";
			}
			else if (xx::Is<FishManage::ResCombine>(res)) {
				typeName = "Combine";
			}
			else {
				typeName = "unknown";
			}
			CreateLabelPair(p, "type: ", typeName, itemNode);
		}

	}



	//                   ->                [Cancel]      [Save & Quit]
	{
		p.x = W - margin;
		p.y = lineHeight / 2;
		auto bNext = CreateButton(p, "[Save & Quit]", [this, resCombine, SaveDataToRes](auto) {
			SaveDataToRes();
			if (resCombine->name.empty()) {
				PopupMessage("please input res name!");
				return;
			}
			if (resCombine->items.empty()) {
				PopupMessage("please drag more than one res in scene!");
				return;
			}
			resCombine->lastUpdateTime = xx::NowEpoch10m();
			if (std::find(data.ress.begin(), data.ress.end(), resCombine) == data.ress.end()) {
				data.ress.push_back(resCombine);
			}
			SaveData();
			ManageResources();
		});
		bNext->setAnchorPoint({ 1, 0.5 });


		p.x -= GetWidth(bNext) + lineHeight * 2;
		auto bCancel = CreateButton(p, "[Cancel]", [this](auto) {
			ManageResources();
		});
		bCancel->setAnchorPoint({ 1, 0.5 });
	}
}
