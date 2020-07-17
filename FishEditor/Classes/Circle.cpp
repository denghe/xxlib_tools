#include "Circle.h"
#include "HelloWorldScene.h"

Circle* Circle::create() {
	auto o = new (std::nothrow) Circle();
	if (o && o->init()) {
		o->autorelease();
		return o;
	}
	CC_SAFE_DELETE(o);
	return nullptr;
}

bool Circle::init() {
	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](cocos2d::Touch* t, cocos2d::Event* e) {
		auto&& tL = t->getLocation();
		auto&& p = convertToNodeSpace(tL);
		// 如果点击在圈内则认为选中
		if (p.distance({ 0,0 }) <= r) {
			touching = true;
			scene->currCircle = this;
			lastPos = p;
			color = cocos2d::Color4F::BLUE;
			Draw(r);
			return true;
		}
		return false;
	};
	touchListener->onTouchMoved = [this](cocos2d::Touch* t, cocos2d::Event* e) {
		if (!touching) return false;
		auto&& tL = t->getLocation();
		auto&& p = convertToNodeSpace(tL);
		auto&& diff = p - lastPos;
		setPosition(getPosition() + diff);
		return true;
	};
	touchListener->onTouchEnded = [this](cocos2d::Touch* t, cocos2d::Event* e) {
		// 如果拖拽到蓝线条外，就自杀
		touching = false;
		scene->currCircle = nullptr;
		color = cocos2d::Color4F::RED;
		Draw(r);
		auto&& p = getPosition();
		if (p.x < -scene->DW_2 || p.x > scene->DW_2 || p.y < -scene->DH_2 || p.y > scene->DH_2) {
			removeFromParentAndCleanup(true);
		}
		return true;
	};
	touchListener->onTouchCancelled = touchListener->onTouchEnded;
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	drawNode = cocos2d::DrawNode::create();
	addChild(drawNode);

	return true;
}

void Circle::Draw(float const& r) {
	this->r = r;
	drawNode->clear();
	drawNode->drawCircle({0,0}, r, 0, 100, false, color);
}

void Circle::update(float delta) {
	if (rChange != 0) {
		r += delta * rChange;
	}
	Draw(r);
}
