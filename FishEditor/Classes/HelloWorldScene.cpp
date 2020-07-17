#include "HelloWorldScene.h"
#include "AppDelegate.h"
#include "ActionPlayer_SpriteFrame.h"
#include "xx_file.h"
#include "xx_math.h"
#include "xx_chrono.h"

#pragma region funcs

void HelloWorld::PopupMessage(std::string const& txt, cocos2d::Color3B const& color) {
	cocos2d::Vec2 pos(W / 2, H * 0.7);
	auto&& t = CreateLabel(pos, txt);
	t->setAnchorPoint({ 0.5, 0.5 });
	t->setColor(color);
	t->runAction(cocos2d::Sequence::create(
		cocos2d::DelayTime::create(1.0f)
		, cocos2d::Spawn::create(
			cocos2d::FadeOut::create(0.5f)
			, cocos2d::MoveTo::create(0.5f, { W / 2, H })
			, nullptr
		)
		, cocos2d::RemoveSelf::create()
		, nullptr
	));
}

cocos2d::Label* HelloWorld::CreateLabel(cocos2d::Vec2 const& pos, std::string const& txt, cocos2d::Node* const& container) {
	auto l = cocos2d::Label::createWithBMFont("3500.fnt", txt);
	if (!l) return l;
	l->setScale(fontSize / 32.0f);
	l->setAnchorPoint({ 0, 0.5 });
	l->setPosition(pos);
	if (container) {
		container->addChild(l);
	}
	else {
		this->addChild(l);
	}
	return l;
}
std::pair<cocos2d::Label*, cocos2d::Label*> HelloWorld::CreateLabelPair(cocos2d::Vec2 const& pos, std::string const& key, std::string const& value, cocos2d::Node* const& container) {
	std::pair<cocos2d::Label*, cocos2d::Label*> rtv;
	rtv.first = CreateLabel(pos, key, container);
	rtv.second = CreateLabel({pos.x + GetWidth(rtv.first), pos.y}, value, container);
	rtv.second->setColor(yellow);
	return rtv;
}

cocos2d::ui::Button* HelloWorld::CreateButton(cocos2d::Vec2 const& pos, std::string const& txt, cocos2d::ccMenuCallback&& callback, cocos2d::Node* const& container) {
	auto b = cocos2d::ui::Button::create();
	if (!b) return b;
	b->setTitleColor(blue);
	b->setTitleFontName("arial");
	b->setTitleFontSize(fontSize);
	b->setTitleText(txt);
	b->setAnchorPoint({ 0, 0.5 }); 
	b->setPosition(pos);
	b->setZoomScale(0.1f);
	b->setPressedActionEnabled(true);
	b->addClickEventListener(std::move(callback));
	if (container) {
		container->addChild(b);
	}
	else {
		this->addChild(b);
	}
	return b;
}

cocos2d::ui::EditBox* HelloWorld::CreateEditBox(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& text, std::string const& holderText, cocos2d::Node* const& container) {
	auto et = cocos2d::ui::EditBox::create(siz, "green_edit.png");
	et->setDelegate(this);
	et->setContentSize(siz);
	et->setAnchorPoint({ 0, 0.5 });
	et->setPosition(pos);
	et->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	et->setFontSize(fontSize);
	et->setText(text.c_str());
	et->setPlaceHolder(holderText.c_str());
	if (container) {
		container->addChild(et);
	}
	else {
		this->addChild(et);
	}
	return et;
}

cocos2d::Sprite3D* HelloWorld::CreateOrc(cocos2d::Vec2 const& pos, float const& r, cocos2d::Node* const& container) {
	auto s = cocos2d::Sprite3D::create("orc.c3b");
	if (!s) return nullptr;
	if (auto a = cocos2d::Animation3D::create("orc.c3b", "Take 001")) {
		s->runAction(cocos2d::RepeatForever::create(
			cocos2d::Animate3D::create(a)
		));
	}
	s->setPosition(pos);
	s->setRotation3D({ -90, 180, 90 + r });
	s->setScale(4);
	if (container) {
		container->addChild(s);
	}
	else {
		this->addChild(s);
	}
	return s;
}

ActionPlayer_SpriteFrame* HelloWorld::CreateActionPlayer_SpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::vector<std::string> const& plists, std::shared_ptr<FishManage::Action2d> const& action, cocos2d::Node* const& container) {
	auto a = ActionPlayer_SpriteFrame::create();
	a->setAnchorPoint({ 0.5, 0.5 });
	a->setPosition(pos);
	a->SetActionData(plists, action);
	a->Play();
	auto&& cs = a->getContentSize();
	if (cs.width > cs.height) {
		a->setScale(siz.width / cs.width);
	}
	else {
		a->setScale(siz.height / cs.height);
	}
	if (container) {
		container->addChild(a);
	}
	else {
		this->addChild(a);
	}
	return a;
}



cocos2d::ui::ScrollView* HelloWorld::CreateSV(cocos2d::Vec2 const& pos, cocos2d::Size const& cutSize, cocos2d::Size const& itemsSize, cocos2d::Node* const& container) {
	auto sv = cocos2d::ui::ScrollView::create();
	if (!sv) return sv;
	sv->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
	sv->setTouchEnabled(true);
	sv->setBounceEnabled(true);
	sv->setBackGroundImageScale9Enabled(true);
	sv->setBackGroundImage("green_edit.png");
	sv->setScrollBarWidth(4);
	sv->setScrollBarPositionFromCorner(cocos2d::Vec2(6, 6));
	sv->setScrollBarColor(cocos2d::Color3B::WHITE);

	sv->setAnchorPoint({ 0, 1 });
	sv->setPosition(pos);
	sv->setContentSize(cutSize);
	sv->setInnerContainerSize(itemsSize);
	if (container) {
		container->addChild(sv);
	}
	else {
		this->addChild(sv);
	}
	return sv;
}

cocos2d::LayerColor* HelloWorld::CreateBG(cocos2d::Node* const& container) {
	auto bg = cocos2d::LayerColor::create({ 45, 45, 48, 255 }, W, H);
	if (!bg) return bg;
	bg->setPosition(0, 0);
	bg->setAnchorPoint({ 0, 0 });
	if (container) {
		container->addChild(bg);
	}
	else {
		this->addChild(bg);
	}
	return bg;
}

cocos2d::Sprite* HelloWorld::CreateSprite(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& fileName, cocos2d::Node* const& container) {
	auto s = cocos2d::Sprite::create();
	s->setTexture(fileName);
	s->setAnchorPoint({ 0.5, 0.5 });
	s->setPosition(pos);
	auto&& cs = s->getContentSize();
	if (cs.width > cs.height) {
		s->setScale(siz.width / cs.width);
	}
	else {
		s->setScale(siz.height / cs.height);
	}
	if (container) {
		container->addChild(s);
	}
	else {
		this->addChild(s);
	}
	return s;
}

