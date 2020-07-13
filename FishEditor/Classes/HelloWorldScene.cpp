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



void HelloWorld::ConfigSpriteFrame(std::shared_ptr<FishManage::Res2d> const& res2d, std::shared_ptr<FishManage::ActionBase> const& action) {
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
	auto ebActionName = CreateEditBox(p, { lineHeight * 6, fontSize * 1.1f }, action->name, "", fontSize, this);

	// �����±� 0
	editBoxs.push_back(ebActionName);

	// ���·����谴ť
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Save & Exit]", fontSize, [this, res2d, action](auto) {
		// editBox -> data
		action->name = editBoxs[0]->getText();
		for (int i = 1; i < (int)editBoxs.size(); ++i) {
			action->frames[i - 1]->moveDistance = std::atof(editBoxs[i]->getText());
		}
		// �¶������ӵ��б�
		if(std::find(res2d->actions.begin(), res2d->actions.end(), action) == res2d->actions.end()) {
			res2d->actions.push_back(action);
		}
		EditRes2d(res2d);
	}, this);
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= bNext->getContentSize().width + lineHeight * 2;
	auto bCancel = CreateTextButton(p, "[Back]", fontSize, [this, res2d, action](auto) {
		ChooseSpriteFrame(res2d, action);
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
		auto&& frame = xx::As<FishManage::Frame2d>(action->frames[i]);

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		p.x = pos.x + itemHeight / 2;
		p.y = pos.y - itemHeight / 2;
		auto spr = CreateSpriteFrame(p, { itemHeight, itemHeight }, frame->spriteFrameName, sv);

		p.x = pos.x + itemHeight + margin;
		p.y = pos.y - lineHeight / 2;
		auto txt0 = CreateLabel(p, std::string("sprite frame name: "), fontSize, sv);

		p.x += txt0->getContentSize().width;
		auto txt00 = CreateLabel(p, frame->spriteFrameName, fontSize, sv);
		txt00->setColor(yellow);

		p.x = pos.x + itemHeight + margin;
		p.y -= lineHeight;
		auto txt1 = CreateLabel(p, "moveDistance: ", fontSize, sv);

		p.x += txt1->getContentSize().width;
		auto e1 = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, std::to_string(frame->moveDistance), "", fontSize, sv);
		e1->setInputMode(cocos2d::ui::EditBox::InputMode::DECIMAL);
		editBoxs.push_back(e1);

		p.x = pos.x + itemHeight + margin;
		p.y -= lineHeight;
		auto bCopy = CreateTextButton(p, "[Copy]", fontSize, [this, sv, i = i, res2d, action](auto) {
			action->frames.insert(action->frames.begin() + i, action->frames[i]);
			spriteFrameConfigScrolledPercentVertical = sv->getScrolledPercentVertical();
			ConfigSpriteFrame(res2d, action);
		}, sv);

		p.x += bCopy->getContentSize().width + lineHeight * 10;
		auto bDelete = CreateTextButton(p, "[Delete]", fontSize, [this, sv, i = i, res2d, action](auto) {
			action->frames.erase(action->frames.begin() + i);
			spriteFrameConfigScrolledPercentVertical = sv->getScrolledPercentVertical();
			ConfigSpriteFrame(res2d, action);
		}, sv);
	}

	// ��ԭ����λ��
	if (svContentHeight > svSize.height) {
		sv->jumpToPercentVertical(spriteFrameConfigScrolledPercentVertical);
	}
	else {
		spriteFrameConfigScrolledPercentVertical = 0;
	}
}



