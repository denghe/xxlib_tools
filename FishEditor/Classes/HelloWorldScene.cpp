#include "HelloWorldScene.h"
#include "AppDelegate.h"
#include "ActionPlayer_SpriteFrame.h"
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

ActionPlayer_SpriteFrame* HelloWorld::CreateActionPlayer_SpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::vector<std::string> const& plists, FishManage::Fish_2D_Action const& action, cocos2d::Node* const& container) {
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



void HelloWorld::DrawSpriteFrameConfig(FishManage::Fish_2D* const& fish, FishManage::Fish_2D_Action* const& action) {
	// ��ʼ���� names (sprite frame names) ������. ��ʱ�����֮ǰ������
	removeAllChildren();
	editBoxs.clear();

	// ����
	CreateBG(this);

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// ���Ϸ� label + editbox Ҫ������ ������
	auto lblActionName = CreateLabel(p, "action name: ", fontSize, this);

	p.x += lblActionName->getContentSize().width;
	auto ebActionName = CreateEditBox(p, { lineHeight * 6, fontSize * 1.1f }, action->actionName, "", fontSize, this);

	// �����±� 0
	editBoxs.push_back(ebActionName);

	// ���·����谴ť
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Save & Exit]", fontSize, [this, fish, action](auto) {
		// editBox -> data
		action->actionName = editBoxs[0]->getText();
		for (int i = 1; i < (int)editBoxs.size(); ++i) {
			action->frames[i - 1].moveDistance = std::atof(editBoxs[i]->getText());
		}
		// �¶������ӵ��б�
		if (currentActionIndex == -1) {
			fish->actions.push_back(*action);
		}
		DrawFish2DSpriteFrame(fish);
	}, this);
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= bNext->getContentSize().width + lineHeight * 2;
	auto bCancel = CreateTextButton(p, "[Back]", fontSize, [this, fish, action](auto) {
		DrawSpriteFrameChoose(fish, action);
	}, this);
	bCancel->setAnchorPoint({ 1, 0.5 });

	// �� sv ��ʾ���� �� ���
	p.x = margin;
	p.y = H - lineHeight;
	cocos2d::Size svSize(W - margin * 2, H - lineHeight * 2);

	// ÿ�� item ���ࣺ
	/*
+-----+ sprite frame name: xxxxx
| pic | moveDistance: [___________]
+-----+ [Copy]                 [Delete]
*/
// item �߶�
	const auto itemHeight = lineHeight * 3;

	// �����ܸ߶�
	auto svContentHeight = margin + (itemHeight + margin) * action->frames.size();
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// ���� ����size, ����size ���� sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

	// �� sv ��� items
	// sv ����Ķ�������ֱ�ӷ���, �����һ�� node ɶ�ģ��ᵼ�²���ʧ��
	for (size_t i = 0; i < action->frames.size(); ++i) {
		auto&& frame = action->frames[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		p.x = pos.x + itemHeight / 2;
		p.y = pos.y - itemHeight / 2;
		auto spr = CreateSpriteFrame(p, { itemHeight, itemHeight }, frame.spriteFrameName, sv);

		p.x = pos.x + itemHeight + margin;
		p.y = pos.y - lineHeight / 2;
		auto txt0 = CreateLabel(p, std::string("sprite frame name: "), fontSize, sv);

		p.x += txt0->getContentSize().width;
		auto txt00 = CreateLabel(p, frame.spriteFrameName, fontSize, sv);
		txt00->setColor(yellow);

		p.x = pos.x + itemHeight + margin;
		p.y -= lineHeight;
		auto txt1 = CreateLabel(p, "moveDistance: ", fontSize, sv);

		p.x += txt1->getContentSize().width;
		auto e1 = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, std::to_string(frame.moveDistance), "", fontSize, sv);
		e1->setInputMode(cocos2d::ui::EditBox::InputMode::DECIMAL);
		editBoxs.push_back(e1);

		p.x = pos.x + itemHeight + margin;
		p.y -= lineHeight;
		auto bCopy = CreateTextButton(p, "[Copy]", fontSize, [this, sv, i = i, fish, action](auto) {
			// todo
			currentScrollBarPos = sv->getScrollBarPositionFromCornerForVertical();
			DrawSpriteFrameConfig(fish, action);
		}, sv);

		p.x += bCopy->getContentSize().width + lineHeight * 10;
		auto bDelete = CreateTextButton(p, "[Delete]", fontSize, [this, sv, i = i, fish, action](auto) {
			// todo
			currentScrollBarPos = sv->getScrollBarPositionFromCornerForVertical();
			DrawSpriteFrameConfig(fish, action);
		}, sv);
	}
}



