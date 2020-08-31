#include "FileExts_class_lite.h"
//#include "xx_lua.h"
//#include <iostream>
//#include <chrono>
//
//namespace XL = xx::Lua;
//
//#include "FileExts_class_lite.h"
//// todo: ajson macro
//
//

// 移动路线 -- 点
struct PathwayPoint {
	// 2d坐标, 角度, 距离
	float x = 0, y = 0, a = 0, d = 0;
	PathwayPoint() = default;
	PathwayPoint(PathwayPoint const&) = default;
	PathwayPoint& operator=(PathwayPoint const&) = default;
	PathwayPoint(float const& x, float const& y, float const& a, float const& d) : x(x), y(y), a(a), d(d) {	}
	PathwayPoint(FileExts::PathwayPoint const& p) : x(p.x), y(p.y) {}
};

// 移动路线
struct Pathway {
	// 存储创建时读入的文件名
	std::string fileName;

	// 是否闭合( 是 则 最后一个点 的下一个指向 第一个点 )
	bool isLoop;

	// 点集合
	std::vector<PathwayPoint> points;
};

// 移动路线管理器：负责加载 .pathway 文件，并转为 线段 数据格式 返回
struct PathwayLoader {

	// 已加载的 pathway 容器
	std::unordered_map<std::string, std::shared_ptr<Pathway>> pathways;

	// 临时容器
	std::vector<FileExts::PathwayPoint> bs, cs;

	// 加载并返回一条 移动路线
	// 如果 pathways 中没找到 就加载文件 并放入
	std::shared_ptr<Pathway> Load(std::string const& fn);

	// 清除 pathways 值部分引用计数为 1 的 移动路线
	void RemoveUnused();
};


//// todo: 序列化接口?
// 动画基类
struct AnimBase {
	// 加载物理文件名 并初始化显示
	virtual void Load(std::string const& cfg) = 0;

	// 改变当前播放的动画 并从该动画的开头开始播放
	virtual void SetAction(std::string const& actionName) = 0;

	// 动画播放完毕后触发( 非循环播放的情况下 ), 可能切换动画继续播放返回 true，也可能自杀返回 false?
	virtual bool OnFinish() = 0;

	// 根据传入的 经历时长，调整动画状态. 返回 移动距离
	virtual float Update(float elapsedSeconds) = 0;

	// 判断 点(r == 0) 或 圆 是否和某 cdCircle 相交( touch, bullet hit 判断需要 )
	[[nodiscard]] virtual bool IsIntersect(float const& x, float const& y, float const& r) const = 0;

	// 判断是否能被 lock( 有某锁定点在屏幕范围内 )
	[[nodiscard]] virtual bool Lockable() const = 0;

	// 获取锁定坐标
	[[nodiscard]] virtual std::tuple<float, float> GetLockPoint() const = 0;

	// todo: 坐标，角度，pathway 设置等等?? 两种模式？ 1. pathway 自动驱动   2. 不指定 pathway，每帧外部改坐标驱动？

	// todo: 直接在这里管理 childs?


};

// todo: 附加对文件的加载和显示功能?
// todo: 附加对 pathway 的管理，附加坐标，移动功能?


// 文件类动画基类( spine, 3d, frames )
struct Anim : AnimBase {
	// todo: onXxxx 以便 Load 的时候 bind 和文件类型相应的 绘制, 快进 操作?

	// 指向当前 anim
	std::shared_ptr<FileExts::File_Anim> anim;

	// 指向当前 action( 位于 anim 中 )
	FileExts::Action* action = nullptr;

	// 记录相应时间线的游标/下标
	size_t lpsCursor = 0;
	size_t cdsCursor = 0;
	size_t ssCursor = 0;
	size_t fsCursor = 0;

	// 当前 action 已经历的总时长
	float totalElapsedSeconds = 0;

protected:
	// 内部函数. 被 Update 调用。确保传入的 经历时长 不会超出当前 timeLine 的范围. 返回距离
	float UpdateCore(float elapsedSeconds);

public:

	// 只实现了更新指针和计算移动距离。更新显示要覆写
	float Update(float elapsedSeconds) override;

	bool OnFinish() override;

	// 判断 点(r == 0) 或 圆 是否和单个 cdCircle 相交
	static bool IsIntersect(FileExts::CDCircle const& c, float const& x, float const& y, float const& r);

	// 判断 点(r==0) 或 圆 是否和某 cdCircle 相交( touch, bullet hit 判断需要 )
	[[nodiscard]] bool IsIntersect(float const& x, float const& y, float const& r) const override;

	// 返回是否能被锁定( 判断是否有任意锁定点在子弹射击范围内
	[[nodiscard]] bool Lockable() const override;

	[[nodiscard]] std::tuple<float, float> GetLockPoint() const override;
};




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
