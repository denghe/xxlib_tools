#include "MainScene.h"

void MainScene::ChoosePList(std::shared_ptr<FishManage::Res2d> const& res2d) {
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
	std::vector<std::filesystem::path> paths;
	for (auto&& entry : std::filesystem::directory_iterator(resPath)) {
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
