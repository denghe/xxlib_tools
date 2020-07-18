#include "MainScene.h"

void MainScene::ConfigSpriteFrame(std::shared_ptr<FishManage::Res2d> const& res2d, std::shared_ptr<FishManage::Action2d> const& action2d) {
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
		if (std::find(res2d->actions.begin(), res2d->actions.end(), action2d) == res2d->actions.end()) {
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