cocos2d::Sprite* HelloWorld::CreateSpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& spriteFrameName, cocos2d::Node* const& container) {
	auto s = cocos2d::Sprite::create();
	s->setSpriteFrame(spriteFrameName);
	s->setAnchorPoint({ 0.5, 0.5 });
	s->setPosition(pos);
	if (siz.width > 0 && siz.height > 0) {
		auto&& cs = s->getContentSize();
		if (cs.width > cs.height) {
			s->setScale(siz.width / cs.width);
		}
		else {
			s->setScale(siz.height / cs.height);
		}
	}
	if (container) {
		container->addChild(s);
	}
	else {
		this->addChild(s);
	}
	return s;
}

cocos2d::ui::CheckBox* HelloWorld::CreateCheckBox(cocos2d::Vec2 const& pos, bool const& value, cocos2d::ui::CheckBox::ccCheckBoxCallback&& callback, cocos2d::Node* const& container) {
	auto cb = cocos2d::ui::CheckBox::create(
		"check_box_normal.png",
		"check_box_normal_press.png",
		"check_box_active.png",
		"check_box_normal_disable.png",
		"check_box_active_disable.png");
	cb->setAnchorPoint({ 0, 0.5 });
	cb->setPosition(pos);
	cb->addEventListener(std::move(callback));
	cb->setSelected(value);
	if (container) {
		container->addChild(cb);
	}
	else {
		this->addChild(cb);
	}
	return cb;
}


float HelloWorld::GetWidth(cocos2d::Node* const& tar) {
	return tar->getContentSize().width * tar->getScaleX();
}

float HelloWorld::GetWidth(std::pair<cocos2d::Label*, cocos2d::Label*> const& tar) {
	return tar.first->getContentSize().width + tar.second->getContentSize().width;
}


void HelloWorld::CreateResPreview(cocos2d::Vec2 const& pos, cocos2d::Size siz, std::shared_ptr<FishManage::ResBase> res, cocos2d::Node* const& container) {
	if (auto&& r = xx::As<FishManage::Res2d>(res)) {
		CreateActionPlayer_SpriteFrame(pos, siz, r->plistFileNames, xx::As<FishManage::Action2d>(r->actions[0]), container);
		// todo: 影子相关
	}
	else if (auto&& r = xx::As<FishManage::ResSpine>(res)) {
		// todo
	}
	else if (auto&& r = xx::As<FishManage::Res3d>(res)) {
		// todo
	}
	else if (auto&& r = xx::As<FishManage::ResCombine>(res)) {
		// todo
	}
	else {
	}
}

#pragma endregion

void HelloWorld::EditFrameCD(std::shared_ptr<FishManage::ResBase> const& res, std::shared_ptr<FishManage::ActionBase> const& action, int const& index) {
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
			auto&& nc = dynamic_cast<Circle*>(n);
			if (nc) {
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
		auto bCopyCircleFromPrev = CreateButton(p, "[Copy Circle From Prev]", [this, res, action, index](auto) {
			auto&& pf = action->frames[index - 1];
			auto&& f = action->frames[index];
			f->maxCDCircle = pf->maxCDCircle;
			f->cdCircles = pf->cdCircles;
			EditFrameCD(res, action, index);
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
			PopupMessage(xx::ToString("p = ", p.x, ", ", p.y));
			lastPos = p;
			assert(!newCircle);
			newCircle = CreateCircle(p, 1);
			return true;
		}
		return false;
	};
	touchListener->onTouchMoved = [this, nodeCircles](cocos2d::Touch* t, cocos2d::Event* e) {
		if (!newCircle) return false;
		auto&& tL = t->getLocation();
		auto&& p = nodeCircles->convertToNodeSpace(tL);
		auto&& d = p.getDistance(lastPos);
		newCircle->Draw(d);
		return true;
	};
	touchListener->onTouchEnded = [this, nodeCircles](cocos2d::Touch* t, cocos2d::Event* e) {
		if (newCircle->r <= 3) {
			newCircle->removeFromParentAndCleanup(true);
		}
		newCircle = nullptr;
		return false;
	};
	touchListener->onTouchCancelled = touchListener->onTouchEnded;
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, nodeCircles);
}

void HelloWorld::EditFrameLock(std::shared_ptr<FishManage::ResBase> const& res, std::shared_ptr<FishManage::ActionBase> const& action, int const& index) {
	// todo
}

