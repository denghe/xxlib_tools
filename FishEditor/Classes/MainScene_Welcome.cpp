#include "MainScene.h"

void MainScene::Welcome() {
	removeAllChildren();

	// 首页

	// 背景
	CreateBG(this);

	// [Browse Resources]      [Browse Fishs]
	cocos2d::Vec2 p(margin, H - lineHeight / 2);
	auto bBR = CreateButton(p, "[Manage Resources]", [this](auto) {
		ManageResources();
	});

	p.x += GetWidth(bBR) + lineHeight * 3;
	auto bBF = CreateButton(p, "[Manage Fishs]", [this](auto) {
		ManageFishs();
	});

	// todo: 未来预期功能：给鱼分组？罗列分组鱼引用到的所有资源文件？算体积？

	// 显示一些针对 data 的 summary 信息
	p.x = margin;
	p.y -= lineHeight;
	CreateLabelPair(p, "ress.size() = ", xx::ToString(data.ress.size()));

	p.y -= lineHeight;
	CreateLabelPair(p, "fishs.size() = ", xx::ToString(data.fishs.size()));

	// todo: 分类统计？
}
