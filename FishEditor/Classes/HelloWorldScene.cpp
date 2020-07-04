#include "HelloWorldScene.h"
#include "AppDelegate.h"
#include "xx_file.h"
#include "xx_math.h"

#pragma region create funcs

cocos2d::Label* HelloWorld::CreateLabel(cocos2d::Vec2 const& pos, std::string const& txt, int const& fontSize, cocos2d::Node* const& container) {
	auto l = cocos2d::Label::createWithSystemFont(txt, "", fontSize);
	if (!l) return l;
	l->setAnchorPoint({ 0, 1 });
	l->setPosition(pos);
	if (container) {
		container->addChild(l);
	}
	return l;
}

cocos2d::ui::Button* HelloWorld::CreateTextButton(cocos2d::Vec2 const& pos, std::string const& txt, int const& fontSize, cocos2d::ccMenuCallback&& callback, cocos2d::Node* const& container) {
	auto b = cocos2d::ui::Button::create();
	if (!b) return b;
	b->setAnchorPoint({ 0, 1 });
	b->setPosition(pos);
	b->setTitleColor({ 122,192,255 });
	b->setTitleText(txt);
	b->setTitleFontSize(fontSize);
	b->setZoomScale(0.3f);
	b->setPressedActionEnabled(true);
	b->addClickEventListener(std::move(callback));
	if (container) {
		container->addChild(b);
	}
	return b;
}

cocos2d::ui::EditBox* HelloWorld::CreateEditBox(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& text, std::string const& holderText, int const& fontSize, cocos2d::Node* const& container) {
	auto et = cocos2d::ui::EditBox::create(siz, "green_edit.png");
	et->setDelegate(this);
	et->setContentSize(siz);
	et->setAnchorPoint({ 0, 1 });
	et->setPosition(pos);
	et->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	et->setFontSize(fontSize);
	et->setText(text.c_str());
	et->setPlaceHolder(holderText.c_str());
	if (container) {
		container->addChild(et);
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
	return s;
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
	return s;
}

cocos2d::Sprite* HelloWorld::CreateSpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& spriteFrameName, cocos2d::Node* const& container) {
	auto s = cocos2d::Sprite::create();
	s->setSpriteFrame(spriteFrameName);
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
	return cb;
}


template<typename T>
T* HelloWorld::HorizontalLeft(cocos2d::Vec2& offset, float& maxHeight, T* o) {
	auto&& scaleX = o->getScaleX();
	auto&& scaleY = o->getScaleY();
	auto cs = o->getContentSize();
	cs.width *= scaleX;
	cs.height *= scaleY;
	o->setPosition(offset);
	o->setAnchorPoint({ 0, 1 });
	offset.x += cs.width;
	if (cs.height > maxHeight) {
		maxHeight = cs.height;
	}
	return o;
}

template<typename T>
T* HelloWorld::HorizontalRight(cocos2d::Vec2& offset, float& maxHeight, T* o) {
	auto&& scaleX = o->getScaleX();
	auto&& scaleY = o->getScaleY();
	auto cs = o->getContentSize();
	cs.width *= scaleX;
	cs.height *= scaleY;
	o->setPosition(offset);
	o->setAnchorPoint({ 1, 0 });
	offset.x -= cs.width;
	if (cs.height > maxHeight) {
		maxHeight = cs.height;
	}
	return o;
}

template<typename T>
T* HelloWorld::VerticalTop(cocos2d::Vec2& offset, T* o) {
	auto&& scaleX = o->getScaleX();
	auto&& scaleY = o->getScaleY();
	auto cs = o->getContentSize();
	cs.width *= scaleX;
	cs.height *= scaleY;
	o->setPosition(offset);
	o->setAnchorPoint({ 0, 1 });
	offset.y -= cs.height;
	return o;
}




#pragma endregion



