#include "MainScene.h"
#include "Anim.h"
#include "Pathway.h"
//#include "xx_object.h"
//#include "xx_lua.h"
//#include <iostream>
//#include <chrono>
//
//namespace XL = xx::Lua;

// 内部函数. 被 Update 调用。确保传入的 经历时长 不会超出当前 timeLine 的范围. 返回距离
float Anim::UpdateCore(float elapsedSeconds) {
	// 判断下一个 tp 时间是否在范围内. 如果没有下一个 tp 或 时间点不在当前范围，则直接计算并返回
	// 如果有，则计算当前时间点到它的时间的跨度，应用该时间点数据并计算一波，从 elapsedSeconds 扣除该跨度
	// 如果 elapsedSeconds 还有剩余，则跳转到开头重复这一过程
	float rtv = 0;
	auto&& ss = action->ss;
	if (ss.empty()) return rtv;
LabBegin:
	auto next = ss.data() + ssCursor + 1;   // 跳过越界检查
	if (ss.size() > ssCursor + 1 && next->time <= totalElapsedSeconds + elapsedSeconds) {
		auto es = next->time - totalElapsedSeconds;
		rtv += ss[ssCursor++].speed * es;
		elapsedSeconds -= es;
		totalElapsedSeconds = next->time;
		goto LabBegin;
	}
	else {
		totalElapsedSeconds += elapsedSeconds;
		rtv += ss[ssCursor].speed * elapsedSeconds;
	}
	return rtv;
}


// 只实现了更新指针和计算移动距离。更新显示要覆写
float Anim::Update(float elapsedSeconds) {
	float rtv = 0;
LabBegin:
	// 计算距离
	// 判断传入时长是否会超出当前 timeLine 的范围. 如果有超出则切割计算
	auto left = action->totalSeconds - totalElapsedSeconds;
	if (elapsedSeconds > left) {
		elapsedSeconds -= left;
		rtv += UpdateCore(left);
		if (!OnFinish()) return rtv;
		goto LabBegin;
	}
	else {
		rtv += UpdateCore(elapsedSeconds);
		// 同步 锁定，碰撞，帧 游标( 此时 totalElapsedSeconds 已经 + 了 elapsedSeconds )
		while (action->lps.size() > lpsCursor + 1 && action->lps[lpsCursor + 1].time <= totalElapsedSeconds) {
			++lpsCursor;
		}
		while (action->cds.size() > cdsCursor + 1 && action->cds[cdsCursor + 1].time <= totalElapsedSeconds) {
			++cdsCursor;
		}
		while (action->fs.size() > fsCursor + 1 && action->fs[fsCursor + 1].time <= totalElapsedSeconds) {
			++fsCursor;
		}
	}
	return rtv;
}

bool Anim::OnFinish() {
	// 当前逻辑是 repeat
	totalElapsedSeconds = 0;
	lpsCursor = 0;
	cdsCursor = 0;
	ssCursor = 0;
	fsCursor = 0;
	return true;
}

// 判断 点(r == 0) 或 圆 是否和单个 cdCircle 相交
bool Anim::IsIntersect(FileExts::CDCircle const& c, float const& x, float const& y, float const& r) {
	return (c.x - x) * (c.x - x) + (c.y - y) * (c.y - y) <= (c.r + r) * (c.r + r);
}

// 判断 点(r == 0) 或 圆 是否和某 cdCircle 相交( touch, bullet hit 判断需要 )
bool Anim::IsIntersect(float const& x, float const& y, float const& r) const {
	if (!action || action->cds.empty()) return false;
	auto&& cd = action->cds[cdsCursor];
	if (!IsIntersect(cd.maxCDCircle, x, y, r)) return false;
	for (auto&& c : cd.cdCircles) {
		if (IsIntersect(c, x, y, r)) return true;
	}
	return false;
}

bool Anim::Lockable() const {
	if (!action || action->lps.empty()) return false;
	// todo
	return true;
}

std::tuple<float, float> Anim::GetLockPoint() const {
	std::tuple<float, float> rtv;
	if (!action || action->lps.empty()) return rtv;
	// todo: 需结合坐标以及屏幕裁剪范围来算
	std::get<0>(rtv) = action->lps[lpsCursor].mainLockPoint.x;
	std::get<1>(rtv) = action->lps[lpsCursor].mainLockPoint.y;
	return rtv;
}







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
