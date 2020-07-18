#include "MainScene.h"

void MainScene::EditResCombine(std::shared_ptr<FishManage::ResCombine> const& resCombine, int const& pageIndex) {
	removeAllChildren();

	// ����
	CreateBG(this);

	// ���� / �༭�����

	// ��ʼ�� editBoxs ��������. ׼�����ݱ��溯��
	editBoxs.clear();

	// �ȴ��� item �������ٴ��� design area. ȷ����קʱ����ʾ�㼶��ȷ
	auto itemNode = cocos2d::Node::create();
	addChild(itemNode);

	// design area
	auto drawNode = cocos2d::DrawNode::create();
	drawNode->setPosition(W_2 + 250, H_2);
	drawNode->drawPoint({ 0,0 }, 2, cocos2d::Color4F::BLUE);
	drawNode->drawRect({ -DW_2, -DH_2 }, { DW_2, DH_2 }, cocos2d::Color4F::BLUE);
	addChild(drawNode);

	// �� items ������
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
		// todo: ɨ drawNode �ĳ�Ա, ͬ�� resCombine->items
		// �� drawNode ���˳����� DraggingRes �ڵ�
		std::vector<DraggingRes*> rs;
		for (auto&& n : drawNode->getChildren()) {
			if (auto&& o = dynamic_cast<DraggingRes*>(n)) {
				rs.push_back(o);
			}
		}
		// �洢����
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

	// ��߷�ҳ��ʾ������Դ�б�( ����� scroll view �������е��鷳 ), �ұ���ʾ������
	// �������ק������Դ����������קʱ ��ʵ�ʴ�С ������������� / touch �ƶ��� touch up ʱ�ж�������� �������� ���� ���� ɱ��
	// ͬʱͬ���������ݽṹ. ���� setUserData ����Ӧ����, ���ɨ����Щ�ڵ� ��䵽����

	// ÿ�� item ���ࣺ
/*
+-------+ name: resName
|preview|
+-------+ type: 2d? spine? 3d? combine?
	*/

	// item �߶�
	auto itemHeight = lineHeight * 2;

	// �б������ʾ�߶�
	auto avaliableHeight = H - lineHeight * 4 - margin;
	
	// ÿҳ����ʾ������
	auto pageSize = (int)floor(avaliableHeight / (itemHeight + margin));

	// ��Ա����
	decltype(data.ress) ress;
	for (auto&& o : data.ress) {
		if (!xx::Is<FishManage::ResCombine>(o)) ress.emplace_back(o);
	}
	auto itemCount = (int)ress.size();

	// ��ҳ��
	auto pageCount = itemCount / pageSize;
	if (pageCount * pageSize < itemCount) {
		++pageCount;
	}

	// ��ǰҳ item ��ʼ�±�
	auto beginRowIndex = pageSize * pageIndex;

	// �����±�
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
		// ������ʼ����

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
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
				// ��������img��Χ��
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
				// �����ק�������⣬����ɱ
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