void HelloWorld::DrawFishMenu_SpriteFrame() {
	this->removeAllChildren();
	editBoxs.clear();
	editBoxMap.clear();

	// 背景
	CreateBG(this);

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(defaultMargin, H - defaultMargin);

	// 最上方 label + editbox 要求输入 鱼名
	float mh = 0;
	HorizontalLeft(p, mh, CreateLabel({ 0,0 }, "fish name: ", defaultFontSize, this));
	auto et = CreateEditBox({ 0, 0 }, { 300, defaultFontSize + 6 }, "", "", defaultFontSize, this);
	HorizontalLeft(p, mh, et);
	editBoxs.push_back(et);		// 放在下标 0


	// todo: 别的鱼的基础配置显示在此, 诸如倍率, 啥啥. 兼容 edit mode


	// 第二排显示 [new action] 按钮
	p.x = defaultMargin;
	p.y -= mh;
	mh = 0;
	HorizontalLeft(p, mh, CreateTextButton({ 0,0 }, "[New Action]", defaultFontSize, [this](cocos2d::Ref* ref) { this->DrawPListChoose(); }, this));


	// 算 sv 显示坐标 与 体积
	p.x = defaultMargin;
	p.y -= mh + defaultMargin;
	auto svPos = p;
	cocos2d::Size svSize(W - defaultMargin * 2, p.y);

	// 最下方 提交并退出 和 取消 按钮
	mh = 0;
	p.x = W - defaultMargin;
	p.y = defaultMargin;
	HorizontalRight(p, mh, CreateTextButton({ 0, 0 }, "[Save & Quit]", defaultFontSize, [this](cocos2d::Ref* ref) { this->SaveFishMenu_SpriteFrame(); }, this));
	p.x -= defaultMargin * 2;
	HorizontalRight(p, mh, CreateTextButton({ 0,0 }, "[Cancel]", defaultFontSize, [this](cocos2d::Ref* ref) { this->DrawWelcome(); }, this));

	// 修正 sv 体积
	svSize.height -= mh + defaultMargin;

	// 每条 item 长相：
	/*
+---------+ action name: xxxxxxxxxx
|         | total num of physics frames:
| preview | total num of logic frames:
|         | total distance: xxxxxxx
+---------+ [delete action]
*/
// item 高度
	auto itemHeight = 30.0f * 5;

	// 内容总高度
	auto svContentHeight = (itemHeight + defaultMargin) * names.size() - defaultMargin;
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// 根据 裁切size, 内容size 创建 sv
	auto&& sv = CreateSV(svPos, svSize, { svSize.width, svContentHeight }, this);

	//// 向 sv 填充 items
	//for (int i = 0; i < names.size(); ++i) {
	//	auto&& frameName = names[i];

	//	// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
	//	cocos2d::Vec2 pos(0, svContentHeight - (itemHeight + defaultMargin) * i);

	//	// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
	//	auto spr = CreateSpriteFrame({ pos.x + defaultMargin + 45,  pos.y - 45 }, { 90, 90 }, frameName, sv);

	//	auto txt0 = CreateLabel({ pos.x + defaultMargin + 90 + defaultMargin,  pos.y - 15 }, std::string(" sprite frame name: "), defaultFontSize, sv);
	//	txt0->setAnchorPoint({ 0, 0.5 });
	//	auto txt00 = CreateLabel({ pos.x + defaultMargin + 90 + defaultMargin + txt0->getContentSize().width, pos.y - 15 }, frameName, defaultFontSize, sv);
	//	txt00->setAnchorPoint({ 0, 0.5 });
	//	txt00->setColor({ 255, 127, 39 });

	//	auto txt1 = CreateLabel({ pos.x + defaultMargin + 90 + defaultMargin,  pos.y - 45 }, "distance( string ): ", defaultFontSize, sv);
	//	txt1->setAnchorPoint({ 0, 0.5 });
	//	auto e1 = CreateEditBox({ pos.x + defaultMargin + 90 + defaultMargin + txt1->getContentSize().width,  pos.y - 45 }, { 100, defaultFontSize + 6 }, "1.2", "", defaultFontSize, sv);
	//	e1->setInputMode(cocos2d::ui::EditBox::InputMode::DECIMAL);
	//	e1->setAnchorPoint({ 0, 0.5 });
	//	editBoxMap[frameName + "*d"] = e1;

	//	auto txt2 = CreateLabel({ pos.x + defaultMargin + 90 + defaultMargin,  pos.y - 75 }, "frame count( int ): ", defaultFontSize, sv);
	//	txt2->setAnchorPoint({ 0, 0.5 });
	//	auto e2 = CreateEditBox({ pos.x + defaultMargin + 90 + defaultMargin + txt2->getContentSize().width,  pos.y - 75 }, { 100, defaultFontSize + 6 }, "1", "", defaultFontSize, sv);
	//	e2->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
	//	e2->setAnchorPoint({ 0, 0.5 });
	//	editBoxMap[frameName + "*c"] = e2;
	//}
}
void HelloWorld::SaveFishMenu_SpriteFrame() {

}


