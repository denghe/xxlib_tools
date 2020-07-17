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
		// ��������Ȧ������Ϊѡ��
		if (p.distance({ 0,0 }) <= r) {
			touching = true;
			scene->currCircle = this;
			lastPos = p;
			color = highlightColor;
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
		if (pointMode) {
			Draw(r);
		}
		return true;
	};
	touchListener->onTouchEnded = [this](cocos2d::Touch* t, cocos2d::Event* e) {
		// �����ק���������⣬����ɱ
		touching = false;
		scene->currCircle = nullptr;
		color = defaultColor;
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
	DrawLine();
	if (pointMode) {
		drawNode->drawSolidCircle({ 0,0 }, r, 0, 100, color);
	}
	else {
		drawNode->drawCircle({ 0,0 }, r, 0, 100, false, color);
	}
}

void Circle::DrawLine() {
	if (!pointMode) return;

	// ���˳�����ͬ��
	std::vector<Circle*> ncs;
	for (auto&& n : getParent()->getChildren()) {
		if (auto&& nc = dynamic_cast<Circle*>(n)) {
			ncs.push_back(nc);
		}
	}

	// �����ǰ 2 ����ֱ���˳�
	if (ncs[0] == this || ncs[1] == this) return;

	// �ҵ��Լ����±�
	size_t i = 1;
	for (; i < ncs.size(); ++i) {
		if (ncs[i] == this) break;
	}

	// ��λ����һ��
	auto&& p = ncs[i - 1];
	auto&& pPos = p->getPosition();
	drawNode->drawLine({ 0,0 }, pPos - getPosition(), lineColor);

	// ��λ����һ��
	if (i + 1 < ncs.size()) {
		ncs[i + 1]->Draw(ncs[i + 1]->r);
	}
}

void Circle::update(float delta) {
	if (rChange != 0) {
		r += delta * rChange;
	}
	Draw(r);
}
