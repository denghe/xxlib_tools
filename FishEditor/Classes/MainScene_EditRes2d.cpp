#include "MainScene.h"

void MainScene::EditRes2d(std::shared_ptr<FishManage::Res2d> const& res2d) {
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

	//             ->            [Cancel]    [Save & Quit]
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
