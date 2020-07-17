#pragma once
#include "cocos2d.h"

struct HelloWorld;
struct Circle : public cocos2d::Node {
	using cocos2d::Node::Node;
	static Circle* create();

	// ָ���������ģ�����ȡ��ʾ����
	HelloWorld* scene;

	// ���ڻ��ƵĽڵ�( ֱ�Ӽ̳����ƺ��ᵼ�³��ֻ��� bug )
	cocos2d::DrawNode* drawNode = nullptr;

	cocos2d::Color4F color = cocos2d::Color4F::RED;

	// ��ǰ�뾶
	float r = 0;
	float rChange = 0;

	// �ϴ� touch λ��
	cocos2d::Vect lastPos;

	// �Ƿ����� touch
	bool touching = false;

	// ��ʼ�� touch event listener, ʵ����ק����. �ϵ�ĳ�������ɾ��
	bool init() override;

	// ���� r �뾶������ʾ
	void Draw(float const& r);

	// ��Ӧ���̰��� + - ���ϸı��С��Ч��
	void update(float delta) override;
};
