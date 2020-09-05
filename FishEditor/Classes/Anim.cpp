#include "MainScene.h"
#include "Anim.h"
#include "FileExts_class_lite.ajson.h"

// todo: 以后再补合法性检测, 异常处理

Anim_Frames::~Anim_Frames() {
	if (sprite) {
		sprite->removeFromParentAndCleanup(true);
	}
}
int Anim_Frames::Load() {
	// 加载文件数据
	LoadJson(file, fileName);
	// 缓存相关 plists
	auto&& sfc = cocos2d::SpriteFrameCache::getInstance();
	for (auto&& fn : file.plists) {
		sfc->addSpriteFramesWithFile(fn);
	}
	// 设置当前动作
	action = &file.actions[0];
	return 0;
}
void Anim_Frames::SetAction(size_t const& index) {
	action = &file.actions[index];
	totalElapsedSeconds = 0;
	frameIndex = 0;
}
int Anim_Frames::Update(float const& elapsedSeconds) {
	totalElapsedSeconds += elapsedSeconds;
	if (totalElapsedSeconds >= action->totalSeconds) {
		if (loop) {
			totalElapsedSeconds = fmodf(totalElapsedSeconds, action->totalSeconds);
			frameIndex = 0;
		}
		else {
			totalElapsedSeconds = action->totalSeconds;
			frameIndex = action->frames.size() - 1;
			return 1;
		}
	}
	while (action->frames.size() > frameIndex + 1 && action->frames[frameIndex + 1].time <= totalElapsedSeconds) {
		++frameIndex;
	}
	return 0;
}
void Anim_Frames::Draw() {
	if (!sprite) {
		sprite = cocos2d::Sprite::create();
	}
	sprite->setSpriteFrame(action->frames[frameIndex].picName);
}


Anim_Atlas::~Anim_Atlas() {}
int Anim_Atlas::Load() { return 0; }
void Anim_Atlas::SetAction(size_t const& index) {}
int Anim_Atlas::Update(float const& elapsedSeconds) { return 0; }
void Anim_Atlas::Draw() {}


Anim_C3b::~Anim_C3b() {}
int Anim_C3b::Load() { return 0; }
void Anim_C3b::SetAction(size_t const& index) {}
int Anim_C3b::Update(float const& elapsedSeconds) { return 0; }
void Anim_C3b::Draw() {}


// 根据文件名加载指定动画. 根据扩展名路由创建 Anim_Frames / Anim_Atlas / Anim_C3b
std::shared_ptr<Anim> CreateAnim(std::string const& fn, cocos2d::Node* const& container) {
	// todo
	return nullptr;
}




std::shared_ptr<AnimExt> CreateAnimExt(std::string const& fn, cocos2d::Node* const& container) {
	// todo
	return nullptr;
}



//#include "xx_lua.h"
//#include <iostream>
//#include <chrono>
//namespace XL = xx::Lua;


