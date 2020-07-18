#include "MainScene.h"

void MainScene::EditFrameLock(std::shared_ptr<FishManage::ResBase> const& res, std::shared_ptr<FishManage::ActionBase> const& action, int const& index) {
	removeAllChildren();

	// �༭ action ��ĳ frame ����ײ

	// ����
	CreateBG(this);

	// ����������
	auto nodePoints = cocos2d::Node::create();
	nodePoints->setPosition(W_2, H_2);
	addChild(nodePoints);

	// ��ԲȦ��������ԲȦ
	auto&& CreatePoint = [this, nodePoints](cocos2d::Vec2 const& pos)->Circle* {
		auto&& nc = Circle::create();
		nodePoints->addChild(nc);
		nc->scene = this;
		nc->pointMode = true;
		nc->setPosition(pos);
		nc->Draw(6);
		return nc;
	};

	// ָ��ǰ֡
	auto&& frame = action->frames[index];

	// ������������
	auto&& mp = frame->mainLockPoint;
	{
		auto p = CreatePoint({ mp.x, mp.y });
		p->defaultColor = cocos2d::Color4F::GREEN;
		p->color = cocos2d::Color4F::GREEN;
		p->Draw(p->r);
	}

	// ����������
	for (auto&& p : frame->lockPoints) {
		CreatePoint({ p.x, p.y });
	}

	// ɨ��ԲȦ���������浽 res
	auto&& SaveCirclesToRes = [this, nodePoints, action, index] {
		// ָ��ǰ֡
		auto&& frame = action->frames[index];
		// ���� 0
		frame->mainLockPoint.x = 0;
		frame->mainLockPoint.y = 0;
		frame->lockPoints.clear();
		// �� nodePoint ���˳����� Circle �ڵ�( �������� )
		std::vector<Circle*> ncs;
		for (auto&& n : nodePoints->getChildren()) {
			if (auto&& nc = dynamic_cast<Circle*>(n)) {
				ncs.push_back(nc);
			}
		}
		// �洢��Ҫ����������
		if (ncs.size()) {
			frame->mainLockPoint.x = ncs[0]->getPositionX();
			frame->mainLockPoint.y = ncs[0]->getPositionY();
		}
		// �洢������
		for (size_t i = 1; i < ncs.size(); ++i) {
			auto&& nc = ncs[i];
			auto&& p = frame->lockPoints.emplace_back();
			p.x = nc->getPositionX();
			p.y = nc->getPositionY();
		}
	};

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// [Cleanup]
	auto bCleanup = CreateButton(p, "[Cleanup]", [this, res, action, index](auto) {
		auto&& frame = action->frames[index];
		frame->cdCircles.clear();
		auto&& mc = frame->maxCDCircle;
		mc.x = mc.y = mc.r = 0;
		EditFrameLock(res, action, index);
		});

	p.y -= lineHeight;
	CreateLabel(p, "please touch or mouse click in the blue box to create POINT. first POINT is MAIN LOCK POINT");

	// [<--]  idx / max  [-->]                                    [Exit]
	p.x = lineHeight * 8;
	p.y = lineHeight / 2;
	auto bPrev = CreateButton(p, "[<---]", [this, res, action, index, SaveCirclesToRes](auto) {
		if (index == 0) return;
		SaveCirclesToRes();
		EditFrameLock(res, action, index - 1);
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
		EditFrameLock(res, action, index + 1);
		});

	if (index) {
		p.x += GetWidth(bNext) + lineHeight * 8;
		auto bCopyCircleFromPrev = CreateButton(p, "[Copy Points From Prev]", [this, res, action, index](auto) {
			auto&& pf = action->frames[index - 1];
			auto&& f = action->frames[index];
			f->mainLockPoint = pf->mainLockPoint;
			f->lockPoints = pf->lockPoints;
			EditFrameLock(res, action, index);
			});
	}

	p.x = W - margin;
	auto bExit = CreateButton(p, "[Exit]", [this, res, action, SaveCirclesToRes](auto) {
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


	// ���м���ƶ�������֡ͣ�� index λ��. touch ��ɫ�����ڿɻ��Ƶ�, ����ק�ƶ�


	auto drawNode = cocos2d::DrawNode::create();
	//drawNode->setPosition(W_2, H_2);
	drawNode->drawPoint({ 0,0 }, 2, cocos2d::Color4F::BLUE);
	drawNode->drawRect({ -DW_2, -DH_2 }, { DW_2, DH_2 }, cocos2d::Color4F::BLUE);
	nodePoints->addChild(drawNode);


	if (auto&& frame2d = xx::As<FishManage::Frame2d>(frame)) {
		auto&& spr = CreateSpriteFrame({ W_2, H_2 }, { 0,0 }, frame2d->spriteFrameName);
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
	touchListener->onTouchBegan = [this, nodePoints, CreatePoint](cocos2d::Touch* t, cocos2d::Event* e) {
		auto&& tL = t->getLocation();
		auto&& p = nodePoints->convertToNodeSpace(tL);
		if (p.x >= -DW_2 && p.x <= DW_2 && p.y >= -DH_2 && p.y <= DH_2) {
			CreatePoint(p);
			return true;
		}
		return false;
	};
	touchListener->onTouchMoved = [](cocos2d::Touch* t, cocos2d::Event* e) {
		return false;
	};
	touchListener->onTouchEnded = [this](cocos2d::Touch* t, cocos2d::Event* e) {
		return false;
	};
	touchListener->onTouchCancelled = touchListener->onTouchEnded;
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, nodePoints);
}
