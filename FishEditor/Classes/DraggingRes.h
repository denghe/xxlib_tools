#pragma once
#include "cocos2d.h"
#include "FishManage_class_lite.h"

struct MainScene;
struct DraggingRes : public cocos2d::Node {
	using cocos2d::Node::Node;
	static DraggingRes* create();

	// ָ���������ģ�����ȡ��ʾ����. �ⲿ��ֵ
	MainScene* scene = nullptr;

	// ָ�������ʾ��Դ�����Ľڵ�. �ⲿ��������ֵ
	cocos2d::Node* item = nullptr;

	// ���̸ı�뾶�� delta �˷�ϵ��
	float rChange = 0;

	// �ϴ� touch λ��
	cocos2d::Vect lastPos;

	// �Ƿ����� touch
	bool touching = false;

	// ��ʼ�� touch event listener, ʵ����ק����. �ϵ�ĳ�������ɾ��
	bool init() override;

	// ��Ӧ���̰��� + - ���ϸı��С��Ч��
	void update(float delta) override;
};