void HelloWorld::ConfigSpriteFrame(std::shared_ptr<FishManage::Res2d> const& res2d, std::shared_ptr<FishManage::Action2d> const& action2d) {
	// 开始遍历 names (sprite frame names) 并加载. 此时可清除之前的内容
	removeAllChildren();

	// 初始化 editBoxs 引用容器. 准备数据保存函数
	editBoxs.clear();
	auto&& SaveEditBoxDataToRes = [this, res2d, action2d] {
		action2d->name = editBoxs[0]->getText();
		xx::Convert(editBoxs[1]->getText(), action2d->frameRate);
		xx::Convert(editBoxs[2]->getText(), action2d->width);
		xx::Convert(editBoxs[3]->getText(), action2d->height);
		// editBoxs[4] 用于临时填写 distance
		for (int i = 5; i < (int)editBoxs.size(); ++i) {
			xx::Convert(editBoxs[i]->getText(), action2d->frames[i - 5]->moveDistance);
		}
	};

	// 背景
	CreateBG(this);

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// action name: [_____________________]     frameRate: [_________]       width: [_________]       height: [_________]
	auto tActionName = CreateLabel(p, "action name: ");

	p.x += GetWidth(tActionName);
	auto eActionName = CreateEditBox(p, { lineHeight * 8, fontSize * 1.1f }, action2d->name, "");

	p.x += GetWidth(eActionName) + lineHeight * 2;
	auto tFrameRate = CreateLabel(p, "frameRate: ");

	p.x += GetWidth(tFrameRate);
	auto eFrameRate = CreateEditBox(p, { lineHeight * 3, fontSize * 1.1f }, xx::ToString(action2d->frameRate), "");
	eFrameRate->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);

	// 如果宽高没有填写过，则取第一张图的宽高填入
	if (action2d->width == 0 || action2d->height == 0) {
		auto tmp = cocos2d::Sprite::createWithSpriteFrameName(xx::As<FishManage::Frame2d>(action2d->frames[0])->spriteFrameName);
		auto siz = tmp->getContentSize();
		action2d->width = siz.width;
		action2d->height = siz.height;
	}

	p.x += GetWidth(eFrameRate) + lineHeight * 2;
	auto tWidth = CreateLabel(p, "width: ");

	p.x += GetWidth(tWidth);
	auto eWidth = CreateEditBox(p, { lineHeight * 3, fontSize * 1.1f }, xx::ToString(action2d->width), "");
	eWidth->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);

	p.x += GetWidth(eWidth) + lineHeight * 2;
	auto tHeight = CreateLabel(p, "height: ");

	p.x += GetWidth(tHeight);
	auto eHeight = CreateEditBox(p, { lineHeight * 3, fontSize * 1.1f }, xx::ToString(action2d->height), "");
	eHeight->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);

	p.x += GetWidth(tHeight) + lineHeight * 2;
	auto eDistance = CreateEditBox(p, { lineHeight * 3, fontSize * 1.1f }, "1", "");
	eDistance->setInputMode(cocos2d::ui::EditBox::InputMode::DECIMAL);

	p.x += GetWidth(eDistance) + margin;
	auto bFillDistance = CreateButton(p, "[Fill All Distance]", [this, res2d, action2d, SaveEditBoxDataToRes](auto) {
		SaveEditBoxDataToRes();
		std::string distanceText = editBoxs[4]->getText();
		if (distanceText.empty()) {
			PopupMessage("please input distance!");
			return;
		}
		float distance = 0;
		xx::Convert(distanceText.c_str(), distance);
		for (size_t i = 0; i < action2d->frames.size(); ++i) {
			action2d->frames[i]->moveDistance = distance;
		}
		ConfigSpriteFrame(res2d, action2d);
	});

	editBoxs.push_back(eActionName);
	editBoxs.push_back(eFrameRate);
	editBoxs.push_back(eWidth);
	editBoxs.push_back(eHeight);
	editBoxs.push_back(eDistance);


	// 最下方步骤按钮
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateButton(p, "[Save & Exit]", [this, res2d, action2d, SaveEditBoxDataToRes](auto) {
		SaveEditBoxDataToRes();
		if (action2d->name.empty()) {
			PopupMessage("please input action name!");
			return;
		}
		// 新动作？加到列表
		if(std::find(res2d->actions.begin(), res2d->actions.end(), action2d) == res2d->actions.end()) {
			res2d->actions.push_back(action2d);
		}
		EditRes2d(res2d);
	});
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= GetWidth(bNext) + lineHeight * 2;
	auto bCancel = CreateButton(p, "[Back]", [this, res2d, action2d, SaveEditBoxDataToRes](auto) {
		if (std::find(res2d->actions.begin(), res2d->actions.end(), action2d) == res2d->actions.end()) {
			ChooseSpriteFrame(res2d, action2d);
		}
		else {
			EditRes2d(res2d);
		}
	});
	bCancel->setAnchorPoint({ 1, 0.5 });

	// 算 sv 显示坐标 与 体积
	p.x = margin;
	p.y = H - lineHeight;
	cocos2d::Size svSize(W - margin * 2, H - lineHeight * 2);

	// 每条 item 长相：
	/*
+-----+ sprite frame name: xxxxx
| pic | moveDistance: [___________]
+-----+ [Copy]                 [Delete]
*/
// item 高度
	const auto itemHeight = lineHeight * 3;

	// 内容总高度
	auto svContentHeight = margin + (itemHeight + margin) * action2d->frames.size();
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// 根据 裁切size, 内容size 创建 sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight });

	// 向 sv 填充 items
	// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
	for (size_t i = 0; i < action2d->frames.size(); ++i) {
		auto&& frame = xx::As<FishManage::Frame2d>(action2d->frames[i]);

		// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		p.x = pos.x + itemHeight / 2;
		p.y = pos.y - itemHeight / 2;
		auto spr = CreateSpriteFrame(p, { itemHeight, itemHeight }, frame->spriteFrameName, sv);

		p.x = pos.x + itemHeight + margin;
		p.y = pos.y - lineHeight / 2;
		CreateLabelPair(p, "sprite frame name: ", xx::ToString(frame->spriteFrameName), sv);

		p.x = pos.x + itemHeight + margin;
		p.y -= lineHeight;
		auto txt1 = CreateLabel(p, "moveDistance: ", sv);

		p.x += GetWidth(txt1);
		auto e1 = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, xx::ToString(frame->moveDistance), "", sv);
		e1->setInputMode(cocos2d::ui::EditBox::InputMode::DECIMAL);
		editBoxs.push_back(e1);

		p.x = pos.x + itemHeight + margin;
		p.y -= lineHeight;
		auto bCopy = CreateButton(p, "[Copy]", [this, sv, i = i, res2d, action2d, SaveEditBoxDataToRes](auto) {
			SaveEditBoxDataToRes();
			action2d->frames.insert(action2d->frames.begin() + i, action2d->frames[i]);
			configSpriteFrameScrolledPercentVertical = sv->getScrolledPercentVertical();
			ConfigSpriteFrame(res2d, action2d);
		}, sv);

		p.x += GetWidth(bCopy) + lineHeight * 2;
		auto bEditCDCircle = CreateButton(p, "[Edit CD]", [this, sv, i = i, res2d, action2d, SaveEditBoxDataToRes](auto) {
			SaveEditBoxDataToRes();
			EditFrameCD(res2d, action2d, i);
		}, sv);

		p.x += GetWidth(bEditCDCircle) + lineHeight * 2;
		auto bEditLock = CreateButton(p, "[Edit Lock]", [this, sv, i = i, res2d, action2d, SaveEditBoxDataToRes](auto) {
			SaveEditBoxDataToRes();
			EditFrameLock(res2d, action2d, i);
		}, sv);

		p.x += GetWidth(bEditLock) + lineHeight * 10;
		auto bDelete = CreateButton(p, "[Delete]", [this, sv, i = i, res2d, action2d, SaveEditBoxDataToRes](auto) {
			SaveEditBoxDataToRes();
			action2d->frames.erase(action2d->frames.begin() + i);
			configSpriteFrameScrolledPercentVertical = sv->getScrolledPercentVertical();
			ConfigSpriteFrame(res2d, action2d);
		}, sv);
	}

	// 还原滚动位置
	if (svContentHeight > svSize.height) {
		sv->jumpToPercentVertical(configSpriteFrameScrolledPercentVertical);
	}
	else {
		configSpriteFrameScrolledPercentVertical = 0;
	}
}