void HelloWorld::ChooseSpriteFrame(std::shared_ptr<FishManage::Res2d> const& res2d, std::shared_ptr<FishManage::ActionBase> const& action) {
	// ��ʼ���� names (plist) ������. ��ʱ�����֮ǰ������
	removeAllChildren();

	// ����
	CreateBG(this);

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// ���Ϸ�˵������
	CreateLabel(p, "please multi select sprite frame for this action:", fontSize, this);

	// �ڶ��� ȫѡ ȫ��ѡ / ǰ׺��ѡ
	p.y -= lineHeight;
	auto bSelectAll = CreateTextButton(p, "[SelectAll]", fontSize, [this, res2d](auto) {
		for (auto&& kv : cbNames) {
			kv.first->setSelected(true);
		}
	}, this);
	
	p.x += bSelectAll->getContentSize().width + margin * 5;
	auto bClear = CreateTextButton(p, "[Clear]", fontSize, [this, res2d](auto) {
		for (auto&& kv : cbNames) {
			kv.first->setSelected(false);
		}
	}, this);

	p.x += bClear->getContentSize().width + margin * 5;
	auto tPrefix = CreateLabel(p, "prefix: ", fontSize, this);

	p.x += tPrefix->getContentSize().width;
	auto ePrefix = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, "", "", fontSize, this);

	p.x += ePrefix->getContentSize().width;
	auto bSelectPrefix = CreateTextButton(p, "[SelectPrefix]", fontSize, [this, res2d, ePrefix](auto) {
		std::string prefix = ePrefix->getText();
		for (auto&& kv : cbNames) {
			if (kv.second.size() >= prefix.size() && memcmp(kv.second.data(), prefix.data(), prefix.size()) == 0) {
				kv.first->setSelected(true);
			}
		}
	}, this);


	// ���·����谴ť
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Next]", fontSize, [this, res2d, action](auto) {
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
			auto&& f = xx::As<FishManage::Frame2d>(action->frames[i]);
			bool found = false;
			for (auto&& name : names) {
				if (f->spriteFrameName == name) {
					found = true;
					break;
				}
			}
			action->frames.erase(action->frames.begin() + i);
		}
		// ׷���µ�
		for(auto&& name : names) {
			bool found = false;
			for (int i = (int)action->frames.size() - 1; i >= 0; --i) {
				auto&& f = xx::As<FishManage::Frame2d>(action->frames[i]);
				if (f->spriteFrameName == name) {
					found = true;
					break;
				}
			}
			if (found) continue;
			auto f = xx::Make<FishManage::Frame2d>();
			action->frames.emplace_back(f);
			f->spriteFrameName = name;
			f->moveDistance = 1;
		}
		// ����
		std::sort(action->frames.begin(), action->frames.end(), [](auto a, auto b)->bool {
			return xx::InnerNumberToFixed(xx::As<FishManage::Frame2d>(a)->spriteFrameName) < xx::InnerNumberToFixed(xx::As<FishManage::Frame2d>(b)->spriteFrameName);
		});

		// ���ù�����λ��
		spriteFrameConfigScrolledPercentVertical = 0;
		ConfigSpriteFrame(res2d, action);
	}, this);
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= bNext->getContentSize().width + lineHeight * 2;
	auto bCancel = CreateTextButton(p, "[Cancel]", fontSize, [this, res2d](auto) { EditRes2d(res2d); }, this);
	bCancel->setAnchorPoint({ 1, 0.5 });



	// ����������� plist, �ҳ����� sprite frame name
	std::vector<std::string> names;
	auto&& fu = cocos2d::FileUtils::getInstance();
	for (auto&& plistFileName : res2d->plistFileNames) {
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
	p.y = H - lineHeight * 2;
	cocos2d::Size svSize(W - margin * 2, H - lineHeight * 3);

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
			if (xx::As<FishManage::Frame2d>(frame)->spriteFrameName == frameName) {
				cb->setSelected(true);
			}
		}

		p.x += cb->getContentSize().width + margin + itemHeight / 2;
		auto spr = CreateSpriteFrame(p, { itemHeight, itemHeight }, frameName, sv);

		p.x += itemHeight + margin;
		auto txt = CreateLabel(p, frameName, fontSize, sv);
	}
}



