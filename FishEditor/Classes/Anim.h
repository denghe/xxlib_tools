#pragma once
#include "Pathway.h"
#include "xx_object.h"
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

// 带移动功能的动画 基类
struct AnimBase : xx::Object {

	// 坐标
	xx::Point pos;

	// 角度
	float angle = 0;

	// 尺寸缩放比. 默认为 1
	float sizeScale = 1;

	// pathway 之 当前点下标
	size_t pathwayI = 0;

	// pathway 之 当前点已移动距离
	float pathwayD = 0;

	// 移动速度系数. 默认为 1, 0 为停止, 负数为倒退
	float speedScale = 1;

	// 显示 / 隐藏
	bool visible = true;

	// todo: z order?

	// 当前移动路线
	std::shared_ptr<xx::Pathway> const& pathway;

	// 子集合，组合啥的会用到。母体函数分发判断 lock attack 啥的。pathway 通常依附于母体，走相对坐标
	std::vector<std::shared_ptr<AnimBase>> childs;


	// 加载文件数据, 初始化成员变量. 返回 0 表示成功
	virtual int Load(std::string const& fileName) = 0;

	// 动画播放完毕后触发( 非循环播放的情况下 ), 可能切换动画并继续. 返回非 0 表示不再继续
	virtual int ActionEnd() = 0;

	// 沿着之前设定的路线( 如果有的话 ), 方向，移动指定距离 * 速度缩放比，客户端在显示上可能有所体现
	// 如果移到头了（非循环线），返回非 0
	virtual int Move(float const& distance) = 0;

	// 帧逻辑事件( 调用 Step + Move ? ). 返回 非 0 表示 生命周期结束
	virtual int Update(float elapsedSeconds) = 0;

	// 判断 传入点(r == 0) 或 圆 是否和某 cdCircle 相交( touch, bullet hit 判断需要 )
	virtual bool IsIntersect(float const& x, float const& y, float const& r) const = 0;

	// 判断是否能被 lock( 有某锁定点在屏幕范围内 )
	virtual bool Lockable() const = 0;

	// 获取锁定坐标
	virtual std::tuple<float, float> GetLockPoint() const = 0;

	// 判断是否能被 attack( 可能存在 无敌？遁入虚空？等无法攻击的状态 )
	virtual bool Attackable() const = 0;


	// 绘制( 客户端 only )
	virtual void Draw() = 0;


	// 被锁定通知（显示准星？)
	virtual void Lock() = 0;	// todo: 参数？准星样式？

	// 清除被锁定状态, 客户端在显示上可能有所体现（清除准星？）
	virtual void Unlock() = 0;

	// 被击中通知（变红一会儿？）
	virtual void Attack() = 0;	// todo: 参数？

	// 死亡通知
	virtual void Death() = 0;	// todo: 参数？死法？

	// 别的扩展事件
	virtual void Event(std::string const& event) = 0;

	// 根据扩展名( .frames,  .atlas.ext, .c3b.ext, .lua )创建相应的 Anim 类，并 Load
	static std::shared_ptr<AnimBase> Create(std::string const& fileName);

	//T() = default;
	//T(T const&) = default;
	//T& operator=(T const&) = default;
	//T(T&& o) noexcept;
	//T& operator=(T&& o) noexcept;
	//uint16_t GetTypeId() const override;
	//void Serialize(xx::DataWriterEx& dw) const override;
	//int Deserialize(xx::DataReaderEx& dr) override;
	//void ToString(xx::ObjectHelper& oh) const override;
	//void ToStringCore(xx::ObjectHelper& oh) const override;
	//void Clone1(xx::ObjectHelper& oh, std::shared_ptr<Object> const& tar) const override;
	//void Clone2(xx::ObjectHelper& oh, std::shared_ptr<Object> const& tar) const override;
};

enum class AnimTypes {
	Unknown, Frames, Atlas, C3b
};

// 文件类动画基类( spine, 3d, frames )
struct Anim : AnimBase {
	// 动画类型。 由 Load 决定
	AnimTypes animType;

	// 指向当前 anim
	std::shared_ptr<FileExts::File_Anim> anim;

	// 指向当前 action( 位于 anim 中 )
	FileExts::Action* action = nullptr;

	// 动画已经历秒数
	float totalElapsedSeconds = 0;

	// 记录相应时间线的游标/下标
	size_t lpsCursor = 0;
	size_t cdsCursor = 0;
	size_t ssCursor = 0;
	size_t fsCursor = 0;

	// .frames,  .atlas.ext, .c3b.ext
	int Load(std::string const& fileName) override;

	int ActionEnd() override;

	int Move(float const& distance) override;

	int Update(float elapsedSeconds) override;

	static bool IsIntersect(FileExts::CDCircle const& c, float const& x, float const& y, float const& r);

	bool IsIntersect(float const& x, float const& y, float const& r) const override;

	bool Lockable() const override;

	std::tuple<float, float> GetLockPoint() const override;

	void Lock() override;

	void Unlock() override;

	bool Attackable() const override;

	void Draw() override;
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
