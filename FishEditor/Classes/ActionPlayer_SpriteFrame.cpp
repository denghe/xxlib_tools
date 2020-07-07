#include "ActionPlayer_SpriteFrame.h"

ActionPlayer_SpriteFrame* ActionPlayer_SpriteFrame::create() {
	auto o = new (std::nothrow) ActionPlayer_SpriteFrame();
	if (o && o->init()) {
		o->autorelease();
		return o;
	}
	CC_SAFE_DELETE(o);
	return nullptr;
}

void ActionPlayer_SpriteFrame::SetActionData(std::vector<std::string> const& plistFileNames, FishManage::Fish_2D_Action const& actionData) {
	// Ô¤¼ÓÔØ plist
	for (auto&& fn : plistFileNames) {
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fn);
	}
	this->actionData = actionData;
}

void ActionPlayer_SpriteFrame::SetFrameRate(float const& frameRate) {
	this->frameRate = frameRate;
	this->ticksPerFrame = 1.0 / frameRate;
}

void ActionPlayer_SpriteFrame::SetAutoRepeat(bool const& autoRepeat) {
	this->autoRepeat = autoRepeat;
}

void ActionPlayer_SpriteFrame::Play(int const& beginIndex) {
	if (actionData.frames.empty()) return;
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
	if (frameIndex >= (int)actionData.frames.size()) {
		frameIndex = 0;
		if (!autoRepeat) {
			unscheduleUpdate();
		}
	}
	Draw();
}

void ActionPlayer_SpriteFrame::Draw() {
	this->setSpriteFrame(actionData.frames[frameIndex].spriteFrameName);
}

void ActionPlayer_SpriteFrame::update(float delta) {
	ticksPool += delta;
	while (ticksPool > ticksPerFrame) {
		ticksPool -= ticksPerFrame;
		Next();
	}
}
