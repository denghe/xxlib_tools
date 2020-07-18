#pragma once
#include "cocos2d.h"
#include "FishManage_class_lite.h"

struct ActionPlayer_SpriteFrame : public cocos2d::Sprite {
	using cocos2d::Sprite::Sprite;
	static ActionPlayer_SpriteFrame* create();

	// ��������������
	std::shared_ptr<FishManage::Action2d> action2d;

	// ����״̬���
	bool autoRepeat = true;
	int frameIndex = 0;

	// ֡�ʣ�ÿ��֡����
	float frameRate = 30;

	// ÿ֡��ʱ���룩
	float ticksPerFrame = 1.0 / frameRate;

	// ��ʱ�أ���֡/��֡�ã�
	float ticksPool = 0;

	// ��䶯�����������Ĳ�Ԥ���� plist
	void SetActionData(std::vector<std::string> const& plistFileNames, std::shared_ptr<FishManage::Action2d> const& action2d);

	// ���ò��Ų���
	void SetFrameRate(float const& frameRate = 30);
	void SetAutoRepeat(bool const& autoRepeat);

	// ��ʼ����( Draw & scheduleUpdate )
	void Play(int const& beginIndex = 0);

	// unscheduleUpdate
	void Stop();

	// ǰ��һ֡( ++frameIndex & Draw )
	void Next();

	// ���ݵ�ǰ frameIndex ������Ӧ����
	void Draw();

	// �Զ����� Next
	void update(float delta) override;

	// ��ײ���. �ж�ĳ�����Ƿ�λ�� cdCircles ��
	bool IsInside(cocos2d::Vec2 const& p);
};