void HelloWorld::ChoosePList(std::shared_ptr<FishManage::Res2d> const& res2d) {
	removeAllChildren();

	// ��� create 2d sprite frame res2d ֮����ת����ѡ�� plist �ļ�ҳ

	// ����
	CreateBG(this);

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// ���Ϸ�˵������
	CreateLabel(p, "please multi select every plist file include your sprite frames:", fontSize, this);

	// ���·����谴ť
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Save & Exit]", fontSize, [this, res2d](auto) {
		// ���� checkbox. ����Ӧ�� plist file names ��������
		res2d->plistFileNames.clear();
		for (auto&& kv : cbNames) {
			if (kv.first->isSelected()) {
				res2d->plistFileNames.push_back(kv.second);
			}
		}
		EditRes2d(res2d);
	}, this);
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= bNext->getContentSize().width + lineHeight * 2;
	auto bCancel = CreateTextButton(p, "[Cancel]", fontSize, [this, res2d](auto) {
		EditRes2d(res2d);
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
		if (std::find(res2d->plistFileNames.begin(), res2d->plistFileNames.end(), fn) != res2d->plistFileNames.end()) {
			cb->setSelected(true);
		}

		p.x += cb->getContentSize().width + margin;
		CreateLabel(p, fn, fontSize, sv);
	}

	// �� sv ��ȷ���� 3d ����
	sv->setGlobalZOrder(1);
}



