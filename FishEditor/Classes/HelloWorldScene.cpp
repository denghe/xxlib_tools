#include "HelloWorldScene.h"
#include "AppDelegate.h"
#include "xx_file.h"
#include "xx_math.h"

#pragma region create funcs

cocos2d::Label* HelloWorld::CreateLabel(cocos2d::Vec2 const& pos, std::string const& txt, int const& fontSize, cocos2d::Node* const& container) {
	auto l = cocos2d::Label::createWithSystemFont(txt, "", fontSize);
	if (!l) return l;
	l->setAnchorPoint({ 0, 0.5 });
	l->setPosition(pos);
	if (container) {
		container->addChild(l);
	}
	return l;
}

cocos2d::ui::Button* HelloWorld::CreateTextButton(cocos2d::Vec2 const& pos, std::string const& txt, int const& fontSize, cocos2d::ccMenuCallback&& callback, cocos2d::Node* const& container) {
	auto b = cocos2d::ui::Button::create();
	if (!b) return b;
	b->setAnchorPoint({ 0, 0.5 });
	b->setPosition(pos);
	b->setTitleColor(blue);
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
	et->setAnchorPoint({ 0, 0.5 });
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


#pragma endregion



void HelloWorld::DrawSpriteFrameConfig() {
	// �Ȳ����������ʾ. ���� sv ���ӣ��õ���ѡ�嵥�����һ����û�й�ѡ����ֱ�� return������ȥ���˰�ťû��Ӧ�� todo: ���������Զ���ʧ����ʾ����
	if (!cbNames.size()) return;
	names.clear();
	for (auto&& kv : cbNames) {
		if (kv.first->isSelected()) {
			names.push_back(kv.second);
		}
	}
	if (names.empty()) return;

	// ��ʼ���� names (sprite frame names) ������. ��ʱ�����֮ǰ������
	this->removeAllChildren();
	editBoxs.clear();
	editBoxMap.clear();

	// ����
	CreateBG(this);

	// �綨�и�
	auto lineHeight = fontSize * 1.4f;

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// ���Ϸ� label + editbox Ҫ������ ������
	auto lblActionName = CreateLabel(p, "action name: ", fontSize, this);

	p.x += lblActionName->getContentSize().width;
	auto ebActionName = CreateEditBox(p, { lineHeight * 6, lineHeight }, "", "", fontSize, this);

	// �����±� 0
	editBoxs.push_back(ebActionName);

	// ���·����谴ť
	p.x = W - margin;
	p.y = margin;
	auto txtNext = CreateTextButton(p, "[Next]", fontSize, [this](cocos2d::Ref* ref) { this->SaveSpriteFrameConfig(); }, this);
	txtNext->setAnchorPoint({ 1, 0.5 });

	p.x -= txtNext->getContentSize().width + margin * 2;
	auto txtCancel = CreateTextButton(p, "[Cancel]", fontSize, [this](cocos2d::Ref* ref) { this->DrawPListChoose(); }, this);
	txtCancel->setAnchorPoint({ 1, 0.5 });

	// �� sv ��ʾ���� �� ���
	p.x = margin;
	p.y = H - (lineHeight + margin);
	cocos2d::Size svSize(W - margin * 2, H - (lineHeight + margin) * 2);

	// ����( ����������֣������е����ֲ��ִ�С���� )
	std::sort(names.begin(), names.end(), [](std::string const& a, std::string const& b)->bool {
		return xx::InnerNumberToFixed(a) < xx::InnerNumberToFixed(b);
		});

	// ÿ�� item ���ࣺ
	/*
+-----+ sprite frame name:
| pic | distance:
+-----+ frame count:
*/
// item �߶�
	const auto itemHeight = lineHeight * 3;

	// �����ܸ߶�
	auto svContentHeight = (itemHeight + margin) * names.size() - margin;
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// ���� ����size, ����size ���� sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

	// �� sv ��� items
	// sv ����Ķ�������ֱ�ӷ���, �����һ�� node ɶ�ģ��ᵼ�²���ʧ��
	for (size_t i = 0; i < names.size(); ++i) {
		auto&& frameName = names[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(0, svContentHeight - (itemHeight + margin) * i);

		p.x = pos.x + margin + itemHeight / 2;
		p.y = pos.y - itemHeight / 2;
		auto spr = CreateSpriteFrame(p, { itemHeight, itemHeight }, frameName, sv);

		p.x = pos.x + margin + itemHeight + margin;
		p.y = pos.y - lineHeight / 2;
		auto txt0 = CreateLabel(p, std::string(" sprite frame name: "), fontSize, sv);
		p.x += txt0->getContentSize().width;
		auto txt00 = CreateLabel(p, frameName, fontSize, sv);
		txt00->setColor(yellow);

		p.x = pos.x + margin + itemHeight + margin;
		p.y -= lineHeight;
		auto txt1 = CreateLabel(p, "distance( string ): ", fontSize, sv);

		p.x += txt1->getContentSize().width;
		auto e1 = CreateEditBox(p, { lineHeight * 3, lineHeight }, "1.2", "", fontSize, sv);
		e1->setInputMode(cocos2d::ui::EditBox::InputMode::DECIMAL);
		editBoxMap[frameName + "*d"] = e1;

		p.x = pos.x + margin + itemHeight + margin;
		p.y -= lineHeight;
		auto txt2 = CreateLabel(p, "frame count( int ): ", fontSize, sv);

		p.x += txt2->getContentSize().width;
		auto e2 = CreateEditBox(p, { lineHeight * 3, lineHeight }, "1", "", fontSize, sv);
		e2->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
		editBoxMap[frameName + "*c"] = e2;
	}
}
void HelloWorld::SaveSpriteFrameConfig() {
	// todo: ɨ 
	// editBoxs
		// editBoxMap
	// ����
}



void HelloWorld::DrawSpriteFrameChoose() {
	// �Ȳ����������ʾ. ���� sv ���ӣ��õ���ѡ�嵥�����һ����û�й�ѡ����ֱ�� return������ȥ���˰�ťû��Ӧ�� todo: ���������Զ���ʧ����ʾ����
	if (!cbNames.size()) return;
	names.clear();
	for (auto&& kv : cbNames) {
		if (kv.first->isSelected()) {
			names.push_back(kv.second);
		}
	}
	if (names.empty()) return;

	// ��ʼ���� names (plist) ������. ��ʱ�����֮ǰ������
	this->removeAllChildren();

	// ����
	CreateBG(this);

	// �и�
	float lineHeight = fontSize * 1.4f;

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// ���Ϸ�˵������
	CreateLabel(p, "please multi select every sprite frame:", fontSize, this);

	// ���·����谴ť
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Next]", fontSize, [this](cocos2d::Ref* ref) { this->DrawSpriteFrameConfig(); }, this);
	bNext->setAnchorPoint({ 1, 0.5 });
	p.x -= bNext->getContentSize().width + margin * 2;
	auto bCancel = CreateTextButton(p, "[Cancel]", fontSize, [this](cocos2d::Ref* ref) { this->DrawPListChoose(); }, this);



	// ����������� plist, �ҳ����� sprite frame name
	frameNames.clear();
	auto&& fu = cocos2d::FileUtils::getInstance();
	for (auto&& name : names) {
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name);
		// д��ȷ�������溯���ڲ�һ��
		std::string fullPath = fu->fullPathForFilename(name);
		auto&& dict = fu->getValueMapFromFile(fullPath);
		auto&& framesDict = dict["frames"].asValueMap();
		for (auto&& iter : framesDict) {
			auto&& frameDict = iter.second.asValueMap();
			frameNames.push_back(iter.first);
		}
	}

	// ����( ����������֣������е����ֲ��ִ�С���� )
	std::sort(frameNames.begin(), frameNames.end(), [](std::string const& a, std::string const& b)->bool {
		return xx::InnerNumberToFixed(a) < xx::InnerNumberToFixed(b);
		});


	// ÿ�� item ���ࣺ
	/*
	 +-----+
[  ] | pic | sprite frame name
	 +-----+
*/

// �� sv ��ʾ���� �� ���
	p.x = margin;
	p.y = H - lineHeight - margin;
	cocos2d::Size svSize(W - margin * 2, H - (lineHeight + margin) * 2);

	// item �߶�
	auto itemHeight = lineHeight * 2;

	// �����ܸ߶�
	auto svContentHeight = (itemHeight + margin) * frameNames.size() - margin;
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// ���� ����size, ����size ���� sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

	// ׼������
	cbNames.clear();

	// �� sv ��� items
	// sv ����Ķ�������ֱ�ӷ���, �����һ�� node ɶ�ģ��ᵼ�²���ʧ��
	for (size_t i = 0; i < frameNames.size(); ++i) {
		auto&& frameName = frameNames[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(0, svContentHeight - (itemHeight + margin) * i);

		p.x = pos.x + margin;
		p.y = pos.y - itemHeight / 2;
		auto cb = CreateCheckBox(p, false, nullptr, sv);
		cbNames[cb] = frameName;

		p.x += cb->getContentSize().width + margin + itemHeight / 2;
		auto spr = CreateSpriteFrame(p, { itemHeight, itemHeight }, frameName, sv);

		p.x += itemHeight + margin;
		auto txt = CreateLabel(p, frameName, fontSize, sv);
	}
}



void HelloWorld::DrawPListChoose() {
	// todo: ���� DrawFishMenu_SpriteFrame ������

	this->removeAllChildren();

	// ��� create 2d sprite frame fish ֮����ת����ѡ�� plist �ļ�ҳ

	// ����
	CreateBG(this);

	// �и�
	float lineHeight = fontSize * 1.4f;

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// ���Ϸ�˵������
	CreateLabel(p, "please multi select every plist file include your sprite frames:", fontSize, this);

	// ���·����谴ť
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Next]", fontSize, [this](cocos2d::Ref* ref) { this->DrawSpriteFrameChoose(); }, this);
	bNext->setAnchorPoint({ 1, 0.5 });
	p.x -= bNext->getContentSize().width + margin * 2;
	auto bCancel = CreateTextButton(p, "[Cancel]", fontSize, [this](cocos2d::Ref* ref) { this->DrawFishMenu_SpriteFrame(); }, this);


	// �������� .plist
	auto&& sps = cocos2d::FileUtils::getInstance()->getSearchPaths();
	assert(sps.size() == 1);
	std::vector<std::filesystem::path> paths;
	for (auto&& entry : std::filesystem::directory_iterator(sps[0])) {
		if (entry.is_regular_file() && entry.path().extension().u8string() == ".plist") {
			paths.emplace_back(entry);
		}
	}

	// ÿ�� item ���ࣺ
	/*
[  ] file name
	*/

	// �� sv ��ʾ���� �� ���
	p.x = margin;
	p.y = H - lineHeight - margin;
	cocos2d::Size svSize(W - margin * 2, H - (lineHeight + margin) * 2);

	// item �߶�
	auto itemHeight = lineHeight;

	// �����ܸ߶�
	auto svContentHeight = (itemHeight + margin) * paths.size() - margin;
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// ���� ����size, ����size ���� sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

	// ׼������
	cbNames.clear();

	// �� sv ��� items
	// sv ����Ķ�������ֱ�ӷ���, �����һ�� node ɶ�ģ��ᵼ�²���ʧ��
	for (size_t i = 0; i < paths.size(); ++i) {
		auto&& path = paths[i];
		auto&& fn = path.filename().u8string();

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(0, svContentHeight - (itemHeight + margin) * i);

		p.x = pos.x + margin;
		p.y = pos.y - itemHeight / 2;
		auto cb = CreateCheckBox(p, false, nullptr, sv);
		cbNames[cb] = fn;

		p.x += cb->getContentSize().width + margin;
		CreateLabel(p, fn, fontSize, sv);
	}

	// �� sv ��ȷ���� 3d ����
	sv->setGlobalZOrder(1);

}