void HelloWorld::DrawSpriteFrameConfig() {
	// 先不急着清除显示. 遍历 sv 的子，得到勾选清单。如果一个都没有勾选，则直接 return（看上去点了按钮没反应） todo: 后期增加自动消失的提示文字
	if (!cbNames.size()) return;
	names.clear();
	for (auto&& kv : cbNames) {
		if (kv.first->isSelected()) {
			names.push_back(kv.second);
		}
	}
	if (names.empty()) return;

	// 开始遍历 names (sprite frame names) 并加载. 此时可清除之前的内容
	this->removeAllChildren();
	editBoxs.clear();
	editBoxMap.clear();

	// 背景
	CreateBG(this);

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(defaultMargin, H - defaultMargin);

	// 最上方 label + editbox 要求输入 动作名
	float mh = 0;
	HorizontalLeft(p, mh, CreateLabel({ 0,0 }, "action name: ", defaultFontSize, this));
	auto et = CreateEditBox({ 0, 0 }, { 300, defaultFontSize + 6 }, "", "", defaultFontSize, this);
	HorizontalLeft(p, mh, et);
	editBoxs.push_back(et);		// 放在下标 0


	// 算 sv 显示坐标 与 体积
	p.x = defaultMargin;
	p.y -= mh + defaultMargin;
	auto svPos = p;
	cocos2d::Size svSize(W - defaultMargin * 2, p.y);

	// 最下方步骤按钮
	mh = 0;
	p.x = W - defaultMargin;
	p.y = defaultMargin;
	HorizontalRight(p, mh, CreateTextButton({ 0, 0 }, "[Next]", defaultFontSize, [this](cocos2d::Ref* ref) { this->SaveSpriteFrameConfig(); }, this));
	p.x -= defaultMargin * 2;
	HorizontalRight(p, mh, CreateTextButton({ 0,0 }, "[Cancel]", defaultFontSize, [this](cocos2d::Ref* ref) { this->DrawPListChoose(); }, this));

	// 修正 sv 体积
	svSize.height -= mh + defaultMargin;

	// 排序( 如果含有数字，以其中的数字部分大小来排 )
	std::sort(names.begin(), names.end(), [](std::string const& a, std::string const& b)->bool {
		return xx::InnerNumberToFixed(a) < xx::InnerNumberToFixed(b);
		});


	// 每条 item 长相：
	/*
+-----+ sprite frame name:
| pic | distance:
+-----+ frame count:
*/
// item 高度
	auto itemHeight = 90.0f;

	// 内容总高度
	auto svContentHeight = (itemHeight + defaultMargin) * names.size() - defaultMargin;
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// 根据 裁切size, 内容size 创建 sv
	auto&& sv = CreateSV(svPos, svSize, { svSize.width, svContentHeight }, this);

	// 向 sv 填充 items
	for (int i = 0; i < names.size(); ++i) {
		auto&& frameName = names[i];

		// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
		cocos2d::Vec2 pos(0, svContentHeight - (itemHeight + defaultMargin) * i);

		// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
		auto spr = CreateSpriteFrame({ pos.x + defaultMargin + 45,  pos.y - 45 }, { 90, 90 }, frameName, sv);

		auto txt0 = CreateLabel({ pos.x + defaultMargin + 90 + defaultMargin,  pos.y - 15 }, std::string(" sprite frame name: "), defaultFontSize, sv);
		txt0->setAnchorPoint({ 0, 0.5 });
		auto txt00 = CreateLabel({ pos.x + defaultMargin + 90 + defaultMargin + txt0->getContentSize().width, pos.y - 15 }, frameName, defaultFontSize, sv);
		txt00->setAnchorPoint({ 0, 0.5 });
		txt00->setColor({ 255, 127, 39 });

		auto txt1 = CreateLabel({ pos.x + defaultMargin + 90 + defaultMargin,  pos.y - 45 }, "distance( string ): ", defaultFontSize, sv);
		txt1->setAnchorPoint({ 0, 0.5 });
		auto e1 = CreateEditBox({ pos.x + defaultMargin + 90 + defaultMargin + txt1->getContentSize().width,  pos.y - 45 }, { 100, defaultFontSize + 6 }, "1.2", "", defaultFontSize, sv);
		e1->setInputMode(cocos2d::ui::EditBox::InputMode::DECIMAL);
		e1->setAnchorPoint({ 0, 0.5 });
		editBoxMap[frameName + "*d"] = e1;

		auto txt2 = CreateLabel({ pos.x + defaultMargin + 90 + defaultMargin,  pos.y - 75 }, "frame count( int ): ", defaultFontSize, sv);
		txt2->setAnchorPoint({ 0, 0.5 });
		auto e2 = CreateEditBox({ pos.x + defaultMargin + 90 + defaultMargin + txt2->getContentSize().width,  pos.y - 75 }, { 100, defaultFontSize + 6 }, "1", "", defaultFontSize, sv);
		e2->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
		e2->setAnchorPoint({ 0, 0.5 });
		editBoxMap[frameName + "*c"] = e2;
	}
}
void HelloWorld::SaveSpriteFrameConfig() {
	// todo: 扫 
	// editBoxs
		// editBoxMap
	// 存盘
}