void HelloWorld::ChooseSpriteFrame(std::shared_ptr<FishManage::Res2d> const& res2d, std::shared_ptr<FishManage::Action2d> const& action2d) {
	// 开始遍历 names (plist) 并加载. 此时可清除之前的内容
	removeAllChildren();

	// 背景
	CreateBG(this);

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// 最上方说明文字
	CreateLabel(p, "please multi select sprite frame for this action:");

	// 第二排 全选 全不选 / 前缀勾选
	p.y -= lineHeight;
	auto bSelectAll = CreateButton(p, "[SelectAll]", [this, res2d](auto) {
		for (auto&& kv : cbNames) {
			kv.first->setSelected(true);
		}
	});
	
	p.x += GetWidth(bSelectAll) + margin * 5;
	auto bClear = CreateButton(p, "[Clear]", [this, res2d](auto) {
		for (auto&& kv : cbNames) {
			kv.first->setSelected(false);
		}
	});

	p.x += GetWidth(bClear) + margin * 5;
	auto tPrefix = CreateLabel(p, "prefix: ");

	p.x += GetWidth(tPrefix);
	auto ePrefix = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, "", "");

	p.x += GetWidth(ePrefix);
	auto bSelectPrefix = CreateButton(p, "[SelectPrefix]", [this, res2d, ePrefix](auto) {
		std::string prefix = ePrefix->getText();
		for (auto&& kv : cbNames) {
			if (kv.second.size() >= prefix.size() && memcmp(kv.second.data(), prefix.data(), prefix.size()) == 0) {
				kv.first->setSelected(true);
			}
		}
	});


	// 最下方步骤按钮
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateButton(p, "[Next]", [this, res2d, action2d](auto) {
		// 根据选中的 frames 同步 action 的 frames
		// 列出选中的
		std::vector<std::string> names;
		for (auto&& kv : cbNames) {
			if (kv.first->isSelected()) {
				names.push_back(kv.second);
			}
		}
		// 删掉不存在的
		for (int i = (int)action2d->frames.size() - 1; i >= 0; --i) {
			auto&& f = xx::As<FishManage::Frame2d>(action2d->frames[i]);
			bool found = false;
			for (auto&& name : names) {
				if (f->spriteFrameName == name) {
					found = true;
					break;
				}
			}
			action2d->frames.erase(action2d->frames.begin() + i);
		}
		// 追加新的
		for(auto&& name : names) {
			bool found = false;
			for (int i = (int)action2d->frames.size() - 1; i >= 0; --i) {
				auto&& f = xx::As<FishManage::Frame2d>(action2d->frames[i]);
				if (f->spriteFrameName == name) {
					found = true;
					break;
				}
			}
			if (found) continue;
			auto f = xx::Make<FishManage::Frame2d>();
			action2d->frames.emplace_back(f);
			f->spriteFrameName = name;
			f->moveDistance = 1;
		}
		// 排序
		std::sort(action2d->frames.begin(), action2d->frames.end(), [](auto a, auto b)->bool {
			return xx::InnerNumberToFixed(xx::As<FishManage::Frame2d>(a)->spriteFrameName) < xx::InnerNumberToFixed(xx::As<FishManage::Frame2d>(b)->spriteFrameName);
		});

		// 重置滚动条位置
		configSpriteFrameScrolledPercentVertical = 0;
		ConfigSpriteFrame(res2d, action2d);
	});
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= GetWidth(bNext) + lineHeight * 2;
	auto bCancel = CreateButton(p, "[Cancel]", [this, res2d](auto) { EditRes2d(res2d); });
	bCancel->setAnchorPoint({ 1, 0.5 });



	// 逐个加载所有 plist, 找出所有 sprite frame name
	std::vector<std::string> names;
	auto&& fu = cocos2d::FileUtils::getInstance();
	for (auto&& plistFileName : res2d->plistFileNames) {
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistFileName);
		// 写法确保与上面函数内部一致
		std::string fullPath = fu->fullPathForFilename(plistFileName);
		auto&& dict = fu->getValueMapFromFile(fullPath);
		auto&& framesDict = dict["frames"].asValueMap();
		for (auto&& iter : framesDict) {
			auto&& frameDict = iter.second.asValueMap();
			names.push_back(iter.first);
		}
	}

	// 排序( 如果含有数字，以其中的数字部分大小来排 )
	std::sort(names.begin(), names.end(), [](std::string const& a, std::string const& b)->bool {
		return xx::InnerNumberToFixed(a) < xx::InnerNumberToFixed(b);
	});


	// 每条 item 长相：
	/*
	 +-----+
[  ] | pic | sprite frame name
	 +-----+
*/

// 算 sv 显示坐标 与 体积
	p.x = margin;
	p.y = H - lineHeight * 2;
	cocos2d::Size svSize(W - margin * 2, H - lineHeight * 3);

	// item 高度
	auto itemHeight = lineHeight * 2;

	// 内容总高度
	auto svContentHeight = margin + (itemHeight + margin) * names.size();
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// 根据 裁切size, 内容size 创建 sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight });

	// 准备容器
	cbNames.clear();

	// 向 sv 填充 items
	// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
	for (size_t i = 0; i < names.size(); ++i) {
		auto&& frameName = names[i];

		// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		p.x = pos.x;
		p.y = pos.y - itemHeight / 2;
		auto cb = CreateCheckBox(p, false, nullptr, sv);
		cbNames[cb] = frameName;
		for (auto&& frame : action2d->frames) {
			if (xx::As<FishManage::Frame2d>(frame)->spriteFrameName == frameName) {
				cb->setSelected(true);
			}
		}

		p.x += GetWidth(cb) + margin + itemHeight / 2;
		auto spr = CreateSpriteFrame(p, { itemHeight, itemHeight }, frameName, sv);

		p.x += itemHeight + margin;
		auto txt = CreateLabel(p, frameName, sv);
	}
}