void HelloWorld::DrawFishMenu_SpriteFrame() {
	this->removeAllChildren();
	editBoxs.clear();
	editBoxMap.clear();

	// �ж��Ǵ������㻹���޸ľ���. ��ָ��ָ��洢��
	FishManage::Fish_2D* fish;
	if (currentFishIndex == -1) {
		fish = &fish2d;
	}
	else {
		fish = &data.fish_2ds[currentFishIndex];
	}

	// ����
	CreateBG(this);


	// �и�
	float lineHeight = fontSize * 1.4f;

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// ���Ϸ� label + editbox Ҫ������ ����
	auto lblFishName = CreateLabel(p, "fish name: ", fontSize, this);

	p.x += lblFishName->getContentSize().width;
	auto et = CreateEditBox(p, { lineHeight * 10, lineHeight }, fish->fishName, "", fontSize, this);
	editBoxs.push_back(et);		// �����±� 0

	// todo: �����Ļ���������ʾ�ڴ�, ���籶��, ɶɶ. ���� edit mode

	// ��һ����ʾ [new action] ��ť
	p.x = margin;
	p.y -= lineHeight;
	CreateTextButton(p, "[New Action]", fontSize, [this](cocos2d::Ref* ref) { this->DrawPListChoose(); }, this);

	// ���·����谴ť
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Save & Quit]", fontSize, [this](cocos2d::Ref* ref) { this->SaveFishMenu_SpriteFrame(); }, this);
	bNext->setAnchorPoint({ 1, 0.5 });
	p.x -= bNext->getContentSize().width + margin * 2;
	auto bCancel = CreateTextButton(p, "[Cancel]", fontSize, [this](cocos2d::Ref* ref) { this->DrawWelcome(); }, this);



	// ÿ�� item ���ࣺ
	/*
+---------+ action name: xxxxxxxxxx
|         | total num of physics frames:
| preview | total num of logic frames:
|         | total distance: xxxxxxx
+---------+ [delete action]
	*/

	// �� sv ��ʾ���� �� ���
	p.x = margin;
	p.y = H - lineHeight * 2 - margin;
	cocos2d::Size svSize(W - margin * 2, H - lineHeight * 3 - margin * 2);

	// item �߶�
	auto itemHeight = lineHeight * 5;

	// �����ܸ߶�
	auto svContentHeight = (itemHeight + margin) * names.size() - margin;
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// ���� ����size, ����size ���� sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

	// todo
}
void HelloWorld::SaveFishMenu_SpriteFrame() {

}