//
//int Anim::Load(std::string const& fn) {
//	animType = AnimTypes::Unknown;
//	std::string ofn;
//
//	// 检查文件名是否合法, 分析文件类型
//	const auto exts = xx::GetFileNameExts(fn);
//	if (exts.first == ".frames") {
//		animType = AnimTypes::Frames;
//		ofn = fn;
//	}
//	else if (exts.first == ".ext") {
//		if (exts.second == ".atlas") {
//			animType = AnimTypes::Atlas;
//			ofn = fn.substr(0, fn.size() - exts.first.size());
//		}
//		else if (exts.second == ".c3b") {
//			animType = AnimTypes::C3b;
//			ofn = fn.substr(0, fn.size() - exts.first.size());
//		}
//		else return -2;
//	}
//	else return -3;
//
//	xx::MakeTo(anim);
//	if (int r = LoadJson(*anim, fn)) return r;
//	if (anim->actions.empty()) return -4;
//	action = &anim->actions[0];
//
//	switch (animType) {
//	case AnimTypes::Frames:
//		// 数据全在 anim
//		break;
//	case AnimTypes::Atlas:
//		// todo: 加载源文件
//		// todo: 加载第一个动作?
//		break;
//	case AnimTypes::C3b:
//		// todo: 加载源文件
//		// todo: 加载第一个动作?
//		break;
//	}
//}
//
//int Anim::ActionEnd() {
//	// 当前逻辑是 repeat
//	totalElapsedSeconds = 0;
//	lpsCursor = 0;
//	cdsCursor = 0;
//	ssCursor = 0;
//	fsCursor = 0;
//	return 0;
//}
//
//int Anim::Move(float const& distance) {
//	if (!pathway) return 0;
//	// 根据 speedScale 来揣测移动方向
//	if (speedScale == 0) return 0;
//	else if (speedScale > 0) {
//		pathway->Forward(distance, pathwayI, pathwayD, pos, angle);
//	}
//	else {
//		pathway->Backward(distance, pathwayI, pathwayD, pos, angle);
//	}
//	return 0;
//}
//
//int Anim::Update(float elapsedSeconds) {
//	float d = 0;
//	// 判断下一个 tp 时间是否在范围内. 如果没有下一个 tp 或 时间点不在当前范围，则直接计算并返回
//	// 如果有，则计算当前时间点到它的时间的跨度，应用该时间点数据并计算一波，从 elapsedSeconds 扣除该跨度
//	// 如果 elapsedSeconds 还有剩余，则跳转到开头重复这一过程
//	auto Calc = [&](float es) {
//		auto&& ss = action->ss;
//		if (ss.empty()) return;
//	LabBegin:
//		auto next = ss.data() + ssCursor + 1;   // 跳过越界检查
//		if (ss.size() > ssCursor + 1 && next->time <= totalElapsedSeconds + es) {
//			auto es = next->time - totalElapsedSeconds;
//			d += ss[ssCursor++].speed * es;
//			es -= es;
//			totalElapsedSeconds = next->time;
//			goto LabBegin;
//		}
//		else {
//			totalElapsedSeconds += es;
//			d += ss[ssCursor].speed * es;
//		}
//	};
//LabBegin:
//	// 计算距离
//	// 判断传入时长是否会超出当前 timeLine 的范围. 如果有超出则切割计算
//	auto left = action->totalSeconds - totalElapsedSeconds;
//	if (elapsedSeconds > left) {
//		elapsedSeconds -= left;
//		Calc(left);
//		if (int r = ActionEnd()) return r;
//		goto LabBegin;
//	}
//	else {
//		Calc(elapsedSeconds);
//		// 同步 锁定，碰撞，帧 游标( 此时 totalElapsedSeconds 已经 + 了 elapsedSeconds )
//		while (action->lps.size() > lpsCursor + 1 && action->lps[lpsCursor + 1].time <= totalElapsedSeconds) {
//			++lpsCursor;
//		}
//		while (action->cds.size() > cdsCursor + 1 && action->cds[cdsCursor + 1].time <= totalElapsedSeconds) {
//			++cdsCursor;
//		}
//		while (action->fs.size() > fsCursor + 1 && action->fs[fsCursor + 1].time <= totalElapsedSeconds) {
//			++fsCursor;
//		}
//	}
//	// 用算出来的距离在 pathway 上移动
//	return Move(d);
//}
//
//// 判断 点(r == 0) 或 圆 是否和单个 cdCircle 相交
//bool Anim::IsIntersect(FileExts::CDCircle const& c, float const& x, float const& y, float const& r) {
//	return (c.x - x) * (c.x - x) + (c.y - y) * (c.y - y) <= (c.r + r) * (c.r + r);
//}
//
//// 判断 点(r == 0) 或 圆 是否和某 cdCircle 相交( touch, bullet hit 判断需要 )
//bool Anim::IsIntersect(float const& x, float const& y, float const& r) const {
//	if (!action || action->cds.empty()) return false;
//	auto&& cd = action->cds[cdsCursor];
//	if (!IsIntersect(cd.maxCDCircle, x, y, r)) return false;
//	for (auto&& c : cd.cdCircles) {
//		if (IsIntersect(c, x, y, r)) return true;
//	}
//	return false;
//}
//
//bool Anim::Lockable() const {
//	if (!action || action->lps.empty()) return false;
//	// todo
//	return true;
//}
//
//std::tuple<float, float> Anim::GetLockPoint() const {
//	std::tuple<float, float> rtv;
//	if (!action || action->lps.empty()) return rtv;
//	// todo: 需结合坐标以及屏幕裁剪范围来算
//	std::get<0>(rtv) = action->lps[lpsCursor].mainLockPoint.x;
//	std::get<1>(rtv) = action->lps[lpsCursor].mainLockPoint.y;
//	return rtv;
//}
//






//// Lua 类动画基类, 虚函数调用到和 lua 函数绑定的 std::function
//struct AnimLua : AnimBase {
//    lua_State *L;
//    std::string scriptName;
//    // AnimXxxx 容器? lua 可能创建 n 个 并控制它们. 通常创建 1 个
//
//    // 加载脚本并映射函数
//    AnimLua(lua_State *const &L, std::string scriptName) : L(L), scriptName(std::move(scriptName)) {
//        // todo: load script, bind func
//    };
//
//    std::function<void(std::string const &actionName)> onSetAction;
//
//    void SetAction(std::string const &actionName) override {
//        onSetAction(actionName);
//    }
//
//    // more
//};


//
//
//int main() {
//    xx::Lua::State L;
//    if (auto r = XL::Try(L, [&] {
//        int x = 0;
//        XL::SetGlobal(L, "beep", [&x] { return ++x; });
//
//        auto t = std::chrono::steady_clock::now();
//        auto &&Show = [&] {
//            std::cout << "x = " << x << " ms = " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - t).count() << std::endl;
//            t = std::chrono::steady_clock::now();
//        };
//
//        luaL_dostring(L, R"(
//for i = 1, 1000000 do
//    beep()
//end
//)");
//        Show();
//
//        std::function<int()> f;
//        XL::GetGlobal(L, "beep", f);
//        for (int i = 0; i < 1000000; ++i) {
//            f();
//        }
//        Show();
//
//    })) {
//        std::cout << "error! " << r.m << std::endl;
//    }
//}
//
