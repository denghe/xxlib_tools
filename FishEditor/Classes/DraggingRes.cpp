#include "DraggingRes.h"
#include "MainScene.h"

DraggingRes* DraggingRes::create() {
	auto o = new (std::nothrow) DraggingRes();
	if (o && o->init()) {
		o->autorelease();
		return o;
	}
	CC_SAFE_DELETE(o);
	return nullptr;
}

bool DraggingRes::init() {
	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](cocos2d::Touch* t, cocos2d::Event* e) {
		auto&& tL = t->getLocation();
		auto&& p = convertToNodeSpace(tL);
		// 碰撞检测. 如果点击在当前帧 任意cdCircles圈内 则认为选中
		if (auto&& o = dynamic_cast<ActionPlayer_SpriteFrame*>(item)) {
			if (o->IsInside(p)) {
					touching = true;
					scene->currDraggingRes = this;
					lastPos = tL;
					return true;
			}
		}
		// else if ( ...... )
		return false;
	};
	touchListener->onTouchMoved = [this](cocos2d::Touch* t, cocos2d::Event* e) {
		if (!touching) return false;
		auto&& tL = t->getLocation();
		auto&& diff = tL - lastPos;
		lastPos = tL;
		setPosition(getPosition() + diff);
		return true;
	};
	touchListener->onTouchEnded = [this](cocos2d::Touch* t, cocos2d::Event* e) {
		if (!touching) return false;
		// 如果拖拽到蓝线条外，就自杀
		touching = false;
		scene->currDraggingRes = nullptr;
		auto&& p = getPosition();
		if (p.x < -scene->DW_2 || p.x > scene->DW_2 || p.y < -scene->DH_2 || p.y > scene->DH_2) {
			removeFromParentAndCleanup(true);
		}
		return true;
	};
	touchListener->onTouchCancelled = touchListener->onTouchEnded;
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

void DraggingRes::update(float delta) {
	if (rChange != 0) {
		auto scale = getScale();
		scale += delta * rChange;
		if (rChange < 0 && scale < 0.1) {
			scale = 0.1f;
		}
		setScale(scale);
	}
}