template<typename FishType>
void HelloWorld::CreateSVItem(cocos2d::ui::ScrollView* const& sv, float const& itemHeight, cocos2d::Vec2 const& pos, FishType const& fish) {
	float lineHeight = fontSize * 1.4f;
	cocos2d::Vec2 p;

	// name: fishName
	{
		p.x = pos.x + margin + itemHeight + margin;
		p.y = pos.y - lineHeight / 2;
		auto tk = CreateLabel(p, "name: ", fontSize, sv);

		p.x += tk->getContentSize().width;
		auto tv = CreateLabel(p, fish.fishName, fontSize, sv);
		tv->setColor(yellow);
	}

	// type: 2d? spine? 3d? combine?
	{
		p.x = pos.x + margin + itemHeight + margin;
		p.y -= lineHeight;
		auto tk = CreateLabel(p, "type: ", fontSize, sv);

		p.x += tk->getContentSize().width;
		auto tv = CreateLabel(p, "2D Sprite Frame", fontSize, sv);
		tv->setColor(yellow);
	}

	// actions: .........
	{
		p.x = pos.x + margin + itemHeight + margin;
		p.y -= lineHeight;
		auto tk = CreateLabel(p, "actions: ", fontSize, sv);

		p.x += tk->getContentSize().width;
		for (auto&& action : fish.actions) {
			auto tv = CreateLabel(p, action.actionName + ((&action == &fish.actions.back()) ? "" : ", "), fontSize, sv);
			tv->setColor(yellow);
			p.x += tv->getContentSize().width + margin;
		}
	}

	// coin1:       coin2:
	{
		p.x = pos.x + margin + itemHeight + margin;
		p.y -= lineHeight;
		auto tk1 = CreateLabel(p, "coin1: ", fontSize, sv);

		p.x += tk1->getContentSize().width;
		auto tv1 = CreateLabel(p, std::to_string(fish.coin1), fontSize, sv);
		tv1->setColor(yellow);

		p.x += tv1->getContentSize().width + margin;
		auto tk2 = CreateLabel(p, "coin2: ", fontSize, sv);

		p.x += tk2->getContentSize().width;
		auto tv2 = CreateLabel(p, std::to_string(fish.coin2), fontSize, sv);
		tv2->setColor(yellow);
	}

	// [Edit]                     [Delete]
	{
		p.x = pos.x + margin + itemHeight + margin;
		p.y -= lineHeight;
		auto b1 = CreateTextButton(p, "[Edit]", fontSize, [this](cocos2d::Ref* ref) { /* todo: �� currentFishIndex = xxxx */ this->DrawFishMenu_SpriteFrame(); }, sv);

		p.x += b1->getContentSize().width + lineHeight * 10;
		auto b2 = CreateTextButton(p, "[Delete]", fontSize, [this](cocos2d::Ref* ref) { /* todo: ��¼��ǰ sv ����λ�� ��ɾ��? */ }, sv);
	}
}

