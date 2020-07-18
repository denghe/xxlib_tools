#include "MainScene.h"

void MainScene::ManageFishs() {
	removeAllChildren();

	// 鱼管理

	// 背景
	CreateBG(this);

	// 定位到屏幕左上方的位置
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// [create XXXX]   [create XXXX]   [create XXXX]   [create XXXX] ....
	auto b = CreateButton(p, "[create Normal]", [this](auto) {
		auto&& fish = xx::Make<FishManage::FishNormal>();
		// todo: more init
		EditFishNormal(fish);
		// todo: 
		});

	p.x += GetWidth(b) + lineHeight * 3;
	b = CreateButton(p, "[create Bomb]", [this](auto) {
		auto&& fish = xx::Make<FishManage::FishBomb>();
		// todo: more init
		EditFishBomb(fish);
		// todo: 
		});

	p.x += GetWidth(b) + lineHeight * 3;
	b = CreateButton(p, "[create Drill]", [this](auto) {
		auto&& fish = xx::Make<FishManage::FishDrill>();
		// todo: more init
		EditFishDrill(fish);
		// todo: 
		});

	p.x += GetWidth(b) + lineHeight * 3;
	b = CreateButton(p, "[create Fury]", [this](auto) {
		auto&& fish = xx::Make<FishManage::FishFury>();
		// todo: more init
		EditFishFury(fish);
		// todo: 
		});

	p.x += GetWidth(b) + lineHeight * 3;
	b = CreateButton(p, "[create Cyclone]", [this](auto) {
		auto&& fish = xx::Make<FishManage::FishCyclone>();
		// todo: more init
		EditFishCyclone(fish);
		// todo: 
		});

	p.x += GetWidth(b) + lineHeight * 3;
	b = CreateButton(p, "[create Eater]", [this](auto) {
		auto&& fish = xx::Make<FishManage::FishEater>();
		// todo: more init
		EditFishEater(fish);
		// todo: 
		});




	//        ->          [Back]
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bBack = CreateButton(p, "[Back]", [this](auto) {
		Welcome();
	});
	bBack->setAnchorPoint({ 1, 0.5 });

	// 每条 item 长相：
	/*
+---------+ name: fishName
|         | type: normal? bomb? drill? ......
| preview | coin1:       coin2:
|         | ..........
+---------+ [Edit]                     [Delete]
	*/

	// 算 sv 显示坐标 与 体积
	p.x = margin;
	p.y = H - lineHeight;
	cocos2d::Size svSize(W - margin * 2, H - lineHeight * 2);

	// item 高度
	auto itemHeight = lineHeight * 5;

	// 内容总高度
	auto svContentHeight = margin + (itemHeight + margin) * data.fishs.size();
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// 根据 裁切size, 内容size 创建 sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight });

	// 向 sv 填充 items
	// sv 里面的东西必须直接放入, 如果套一层 node 啥的，会导致裁切失败
	for (size_t i = 0; i < data.fishs.size(); ++i) {
		auto&& fish = data.fishs[i];

		// 每 item 内部 0, 0 点起始，在左上角. 向下是负坐标
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		// 帧动画预览第一个动作
		p.x = pos.x + itemHeight / 2;
		p.y = pos.y - itemHeight / 2;
		if (auto&& res = fish->res.lock()) {
			CreateResPreview(p, { itemHeight ,itemHeight }, res, sv);
		}

		// 继续绘制预览图右侧的东西
		// name
		{
			p.x = pos.x + itemHeight + margin;
			p.y = pos.y - lineHeight / 2;
			CreateLabelPair(p, "name: ", xx::ToString(fish->name), sv);
		}

		// type
		{
			p.y -= lineHeight;
			std::string typeName;
			if (xx::Is<FishManage::FishNormal>(fish)) {
				typeName = "Normal";
			}
			else if (xx::Is<FishManage::FishBomb>(fish)) {
				typeName = "Bomb";
			}
			else if (xx::Is<FishManage::FishDrill>(fish)) {
				typeName = "Drill";
			}
			else if (xx::Is<FishManage::FishFury>(fish)) {
				typeName = "Fury";
			}
			else if (xx::Is<FishManage::FishCyclone>(fish)) {
				typeName = "Cyclone";
			}
			else if (xx::Is<FishManage::FishEater>(fish)) {
				typeName = "Eater";
			}
			else {
				typeName = "unknown";
			}
			CreateLabelPair(p, "type: ", typeName, sv);
		}

		// coin1    coin2
		{
			p.x = pos.x + itemHeight + margin;
			p.y = pos.y - lineHeight / 2;
			auto kv = CreateLabelPair(p, "coin1: ", xx::ToString(fish->coin1), sv);

			p.x += GetWidth(kv) + itemHeight * 3;
			CreateLabelPair(p, "coin2: ", xx::ToString(fish->coin2), sv);
		}

		// lastUpdateTime
		{
			p.x = pos.x + itemHeight + margin;
			p.y -= lineHeight;
			CreateLabelPair(p, "lastUpdateTime: ", xx::ToString(xx::Epoch10mToTimePoint(fish->lastUpdateTime)), sv);
		}

		// [Edit Clone]                     [Delete]
		{
			p.x = pos.x + itemHeight + margin;
			p.y -= lineHeight;
			auto b1 = CreateButton(p, "[Edit Clone]", [this, fish](auto) {
				auto&& cloneFish = oh.Clone(fish);
				if (auto&& r = xx::As<FishManage::FishNormal>(cloneFish)) {
					EditFishNormal(r);
				}
				else if (auto&& r = xx::As<FishManage::FishBomb>(cloneFish)) {
					EditFishBomb(r);
				}
				else if (auto&& r = xx::As<FishManage::FishDrill>(cloneFish)) {
					EditFishDrill(r);
				}
				else if (auto&& r = xx::As<FishManage::FishFury>(cloneFish)) {
					EditFishFury(r);
				}
				else if (auto&& r = xx::As<FishManage::FishCyclone>(cloneFish)) {
					EditFishCyclone(r);
				}
				else if (auto&& r = xx::As<FishManage::FishEater>(cloneFish)) {
					EditFishEater(r);
				}
				else {
					// 
				}
				}, sv);

			p.x += GetWidth(b1) + lineHeight * 10;
			auto b2 = CreateButton(p, "[Delete]", [this, i, sv](auto) {
				manageFishsScrolledPercentVertical = sv->getScrolledPercentVertical();
				data.ress.erase(data.ress.begin() + i);
				SaveData();
				ManageResources();
				}, sv);
		}
	}

	// 令 sv 正确裁切 3d 内容
	sv->setGlobalZOrder(1);

	// 还原滚动位置
	if (svContentHeight > svSize.height) {
		sv->jumpToPercentVertical(manageFishsScrolledPercentVertical);
	}
	else {
		manageFishsScrolledPercentVertical = 0;
	}
}
