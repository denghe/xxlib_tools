#pragma once
#include "cocos2d.h"
#include "FishManage_class_lite.h"

struct MainScene;
struct DraggingRes : public cocos2d::Node {
	using cocos2d::Node::Node;
	static DraggingRes* create();

	// 指向总上下文，方便取显示参数. 外部赋值
	MainScene* scene = nullptr;

	// 指向具体显示资源动画的节点. 外部创建并赋值
	cocos2d::Node* item = nullptr;

	// 键盘改变半径的 delta 乘法系数
	float rChange = 0;

	// 上次 touch 位置
	cocos2d::Vect lastPos;

	// 是否正在 touch
	bool touching = false;

	// 初始化 touch event listener, 实现拖拽功能. 拖到某区域就是删除
	bool init() override;

	// 响应键盘按下 + - 不断改变大小的效果
	void update(float delta) override;
};