void HelloWorld::DrawWelcome() {
	this->removeAllChildren();

	// ��ӭҳ

	// ����
	CreateBG(this);


	// �и�
	float lineHeight = fontSize * 1.4f;

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// �Ϸ�������ʾ 4 ����ť
	auto b1 = CreateTextButton(p, "[create 2d sprite frame fish]", fontSize, [this](cocos2d::Ref* ref) { this->DrawFishMenu_SpriteFrame();	}, this);

	p.x += b1->getContentSize().width + margin * 3;
	auto b2 = CreateTextButton(p, "[create spine fish]", fontSize, [this](cocos2d::Ref* ref) { /* this->DrawSpineChoose(); */ }, this);

	p.x += b2->getContentSize().width + margin * 3;
	auto b3 = CreateTextButton(p, "[create 3d c3b fish]", fontSize, [this](cocos2d::Ref* ref) { /* this->DrawC3bChoose(); */ }, this);

	p.x += b3->getContentSize().width + margin * 3;
	auto b4 = CreateTextButton(p, "[create combine fish]", fontSize, [this](cocos2d::Ref* ref) { /* this->DrawFishsChoose(); */ }, this);



	// ���û�����ݣ�������һ����Ч��
	if (data.fish_2ds.empty()) {
		auto&& f = data.fish_2ds.emplace_back();
		f.fishName = "fish_001";
		f.coin1 = 11;
		f.coin2 = 222;
		auto&& a1 = f.actions.emplace_back();
		a1.actionName = "idle";
		auto&& a2 = f.actions.emplace_back();
		a2.actionName = "die";
	}



	// ÿ�� item ���ࣺ
	/*
+---------+ name: fishName
|         | type: 2d? spine? 3d? combine?
| preview | actions: ���ŷָ��г�
|         | coin1:       coin2:
+---------+ [Edit]                     [Delete]
	*/

	// ��ť�·��� scroll view
	p.x = margin;
	p.y = H - lineHeight;

	// ���з�Χ
	cocos2d::Size svSize(W - margin * 2, H - lineHeight - margin);

	// item �߶�
	auto itemHeight = lineHeight * 5;

	// �����ܸ߶�
	auto svContentHeight = margin + (itemHeight + margin) * (data.fish_2ds.size() + data.fish_spines.size() + data.fish_3ds.size() + data.fish_combines.size());
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// ���� ����size, ����size ���� sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

	// �� sv ��� items
	// sv ����Ķ�������ֱ�ӷ���, �����һ�� node ɶ�ģ��ᵼ�²���ʧ��
	for (size_t i = 0; i < data.fish_2ds.size(); ++i) {
		auto&& fish = data.fish_2ds[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(0, svContentHeight - margin - (itemHeight + margin) * i);

		// todo: ֡����
		//auto spr = CreateSpriteFrame({ pos.x + margin + itemHeight/2,  pos.y - itemHeight/2 }, { itemHeight, itemHeight }, fish.actions[0].frames[0].spriteFrameName, sv);

		// ��������Ԥ��ͼ�Ҳ�Ķ���
		CreateSVItem(sv, itemHeight, pos, fish);
	}
	for (size_t i = 0; i < data.fish_spines.size(); ++i) {
		auto&& fish = data.fish_spines[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(0, svContentHeight - (itemHeight + margin) * i);

		// todo: spine ����
		//auto spr = CreateSpriteFrame({ pos.x + margin + itemHeight / 2,  pos.y - itemHeight / 2 }, { itemHeight, itemHeight }, fish.actions[0].frames[0].spriteFrameName, sv);

		// ��������Ԥ��ͼ�Ҳ�Ķ���
		CreateSVItem(sv, itemHeight, pos, fish);
	}
	for (size_t i = 0; i < data.fish_3ds.size(); ++i) {
		auto&& fish = data.fish_3ds[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(0, svContentHeight - (itemHeight + margin) * i);

		// todo: 3d ����
		//auto spr = CreateSpriteFrame({ pos.x + margin + itemHeight / 2,  pos.y - itemHeight / 2 }, { itemHeight, itemHeight }, fish.actions[0].frames[0].spriteFrameName, sv);

		// ��������Ԥ��ͼ�Ҳ�Ķ���
		CreateSVItem(sv, itemHeight, pos, fish);
	}
	for (size_t i = 0; i < data.fish_combines.size(); ++i) {
		auto&& fish = data.fish_combines[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(0, svContentHeight - (itemHeight + margin) * i);

		// todo: ����㶯��
		//auto spr = CreateSpriteFrame({ pos.x + margin + itemHeight / 2,  pos.y - itemHeight / 2 }, { itemHeight, itemHeight }, fish.actions[0].frames[0].spriteFrameName, sv);

		// ��������Ԥ��ͼ�Ҳ�Ķ���
		CreateSVItem(sv, itemHeight, pos, fish);
	}

	// ��㻭Щ 3d ģ�� �� scroll view
	for (size_t i = 0; i < 100; ++i) {
		auto o = CreateOrc({ (float)cocos2d::random(0, (int)svSize.width), (float)cocos2d::random(0, (int)svContentHeight) }, cocos2d::random(0, 360));
		sv->addChild(o);
	}

	// �� sv ��ȷ���� 3d ����
	sv->setGlobalZOrder(1);
}



bool HelloWorld::init() {
	if (!Scene::init()) return false;

	LoadData();

	W = AppDelegate::designWidth;
	H = AppDelegate::designHeight;
	DrawWelcome();

	return true;
}

void HelloWorld::LoadData() {
	if (std::filesystem::exists("fishs.data")) {
		xx::Data d;
		xx::ReadAllBytes("fishs.data", d);
		xx::DataReader dr(d);
		int r = dr.Read(data);
		if (r) throw std::logic_error("can't read fish.data");
	}
}
void HelloWorld::SaveData() {
	xx::Data d;
	xx::Write(d, data);
	xx::WriteAllBytes("data", d);
}

void HelloWorld::editBoxReturn(cocos2d::ui::EditBox* editBox) {
	//std::string s = editBox->getText();
	//printf(s.c_str());
}