void HelloWorld::DrawSpriteFrameChoose() {
	// 先不急着清除显示. 遍历 sv 的子，得到勾选清单。如果一个都没有勾选，则直接 return（看上去点了按钮没反应） todo: 后期增加自动消失的提示文字
	if (!cbNames.size()) return;
	names.clear();
	for (auto&& kv : cbNames) {
		if (kv.first->isSelected()) {
			names.push_back(kv.second);
		}
	}
	if (names.empty()) return;

	// 开始遍历 names (plist) 并加载. 此时可清除之前的内容
	this->removeAllChildren();

	// 背景
	CreateBG(this);
	float mh = 0;

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(defaultMargin, H - defaultMargin);

	// 最上方说明文字
	mh = 0;
	HorizontalLeft(p, mh, CreateLabel({ 0,0 }, "please multi select every sprite frame:", defaultFontSize, this));

	// 算 sv 显示坐标 与 体积
	p.x = defaultMargin;
	p.y -= mh + defaultMargin;
	auto svPos = p;
	cocos2d::Size svSize(W - defaultMargin * 2, p.y);

	// 最下方步骤按钮
	mh = 0;
	p.x = W - defaultMargin;
	p.y = defaultMargin;
	HorizontalRight(p, mh, CreateTextButton({ 0, 0 }, "[Next]", defaultFontSize, [this](cocos2d::Ref* ref) { this->DrawSpriteFrameConfig(); }, this));
	p.x -= defaultMargin * 2;
	HorizontalRight(p, mh, CreateTextButton({ 0,0 }, "[Cancel]", defaultFontSize, [this](cocos2d::Ref* ref) { this->DrawPListChoose(); }, this));

	// 修正 sv 体积
	svSize.height -= mh + defaultMargin;

	// 逐个加载所有 plist, 找出所有 sprite frame name
	frameNames.clear();
	auto&& fu = cocos2d::FileUtils::getInstance();
	for (auto&& name : names) {
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name);
		// 写法确保与上面函数内部一致
		std::string fullPath = fu->fullPathForFilename(name);
		auto&& dict = fu->getValueMapFromFile(fullPath);
		auto&& framesDict = dict["frames"].asValueMap();
		for (auto&& iter : framesDict) {
			auto&& frameDict = iter.second.asValueMap();
			frameNames.push_back(iter.first);
		}
	}

	// 排序( 如果含有数字，以其中的数字部分大小来排 )
	std::sort(frameNames.begin(), frameNames.end(), [](std::string const& a, std::string const& b)->bool {
		return xx::InnerNumberToFixed(a) < xx::InnerNumberToFixed(b);
		});


	// 每条 item 长相：
	/*
	 +-----+
[  ] | pic | sprite frame name
	 +-----+
*/
// item 高度
	auto itemHeight = 50.0f;

	// 内容总高度
	auto svContentHeight = (itemHeight + defaultMargin) * frameNames.size() - defaultMargin;
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// 根据 裁切size, 内容size 创建 sv
	auto&& sv = CreateSV(svPos, svSize, { svSize.width, svContentHeight }, this);

	// 准备容器
	cbNames.clear();

	// 向 sv 填充 items
	for (int i = 0; i < frameNames.size(); ++i) {
		auto&& frameName = frameNames[i];

		// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
		cocos2d::Vec2 pos(0, svContentHeight - (itemHeight + defaultMargin) * i);

		// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
		auto cb = CreateCheckBox({ pos.x + defaultMargin, pos.y - 25 }, false, nullptr, sv);
		auto cbWidth = cb->getContentSize().width;
		cbNames[cb] = frameName;
		auto spr = CreateSpriteFrame({ pos.x + defaultMargin + cbWidth + defaultMargin + 25,  pos.y - 25 }, { 50, 50 }, frameName, sv);
		auto txt = CreateLabel({ pos.x + defaultMargin + cbWidth + defaultMargin + 50 + defaultMargin,  pos.y - 25 }, frameName, defaultFontSize, sv);
		txt->setAnchorPoint({ 0, 0.5 });
	}
}



