#include "MainScene.h"

void MainScene::EditFrameCD(std::shared_ptr<FishManage::ResBase> const& res, std::shared_ptr<FishManage::ActionBase> const& action, int const& index) {
	removeAllChildren();

	// 编辑 action 下某 frame 的碰撞

	// 背景
	CreateBG(this);

	// 圆圈容器
	auto nodeCircles = cocos2d::Node::create();
	nodeCircles->setPosition(W_2, H_2);
	addChild(nodeCircles);

	// 向圆圈容器创建圆圈
	auto&& CreateCircle = [this, nodeCircles](cocos2d::Vec2 const& pos, float const& r)->Circle* {
		auto&& nc = Circle::create();
		nodeCircles->addChild(nc);
		nc->scene = this;
		nc->setPosition(pos);
		nc->Draw(r);
		return nc;
	};

	// 指向当前帧
	auto&& frame = action->frames[index];

	// 指向包围盒. 如果有的话就绘制
	auto&& mc = frame->maxCDCircle;
	if (mc.r != 0) {
		CreateCircle({ mc.x, mc.y }, mc.r);
	}

	// 绘制次级小圆
	for(auto&& c : frame->cdCircles) {
		CreateCircle({ c.x, c.y }, c.r);
	}

	// 扫描圆圈容器并保存到 res
	auto&& SaveCirclesToRes = [this, nodeCircles, action, index] {
		// 从 nodeCircles 过滤出所有 Circle 节点
		std::vector<Circle*> ncs;
		for (auto&& n : nodeCircles->getChildren()) {
			if (auto&& nc = dynamic_cast<Circle*>(n)) {
				ncs.push_back(nc);
			}
		}
		// 指向当前帧
		auto&& frame = action->frames[index];
		// 指向包围盒
		auto&& mc = frame->maxCDCircle;
		// 先清 0
		mc.x = mc.y = mc.r = 0;
		frame->cdCircles.clear();
		// 存储包围盒数据
		if (!ncs.empty()) {
			auto&& nc = ncs[0];
			mc.x = nc->getPositionX();
			mc.y = nc->getPositionY();
			mc.r = nc->r;
		}
		// 存储次级圆圈数据
		for(size_t i = 1; i < ncs.size(); ++i) {
			auto&& nc = ncs[i];
			auto&& c = frame->cdCircles.emplace_back();
			c.x = nc->getPositionX();
			c.y = nc->getPositionY();
			c.r = nc->r;
		}
	};

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// [Cleanup]
	auto bCleanup = CreateButton(p, "[Cleanup]", [this, res, action, index](auto) {
		auto&& frame = action->frames[index];
		frame->cdCircles.clear();
		auto&& mc = frame->maxCDCircle;
		mc.x = mc.y = mc.r = 0;
		EditFrameCD(res, action, index);
	});

	p.y -= lineHeight;
	CreateLabel(p, "please touch or mouse click in the blue box and drag to create CIRCLE. first CIRCLE is BONDING BOX");
	p.y -= lineHeight;
	CreateLabel(p, "press + - when selected circle, can change radius.");

	// [<--]  idx / max  [-->]                                    [Exit]
	p.x = lineHeight * 8;
	p.y = lineHeight / 2;
	auto bPrev = CreateButton(p, "[<---]", [this, res, action, index, SaveCirclesToRes](auto) {
		if (index == 0) return;
		SaveCirclesToRes();
		EditFrameCD(res, action, index - 1);
	});

	p.x += GetWidth(bPrev) + margin;
	auto tIndex = CreateLabel(p, xx::ToString(index + 1));

	p.x += GetWidth(tIndex);
	auto tSplit = CreateLabel(p, " / ");
	tSplit->setColor(yellow);

	p.x += GetWidth(tSplit);
	auto tCount = CreateLabel(p, xx::ToString(action->frames.size()));

	p.x += GetWidth(tCount) + margin;
	auto bNext = CreateButton(p, "[--->]", [this, res, action, index, SaveCirclesToRes](auto) {
		if (index + 1 == action->frames.size()) return;
		SaveCirclesToRes();
		EditFrameCD(res, action, index + 1);
	});

	if (index) {
		p.x += GetWidth(bNext) + lineHeight * 8;
		keyboardCallback_C = [this, res, action, index](auto) {
			auto&& pf = action->frames[index - 1];
			auto&& f = action->frames[index];
			f->maxCDCircle = pf->maxCDCircle;
			f->cdCircles = pf->cdCircles;
			EditFrameCD(res, action, index);
		};
		auto bCopyCircleFromPrev = CreateButton(p, "[Copy Circle From Prev]", cocos2d::ccMenuCallback( keyboardCallback_C));
	}

	p.x = W - margin;
	auto bExit = CreateButton(p, "[Exit]", [this, res, action, SaveCirclesToRes](auto) {
		keyboardCallback_C = nullptr;
		SaveCirclesToRes();
		if (auto&& o = xx::As<FishManage::Res2d>(res)) {
			ConfigSpriteFrame(o, xx::As<FishManage::Action2d>(action));
		}
		//else if (auto&& o = xx::As<FishManage::ResSpine>(res)) {
		//	ConfigSpriteFrame(o, xx::As<FishManage::ActionSpine>(action));
		//}
		//else if (auto&& o = xx::As<FishManage::Res3d>(res)) {
		//	ConfigSpriteFrame(o, xx::As<FishManage::Action3d>(action));
		//}
		//else if (auto&& o = xx::As<FishManage::ResCombine>(res)) {
		//	ConfigSpriteFrame(o, xx::As<FishManage::ActionCombine>(action));
		//}
	});
	bExit->setAnchorPoint({ 1, 0.5 });


	// 在中间绘制动作，令帧停在 index 位置. touch 蓝色区域内可绘制圆环, 可移动圆环


	auto drawNode = cocos2d::DrawNode::create();
	//drawNode->setPosition(W_2, H_2);
	drawNode->drawPoint({ 0,0 }, 2, cocos2d::Color4F::BLUE);
	drawNode->drawRect({ -DW_2, -DH_2 }, { DW_2, DH_2 }, cocos2d::Color4F::BLUE);
	nodeCircles->addChild(drawNode);


	if (auto&& frame2d = xx::As<FishManage::Frame2d>(frame)) {
		auto&& spr = CreateSpriteFrame({W_2, H_2}, { 0,0 }, frame2d->spriteFrameName);
		spr->setOpacity(127);
	}
	//else if (auto&& o = xx::As<FishManage::ResSpine>(res)) {
	//	ConfigSpriteFrame(o, xx::As<FishManage::ActionSpine>(action));
	//}
	//else if (auto&& o = xx::As<FishManage::Res3d>(res)) {
	//	ConfigSpriteFrame(o, xx::As<FishManage::Action3d>(action));
	//}
	//else if (auto&& o = xx::As<FishManage::ResCombine>(res)) {
	//	ConfigSpriteFrame(o, xx::As<FishManage::ActionCombine>(action));
	//}


	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this, nodeCircles, CreateCircle](cocos2d::Touch* t, cocos2d::Event* e) {
		auto&& tL = t->getLocation();
		auto&& p = nodeCircles->convertToNodeSpace(tL);
		if (p.x >= -DW_2 && p.x <= DW_2 && p.y >= -DH_2 && p.y <= DH_2) {
			lastPos = p;
			assert(!currCircle);
			currCircle = CreateCircle(p, 1);
			return true;
		}
		return false;
	};
	touchListener->onTouchMoved = [this, nodeCircles](cocos2d::Touch* t, cocos2d::Event* e) {
		if (!currCircle) return false;
		auto&& tL = t->getLocation();
		auto&& p = nodeCircles->convertToNodeSpace(tL);
		auto&& d = p.getDistance(lastPos);
		currCircle->Draw(d);
		return true;
	};
	touchListener->onTouchEnded = [this, nodeCircles](cocos2d::Touch* t, cocos2d::Event* e) {
		if (currCircle->r <= 3) {
			currCircle->removeFromParentAndCleanup(true);
		}
		currCircle = nullptr;
		return false;
	};
	touchListener->onTouchCancelled = touchListener->onTouchEnded;
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, nodeCircles);
}
