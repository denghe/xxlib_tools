#include "MainScene.h"

void MainScene::ChoosePList(std::shared_ptr<FishManage::Res2d> const& res2d) {
	removeAllChildren();

	// ��� create 2d sprite frame res2d ֮����ת����ѡ�� plist �ļ�ҳ

	// ����
	CreateBG(this);

	// ��λ����Ļ���Ϸ���λ��
	cocos2d::Vec2 p(margin, H - lineHeight / 2);

	// ���Ϸ�˵������
	CreateLabel(p, "please multi select every plist file include your sprite frames:");

	// ���·����谴ť
	p.x = W - margin;
	p.y = lineHeight / 2;
	auto bNext = CreateButton(p, "[Save & Exit]", [this, res2d](auto) {
		// ���� checkbox. ����Ӧ�� plist file names ��������
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


	// �������� .plist
	std::vector<std::filesystem::path> paths;
	for (auto&& entry : std::filesystem::directory_iterator(resPath)) {
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
	auto&& sv = CreateSV(p, svSize, { svSize.width, svContentHeight });

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

		p.x += GetWidth(cb) + margin;
		CreateLabel(p, fn, sv);
	}

	// �� sv ��ȷ���� 3d ����
	sv->setGlobalZOrder(1);
}