void HelloWorld::EditRes2d(std::shared_ptr<FishManage::Res2d> const& res2d) {
	removeAllChildren();
	editBoxs.clear();

	// ����
	CreateBG(this);

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// ���Ϸ� label + editbox Ҫ������ ����
	auto tName = CreateLabel(p, "res2d name: ", fontSize, this);

	p.x += tName->getContentSize().width;
	auto eName = CreateEditBox(p, { lineHeight * 10, fontSize * 1.1f }, res2d->name, "", fontSize, this);
	editBoxs.push_back(eName);		// �����±� 0

	//// �ڶ�����ʾ coin1, 2
	//p.x = margin;
	//p.y -= lineHeight;
	//auto tCoin1 = CreateLabel(p, "coin1: ", fontSize, this);

	//p.x += tCoin1->getContentSize().width;
	//auto etCoin1 = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, std::to_string(res2d->coin1), "base ratio", fontSize, this);
	//etCoin1->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
	//editBoxs.push_back(etCoin1);		// �����±� 1

	//p.x += etCoin1->getContentSize().width + margin;
	//auto tCoin2 = CreateLabel(p, "coin2: ", fontSize, this);

	//p.x += tCoin2->getContentSize().width;
	//auto etCoin2 = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, std::to_string(res2d->coin2), "extend ratio or negative enum", fontSize, this);
	//etCoin2->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
	//editBoxs.push_back(etCoin2);		// �����±� 2


	// �� editBoxs ��λ������������� res2d д����
	auto&& SaveEditBoxDataToFish = [this, res2d] {
		res2d->name = editBoxs[0]->getText();
		//res2d->coin1 = std::atoi(editBoxs[1]->getText());
		//res2d->coin2 = std::atoi(editBoxs[2]->getText());
	};

	// �����ſ�ʼ��Ϊ���ҽṹ, �����ʾ [New Action]. �ұ���ʾ [Choose PList Files]
	p.x = margin;
	p.y -= lineHeight;
	CreateTextButton(p, "[Choose PList Files]", fontSize, [this, res2d, SaveEditBoxDataToFish](auto) {
		SaveEditBoxDataToFish();
		ChoosePList(res2d);
	}, this);

	p.x = W / 2 + margin;
	CreateTextButton(p, "[New Action]", fontSize, [this, res2d, SaveEditBoxDataToFish](auto) {
		if (res2d->plistFileNames.empty()) return;	// todo: ��̬��ʾ
		SaveEditBoxDataToFish();
		tmpAction = xx::Make<FishManage::Action2d>();
		ChooseSpriteFrame(res2d, tmpAction);
	}, this);


	// ���·����谴ť
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Save & Quit]", fontSize, [this, res2d, SaveEditBoxDataToFish](auto) {
		SaveEditBoxDataToFish();
		if(std::find(data.ress.begin(), data.ress.end(), tmpRes)== data.ress.end()) {
			data.ress.push_back(res2d);
		}
		SaveData();
		Welcome();
	}, this);
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= bNext->getContentSize().width + lineHeight * 2;
	auto bCancel = CreateTextButton(p, "[Cancel]", fontSize, [this](auto) {
		Welcome();
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
		auto svContentHeight = margin + (itemHeight + margin) * res2d->plistFileNames.size();
		if (svContentHeight < svSize.height) {
			svContentHeight = svSize.height;
		}

		// ���� ����size, ����size ���� sv
		auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

		// �� sv ��� items
		// sv ����Ķ�������ֱ�ӷ���, �����һ�� node ɶ�ģ��ᵼ�²���ʧ��
		for (size_t i = 0; i < res2d->plistFileNames.size(); ++i) {
			auto&& fn = res2d->plistFileNames[i];

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
		auto svContentHeight = margin + (itemHeight + margin) * res2d->actions.size();
		if (svContentHeight < svSize.height) {
			svContentHeight = svSize.height;
		}

		// ���� ����size, ����size ���� sv
		auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

		// �� sv ��� items
		// sv ����Ķ�������ֱ�ӷ���, �����һ�� node ɶ�ģ��ᵼ�²���ʧ��
		for (size_t i = 0; i < res2d->actions.size(); ++i) {
			auto&& action = xx::As<FishManage::Action2d>(res2d->actions[i]);

			// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
			cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

			// ����֡����
			p.x = pos.x + itemHeight / 2;
			p.y = pos.y - itemHeight / 2;
			CreateActionPlayer_SpriteFrame(p, { itemHeight ,itemHeight }, res2d->plistFileNames, action, sv);

			// todo: ������� label & edit
		}
	}
}


void HelloWorld::Welcome() {
	removeAllChildren();

	// ��ӭҳ

	// ����
	CreateBG(this);

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// �Ϸ�������ʾ 4 ����ť
	auto b1 = CreateTextButton(p, "[create 2d sprite frame res2d]", fontSize, [this](auto) {
		auto r = xx::Make<FishManage::Res2d>();
		tmpRes = r;
		EditRes2d(r);
	}, this);

	p.x += b1->getContentSize().width + margin * 3;
	auto b2 = CreateTextButton(p, "[create spine res2d]", fontSize, [this](auto) { /* DrawSpineChoose(); */ }, this);

	p.x += b2->getContentSize().width + margin * 3;
	auto b3 = CreateTextButton(p, "[create 3d c3b res2d]", fontSize, [this](auto) { /* DrawC3bChoose(); */ }, this);

	p.x += b3->getContentSize().width + margin * 3;
	auto b4 = CreateTextButton(p, "[create combine res2d]", fontSize, [this](auto) { /* DrawFishsChoose(); */ }, this);


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
	auto svContentHeight = margin + (itemHeight + margin) * data.ress.size();
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// ���� ����size, ����size ���� sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

	// �� sv ��� items
	// sv ����Ķ�������ֱ�ӷ���, �����һ�� node ɶ�ģ��ᵼ�²���ʧ��
	for (size_t i = 0; i < data.ress.size(); ++i) {
		auto&& res = data.ress[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		// ֡����Ԥ����һ������
		p.x = pos.x + itemHeight / 2;
		p.y = pos.y - itemHeight / 2;
		if (auto&& r = xx::As<FishManage::Res2d>(res)) {
			CreateActionPlayer_SpriteFrame(p, { itemHeight ,itemHeight }, r->plistFileNames, xx::As<FishManage::Action2d>(r->actions[0]), sv);
		}
		else if (auto&& r = xx::As<FishManage::ResSpine>(res)) {
		}

		// ��������Ԥ��ͼ�Ҳ�Ķ���
		cocos2d::Vec2 p;

		// name: fishName
		{
			p.x = pos.x + itemHeight + margin;
			p.y = pos.y - lineHeight / 2;
			auto tk = CreateLabel(p, "name: ", fontSize, sv);

			p.x += tk->getContentSize().width;
			auto tv = CreateLabel(p, res->name, fontSize, sv);
			tv->setColor(yellow);
		}

		// type: 2d? spine? 3d? combine?
		{
			p.x = pos.x + itemHeight + margin;
			p.y -= lineHeight;
			auto tk = CreateLabel(p, "type: ", fontSize, sv);

			p.x += tk->getContentSize().width;
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
			auto tv = CreateLabel(p, typeName, fontSize, sv);
			tv->setColor(yellow);
		}

		// actions: .........
		{
			p.x = pos.x + itemHeight + margin;
			p.y -= lineHeight;
			auto tk = CreateLabel(p, "actions: ", fontSize, sv);

			p.x += tk->getContentSize().width;
			for (auto&& action : res->actions) {
				auto tv = CreateLabel(p, action->name + ((&action == &res->actions.back()) ? "" : ", "), fontSize, sv);
				tv->setColor(yellow);
				p.x += tv->getContentSize().width + margin;
			}
		}

		//// coin1:       coin2:
		//{
		//	p.x = pos.x + itemHeight + margin;
		//	p.y -= lineHeight;
		//	auto tk1 = CreateLabel(p, "coin1: ", fontSize, sv);

		//	p.x += tk1->getContentSize().width;
		//	auto tv1 = CreateLabel(p, std::to_string(res2d.coin1), fontSize, sv);
		//	tv1->setColor(yellow);

		//	p.x += tv1->getContentSize().width + margin;
		//	auto tk2 = CreateLabel(p, "coin2: ", fontSize, sv);

		//	p.x += tk2->getContentSize().width;
		//	auto tv2 = CreateLabel(p, std::to_string(res2d.coin2), fontSize, sv);
		//	tv2->setColor(yellow);
		//}

		// [Edit]                     [Delete]
		{
			p.x = pos.x + itemHeight + margin;
			p.y -= lineHeight;
			auto b1 = CreateTextButton(p, "[Edit]", fontSize, [this, i](auto) {
				EditRes2d(xx::As<FishManage::Res2d>(data.ress[i]));
			}, sv);

			p.x += b1->getContentSize().width + lineHeight * 10;
			auto b2 = CreateTextButton(p, "[Delete]", fontSize, [this, i, sv](auto) {
				welcomeScrolledPercentVertical = sv->getScrolledPercentVertical();
				data.ress.erase(data.ress.begin() + i);
				SaveData();
				Welcome();
			}, sv);
		}
	}

	// ��㻭Щ 3d ģ�� �� scroll view
	for (size_t i = 0; i < 10; ++i) {
		auto o = CreateOrc({ (float)cocos2d::random(0, (int)svSize.width), (float)cocos2d::random(0, (int)svContentHeight) }, cocos2d::random(0, 360));
		sv->addChild(o);
	}

	// �� sv ��ȷ���� 3d ����
	sv->setGlobalZOrder(1);

	// ��ԭ����λ��
	if (svContentHeight > svSize.height) {
		sv->jumpToPercentVertical(welcomeScrolledPercentVertical);
	}
	else {
		welcomeScrolledPercentVertical = 0;
	}
}



bool HelloWorld::init() {
	if (!Scene::init()) return false;

	FishManage::PkgGenTypes::RegisterTo(oc);

	LoadData();

	W = AppDelegate::designWidth;
	H = AppDelegate::designHeight;
	Welcome();

	return true;
}

void HelloWorld::LoadData() {
	if (std::filesystem::exists(dataFileName)) {
		xx::Data d;
		if (int r = xx::ReadAllBytes(dataFileName, d)) {
			throw std::logic_error(std::string("d ReadAllBytes error. r = ") + std::to_string(r));
		}

		xx::DataReaderEx dr(d, oc);
		if (int r = dr.ReadOnce(data)) {
			throw std::logic_error(std::string("d ReadOnce error. r = ") + std::to_string(r));
		}
	}
}

void HelloWorld::SaveData() {
	xx::Data d;
	xx::DataWriterEx dw(d);
	dw.WriteOnce(data);
	xx::WriteAllBytes(dataFileName, d);
}

void HelloWorld::editBoxReturn(cocos2d::ui::EditBox* editBox) {
	//std::string s = editBox->getText();
	//printf(s.c_str());
}
