#include "MainScene.h"

void MainScene::ChooseSpriteFrame(std::shared_ptr<FishManage::Res2d> const& res2d, std::shared_ptr<FishManage::Action2d> const& action2d) {
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

		if (action2d->frames.empty()) {
			PopupMessage("please select some sprite frame!");
			return;
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
