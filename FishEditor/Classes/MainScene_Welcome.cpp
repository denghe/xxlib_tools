#include "MainScene.h"

void MainScene::Welcome() {
	removeAllChildren();

	// ��ҳ

	// ����
	CreateBG(this);

	// �Ϸ�Ϊ���࣬���ˣ����� �� ��ѯ��壬�Լ� ���� xxxxx        ��ť
	// �������ɷ�ҳ����ʽ����ֹһ���Լ���̫�࣬�ٶ���
	// ҳ�� ҳ�������·����Լ��˳�
	// todo:  Filter: [All]  [Sound] 

	// [Browse Files]      [Browse Resources]      [Browse Fishs]
	cocos2d::Vec2 p(margin, H - lineHeight / 2);
	auto bBR = CreateButton(p, "[Manage Files]", [this](auto) {
		//ManageResources();
	});

	// ����Դֱ�ӷ������? 
	//p.x += GetWidth(bBR) + lineHeight * 3;
	//auto bBR = CreateButton(p, "[Manage Resources]", [this](auto) {
	//	//ManageResources();
	//});

	p.x += GetWidth(bBR) + lineHeight * 3;
	auto bBF = CreateButton(p, "[Manage Fishs]", [this](auto) {
		//ManageFishs();
	});

	// todo: δ��Ԥ�ڹ��ܣ�������飿���з��������õ���������Դ�ļ����������

	//// ��ʾһЩ��� data �� summary ��Ϣ
	//p.x = margin;
	//p.y -= lineHeight;
	//CreateLabelPair(p, "ress.size() = ", xx::ToString(data.ress.size()));

	//p.y -= lineHeight;
	//CreateLabelPair(p, "fishs.size() = ", xx::ToString(data.fishs.size()));

	// todo: ����ͳ�ƣ�




	// ֱ�����������ļ���
}
