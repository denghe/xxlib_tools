#include "MainScene.h"
//#include "xx_object.h"
//#include "xx_lua.h"
//#include <iostream>
//#include <chrono>
//
//namespace XL = xx::Lua;

AJSON(FileExts::PathwayPoint, x, y, tension, numSegments);
AJSON(FileExts::File_pathway, isLoop, points);


// 2 控制点的贝塞尔( p c c p c c p ... ) 切片转点
void BezierToPoints(std::vector<PathwayPoint>& ps, std::vector<FileExts::PathwayPoint> const& bs) {
	auto len = (bs.size() - 1) / 3;
	size_t totalSegments = 0;
	for (size_t j = 0; j < len; ++j) {
		totalSegments += bs[j * 3].numSegments;
	}
	ps.resize(totalSegments);
	totalSegments = 0;
	for (size_t j = 0; j < len; ++j) {
		auto idx = j * 3;
		auto numSegments = bs[idx].numSegments;
		auto step = 1.0f / numSegments;
		for (size_t i = 0; i < numSegments; ++i) {
			auto t = step * i;
			auto t1 = 1 - t;
			ps[totalSegments + i] = bs[idx] * t1 * t1 * t1
				+ bs[idx + 1] * 3 * t * t1 * t1
				+ bs[idx + 2] * 3 * t * t * (1 - t)
				+ bs[idx + 3] * t * t * t;
		}
		totalSegments += numSegments;
	}
}

// 途径点曲线( p p p ... ) 转 2 控制点的贝塞尔( p c c p c c p ... )
inline void CurveToBezier(std::vector<FileExts::PathwayPoint>& bs, std::vector<FileExts::PathwayPoint> const& cs) {
	auto n = cs.size();
	auto len = n * 3 - 2;
	bs.resize(len);

	bs[0] = cs[0];
	bs[1] = (cs[1] - cs[0]) * cs[0].tension + cs[0];

	for (size_t i = 0; i < n - 2; i++) {
		auto diff = (cs[i + 2] - cs[i]) * cs[i].tension;
		bs[3 * i + 2] = cs[i + 1] - diff;
		bs[3 * i + 3] = cs[i + 1];
		bs[3 * i + 4] = cs[i + 1] + diff;
	}
	bs[len - 2] = (cs[n - 2] - cs[n - 1]) * cs[n - 2].tension + cs[n - 1];
	bs[len - 1] = cs[n - 1];
}

// 计算直线的弧度( 转为角度还要  * (180.0f / float(M_PI) )
template<typename Point1, typename Point2>
inline float GetAngle(Point1 const& from, Point2 const& to) noexcept
{
	if (from == to) return 0.0f;
	auto&& len_y = to.y - from.y;
	auto&& len_x = to.x - from.x;
	return atan2f(len_y, len_x);
}

// 计算距离
template<typename Point1, typename Point2>
inline float GetDistance(Point1 const& a, Point2 const& b) noexcept
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrtf(dx * dx + dy * dy);
}

std::shared_ptr<Pathway> PathwayLoader::Load(std::string const& fn) {
	auto&& iter = pathways.find(fn);
	// 已存在：短路返回
	if (iter != pathways.end()) return iter->second;

	char const* buf = nullptr;
	size_t len = 0;
#ifdef COCOS2D_VERSION
	auto d = cocos2d::FileUtils::getInstance()->getDataFromFile(fn);
	// 错误检查
	if (d.getSize() == 0) return nullptr;
	buf = (char*)d.getBytes();
	len = d.getSize();
#else
	xx::Data d;
	// 错误检查
	if (xx::ReadAllBytes(fn, d) || !d.len) return nullptr;
	buf = d.buf;
	len = d.len;
#endif
	FileExts::File_pathway f;
	// 从 json 加载
	ajson::load_from_buff(f, buf, len); // try catch?

	// 准备返回值容器
	auto rtv = xx::Make<Pathway>();

	auto&& ps = f.points;
	// 缓存长度
	auto siz = ps.size();

	// 点数量需要 >= 2
	if (siz < 2) return nullptr;

	// 保存文件名
	rtv->fileName = fn;
	auto&& rps = rtv->points;

	// 如果只有 2 个点：直线
	if (siz == 2) {
		// 先填充第一个点（计算到第二个点的角度和距离）
		rps.emplace_back(ps[0].x, ps[0].y
			, GetAngle(ps[0], ps[1])
			, GetDistance(ps[0], ps[1]));
		rtv->isLoop = f.isLoop;
		// 不断来回弹的直线?
		if (f.isLoop) {
			// 填充第二个点。角度相反，距离相同
			rps.emplace_back(ps[1].x, ps[1].y
				, rps[0].a + M_PI
				, rps[0].d);
		}
		else {
			rps.emplace_back(ps[1].x, ps[1].y, 0, 0);
		}
	}
	// 曲线
	else {
		// 曲线 转为 带控制点的贝塞尔
		if (f.isLoop) {
			// 循环曲线则前后各追加几个点算控制点
			bs.push_back(ps[ps.size() - 2]);
			bs.push_back(ps[ps.size() - 1]);
			bs.insert(bs.end(), ps.begin(), ps.end());
			bs.push_back(ps[0]);
			bs.push_back(ps[1]);
			bs.push_back(ps[2]);
			CurveToBezier(cs, bs);
			bs.clear();
			// 移除追加
			cs.erase(cs.end() - 6, cs.end() - 1);
			cs.erase(cs.begin(), cs.begin() + 3);
		}
		else {
			CurveToBezier(cs, ps);
		}

		// 带控制点的贝塞尔 转为 点集合
		BezierToPoints(rps, cs);
		cs.clear();

		siz = rps.size();
		// 将第一个点添加到末尾简化计算
		rps.push_back(rps[0]);
		for (size_t i = 0; i < siz; ++i) {
			rps[i].a = GetAngle(rps[i], rps[i + 1]);
			rps[i].d = GetDistance(rps[i], rps[i + 1]);
		}
		// 移除添加的第一个点
		rps.pop_back();
	}

	// 放入字典并返回
	pathways[fn] = rtv;
	return rtv;
}

// 清除 pathways 值部分引用计数为 1 的 移动路线
void PathwayLoader::RemoveUnused() {
	for (auto iter = pathways.begin(); iter != pathways.end(); ) {
		if (iter->second.use_count() == 1) {
			iter = pathways.erase(iter);
		}
		else {
			++iter;
		}
	}
}



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
