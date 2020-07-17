#pragma once
#include "cocos2d.h"

struct HelloWorld;
struct Circle : public cocos2d::Node {
	using cocos2d::Node::Node;
	static Circle* create();

	// 指向总上下文，方便取显示参数
	HelloWorld* scene;

	// 用于绘制的节点( 直接继承它似乎会导致出现绘制 bug )
	cocos2d::DrawNode* drawNode = nullptr;

	cocos2d::Color4F highlightColor = cocos2d::Color4F::BLUE;
	cocos2d::Color4F defaultColor = cocos2d::Color4F::RED;
	cocos2d::Color4F lineColor = cocos2d::Color4F::GREEN;
	cocos2d::Color4F color = cocos2d::Color4F::RED;

	// true: circle 变 point. 半径不可改变. 自动查找 上一个 point, 连线
	bool pointMode = false;

	// 当前半径
	float r = 0;

	// 键盘改变半径的 delta 乘法系数
	float rChange = 0;

	// 上次 touch 位置
	cocos2d::Vect lastPos;

	// 是否正在 touch
	bool touching = false;

	// 初始化 touch event listener, 实现拖拽功能. 拖到某区域就是删除
	bool init() override;

	// 根据 r 半径更新显示
	void Draw(float const& r);

	// 找到上一个 Circle 与其连线( pointMode == true )
	void DrawLine();

	// 响应键盘按下 + - 不断改变大小的效果
	void update(float delta) override;
};