void HelloWorld::DrawSpriteFrameChoose(FishManage::Fish_2D* const& fish, FishManage::Fish_2D_Action* const& action) {
	// ��ʼ���� names (plist) ������. ��ʱ�����֮ǰ������
	removeAllChildren();

	// ����
	CreateBG(this);

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// ���Ϸ�˵������
	CreateLabel(p, "please multi select sprite frame for this action:", fontSize, this);

	// ���·����谴ť
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Next]", fontSize, [this, fish, action](auto) {
		// ����ѡ�е� frames ͬ�� action �� frames
		// �г�ѡ�е�
		std::vector<std::string> names;
		for (auto&& kv : cbNames) {
			if (kv.first->isSelected()) {
				names.push_back(kv.second);
			}
		}
		// ɾ�������ڵ�
		for (int i = (int)action->frames.size() - 1; i >= 0; --i) {
			auto&& f = action->frames[i];
			bool found = false;
			for (auto&& name : names) {
				if (f.spriteFrameName == name) {
					found = true;
					break;
				}
			}
			action->frames.erase(action->frames.begin() + i);
		}
		// ׷���µ�
		for(auto&& name : names) {
			bool found = false;
			for (auto&& f : action->frames) {
				if (f.spriteFrameName == name) {
					found = true;
					break;
				}
			}
			if (found) continue;
			auto&& f = action->frames.emplace_back();
			f.spriteFrameName = name;
			f.moveDistance = 1;
		}
		// ����
		std::sort(action->frames.begin(), action->frames.end(), [](FishManage::Fish_2D_Frame const& a, FishManage::Fish_2D_Frame const& b)->bool {
			return xx::InnerNumberToFixed(a.spriteFrameName) < xx::InnerNumberToFixed(b.spriteFrameName);
		});

		currentScrollBarPos = { 0,0 };
		DrawSpriteFrameConfig(fish, action);
	}, this);
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= bNext->getContentSize().width + lineHeight * 2;
	auto bCancel = CreateTextButton(p, "[Cancel]", fontSize, [this, fish](auto) { DrawFish2DSpriteFrame(fish); }, this);
	bCancel->setAnchorPoint({ 1, 0.5 });



	// ����������� plist, �ҳ����� sprite frame name
	std::vector<std::string> names;
	auto&& fu = cocos2d::FileUtils::getInstance();
	for (auto&& plistFileName : fish->plistFileNames) {
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistFileName);
		// д��ȷ�������溯���ڲ�һ��
		std::string fullPath = fu->fullPathForFilename(plistFileName);
		auto&& dict = fu->getValueMapFromFile(fullPath);
		auto&& framesDict = dict["frames"].asValueMap();
		for (auto&& iter : framesDict) {
			auto&& frameDict = iter.second.asValueMap();
			names.push_back(iter.first);
		}
	}

	// ����( ����������֣������е����ֲ��ִ�С���� )
	std::sort(names.begin(), names.end(), [](std::string const& a, std::string const& b)->bool {
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
	p.y = H - lineHeight;
	cocos2d::Size svSize(W - margin * 2, H - lineHeight * 2);

	// item �߶�
	auto itemHeight = lineHeight * 2;

	// �����ܸ߶�
	auto svContentHeight = margin + (itemHeight + margin) * names.size();
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// ���� ����size, ����size ���� sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

	// ׼������
	cbNames.clear();

	// �� sv ��� items
	// sv ����Ķ�������ֱ�ӷ���, �����һ�� node ɶ�ģ��ᵼ�²���ʧ��
	for (size_t i = 0; i < names.size(); ++i) {
		auto&& frameName = names[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		p.x = pos.x;
		p.y = pos.y - itemHeight / 2;
		auto cb = CreateCheckBox(p, false, nullptr, sv);
		cbNames[cb] = frameName;
		for (auto&& frame : action->frames) {
			if (frame.spriteFrameName == frameName) {
				cb->setSelected(true);
			}
		}

		p.x += cb->getContentSize().width + margin + itemHeight / 2;
		auto spr = CreateSpriteFrame(p, { itemHeight, itemHeight }, frameName, sv);

		p.x += itemHeight + margin;
		auto txt = CreateLabel(p, frameName, fontSize, sv);
	}
}



void HelloWorld::DrawPListChoose(FishManage::Fish_2D* const& fish) {
	removeAllChildren();

	// ��� create 2d sprite frame fish ֮����ת����ѡ�� plist �ļ�ҳ

	// ����
	CreateBG(this);

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// ���Ϸ�˵������
	CreateLabel(p, "please multi select every plist file include your sprite frames:", fontSize, this);

	// ���·����谴ť
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Save & Exit]", fontSize, [this, fish](auto) {
		// ���� checkbox. ����Ӧ�� plist file names ��������
		fish->plistFileNames.clear();
		for (auto&& kv : cbNames) {
			if (kv.first->isSelected()) {
				fish->plistFileNames.push_back(kv.second);
			}
		}
		DrawFish2DSpriteFrame(fish);
	}, this);
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= bNext->getContentSize().width + lineHeight * 2;
	auto bCancel = CreateTextButton(p, "[Cancel]", fontSize, [this, fish](auto) {
		DrawFish2DSpriteFrame(fish);
	}, this);
	bCancel->setAnchorPoint({ 1, 0.5 });


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
	p.y = H - lineHeight * 1;
	cocos2d::Size svSize(W - margin * 2, H - lineHeight * 2);

	// item �߶�
	auto itemHeight = lineHeight;

	// �����ܸ߶�
	auto svContentHeight = margin + (itemHeight + margin) * paths.size();
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
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		p.x = pos.x;
		p.y = pos.y - itemHeight / 2;
		auto cb = CreateCheckBox(p, false, nullptr, sv);
		cbNames[cb] = fn;
		if (std::find(fish->plistFileNames.begin(), fish->plistFileNames.end(), fn) != fish->plistFileNames.end()) {
			cb->setSelected(true);
		}

		p.x += cb->getContentSize().width + margin;
		CreateLabel(p, fn, fontSize, sv);
	}

	// �� sv ��ȷ���� 3d ����
	sv->setGlobalZOrder(1);
}