void HelloWorld::ChoosePList(std::shared_ptr<FishManage::Res2d> const& res2d) {
	removeAllChildren();

	// 点击 create 2d sprite frame res2d 之后跳转到的选择 plist 文件页

	// 背景
	CreateBG(this);

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// 最上方说明文字
	CreateLabel(p, "please multi select every plist file include your sprite frames:");

	// 最下方步骤按钮
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateButton(p, "[Save & Exit]", [this, res2d](auto) {
		// 遍历 checkbox. 将对应的 plist file names 存入容器
		res2d->plistFileNames.clear();
		for (auto&& kv : cbNames) {
			if (kv.first->isSelected()) {
				res2d->plistFileNames.push_back(kv.second);
			}
		}
		EditRes2d(res2d);
	});
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= GetWidth(bNext) + lineHeight * 2;
	auto bCancel = CreateButton(p, "[Cancel]", [this, res2d](auto) {
		EditRes2d(res2d);
	});
	bCancel->setAnchorPoint({ 1, 0.5 });


	// 遍历所有 .plist
	auto&& sps = cocos2d::FileUtils::getInstance()->getSearchPaths();
	assert(sps.size() == 1);
	std::vector<std::filesystem::path> paths;
	for (auto&& entry : std::filesystem::directory_iterator(sps[0])) {
		if (entry.is_regular_file() && entry.path().extension().u8string() == ".plist") {
			paths.emplace_back(entry);
		}
	}

	// 每条 item 长相：
	/*
[  ] file name
	*/

	// 算 sv 显示坐标 与 体积
	p.x = margin;
	p.y = H - lineHeight * 1;
	cocos2d::Size svSize(W - margin * 2, H - lineHeight * 2);

	// item 高度
	auto itemHeight = lineHeight;

	// 内容总高度
	auto svContentHeight = margin + (itemHeight + margin) * paths.size();
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// 根据 裁切size, 内容size 创建 sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight });

	// 准备容器
	cbNames.clear();

	// 向 sv 填充 items
	// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
	for (size_t i = 0; i < paths.size(); ++i) {
		auto&& path = paths[i];
		auto&& fn = path.filename().u8string();

		// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		p.x = pos.x;
		p.y = pos.y - itemHeight / 2;
		auto cb = CreateCheckBox(p, false, nullptr, sv);
		cbNames[cb] = fn;
		if (std::find(res2d->plistFileNames.begin(), res2d->plistFileNames.end(), fn) != res2d->plistFileNames.end()) {
			cb->setSelected(true);
		}

		p.x += GetWidth(cb) + margin;
		CreateLabel(p, fn, sv);
	}

	// 令 sv 正确裁切 3d 内容
	sv->setGlobalZOrder(1);
}

void HelloWorld::EditRes2d(std::shared_ptr<FishManage::Res2d> const& res2d) {
	removeAllChildren();

	// 初始化 editBoxs 引用容器. 准备数据保存函数
	editBoxs.clear();
	auto&& SaveEditBoxDataToRes = [this, res2d] {
		res2d->name = editBoxs[0]->getText();
		xx::Convert(editBoxs[1]->getText(), res2d->shadowScale);
		xx::Convert(editBoxs[2]->getText(), res2d->shadowOffsetX);
		xx::Convert(editBoxs[3]->getText(), res2d->shadowOffsetY);
	};

	// 背景
	CreateBG(this);

	// res name: [________________]
	cocos2d::Vec2 p(margin, H - lineHeight / 2);
	{
		auto tName = CreateLabel(p, "res name: ");
		p.x += GetWidth(tName);
		auto eName = CreateEditBox(p, { lineHeight * 10, fontSize * 1.1f }, res2d->name, "");
		editBoxs.push_back(eName);
	}

	// shadowScale: [_________]     shadowOffsetX: [_________]    shadowOffsetY: [_________]
	{
		p.x = margin;
		p.y -= lineHeight;
		auto tShadowScale = CreateLabel(p, "shadowScale: ");

		p.x += GetWidth(tShadowScale);
		auto eShadowScale = CreateEditBox(p, { lineHeight * 3, fontSize * 1.1f }, xx::ToString(res2d->shadowScale), "");
		editBoxs.push_back(eShadowScale);

		p.x += GetWidth(eShadowScale) + lineHeight * 2;
		auto tShadowOffsetX = CreateLabel(p, "shadowOffsetX: ");

		p.x += GetWidth(tShadowOffsetX);
		auto eShadowOffsetX = CreateEditBox(p, { lineHeight * 3, fontSize * 1.1f }, xx::ToString(res2d->shadowOffsetX), "");
		editBoxs.push_back(eShadowOffsetX);

		p.x += GetWidth(eShadowOffsetX) + lineHeight * 2;
		auto tShadowOffsetY = CreateLabel(p, "shadowOffsetY: ");

		p.x += GetWidth(tShadowOffsetY);
		auto eShadowOffsetY = CreateEditBox(p, { lineHeight * 3, fontSize * 1.1f }, xx::ToString(res2d->shadowOffsetY), "");
		editBoxs.push_back(eShadowOffsetY);
	}

	// [New Action]       ->         [Choose PList Files]
	{
		p.x = margin;
		p.y -= lineHeight;
		CreateButton(p, "[Choose PList Files]", [this, res2d, SaveEditBoxDataToRes](auto) {
			SaveEditBoxDataToRes();
			ChoosePList(res2d);
			});

		p.x = W / 2 + margin;
		CreateButton(p, "[New Action]", [this, res2d, SaveEditBoxDataToRes](auto) {
			if (res2d->plistFileNames.empty()) {
				PopupMessage("please choose plist files first!");
				return;
			}
			SaveEditBoxDataToRes();
			auto a = xx::Make<FishManage::Action2d>();
			a->name = "unnamed_action";
			a->frameRate = 30;
			ChooseSpriteFrame(res2d, a);
			});
	}

	//      ->        [Save & Quit]    [Cancel]
	{
		p.x = W - margin;
		p.y = lineHeight / 2;
		auto bNext = CreateButton(p, "[Save & Quit]", [this, res2d, SaveEditBoxDataToRes](auto) {
			SaveEditBoxDataToRes();
			if (res2d->name.empty()) {
				PopupMessage("please input res name!");
				return;
			}
			if (res2d->actions.empty()) {
				PopupMessage("please create at least one action!");
				return;
			}
			res2d->lastUpdateTime = xx::NowEpoch10m();
			if (std::find(data.ress.begin(), data.ress.end(), res2d) == data.ress.end()) {
				data.ress.push_back(res2d);
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

	// 左边 SV：显示 plist file names
	{
		// 每条 item 长相：
		/*
ssssssssssssssxxxxxxx.plist
		*/

		// 算 sv 显示坐标 与 体积
		p.x = margin;
		p.y = H - lineHeight * 3;
		cocos2d::Size svSize(W / 2 - margin, H - lineHeight * 4);

		// item 高度
		auto itemHeight = lineHeight;

		// 内容总高度
		auto svContentHeight = margin + (itemHeight + margin) * res2d->plistFileNames.size();
		if (svContentHeight < svSize.height) {
			svContentHeight = svSize.height;
		}

		// 根据 裁切size, 内容size 创建 sv
		auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight });

		// 向 sv 填充 items
		// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
		for (size_t i = 0; i < res2d->plistFileNames.size(); ++i) {
			auto&& fn = res2d->plistFileNames[i];

			// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
			cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

			// 创建 label
			p.x = pos.x;
			p.y = pos.y - itemHeight / 2;
			CreateLabel(p, fn, sv);
		}
	}

	// 右边 SV：显示 actions
	{
		// 每条 item 长相：
		/*
+---------+ name: xxxxxxxxxx
|         | numFrames: xxxxxxx
| preview | frameRate: xxxxxxx
|         | total moveDistance: xxxxxxx
+---------+ [Edit]                                      [Delete]
		*/

		// 算 sv 显示坐标 与 体积
		p.x = W / 2 + margin;
		p.y = H - lineHeight * 3;
		cocos2d::Size svSize(W / 2 - margin * 2, H - lineHeight * 4);

		// item 高度
		auto itemHeight = lineHeight * 5;

		// 内容总高度
		auto svContentHeight = margin + (itemHeight + margin) * res2d->actions.size();
		if (svContentHeight < svSize.height) {
			svContentHeight = svSize.height;
		}

		// 根据 裁切size, 内容size 创建 sv
		auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight });

		// 向 sv 填充 items
		// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
		for (size_t i = 0; i < res2d->actions.size(); ++i) {
			auto&& action2d = xx::As<FishManage::Action2d>(res2d->actions[i]);

			// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
			cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

			// 创建帧动画
			p.x = pos.x + itemHeight / 2;
			p.y = pos.y - itemHeight / 2;
			CreateActionPlayer_SpriteFrame(p, { itemHeight ,itemHeight }, res2d->plistFileNames, action2d, sv);

			// name
			p.x = pos.x + itemHeight + margin;
			p.y = pos.y - lineHeight / 2;
			CreateLabelPair(p, "name: ", xx::ToString(action2d->name), sv);

			// frameRate
			p.y -= lineHeight;
			CreateLabelPair(p, "frameRate: ", xx::ToString(action2d->frameRate), sv);

			// numFrames
			p.y -= lineHeight;
			CreateLabelPair(p, "numFrames: ", xx::ToString(action2d->frames.size()), sv);

			// total moveDistance
			p.y -= lineHeight;
			double d = 0;
			for (auto&& frame : action2d->frames) { d += frame->moveDistance; }
			CreateLabelPair(p, "total moveDistance: ", xx::ToString(d), sv);

			// [Edit]                     [Delete]
			{
				p.x = pos.x + itemHeight + margin;
				p.y -= lineHeight;
				auto b1 = CreateButton(p, "[Edit]", [this, res2d, action2d, SaveEditBoxDataToRes](auto) {
					SaveEditBoxDataToRes();
					ConfigSpriteFrame(res2d, action2d);
				}, sv);

				p.x += GetWidth(b1) + lineHeight * 10;
				auto b2 = CreateButton(p, "[Delete]", [this, res2d, i, sv, SaveEditBoxDataToRes](auto) {
					SaveEditBoxDataToRes();
					editRes2dScrolledPercentVertical = sv->getScrolledPercentVertical();
					res2d->actions.erase(res2d->actions.begin() + i);
					EditRes2d(res2d);
				}, sv);
			}
		}

		// 还原滚动位置
		if (svContentHeight > svSize.height) {
			sv->jumpToPercentVertical(editRes2dScrolledPercentVertical);
		}
		else {
			editRes2dScrolledPercentVertical = 0;
		}
	}
}

