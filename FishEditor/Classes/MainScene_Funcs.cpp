#include "MainScene.h"

void MainScene::PopupMessage(std::string const& txt, cocos2d::Color3B const& color) {
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
	t->setGlobalZOrder(2);
}

cocos2d::Label* MainScene::CreateLabel(cocos2d::Vec2 const& pos, std::string const& txt, cocos2d::Node* const& container) {
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
std::pair<cocos2d::Label*, cocos2d::Label*> MainScene::CreateLabelPair(cocos2d::Vec2 const& pos, std::string const& key, std::string const& value, cocos2d::Node* const& container) {
	std::pair<cocos2d::Label*, cocos2d::Label*> rtv;
	rtv.first = CreateLabel(pos, key, container);
	rtv.second = CreateLabel({ pos.x + GetWidth(rtv.first), pos.y }, value, container);
	rtv.second->setColor(yellow);
	return rtv;
}

cocos2d::ui::Button* MainScene::CreateButton(cocos2d::Vec2 const& pos, std::string const& txt, cocos2d::ccMenuCallback&& callback, cocos2d::Node* const& container) {
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

cocos2d::ui::EditBox* MainScene::CreateEditBox(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& text, std::string const& holderText, cocos2d::Node* const& container) {
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

cocos2d::Sprite3D* MainScene::CreateOrc(cocos2d::Vec2 const& pos, float const& r, cocos2d::Node* const& container) {
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

//ActionPlayer_SpriteFrame* MainScene::CreateActionPlayer_SpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, FishManage::FrameAction const& action, cocos2d::Node* const& container) {
//	auto a = ActionPlayer_SpriteFrame::create();
//	a->setAnchorPoint({ 0.5, 0.5 });
//	a->setPosition(pos);
//	a->SetActionData(action);
//	a->Play();
//	if (siz.width != 0 && siz.height != 0) {
//		auto&& cs = a->getContentSize();
//		if (cs.width > cs.height) {
//			a->setScale(siz.width / cs.width);
//		}
//		else {
//			a->setScale(siz.height / cs.height);
//		}
//	}
//	if (container) {
//		container->addChild(a);
//	}
//	else {
//		this->addChild(a);
//	}
//	return a;
//}



cocos2d::ui::ScrollView* MainScene::CreateSV(cocos2d::Vec2 const& pos, cocos2d::Size const& cutSize, cocos2d::Size const& itemsSize, cocos2d::Node* const& container) {
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

cocos2d::LayerColor* MainScene::CreateBG(cocos2d::Node* const& container) {
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

cocos2d::Sprite* MainScene::CreateSprite(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& fileName, cocos2d::Node* const& container) {
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

cocos2d::Sprite* MainScene::CreateSpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& spriteFrameName, cocos2d::Node* const& container) {
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

cocos2d::ui::CheckBox* MainScene::CreateCheckBox(cocos2d::Vec2 const& pos, bool const& value, cocos2d::ui::CheckBox::ccCheckBoxCallback&& callback, cocos2d::Node* const& container) {
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


float MainScene::GetWidth(cocos2d::Node* const& tar) {
	return tar->getContentSize().width * tar->getScaleX();
}

float MainScene::GetWidth(std::pair<cocos2d::Label*, cocos2d::Label*> const& tar) {
	return tar.first->getContentSize().width + tar.second->getContentSize().width;
}


//cocos2d::Node* MainScene::CreateResPreview(cocos2d::Vec2 const& pos, cocos2d::Size siz, std::shared_ptr<FishManage::Res> res, cocos2d::Node* const& container) {
	//if (auto&& r = xx::As<FishManage::Res2d>(res)) {
	//	return CreateActionPlayer_SpriteFrame(pos, siz, r->plistFileNames, xx::As<FishManage::Action2d>(r->actions[0]), container);
	//	// todo: 影子相关
	//}
	//else if (auto&& r = xx::As<FishManage::ResSpine>(res)) {
	//	// todo
	//}
	//else if (auto&& r = xx::As<FishManage::Res3d>(res)) {
	//	// todo
	//}
	//else if (auto&& r = xx::As<FishManage::ResCombine>(res)) {
	//	if (r->items.empty()) return nullptr;

	//	// 查找边缘
	//	float x1 = 99999, y1 = 99999;
	//	float x2 = -99999, y2 = -99999;
	//	for (auto&& o : r->items) {
	//		auto&& res = o.res.lock();
	//		auto&& a = res->actions[0];
	//		x1 = MIN(x1, o.offsetX - a->width  * o.baseScale / 2);
	//		x2 = MAX(x2, o.offsetX + a->width  * o.baseScale / 2);
	//		y1 = MIN(y1, o.offsetY - a->height * o.baseScale / 2);
	//		y2 = MAX(y2, o.offsetY + a->height * o.baseScale / 2);
	//	}

	//	// 以第一条鱼中心点为中心点，得到对称宽度
	//	auto&& fo = r->items[0];
	//	cocos2d::Size cs(MAX(fo.offsetX - x1, x2 - fo.offsetX) * 2, MAX(fo.offsetY - y1, y2 - fo.offsetY) * 2);

	//	// 计算缩放
	//	float scale = 0;
	//	if (siz.width != 0 && siz.height != 0) {
	//		if (cs.width > cs.height) {
	//			scale = siz.width / cs.width;
	//		}
	//		else {
	//			scale = siz.height / cs.height;
	//		}
	//	}

	//	// 以第一条鱼中心点为中心点，绘制所有鱼
	//	for (auto&& o : r->items) {
	//		auto&& res = o.res.lock();
	//		auto&& a = res->actions[0];
	//		auto n = CreateResPreview({ (o.offsetX - fo.offsetX) * scale + pos.x, (o.offsetY - fo.offsetY) * scale + pos.y }, { 0,0 }, res, container);
	//		n->setScale(o.baseScale * scale);
	//		n->setRotation(o.baseAngle);
	//	}
	//}
	//else {
	//}
//	return nullptr;
//}