void HelloWorld::DrawFish2DSpriteFrame(FishManage::Fish_2D* const& fish) {
	removeAllChildren();
	editBoxs.clear();

	// ����
	CreateBG(this);

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// ���Ϸ� label + editbox Ҫ������ ����
	auto tFishName = CreateLabel(p, "fish name: ", fontSize, this);

	p.x += tFishName->getContentSize().width;
	auto etFishName = CreateEditBox(p, { lineHeight * 10, fontSize * 1.1f }, fish->fishName, "", fontSize, this);
	editBoxs.push_back(etFishName);		// �����±� 0

	// �ڶ�����ʾ coin1, 2
	p.x = margin;
	p.y -= lineHeight;
	auto tCoin1 = CreateLabel(p, "coin1: ", fontSize, this);

	p.x += tCoin1->getContentSize().width;
	auto etCoin1 = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, std::to_string(fish->coin1), "base ratio", fontSize, this);
	etCoin1->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
	editBoxs.push_back(etCoin1);		// �����±� 1

	p.x += etCoin1->getContentSize().width + margin;
	auto tCoin2 = CreateLabel(p, "coin2: ", fontSize, this);

	p.x += tCoin2->getContentSize().width;
	auto etCoin2 = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, std::to_string(fish->coin2), "extend ratio or negative enum", fontSize, this);
	etCoin2->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
	editBoxs.push_back(etCoin2);		// �����±� 2


	// �� editBoxs ��λ������������� fish д����
	auto&& SaveEditBoxDataToFish = [this, fish] {
		fish->fishName = editBoxs[0]->getText();
		fish->coin1 = std::atoi(editBoxs[1]->getText());
		fish->coin2 = std::atoi(editBoxs[2]->getText());
	};

	// �����ſ�ʼ��Ϊ���ҽṹ, �����ʾ [New Action]. �ұ���ʾ [Choose PList Files]
	p.x = margin;
	p.y -= lineHeight;
	CreateTextButton(p, "[Choose PList Files]", fontSize, [this, fish, SaveEditBoxDataToFish](auto) {
		SaveEditBoxDataToFish();
		DrawPListChoose(fish);
	}, this);

	p.x = W / 2 + margin;
	CreateTextButton(p, "[New Action]", fontSize, [this, fish, SaveEditBoxDataToFish](auto) {
		if (fish->plistFileNames.empty()) return;	// todo: ��̬��ʾ
		SaveEditBoxDataToFish();
		currentActionIndex = -1;
		fish2dAction = FishManage::Fish_2D_Action();
		DrawSpriteFrameChoose(fish, &fish2dAction);
	}, this);


	// ���·����谴ť
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Save & Quit]", fontSize, [this, fish, SaveEditBoxDataToFish](auto) {
		SaveEditBoxDataToFish();
		if (currentFishIndex == -1) {
			data.fish_2ds.push_back(*fish);
		}
		SaveData();
		DrawWelcome();
	}, this);
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= bNext->getContentSize().width + lineHeight * 2;
	auto bCancel = CreateTextButton(p, "[Cancel]", fontSize, [this](auto) {
		DrawWelcome();
	}, this);
	bCancel->setAnchorPoint({ 1, 0.5 });

	// ��� SV����ʾ plist file names
	{
		// ÿ�� item ���ࣺ
		/*
ssssssssssssssxxxxxxx.plist
		*/

		// �� sv ��ʾ���� �� ���
		p.x = margin;
		p.y = H - lineHeight * 3;
		cocos2d::Size svSize(W / 2 - margin, H - lineHeight * 4);

		// item �߶�
		auto itemHeight = lineHeight;

		// �����ܸ߶�
		auto svContentHeight = margin + (itemHeight + margin) * fish->plistFileNames.size();
		if (svContentHeight < svSize.height) {
			svContentHeight = svSize.height;
		}

		// ���� ����size, ����size ���� sv
		auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

		// �� sv ��� items
		// sv ����Ķ�������ֱ�ӷ���, �����һ�� node ɶ�ģ��ᵼ�²���ʧ��
		for (size_t i = 0; i < fish->plistFileNames.size(); ++i) {
			auto&& fn = fish->plistFileNames[i];

			// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
			cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

			// ���� label
			p.x = pos.x;
			p.y = pos.y - itemHeight / 2;
			CreateLabel(p, fn, fontSize, sv);
		}
	}

	// �ұ� SV����ʾ actions
	{
		// ÿ�� item ���ࣺ
		/*
+---------+ action name: xxxxxxxxxx
|         | total frames: xxxxxxx
| preview | total frameDelay: xxxxxxx
|         | total moveDistance: xxxxxxx
+---------+ [Edit]                                      [Delete]
		*/

		// �� sv ��ʾ���� �� ���
		p.x = W / 2 + margin;
		p.y = H - lineHeight * 3;
		cocos2d::Size svSize(W / 2 - margin * 2, H - lineHeight * 4);

		// item �߶�
		auto itemHeight = lineHeight * 5;

		// �����ܸ߶�
		auto svContentHeight = margin + (itemHeight + margin) * fish->actions.size();
		if (svContentHeight < svSize.height) {
			svContentHeight = svSize.height;
		}

		// ���� ����size, ����size ���� sv
		auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

		// �� sv ��� items
		// sv ����Ķ�������ֱ�ӷ���, �����һ�� node ɶ�ģ��ᵼ�²���ʧ��
		for (size_t i = 0; i < fish->actions.size(); ++i) {
			auto&& action = fish->actions[i];

			// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
			cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

			// ����֡����
			p.x = pos.x + itemHeight / 2;
			p.y = pos.y - itemHeight / 2;
			CreateActionPlayer_SpriteFrame(p, { itemHeight ,itemHeight }, fish->plistFileNames, action, sv);

			// todo: ������� label & edit
		}
	}
}