void HelloWorld::ManageResources() {
	removeAllChildren();

	// 资源管理

	// 背景
	CreateBG(this);

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// [create 2d sprite frame res]   [create spine res]   [create 3d c3b res]   [create combine res]
	auto b1 = CreateButton(p, "[create 2d sprite frame res]", [this](auto) {
		auto&& res = xx::Make<FishManage::Res2d>();
		res->name = "unnamed_res";
		res->shadowScale = 1;
		res->shadowOffsetX = 3;
		res->shadowOffsetY = 3;
		EditRes2d(res);
	});

	p.x += GetWidth(b1) + lineHeight * 3;
	auto b2 = CreateButton(p, "[create spine res]", [this](auto) {
		/* EditResSpine(r); */ 
	});

	p.x += GetWidth(b2) + lineHeight * 3;
	auto b3 = CreateButton(p, "[create 3d c3b res]", [this](auto) {
		/* EditRes3d(r); */
	});

	p.x += GetWidth(b3) + lineHeight * 3;
	auto b4 = CreateButton(p, "[create combine res]", [this](auto) {
		/* EditResCombine(r); */
	});

	//        ->          [Back]
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bBack = CreateButton(p, "[Back]", [this](auto) {
		Welcome();
	});
	bBack->setAnchorPoint({ 1, 0.5 });


	// 每条 item 长相：
	/*
+---------+ name: resName
|         | type: 2d? spine? 3d? combine?
| preview | actions: 逗号分隔列出
|         | coin1:       coin2:
+---------+ [Edit]                     [Delete]
	*/

	// 算 sv 显示坐标 与 体积
	p.x = margin;
	p.y = H - lineHeight;
	cocos2d::Size svSize(W - margin * 2, H - lineHeight * 2);

	// item 高度
	auto itemHeight = lineHeight * 5;

	// 内容总高度
	auto svContentHeight = margin + (itemHeight + margin) * data.ress.size();
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// 根据 裁切size, 内容size 创建 sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight });

	// 向 sv 填充 items
	// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
	for (size_t i = 0; i < data.ress.size(); ++i) {
		auto&& res = data.ress[i];

		// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		// 绘制 动画预览( 第一个动作 )
		p.x = pos.x + itemHeight / 2;
		p.y = pos.y - itemHeight / 2;
		CreateResPreview(p, { itemHeight ,itemHeight }, res, sv);

		// 继续绘制预览图右侧的东西
		// name
		{
			p.x = pos.x + itemHeight + margin;
			p.y = pos.y - lineHeight / 2;
			CreateLabelPair(p, "name: ", xx::ToString(res->name), sv);
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
			CreateLabelPair(p, "type: ", typeName, sv);
		}

		// actions: .........
		{
			p.y -= lineHeight;
			auto tk = CreateLabel(p, "actions: ", sv);

			p.x += GetWidth(tk);
			for (auto&& action : res->actions) {
				auto tv = CreateLabel(p, xx::ToString(action->name, ((&action == &res->actions.back()) ? "" : ", ")), sv);
				tv->setColor(yellow);
				p.x += GetWidth(tv) + margin;
			}
		}

		// lastUpdateTime
		{
			p.x = pos.x + itemHeight + margin;
			p.y -= lineHeight;
			CreateLabelPair(p, "lastUpdateTime: ", xx::ToString(xx::Epoch10mToTimePoint(res->lastUpdateTime)), sv);
		}

		// [Edit Clone]                     [Delete]
		{
			p.x = pos.x + itemHeight + margin;
			p.y -= lineHeight;
			auto b1 = CreateButton(p, "[Edit Clone]", [this, res](auto) {
				auto&& cloneRes = oh.Clone(res);
				if (auto&& r = xx::As<FishManage::Res2d>(cloneRes)) {
					EditRes2d(r);
				}
				else if (auto&& r = xx::As<FishManage::ResSpine>(cloneRes)) {
					// EditResSpine(r);
				}
				else if (auto&& r = xx::As<FishManage::Res3d>(cloneRes)) {
					// EditRes3d(r);
				}
				else if (auto&& r = xx::As<FishManage::ResCombine>(cloneRes)) {
					// EditResCombine(r);
				}
				else {
					// 
				}
			}, sv);

			p.x += GetWidth(b1) + lineHeight * 10;
			auto b2 = CreateButton(p, "[Delete]", [this, i, sv](auto) {
				manageResourcesScrolledPercentVertical = sv->getScrolledPercentVertical();
				data.ress.erase(data.ress.begin() + i);
				SaveData();
				ManageResources();
			}, sv);
		}
	}

	// 随便画些 3d 模型 到 scroll view
	for (size_t i = 0; i < 10; ++i) {
		auto o = CreateOrc({ (float)cocos2d::random(0, (int)svSize.width), (float)cocos2d::random(0, (int)svContentHeight) }, cocos2d::random(0, 360), sv);
	}

	// 令 sv 正确裁切 3d 内容
	sv->setGlobalZOrder(1);

	// 还原滚动位置
	if (svContentHeight > svSize.height) {
		sv->jumpToPercentVertical(manageResourcesScrolledPercentVertical);
	}
	else {
		manageResourcesScrolledPercentVertical = 0;
	}
}