void HelloWorld::DrawPListChoose() {
	// todo: 保存 DrawFishMenu_SpriteFrame 的数据

	this->removeAllChildren();

	// 点击 create 2d sprite frame fish 之后跳转到的选择 plist 文件页

	// 背景
	CreateBG(this);
	float mh = 0;

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(defaultMargin, H - defaultMargin);

	// 最上方说明文字
	mh = 0;
	HorizontalLeft(p, mh, CreateLabel({ 0,0 }, "please multi select every plist file include your sprite frames:", defaultFontSize, this));

	// 算 sv 显示坐标 与 体积
	p.x = defaultMargin;
	p.y -= mh + defaultMargin;
	auto svPos = p;
	cocos2d::Size svSize(W - defaultMargin * 2, p.y);

	// 最下方步骤按钮
	mh = 0;
	p.x = W - defaultMargin;
	p.y = defaultMargin;
	HorizontalRight(p, mh, CreateTextButton({ 0, 0 }, "[Next]", defaultFontSize, [this](cocos2d::Ref* ref) { this->DrawSpriteFrameChoose(); }, this));
	p.x -= defaultMargin * 2;
	HorizontalRight(p, mh, CreateTextButton({ 0,0 }, "[Cancel]", defaultFontSize, [this](cocos2d::Ref* ref) { this->DrawFishMenu_SpriteFrame(); }, this));

	// 修正 sv 体积
	svSize.height -= mh + defaultMargin;


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
// item 高度
	auto itemHeight = 30.0f;

	// 内容总高度
	auto svContentHeight = (itemHeight + defaultMargin) * paths.size() - defaultMargin;
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// 根据 裁切size, 内容size 创建 sv
	auto&& sv = CreateSV(svPos, svSize, { svSize.width, svContentHeight }, this);

	// 准备容器
	cbNames.clear();

	// 向 sv 填充 items
	for (int i = 0; i < paths.size(); ++i) {
		auto&& path = paths[i];
		auto&& fn = path.filename().u8string();

		// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
		cocos2d::Vec2 pos(0, svContentHeight - (itemHeight + defaultMargin) * i);

		// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
		auto cb = CreateCheckBox({ pos.x + defaultMargin, pos.y - 50 }, false, nullptr, sv);
		auto cbWidth = cb->getContentSize().width;
		cbNames[cb] = fn;
		auto txt = CreateLabel({ pos.x + defaultMargin + cbWidth + defaultMargin,  pos.y - 50 }, fn, defaultFontSize, sv);
		txt->setAnchorPoint({ 0, 0.5 });
	}

	// 令 sv 正确裁切 3d 内容
	sv->setGlobalZOrder(1);

}



