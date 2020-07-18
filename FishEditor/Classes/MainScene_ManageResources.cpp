#include "MainScene.h"

void MainScene::ManageResources() {
	removeAllChildren();

	// ��Դ����

	// ����
	CreateBG(this);

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// [create 2d sprite frame res]   [create spine res]   [create 3d c3b res]   [create combine res]
	auto b1 = CreateButton(p, "[create 2d sprite frame res]", [this](auto) {
		auto&& res = xx::Make<FishManage::Res2d>();
		res->name = "unnamed_res";
		res->shadowScale = 1;
		res->shadowOffsetX = 3;
		res->shadowOffsetY = 3;
		EditRes2d(res);
	});

	p.x += GetWidth(b1) + lineHeight * 3;
	auto b2 = CreateButton(p, "[create spine res]", [this](auto) {
		/* EditResSpine(r); */ 
	});

	p.x += GetWidth(b2) + lineHeight * 3;
	auto b3 = CreateButton(p, "[create 3d c3b res]", [this](auto) {
		/* EditRes3d(r); */
	});

	p.x += GetWidth(b3) + lineHeight * 3;
	auto b4 = CreateButton(p, "[create combine res]", [this](auto) {
		auto&& res = xx::Make<FishManage::ResCombine>();
		res->name = "unnamed_res";
		EditResCombine(res);
	});

	//        ->          [Back]
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bBack = CreateButton(p, "[Back]", [this](auto) {
		Welcome();
	});
	bBack->setAnchorPoint({ 1, 0.5 });


	// ÿ�� item ���ࣺ
	/*
+---------+ name: resName
|         | type: 2d? spine? 3d? combine?
| preview | actions: ���ŷָ��г�
|         | coin1:       coin2:
+---------+ [Edit]                     [Delete]
	*/

	// �� sv ��ʾ���� �� ���
	p.x = margin;
	p.y = H - lineHeight;
	cocos2d::Size svSize(W - margin * 2, H - lineHeight * 2);

	// item �߶�
	auto itemHeight = lineHeight * 5;

	// �����ܸ߶�
	auto svContentHeight = margin + (itemHeight + margin) * data.ress.size();
	if (svContentHeight < svSize.height) {
		svContentHeight = svSize.height;
	}

	// ���� ����size, ����size ���� sv
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight });

	// �� sv ��� items
	// sv ����Ķ�������ֱ�ӷ���, �����һ�� node ɶ�ģ��ᵼ�²���ʧ��
	for (size_t i = 0; i < data.ress.size(); ++i) {
		auto&& res = data.ress[i];

		// ÿ item �ڲ� 0, 0 ����ʼ�������Ͻ�. �����Ǹ�����
		cocos2d::Vec2 pos(margin, svContentHeight - margin - (itemHeight + margin) * i);

		// ���� ����Ԥ��( ��һ������ )
		p.x = pos.x + itemHeight / 2;
		p.y = pos.y - itemHeight / 2;
		CreateResPreview(p, { itemHeight ,itemHeight }, res, sv);

		// ��������Ԥ��ͼ�Ҳ�Ķ���
		// name
		{
			p.x = pos.x + itemHeight + margin;
			p.y = pos.y - lineHeight / 2;
			CreateLabelPair(p, "name: ", xx::ToString(res->name), sv);
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
			CreateLabelPair(p, "type: ", typeName, sv);
		}

		// actions: .........
		{
			p.y -= lineHeight;
			auto tk = CreateLabel(p, "actions: ", sv);

			p.x += GetWidth(tk);
			for (auto&& action : res->actions) {
				auto tv = CreateLabel(p, xx::ToString(action->name, ((&action == &res->actions.back()) ? "" : ", ")), sv);
				tv->setColor(yellow);
				p.x += GetWidth(tv) + margin;
			}
		}

		// lastUpdateTime
		{
			p.x = pos.x + itemHeight + margin;
			p.y -= lineHeight;
			CreateLabelPair(p, "lastUpdateTime: ", xx::ToString(xx::Epoch10mToTimePoint(res->lastUpdateTime)), sv);
		}

		// [Edit Clone]        [Edit]        [Delete]
		{
			p.x = pos.x + itemHeight + margin;
			p.y -= lineHeight;
			auto b1 = CreateButton(p, "[Edit Clone]", [this, res, sv](auto) {
				manageResourcesScrolledPercentVertical = sv->getScrolledPercentVertical();
				auto&& cloneRes = oh.Clone(res);
				if (auto&& r = xx::As<FishManage::Res2d>(cloneRes)) {
					EditRes2d(r);
				}
				else if (auto&& r = xx::As<FishManage::ResSpine>(cloneRes)) {
					// EditResSpine(r);
				}
				else if (auto&& r = xx::As<FishManage::Res3d>(cloneRes)) {
					// EditRes3d(r);
				}
				else if (auto&& r = xx::As<FishManage::ResCombine>(cloneRes)) {
					EditResCombine(r);
				}
				else {
					// 
				}
			}, sv);

			//p.x += GetWidth(b1) + lineHeight * 5;
			//auto b2 = CreateButton(p, "[Edit]", [this, res, sv](auto) {
			//	manageResourcesScrolledPercentVertical = sv->getScrolledPercentVertical();
			//	if (auto&& r = xx::As<FishManage::Res2d>(res)) {
			//		EditRes2d(r);
			//	}
			//	else if (auto&& r = xx::As<FishManage::ResSpine>(res)) {
			//		// EditResSpine(r);
			//	}
			//	else if (auto&& r = xx::As<FishManage::Res3d>(res)) {
			//		// EditRes3d(r);
			//	}
			//	else if (auto&& r = xx::As<FishManage::ResCombine>(res)) {
			//		EditResCombine(r);
			//	}
			//	else {
			//		// 
			//	}
			//}, sv);

			p.x += GetWidth(b1) + lineHeight * 10;
			auto b3 = CreateButton(p, "[Delete]", [this, i, res, sv](auto) {
				if (!xx::Is<FishManage::ResCombine>(res)) {
					// ���ü��: ������������ items ����. ��������ɾ
					for (auto&& r : data.ress) {
						if (auto&& o = xx::As<FishManage::ResCombine>(r)) {
							for (auto&& item : o->items) {
								if (item.res.lock() == res) {
									PopupMessage(xx::ToString("delete failed. the res is referenced by ", r->name));
									return;
								}
							}
						}
					}
				}
				manageResourcesScrolledPercentVertical = sv->getScrolledPercentVertical();
				data.ress.erase(data.ress.begin() + i);
				SaveData();
				ManageResources();
			}, sv);
		}
	}

	//// ��㻭Щ 3d ģ�� �� scroll view
	//for (size_t i = 0; i < 10; ++i) {
	//	auto o = CreateOrc({ (float)cocos2d::random(0, (int)svSize.width), (float)cocos2d::random(0, (int)svContentHeight) }, cocos2d::random(0, 360), sv);
	//}

	// �� sv ��ȷ���� 3d ����
	sv->setGlobalZOrder(1);

	// ��ԭ����λ��
	if (svContentHeight > svSize.height) {
		sv->jumpToPercentVertical(manageResourcesScrolledPercentVertical);
	}
	else {
		manageResourcesScrolledPercentVertical = 0;
	}
}