template<typename FishType>
void HelloWorld::CreateSVItem(cocos2d::ui::ScrollView* const& sv, float const& itemHeight, cocos2d::Vec2 const& pos, int const& index, FishType const& fish) {
	cocos2d::Vec2 p;

	// name: fishName
	{
		p.x = pos.x + itemHeight + margin;
		p.y = pos.y - lineHeight / 2;
		auto tk = CreateLabel(p, "name: ", fontSize, sv);

		p.x += tk->getContentSize().width;
		auto tv = CreateLabel(p, fish.fishName, fontSize, sv);
		tv->setColor(yellow);
	}

	// type: 2d? spine? 3d? combine?
	{
		p.x = pos.x + itemHeight + margin;
		p.y -= lineHeight;
		auto tk = CreateLabel(p, "type: ", fontSize, sv);

		p.x += tk->getContentSize().width;
		auto tv = CreateLabel(p, "2D Sprite Frame", fontSize, sv);
		tv->setColor(yellow);
	}

	// actions: .........
	{
		p.x = pos.x + itemHeight + margin;
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
		p.x = pos.x + itemHeight + margin;
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
		p.x = pos.x + itemHeight + margin;
		p.y -= lineHeight;
		auto b1 = CreateTextButton(p, "[Edit]", fontSize, [this, index](auto) {
			currentFishIndex = index;
			DrawFish2DSpriteFrame(&data.fish_2ds[index]);
		}, sv);

		p.x += b1->getContentSize().width + lineHeight * 10;
		auto b2 = CreateTextButton(p, "[Delete]", fontSize, [this](auto) {
			/* todo: ��¼��ǰ sv ����λ�� ��ɾ��? */
		}, sv);
	}
}