void HelloWorld::DrawWelcome() {
	this->removeAllChildren();

	// 欢迎页

	// 背景
	CreateBG(this);
	float defaultMargin = 10, mh = 0;

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(defaultMargin, H - defaultMargin);

	// 上方依次显示 4 个按钮
	HorizontalLeft(p, mh, CreateTextButton({ 0,0 }, "[create 2d sprite frame fish]", defaultFontSize, [this](cocos2d::Ref* ref) { this->DrawFishMenu_SpriteFrame();	}, this));
	p.x += defaultMargin * 3;
	HorizontalLeft(p, mh, CreateTextButton({ 0,0 }, "[create spine fish]", defaultFontSize, [this](cocos2d::Ref* ref) { /* this->DrawSpineChoose(); */ }, this));
	p.x += defaultMargin * 3;
	HorizontalLeft(p, mh, CreateTextButton({ 0,0 }, "[create 3d c3b fish]", defaultFontSize, [this](cocos2d::Ref* ref) { /* this->DrawC3bChoose(); */ }, this));
	p.x += defaultMargin * 3;
	HorizontalLeft(p, mh, CreateTextButton({ 0,0 }, "[create combine fish]", defaultFontSize, [this](cocos2d::Ref* ref) { /* this->DrawFishsChoose(); */ }, this));

	// 按钮下方是 scroll view
	p.x = defaultMargin;
	p.y -= mh + defaultMargin;

	// 裁切范围
	cocos2d::Size svSize(W - defaultMargin * 2, p.y - defaultMargin);


	// 遍历所有 pics
	auto&& sps = cocos2d::FileUtils::getInstance()->getSearchPaths();
	assert(sps.size() == 1);
	std::vector<std::filesystem::path> paths;
	for (auto&& entry : std::filesystem::directory_iterator(sps[0])) {
		if (entry.is_regular_file() && entry.path().extension().u8string() == ".png") {
			paths.emplace_back(entry);
		}
	}

	// 每条 item 长相：
	/*
	 +---------+
	 |         |
[  ] |   pic   | file name
	 |         |
	 +---------+
*/
// item 高度
	auto itemHeight = 100.0f;

	// 内容总高度
	auto svContentHeight = (itemHeight + defaultMargin) * paths.size() - defaultMargin;
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// 根据 裁切size, 内容size 创建 sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

	// 向 sv 填充 items
	for (int i = 0; i < paths.size(); ++i) {
		auto&& path = paths[i];
		auto&& fn = path.filename().u8string();

		// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
		cocos2d::Vec2 pos(0, svContentHeight - (itemHeight + defaultMargin) * i);

		// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
		auto cb = CreateCheckBox({ pos.x + defaultMargin, pos.y - 50 }, false, nullptr, sv);
		auto cbWidth = cb->getContentSize().width;
		auto spr = CreateSprite({ pos.x + defaultMargin + cbWidth + defaultMargin + 50,  pos.y - 50 }, { 100, 100 }, fn, sv);
		auto txt = CreateLabel({ pos.x + defaultMargin + cbWidth + defaultMargin + 100 + defaultMargin,  pos.y - 50 }, fn, defaultFontSize, sv);
		txt->setAnchorPoint({ 0, 0.5 });
	}

	// 随便画些 3d 模型 到 scroll view
	for (int i = 0; i < 200; ++i) {
		auto o = CreateOrc({ (float)cocos2d::random(0, (int)svSize.width), (float)cocos2d::random(0, (int)svContentHeight) }, cocos2d::random(0, 360));
		sv->addChild(o);
	}

	// 令 sv 正确裁切 3d 内容
	sv->setGlobalZOrder(1);
}



void HelloWorld::editBoxReturn(cocos2d::ui::EditBox* editBox) {
	std::string s = editBox->getText();
	printf(s.c_str());
}


bool HelloWorld::init() {
	if (!Scene::init()) return false;
	W = AppDelegate::designWidth;
	H = AppDelegate::designHeight;
	DrawWelcome();
	return true;
}