void HelloWorld::Welcome() {
	removeAllChildren();

	// 首页

	// 背景
	CreateBG(this);

	// [Browse Resources]      [Browse Fishs]
	cocos2d::Vec2 p(margin, H - lineHeight / 2);
	auto bBR = CreateButton(p, "[Manage Resources]", [this](auto) {
		ManageResources();
	});

	p.x += GetWidth(bBR) + lineHeight * 3;
	auto bBF = CreateButton(p, "[Manage Fishs]", [this](auto) {
		ManageFishs();
	});

	// todo: 未来预期功能：给鱼分组？罗列分组鱼引用到的所有资源文件？算体积？

	// 显示一些针对 data 的 summary 信息
	p.x = margin;
	p.y -= lineHeight;
	CreateLabelPair(p, "ress.size() = ", xx::ToString(data.ress.size()));

	p.y -= lineHeight;
	CreateLabelPair(p, "fishs.size() = ", xx::ToString(data.fishs.size()));

	// todo: 分类统计？
}

void HelloWorld::ManageFishs() {
	removeAllChildren();

	// 鱼管理

	// 背景
	CreateBG(this);

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// [create XXXX]   [create XXXX]   [create XXXX]   [create XXXX] ....
	auto b = CreateButton(p, "[create Normal]", [this](auto) {
		auto&& fish = xx::Make<FishManage::FishNormal>();
		// todo: more init
		EditFishNormal(fish);
		// todo: 
		});

	p.x += GetWidth(b) + lineHeight * 3;
	b = CreateButton(p, "[create Bomb]", [this](auto) {
		auto&& fish = xx::Make<FishManage::FishBomb>();
		// todo: more init
		EditFishBomb(fish);
		// todo: 
		});

	p.x += GetWidth(b) + lineHeight * 3;
	b = CreateButton(p, "[create Drill]", [this](auto) {
		auto&& fish = xx::Make<FishManage::FishDrill>();
		// todo: more init
		EditFishDrill(fish);
		// todo: 
		});

	p.x += GetWidth(b) + lineHeight * 3;
	b = CreateButton(p, "[create Fury]", [this](auto) {
		auto&& fish = xx::Make<FishManage::FishFury>();
		// todo: more init
		EditFishFury(fish);
		// todo: 
		});

	p.x += GetWidth(b) + lineHeight * 3;
	b = CreateButton(p, "[create Cyclone]", [this](auto) {
		auto&& fish = xx::Make<FishManage::FishCyclone>();
		// todo: more init
		EditFishCyclone(fish);
		// todo: 
		});

	p.x += GetWidth(b) + lineHeight * 3;
	b = CreateButton(p, "[create Eater]", [this](auto) {
		auto&& fish = xx::Make<FishManage::FishEater>();
		// todo: more init
		EditFishEater(fish);
		// todo: 
		});




	//        ->          [Back]
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bBack = CreateButton(p, "[Back]", [this](auto) {
		Welcome();
	});
	bBack->setAnchorPoint({ 1, 0.5 });

	// 每条 item 长相：
	/*
+---------+ name: fishName
|         | type: normal? bomb? drill? ......
| preview | coin1:       coin2:
|         | ..........
+---------+ [Edit]                     [Delete]
	*/

	// 算 sv 显示坐标 与 体积
	p.x = margin;
	p.y = H - lineHeight;
	cocos2d::Size svSize(W - margin * 2, H - lineHeight * 2);

	// item 高度
	auto itemHeight = lineHeight * 5;

	// 内容总高度
	auto svContentHeight = margin + (itemHeight + margin) * data.fishs.size();
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// 根据 裁切size, 内容size 创建 sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight });

	// 向 sv 填充 items
	// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
	for (size_t i = 0; i < data.fishs.size(); ++i) {
		auto&& fish = data.fishs[i];

		// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		// 帧动画预览第一个动作
		p.x = pos.x + itemHeight / 2;
		p.y = pos.y - itemHeight / 2;
		if (auto&& res = fish->res.lock()) {
			CreateResPreview(p, { itemHeight ,itemHeight }, res, sv);
		}

		// 继续绘制预览图右侧的东西
		// name
		{
			p.x = pos.x + itemHeight + margin;
			p.y = pos.y - lineHeight / 2;
			CreateLabelPair(p, "name: ", xx::ToString(fish->name), sv);
		}

		// type
		{
			p.y -= lineHeight;
			std::string typeName;
			if (xx::Is<FishManage::FishNormal>(fish)) {
				typeName = "Normal";
			}
			else if (xx::Is<FishManage::FishBomb>(fish)) {
				typeName = "Bomb";
			}
			else if (xx::Is<FishManage::FishDrill>(fish)) {
				typeName = "Drill";
			}
			else if (xx::Is<FishManage::FishFury>(fish)) {
				typeName = "Fury";
			}
			else if (xx::Is<FishManage::FishCyclone>(fish)) {
				typeName = "Cyclone";
			}
			else if (xx::Is<FishManage::FishEater>(fish)) {
				typeName = "Eater";
			}
			else {
				typeName = "unknown";
			}
			CreateLabelPair(p, "type: ", typeName, sv);
		}

		// coin1    coin2
		{
			p.x = pos.x + itemHeight + margin;
			p.y = pos.y - lineHeight / 2;
			auto kv = CreateLabelPair(p, "coin1: ", xx::ToString(fish->coin1), sv);

			p.x += GetWidth(kv) + itemHeight * 3;
			CreateLabelPair(p, "coin2: ", xx::ToString(fish->coin2), sv);
		}

		// lastUpdateTime
		{
			p.x = pos.x + itemHeight + margin;
			p.y -= lineHeight;
			CreateLabelPair(p, "lastUpdateTime: ", xx::ToString(xx::Epoch10mToTimePoint(fish->lastUpdateTime)), sv);
		}

		// [Edit Clone]                     [Delete]
		{
			p.x = pos.x + itemHeight + margin;
			p.y -= lineHeight;
			auto b1 = CreateButton(p, "[Edit Clone]", [this, fish](auto) {
				auto&& cloneFish = oh.Clone(fish);
				if (auto&& r = xx::As<FishManage::FishNormal>(cloneFish)) {
					EditFishNormal(r);
				}
				else if (auto&& r = xx::As<FishManage::FishBomb>(cloneFish)) {
					EditFishBomb(r);
				}
				else if (auto&& r = xx::As<FishManage::FishDrill>(cloneFish)) {
					EditFishDrill(r);
				}
				else if (auto&& r = xx::As<FishManage::FishFury>(cloneFish)) {
					EditFishFury(r);
				}
				else if (auto&& r = xx::As<FishManage::FishCyclone>(cloneFish)) {
					EditFishCyclone(r);
				}
				else if (auto&& r = xx::As<FishManage::FishEater>(cloneFish)) {
					EditFishEater(r);
				}
				else {
					// 
				}
				}, sv);

			p.x += GetWidth(b1) + lineHeight * 10;
			auto b2 = CreateButton(p, "[Delete]", [this, i, sv](auto) {
				manageFishsScrolledPercentVertical = sv->getScrolledPercentVertical();
				data.ress.erase(data.ress.begin() + i);
				SaveData();
				ManageResources();
				}, sv);
		}
	}

	// 令 sv 正确裁切 3d 内容
	sv->setGlobalZOrder(1);

	// 还原滚动位置
	if (svContentHeight > svSize.height) {
		sv->jumpToPercentVertical(manageFishsScrolledPercentVertical);
	}
	else {
		manageFishsScrolledPercentVertical = 0;
	}
}