void HelloWorld::DrawWelcome() {
	removeAllChildren();

	// ��ӭҳ

	// ����
	CreateBG(this);

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// �Ϸ�������ʾ 4 ����ť
	auto b1 = CreateTextButton(p, "[create 2d sprite frame fish]", fontSize, [this](auto) {
		currentFishIndex = -1;
		fish2d = FishManage::Fish_2D();
		DrawFish2DSpriteFrame(&fish2d);
	}, this);

	p.x += b1->getContentSize().width + margin * 3;
	auto b2 = CreateTextButton(p, "[create spine fish]", fontSize, [this](auto) { /* DrawSpineChoose(); */ }, this);

	p.x += b2->getContentSize().width + margin * 3;
	auto b3 = CreateTextButton(p, "[create 3d c3b fish]", fontSize, [this](auto) { /* DrawC3bChoose(); */ }, this);

	p.x += b3->getContentSize().width + margin * 3;
	auto b4 = CreateTextButton(p, "[create combine fish]", fontSize, [this](auto) { /* DrawFishsChoose(); */ }, this);


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
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		// ֡����Ԥ����һ������
		p.x = pos.x + itemHeight / 2;
		p.y = pos.y - itemHeight / 2;
		CreateActionPlayer_SpriteFrame(p, { itemHeight ,itemHeight }, fish.plistFileNames, fish.actions[0], sv);

		// ��������Ԥ��ͼ�Ҳ�Ķ���
		CreateSVItem(sv, itemHeight, pos, i, fish);
	}
	for (size_t i = 0; i < data.fish_spines.size(); ++i) {
		auto&& fish = data.fish_spines[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		// todo: spine ����

		// ��������Ԥ��ͼ�Ҳ�Ķ���
		CreateSVItem(sv, itemHeight, pos, i, fish);
	}
	for (size_t i = 0; i < data.fish_3ds.size(); ++i) {
		auto&& fish = data.fish_3ds[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		// todo: 3d ����

		// ��������Ԥ��ͼ�Ҳ�Ķ���
		CreateSVItem(sv, itemHeight, pos, i, fish);
	}
	for (size_t i = 0; i < data.fish_combines.size(); ++i) {
		auto&& fish = data.fish_combines[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		// todo: ����㶯��

		// ��������Ԥ��ͼ�Ҳ�Ķ���
		CreateSVItem(sv, itemHeight, pos, i, fish);
	}

	// ��㻭Щ 3d ģ�� �� scroll view
	for (size_t i = 0; i < 10; ++i) {
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
	if (std::filesystem::exists(dataFileName)) {
		xx::Data d;
		xx::ReadAllBytes(dataFileName, d);
		xx::DataReader dr(d);
		int r = dr.Read(data);
		if (r) throw std::logic_error("can't read fish.data");
	}
}
void HelloWorld::SaveData() {
	xx::Data d;
	xx::Write(d, data);
	xx::WriteAllBytes(dataFileName, d);
}

void HelloWorld::editBoxReturn(cocos2d::ui::EditBox* editBox) {
	//std::string s = editBox->getText();
	//printf(s.c_str());
}
