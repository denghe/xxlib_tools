#include "MainScene.h"

ActionPlayer_SpriteFrame* ActionPlayer_SpriteFrame::create() {
	auto o = new (std::nothrow) ActionPlayer_SpriteFrame();
	if (o && o->init()) {
		o->autorelease();
		return o;
	}
	CC_SAFE_DELETE(o);
	return nullptr;
}

void ActionPlayer_SpriteFrame::SetActionData(FishManage::FrameAction const& action) {
	// 预加载 plist
	std::set<std::string> plists;
	for (auto&& ptr : action.pictures) {
		if (auto&& picture = ptr.lock()) {
			if (auto&& plistFile = picture->atPList.lock()) {
				plists.insert(plistFile->name);
			}
		}
	}
	for (auto&& fn : plists) {
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fn);
	}
	this->action = action;
	SetFrameRate(action.frameRate);
}

void ActionPlayer_SpriteFrame::SetFrameRate(float const& frameRate) {
	this->frameRate = frameRate;
	this->ticksPerFrame = 1.0 / frameRate;
}

void ActionPlayer_SpriteFrame::SetAutoRepeat(bool const& autoRepeat) {
	this->autoRepeat = autoRepeat;
}

void ActionPlayer_SpriteFrame::Play(int const& beginIndex) {
	if (action.pictures.empty()) return;
	frameIndex = beginIndex;
	Draw();
	ticksPool = 0;
	scheduleUpdate();
}

void ActionPlayer_SpriteFrame::Stop() {
	unscheduleUpdate();
}

void ActionPlayer_SpriteFrame::Next() {
	++frameIndex;
	if (frameIndex >= (int)action.pictures.size()) {
		frameIndex = 0;
		if (!autoRepeat) {
			unscheduleUpdate();
		}
	}
	Draw();
}

void ActionPlayer_SpriteFrame::Draw() {
	if (auto&& picture = action.pictures[frameIndex].lock()) {
		if (auto&& plistFile = picture->atPList.lock()) {
			setSpriteFrame(picture->name);
		}
		else {
			setTexture(picture->name);
		}
	}
	// todo: 帧已失效？用替代图？
}

void ActionPlayer_SpriteFrame::update(float delta) {
	ticksPool += delta;
	while (ticksPool > ticksPerFrame) {
		ticksPool -= ticksPerFrame;
		Next();
	}
}

bool ActionPlayer_SpriteFrame::IsInside(cocos2d::Vec2 const& p) {
	if (auto&& frame = action.pictures[frameIndex].lock()) {
		auto&& cd = frame->cdclps;
		auto&& s = getScale();
		if (p.distance({ cd.maxCDCircle.x * s, cd.maxCDCircle.y * s }) <= cd.maxCDCircle.r * s) {
			if (cd.cdCircles.empty()) return true;
			for (auto&& c : cd.cdCircles) {
				if (p.distance({ c.x * s, c.y * s }) <= c.r * s) return true;
			}
		}
	}
	return false;
}