// todo

void HelloWorld::EditFishNormal(std::shared_ptr<FishManage::FishNormal> const& fish) {

}

void HelloWorld::EditFishBomb(std::shared_ptr<FishManage::FishBomb> const& fish) {

}

void HelloWorld::EditFishDrill(std::shared_ptr<FishManage::FishDrill> const& fish) {

}

void HelloWorld::EditFishFury(std::shared_ptr<FishManage::FishFury> const& fish) {

}

void HelloWorld::EditFishCyclone(std::shared_ptr<FishManage::FishCyclone> const& fish) {

}

void HelloWorld::EditFishEater(std::shared_ptr<FishManage::FishEater> const& fish) {

}






bool HelloWorld::init() {
	if (!Scene::init()) return false;

	FishManage::PkgGenTypes::RegisterTo(oh);

	LoadData();

	W = AppDelegate::designWidth;
	H = AppDelegate::designHeight;
	W_2 = W / 2;
	H_2 = H / 2;

	auto kbListener = cocos2d::EventListenerKeyboard::create();
	kbListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
		if (!currCircle) return;
		currCircle->scheduleUpdate();
		switch (keyCode) {
		case cocos2d::EventKeyboard::KeyCode::KEY_PLUS:
		case cocos2d::EventKeyboard::KeyCode::KEY_KP_PLUS:
			currCircle->rChange = 30;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_MINUS:
		case cocos2d::EventKeyboard::KeyCode::KEY_KP_MINUS:
			currCircle->rChange = -30;
			break;
		}
	};
	kbListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
		if (!currCircle) return;
		currCircle->rChange = 0;
		currCircle->unscheduleUpdate();
	};
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kbListener, this);


	Welcome();

	return true;
}


void HelloWorld::LoadData() {
	if (std::filesystem::exists(dataFileName)) {
		xx::Data buf;
		if (int r = xx::ReadAllBytes(dataFileName, buf)) {
			throw std::logic_error(xx::ToString("xx::ReadAllBytes(dataFileName = '", dataFileName, "', buf) == ", r));
		}

		if (int r = oh.ReadFrom(buf, data)) {
			throw std::logic_error(xx::ToString("oh.ReadFrom(buf, data) == ", r));
		}
	}
}

void HelloWorld::SaveData() {
	xx::Data buf;
	oh.WriteTo(buf, data);
	xx::WriteAllBytes(dataFileName, buf);
}

void HelloWorld::editBoxReturn(cocos2d::ui::EditBox* editBox) {
	//std::string s = editBox->getText();
	//printf(s.c_str());
}






//// 第二排显示 coin1, 2
//p.x = margin;
//p.y -= lineHeight;
//auto tCoin1 = CreateLabel(p, "coin1: ");

//p.x += GetWidth(tCoin1);
//auto etCoin1 = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, xx::ToString(res2d->coin1), "base ratio");
//etCoin1->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
//editBoxs.push_back(etCoin1);		// 放在下标 1

//p.x += GetWidth(etCoin1) + margin;
//auto tCoin2 = CreateLabel(p, "coin2: ");

//p.x += GetWidth(tCoin2);
//auto etCoin2 = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, xx::ToString(res2d->coin2), "extend ratio or negative enum");
//etCoin2->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
//editBoxs.push_back(etCoin2);		// 放在下标 2



		//// coin1:       coin2:
		//{
		//	p.x = pos.x + itemHeight + margin;
		//	p.y -= lineHeight;
		//	auto tk1 = CreateLabel(p, "coin1: ", sv);

		//	p.x += GetWidth(tk1);
		//	auto tv1 = CreateLabel(p, xx::ToString(res2d.coin1), sv);
		//	tv1->setColor(yellow);

		//	p.x += GetWidth(tv1) + margin;
		//	auto tk2 = CreateLabel(p, "coin2: ", sv);

		//	p.x += GetWidth(tk2);
		//	auto tv2 = CreateLabel(p, xx::ToString(res2d.coin2), sv);
		//	tv2->setColor(yellow);
		//}


		//res2d->coin1 = std::atoi(editBoxs[1]->getText());
		//res2d->coin2 = std::atoi(editBoxs[2]->getText());
