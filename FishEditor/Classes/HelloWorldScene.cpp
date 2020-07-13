#include "HelloWorldScene.h"
#include "AppDelegate.h"
#include "ActionPlayer_SpriteFrame.h"
#include "xx_file.h"
#include "xx_math.h"

#pragma region funcs

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
std::pair<cocos2d::Label*, cocos2d::Label*> HelloWorld::CreateLabelPair(cocos2d::Vec2 const& pos, std::string const& key, std::string const& value, int const& fontSize, cocos2d::Node* const& container) {
	std::pair<cocos2d::Label*, cocos2d::Label*> rtv;
	rtv.first = CreateLabel(pos, key, fontSize, container);
	rtv.second = CreateLabel({pos.x + rtv.first->getContentSize().width, pos.y}, value, fontSize, container);
	rtv.second->setColor(yellow);
	return rtv;
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



void HelloWorld::ConfigSpriteFrame(std::shared_ptr<FishManage::Res2d> const& res2d, std::shared_ptr<FishManage::Action2d> const& action2d) {
	// 开始遍历 names (sprite frame names) 并加载. 此时可清除之前的内容
	removeAllChildren();

	// 初始化 editBoxs 引用容器. 准备数据保存函数
	editBoxs.clear();
	auto&& SaveEditBoxDataToRes = [this, res2d, action2d] {
		action2d->name = editBoxs[0]->getText();
		xx::Convert(editBoxs[1]->getText(), action2d->frameRate);
		for (int i = 2; i < (int)editBoxs.size(); ++i) {
			xx::Convert(editBoxs[i]->getText(), action2d->frames[i - 2]->moveDistance);
		}
	};

	// 背景
	CreateBG(this);

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// action name: [_____________________]     frameRate: [_________]
	auto tActionName = CreateLabel(p, "action name: ", fontSize, this);

	p.x += tActionName->getContentSize().width;
	auto eActionName = CreateEditBox(p, { lineHeight * 8, fontSize * 1.1f }, action2d->name, "", fontSize, this);

	p.x += eActionName->getContentSize().width + lineHeight * 3;
	auto tFrameRate = CreateLabel(p, "frameRate: ", fontSize, this);

	p.x += tFrameRate->getContentSize().width;
	auto eFrameRate = CreateEditBox(p, { lineHeight * 3, fontSize * 1.1f }, xx::ToString(action2d->frameRate), "", fontSize, this);
	eFrameRate->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);

	// 放在下标 0, 1
	editBoxs.push_back(eActionName);
	editBoxs.push_back(eFrameRate);


	// 最下方步骤按钮
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Save & Exit]", fontSize, [this, res2d, action2d, SaveEditBoxDataToRes](auto) {
		SaveEditBoxDataToRes();
		// 新动作？加到列表
		if(std::find(res2d->actions.begin(), res2d->actions.end(), action2d) == res2d->actions.end()) {
			res2d->actions.push_back(action2d);
		}
		EditRes2d(res2d);
	}, this);
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= bNext->getContentSize().width + lineHeight * 2;
	auto bCancel = CreateTextButton(p, "[Back]", fontSize, [this, res2d, action2d, SaveEditBoxDataToRes](auto) {
		if (std::find(res2d->actions.begin(), res2d->actions.end(), action2d) == res2d->actions.end()) {
			ChooseSpriteFrame(res2d, action2d);
		}
		else {
			EditRes2d(res2d);
		}
	}, this);
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
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

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
		CreateLabelPair(p, "sprite frame name: ", xx::ToString(frame->spriteFrameName), fontSize, sv);

		p.x = pos.x + itemHeight + margin;
		p.y -= lineHeight;
		auto txt1 = CreateLabel(p, "moveDistance: ", fontSize, sv);

		p.x += txt1->getContentSize().width;
		auto e1 = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, xx::ToString(frame->moveDistance), "", fontSize, sv);
		e1->setInputMode(cocos2d::ui::EditBox::InputMode::DECIMAL);
		editBoxs.push_back(e1);

		p.x = pos.x + itemHeight + margin;
		p.y -= lineHeight;
		auto bCopy = CreateTextButton(p, "[Copy]", fontSize, [this, sv, i = i, res2d, action2d, SaveEditBoxDataToRes](auto) {
			SaveEditBoxDataToRes();
			action2d->frames.insert(action2d->frames.begin() + i, action2d->frames[i]);
			spriteFrameConfigScrolledPercentVertical = sv->getScrolledPercentVertical();
			ConfigSpriteFrame(res2d, action2d);
		}, sv);

		p.x += bCopy->getContentSize().width + lineHeight * 10;
		auto bDelete = CreateTextButton(p, "[Delete]", fontSize, [this, sv, i = i, res2d, action2d, SaveEditBoxDataToRes](auto) {
			SaveEditBoxDataToRes();
			action2d->frames.erase(action2d->frames.begin() + i);
			spriteFrameConfigScrolledPercentVertical = sv->getScrolledPercentVertical();
			ConfigSpriteFrame(res2d, action2d);
		}, sv);
	}

	// 还原滚动位置
	if (svContentHeight > svSize.height) {
		sv->jumpToPercentVertical(spriteFrameConfigScrolledPercentVertical);
	}
	else {
		spriteFrameConfigScrolledPercentVertical = 0;
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
	CreateLabel(p, "please multi select sprite frame for this action:", fontSize, this);

	// 第二排 全选 全不选 / 前缀勾选
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


	// 最下方步骤按钮
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Next]", fontSize, [this, res2d, action2d](auto) {
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
		spriteFrameConfigScrolledPercentVertical = 0;
		ConfigSpriteFrame(res2d, action2d);
	}, this);
	bNext->setAnchorPoint({ 1, 0.5 });

	p.x -= bNext->getContentSize().width + lineHeight * 2;
	auto bCancel = CreateTextButton(p, "[Cancel]", fontSize, [this, res2d](auto) { EditRes2d(res2d); }, this);
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
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

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

		p.x += cb->getContentSize().width + margin + itemHeight / 2;
		auto spr = CreateSpriteFrame(p, { itemHeight, itemHeight }, frameName, sv);

		p.x += itemHeight + margin;
		auto txt = CreateLabel(p, frameName, fontSize, sv);
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
	CreateLabel(p, "please multi select every plist file include your sprite frames:", fontSize, this);

	// 最下方步骤按钮
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateTextButton(p, "[Save & Exit]", fontSize, [this, res2d](auto) {
		// 遍历 checkbox. 将对应的 plist file names 存入容器
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
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

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

		p.x += cb->getContentSize().width + margin;
		CreateLabel(p, fn, fontSize, sv);
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
		auto tName = CreateLabel(p, "res name: ", fontSize, this);
		p.x += tName->getContentSize().width;
		auto eName = CreateEditBox(p, { lineHeight * 10, fontSize * 1.1f }, res2d->name, "", fontSize, this);
		editBoxs.push_back(eName);
	}

	// shadowScale: [_________]     shadowOffsetX: [_________]    shadowOffsetY: [_________]
	{
		p.x = margin;
		p.y -= lineHeight;
		auto tShadowScale = CreateLabel(p, "shadowScale: ", fontSize, this);

		p.x += tShadowScale->getContentSize().width;
		auto eShadowScale = CreateEditBox(p, { lineHeight * 3, fontSize * 1.1f }, xx::ToString(res2d->shadowScale), "", fontSize, this);
		editBoxs.push_back(eShadowScale);

		p.x += eShadowScale->getContentSize().width + lineHeight * 2;
		auto tShadowOffsetX = CreateLabel(p, "shadowOffsetX: ", fontSize, this);

		p.x += tShadowOffsetX->getContentSize().width;
		auto eShadowOffsetX = CreateEditBox(p, { lineHeight * 3, fontSize * 1.1f }, xx::ToString(res2d->shadowOffsetX), "", fontSize, this);
		editBoxs.push_back(eShadowOffsetX);

		p.x += eShadowOffsetX->getContentSize().width + lineHeight * 2;
		auto tShadowOffsetY = CreateLabel(p, "shadowOffsetY: ", fontSize, this);

		p.x += tShadowOffsetY->getContentSize().width;
		auto eShadowOffsetY = CreateEditBox(p, { lineHeight * 3, fontSize * 1.1f }, xx::ToString(res2d->shadowOffsetY), "", fontSize, this);
		editBoxs.push_back(eShadowOffsetY);
	}

	// [New Action]       ->         [Choose PList Files]
	{
		p.x = margin;
		p.y -= lineHeight;
		CreateTextButton(p, "[Choose PList Files]", fontSize, [this, res2d, SaveEditBoxDataToRes](auto) {
			SaveEditBoxDataToRes();
			ChoosePList(res2d);
			}, this);

		p.x = W / 2 + margin;
		CreateTextButton(p, "[New Action]", fontSize, [this, res2d, SaveEditBoxDataToRes](auto) {
			if (res2d->plistFileNames.empty()) return;	// todo: 动态提示
			SaveEditBoxDataToRes();
			auto a = xx::Make<FishManage::Action2d>();
			a->frameRate = 30;
			ChooseSpriteFrame(res2d, a);
			}, this);
	}

	//      ->        [Save & Quit]    [Cancel]
	{
		p.x = W - margin;
		p.y = lineHeight / 2;
		auto bNext = CreateTextButton(p, "[Save & Quit]", fontSize, [this, res2d, SaveEditBoxDataToRes](auto) {
			SaveEditBoxDataToRes();

			// todo: 实现克隆功能, 编辑的是克隆体，最后存盘之时永远新增。这样就能保留老数据不会误伤。

			if (std::find(data.ress.begin(), data.ress.end(), res2d) == data.ress.end()) {
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
	}

	// 左边 SV：显示 plist file names
	{
		// 每条 item 长相：
		/*
ssssssssssssssxxxxxxx.plist
		*/

		// 算 sv 显示坐标 与 体积
		p.x = margin;
		p.y = H - lineHeight * 2;
		cocos2d::Size svSize(W / 2 - margin, H - lineHeight * 3);

		// item 高度
		auto itemHeight = lineHeight;

		// 内容总高度
		auto svContentHeight = margin + (itemHeight + margin) * res2d->plistFileNames.size();
		if (svContentHeight < svSize.height) {
			svContentHeight = svSize.height;
		}

		// 根据 裁切size, 内容size 创建 sv
		auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

		// 向 sv 填充 items
		// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
		for (size_t i = 0; i < res2d->plistFileNames.size(); ++i) {
			auto&& fn = res2d->plistFileNames[i];

			// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
			cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

			// 创建 label
			p.x = pos.x;
			p.y = pos.y - itemHeight / 2;
			CreateLabel(p, fn, fontSize, sv);
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
		p.y = H - lineHeight * 2;
		cocos2d::Size svSize(W / 2 - margin * 2, H - lineHeight * 3);

		// item 高度
		auto itemHeight = lineHeight * 5;

		// 内容总高度
		auto svContentHeight = margin + (itemHeight + margin) * res2d->actions.size();
		if (svContentHeight < svSize.height) {
			svContentHeight = svSize.height;
		}

		// 根据 裁切size, 内容size 创建 sv
		auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

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
			CreateLabelPair(p, "name: ", xx::ToString(action2d->name), fontSize, sv);

			// frameRate
			p.y -= lineHeight;
			CreateLabelPair(p, "frameRate: ", xx::ToString(action2d->frameRate), fontSize, sv);

			// numFrames
			p.y -= lineHeight;
			CreateLabelPair(p, "numFrames: ", xx::ToString(action2d->frames.size()), fontSize, sv);

			// total moveDistance
			p.y -= lineHeight;
			double d = 0;
			for (auto&& frame : action2d->frames) { d += frame->moveDistance; }
			CreateLabelPair(p, "total moveDistance: ", xx::ToString(d), fontSize, sv);

			// [Edit]                     [Delete]
			{
				p.x = pos.x + itemHeight + margin;
				p.y -= lineHeight;
				auto b1 = CreateTextButton(p, "[Edit]", fontSize, [this, res2d, action2d, SaveEditBoxDataToRes](auto) {
					SaveEditBoxDataToRes();
					ConfigSpriteFrame(res2d, action2d);
				}, sv);

				p.x += b1->getContentSize().width + lineHeight * 10;
				auto b2 = CreateTextButton(p, "[Delete]", fontSize, [this, res2d, i, sv, SaveEditBoxDataToRes](auto) {
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


void HelloWorld::Welcome() {
	removeAllChildren();

	// 欢迎页

	// 背景
	CreateBG(this);

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// 上方依次显示 4 个按钮
	auto b1 = CreateTextButton(p, "[create 2d sprite frame res]", fontSize, [this](auto) {
		EditRes2d(xx::Make<FishManage::Res2d>());
	}, this);

	p.x += b1->getContentSize().width + margin * 3;
	auto b2 = CreateTextButton(p, "[create spine res]", fontSize, [this](auto) {
		/* EditResSpine(r); */ 
	}, this);

	p.x += b2->getContentSize().width + margin * 3;
	auto b3 = CreateTextButton(p, "[create 3d c3b res]", fontSize, [this](auto) {
		/* EditRes3d(r); */
	}, this);

	p.x += b3->getContentSize().width + margin * 3;
	auto b4 = CreateTextButton(p, "[create combine res]", fontSize, [this](auto) {
		/* EditResCombine(r); */
	}, this);


	// 每条 item 长相：
	/*
+---------+ name: fishName
|         | type: 2d? spine? 3d? combine?
| preview | actions: 逗号分隔列出
|         | coin1:       coin2:
+---------+ [Edit]                     [Delete]
	*/

	// 按钮下方是 scroll view
	p.x = margin;
	p.y = H - lineHeight;

	// 裁切范围
	cocos2d::Size svSize(W - margin * 2, H - lineHeight - margin);

	// item 高度
	auto itemHeight = lineHeight * 5;

	// 内容总高度
	auto svContentHeight = margin + (itemHeight + margin) * data.ress.size();
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// 根据 裁切size, 内容size 创建 sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight }, this);

	// 向 sv 填充 items
	// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
	for (size_t i = 0; i < data.ress.size(); ++i) {
		auto&& res = data.ress[i];

		// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		// 帧动画预览第一个动作
		p.x = pos.x + itemHeight / 2;
		p.y = pos.y - itemHeight / 2;
		if (auto&& r = xx::As<FishManage::Res2d>(res)) {
			CreateActionPlayer_SpriteFrame(p, { itemHeight ,itemHeight }, r->plistFileNames, xx::As<FishManage::Action2d>(r->actions[0]), sv);

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

		// 继续绘制预览图右侧的东西
		cocos2d::Vec2 p;

		// name
		{
			p.x = pos.x + itemHeight + margin;
			p.y = pos.y - lineHeight / 2;
			CreateLabelPair(p, "name: ", xx::ToString(res->name), fontSize, sv);
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
			CreateLabelPair(p, "type: ", typeName, fontSize, sv);
		}

		// actions: .........
		{
			p.y -= lineHeight;
			auto tk = CreateLabel(p, "actions: ", fontSize, sv);

			p.x += tk->getContentSize().width;
			for (auto&& action : res->actions) {
				auto tv = CreateLabel(p, xx::ToString(action->name, ((&action == &res->actions.back()) ? "" : ", ")), fontSize, sv);
				tv->setColor(yellow);
				p.x += tv->getContentSize().width + margin;
			}
		}

		// [Edit]                     [Delete]
		{
			p.x = pos.x + itemHeight + margin;
			p.y -= lineHeight;
			auto b1 = CreateTextButton(p, "[Edit]", fontSize, [this, res](auto) {
				if (auto&& r = xx::As<FishManage::Res2d>(res)) {
					EditRes2d(r);
				}
				else if (auto&& r = xx::As<FishManage::ResSpine>(res)) {
					//EditResSpine(r);
				}
				else if (auto&& r = xx::As<FishManage::Res3d>(res)) {
					//EditRes3d(r);
				}
				else if (auto&& r = xx::As<FishManage::ResCombine>(res)) {
					//EditResCombine(r);
				}
				else {
					//
				}
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

	// 随便画些 3d 模型 到 scroll view
	for (size_t i = 0; i < 10; ++i) {
		auto o = CreateOrc({ (float)cocos2d::random(0, (int)svSize.width), (float)cocos2d::random(0, (int)svContentHeight) }, cocos2d::random(0, 360));
		sv->addChild(o);
	}

	// 令 sv 正确裁切 3d 内容
	sv->setGlobalZOrder(1);

	// 还原滚动位置
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
			throw std::logic_error(xx::ToString("ReadAllBytes from file name:'", dataFileName, "' error. r = ", r));
		}

		xx::DataReaderEx dr(d, oc);
		if (int r = dr.ReadOnce(data)) {
			throw std::logic_error(xx::ToString("d ReadOnce error. r = ", r));
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






//// 第二排显示 coin1, 2
//p.x = margin;
//p.y -= lineHeight;
//auto tCoin1 = CreateLabel(p, "coin1: ", fontSize, this);

//p.x += tCoin1->getContentSize().width;
//auto etCoin1 = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, xx::ToString(res2d->coin1), "base ratio", fontSize, this);
//etCoin1->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
//editBoxs.push_back(etCoin1);		// 放在下标 1

//p.x += etCoin1->getContentSize().width + margin;
//auto tCoin2 = CreateLabel(p, "coin2: ", fontSize, this);

//p.x += tCoin2->getContentSize().width;
//auto etCoin2 = CreateEditBox(p, { lineHeight * 5, fontSize * 1.1f }, xx::ToString(res2d->coin2), "extend ratio or negative enum", fontSize, this);
//etCoin2->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
//editBoxs.push_back(etCoin2);		// 放在下标 2



		//// coin1:       coin2:
		//{
		//	p.x = pos.x + itemHeight + margin;
		//	p.y -= lineHeight;
		//	auto tk1 = CreateLabel(p, "coin1: ", fontSize, sv);

		//	p.x += tk1->getContentSize().width;
		//	auto tv1 = CreateLabel(p, xx::ToString(res2d.coin1), fontSize, sv);
		//	tv1->setColor(yellow);

		//	p.x += tv1->getContentSize().width + margin;
		//	auto tk2 = CreateLabel(p, "coin2: ", fontSize, sv);

		//	p.x += tk2->getContentSize().width;
		//	auto tv2 = CreateLabel(p, xx::ToString(res2d.coin2), fontSize, sv);
		//	tv2->setColor(yellow);
		//}


		//res2d->coin1 = std::atoi(editBoxs[1]->getText());
		//res2d->coin2 = std::atoi(editBoxs[2]->getText());
