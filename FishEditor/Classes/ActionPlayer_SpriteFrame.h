#pragma once
#include "cocos2d.h"
#include "FishManage_class_lite.h"

struct ActionPlayer_SpriteFrame : public cocos2d::Sprite {
	using cocos2d::Sprite::Sprite;
	static ActionPlayer_SpriteFrame* create();

	// 动作数据上下文
	std::shared_ptr<FishManage::Action2d> action2d;

	// 播放状态相关
	bool autoRepeat = true;
	int frameIndex = 0;

	// 帧率（每秒帧数）
	float frameRate = 30;

	// 每帧耗时（秒）
	float ticksPerFrame = 1.0 / frameRate;

	// 耗时池（稳帧/补帧用）
	float ticksPool = 0;

	// 填充动作数据上下文并预加载 plist
	void SetActionData(std::vector<std::string> const& plistFileNames, std::shared_ptr<FishManage::Action2d> const& action2d);

	// 设置播放参数
	void SetFrameRate(float const& frameRate = 30);
	void SetAutoRepeat(bool const& autoRepeat);

	// 开始播放( Draw & scheduleUpdate )
	void Play(int const& beginIndex = 0);

	// unscheduleUpdate
	void Stop();

	// 前进一帧( ++frameIndex & Draw )
	void Next();

	// 根据当前 frameIndex 绘制相应内容
	void Draw();

	// 自动驱动 Next
	void update(float delta) override;

	// 碰撞检测. 判断某个点是否位于 cdCircles 内
	bool IsInside(cocos2d::Vec2 const& p);
};
