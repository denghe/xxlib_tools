#pragma once
#include "xx_object.h"
#include "FishManage_class_lite.h.inc"  // user create it for extend include files
namespace FishManage {
	struct PkgGenMd5 {
		inline static const std::string value = "#*MD5<ff594b4d1e35e0951d554be248625681>*#";
    };
	struct PkgGenTypes {
        static void RegisterTo(xx::ObjectHelper& oh);
    };

    // 鱼基类
    struct FishBase;
    // 资源基类
    struct ResBase;
    // 动作基类
    struct ActionBase;
    // 帧基类
    struct FrameBase;
    // 烈焰风暴( 子弹的一种，先变为图标飞向炮台，再经由炮台不断发射，威力比普通子弹大 )
    struct FishFury;
    // 钻头( 子弹的一种，先变为图标飞向炮台，再经由炮台选角度一次性发射 )
    struct FishDrill;
    // 炸弹( 子弹的一种，原地或移动 延迟爆炸 N 次 )
    struct FishBomb;
    // 普通( 所有 BOSS 也算普通鱼. 从普通鱼派生 )
    struct FishNormal;
    // ResBase 的派生类, 特化 组合 模型 资源数据
    struct ResCombine;
    struct ActionSpine;
    // ResBase 的派生类, 特化 3d 模型 资源数据
    struct Res3d;
    // 旋风( 倍率为同屏所有同类鱼的叠加 )
    struct FishCyclone;
    // ResBase 的派生类, 特化 spine 资源数据
    struct ResSpine;
    // Res2d 的专用 动作帧
    struct Frame2d;
    struct Action2d;
    // ResBase 的派生类, 特化 2d 帧图 资源数据
    struct Res2d;
    struct Action3d;
    // 捕食者( 李逵啥的，接近别的鱼会吞噬对方，倍率相应增加 )
    struct FishEater;
    // 鱼基类
    struct FishBase : xx::Object {
        XX_GENCODE_OBJECT_H(FishBase, xx::Object)
        // 鱼名( 用于创建定位 )
        std::string name;
        // 所用资源
        std::weak_ptr<FishManage::ResBase> res;
        // 倍率基数
        int64_t coin1 = 0;
        // 倍率上限( 不可能小于基数。等于基数 则为固定值，大于基数，普通鱼则为随机上限 )
        int64_t coin2 = 0;
        // 默认鱼线组名
        std::string pathwayGroupName;
        // 最后编辑时间
        int64_t lastUpdateTime = 0;
    };
    // 资源基类
    struct ResBase : xx::Object {
        XX_GENCODE_OBJECT_H(ResBase, xx::Object)
        // 资源名
        std::string name;
        // 基础缩放比例
        float baseScale = 0;
        // 动作集合
        std::vector<std::shared_ptr<FishManage::ActionBase>> actions;
        // 最后编辑时间
        int64_t lastUpdateTime = 0;
    };
    // 动作基类
    struct ActionBase : xx::Object {
        XX_GENCODE_OBJECT_H(ActionBase, xx::Object)
        // 动作名( 用于播放定位 )
        std::string name;
        // 每秒帧率 / 播放速率. 每条鱼的每个动作都可以配置不同帧率. spine/3d 同样受影响
        float frameRate = 0;
        // 总宽度( 2d sprite frame 默认为图集宽度. spine, 3d, combine 都需要手工设置 )
        float width = 0;
        // 总高度( 2d sprite frame 默认为图集高度. spine, 3d, combine 都需要手工设置 )
        float height = 0;
        // 帧集合
        std::vector<std::shared_ptr<FishManage::FrameBase>> frames;
    };
    // 碰撞检测圆
    struct CDCircle {
        XX_GENCODE_STRUCT_H(CDCircle)
        // 相对于鱼的中心点的 0 度（俯视向右）坐标系的圆心
        float x = 0;
        // 相对于鱼的中心点的 0 度（俯视向右）坐标系的圆心
        float y = 0;
        // 半径
        float r = 0;
    };
    // 锁定点. 多点可连线
    struct LockPoint {
        XX_GENCODE_STRUCT_H(LockPoint)
        // 相对于鱼的中心点的 0 度（俯视向右）坐标系的坐标
        float x = 0;
        // 相对于鱼的中心点的 0 度（俯视向右）坐标系的坐标
        float y = 0;
    };
    // 帧基类
    struct FrameBase : xx::Object {
        XX_GENCODE_OBJECT_H(FrameBase, xx::Object)
        // 在默认鱼线上的默认移动距离( 鱼阵代码可能忽略该数据 )
        float moveDistance = 0;
        // 最大范围碰撞检测圆. 用于首检. 需要覆盖住子圆( 该圆心与子圆心的距离 + 子圆心的直径 < 该圆半径 )
        FishManage::CDCircle maxCDCircle;
        // 子碰撞检测圆集合. 按半径由大到小排序. 服务器如果要省 cpu 可以少算几个后面的
        std::vector<FishManage::CDCircle> cdCircles;
        // 主要锁定点
        FishManage::LockPoint mainLockPoint;
        // 锁定线. 当主要锁定点离开屏幕后，由锁定线与屏幕边缘的交点决定锁定点
        std::vector<FishManage::LockPoint> lockPoints;
    };
    // 整套配置的数据存档. 鱼 = 资源数据 + 逻辑数据
    struct Data {
        XX_GENCODE_STRUCT_H(Data)
        std::vector<std::shared_ptr<FishManage::ResBase>> ress;
        std::vector<std::shared_ptr<FishManage::FishBase>> fishs;
    };
    // 烈焰风暴( 子弹的一种，先变为图标飞向炮台，再经由炮台不断发射，威力比普通子弹大 )
    struct FishFury : FishManage::FishBase {
        XX_GENCODE_OBJECT_H(FishFury, FishManage::FishBase)
        // 烈焰风暴: 每次发射的子弹的倍率系数( 以体现威力大 ). 最后一发剩多少算多少
        int64_t numBulletsPerShoot = 0;
    };
    // 钻头( 子弹的一种，先变为图标飞向炮台，再经由炮台选角度一次性发射 )
    struct FishDrill : FishManage::FishBase {
        XX_GENCODE_OBJECT_H(FishDrill, FishManage::FishBase)
        // 保留多少倍率用于爆炸
        int64_t reserveCoin = 0;
    };
    // 炸弹( 子弹的一种，原地或移动 延迟爆炸 N 次 )
    struct FishBomb : FishManage::FishBase {
        XX_GENCODE_OBJECT_H(FishBomb, FishManage::FishBase)
        // 炸弹: 至少连续爆炸多少次
        int32_t timesFrom = 0;
        // 炸弹: 最多连续爆炸多少次( 范围随机 )
        int32_t timesTo = 0;
    };
    // 普通( 所有 BOSS 也算普通鱼. 从普通鱼派生 )
    struct FishNormal : FishManage::FishBase {
        XX_GENCODE_OBJECT_H(FishNormal, FishManage::FishBase)
    };
    // ResCombine 的专用 成员配置
    struct CombineItem {
        XX_GENCODE_STRUCT_H(CombineItem)
        // 指向要用到的资源
        std::shared_ptr<FishManage::ResBase> res;
        // 俯视情况下围绕 z 轴 0 度的 x, y 显示偏移位置
        float offsetX = 0;
        float offsetY = 0;
        // 3d 下 angle 指的是 围绕 z 的旋转角度
        float baseAngle = 0;
        // 再次调整缩放比( 组合鱼里面的鱼的体积可能小于个体 )
        float baseScale = 0;
    };
    // ResBase 的派生类, 特化 组合 模型 资源数据
    struct ResCombine : FishManage::ResBase {
        XX_GENCODE_OBJECT_H(ResCombine, FishManage::ResBase)
        std::vector<FishManage::CombineItem> items;
    };
    struct ActionSpine : FishManage::ActionBase {
        XX_GENCODE_OBJECT_H(ActionSpine, FishManage::ActionBase)
    };
    // ResBase 的派生类, 特化 3d 模型 资源数据
    struct Res3d : FishManage::ResBase {
        XX_GENCODE_OBJECT_H(Res3d, FishManage::ResBase)
        // 3d 资源主文件名
        std::string c3bFileName;
        // 针对 3d 模型资源的角度调整，令其俯卧并朝向 x 正方向
        float baseAngleX = 0;
        float baseAngleY = 0;
        float baseAngleZ = 0;
    };
    // 旋风( 倍率为同屏所有同类鱼的叠加 )
    struct FishCyclone : FishManage::FishBase {
        XX_GENCODE_OBJECT_H(FishCyclone, FishManage::FishBase)
        // 同类鱼的名字
        std::string sameFishName;
    };
    // ResBase 的派生类, 特化 spine 资源数据
    struct ResSpine : FishManage::ResBase {
        XX_GENCODE_OBJECT_H(ResSpine, FishManage::ResBase)
        // spine 资源主文件名
        std::string atlasFileName;
        // 影子显示时的放大系数. 平时与 scale 相等. 部分 boss 影子比身体小
        float shadowScale = 0;
        // 影子的偏移坐标
        float shadowOffsetX = 0;
        float shadowOffsetY = 0;
    };
    // Res2d 的专用 动作帧
    struct Frame2d : FishManage::FrameBase {
        XX_GENCODE_OBJECT_H(Frame2d, FishManage::FrameBase)
        // 精灵帧名
        std::string spriteFrameName;
    };
    struct Action2d : FishManage::ActionBase {
        XX_GENCODE_OBJECT_H(Action2d, FishManage::ActionBase)
    };
    // ResBase 的派生类, 特化 2d 帧图 资源数据
    struct Res2d : FishManage::ResBase {
        XX_GENCODE_OBJECT_H(Res2d, FishManage::ResBase)
        // 所有 action 用到的 sprite frames 所在所有 plist 文件名列表
        std::vector<std::string> plistFileNames;
        // 影子显示时的放大系数. 平时与 scale 相等. 部分 boss 影子比身体小
        float shadowScale = 0;
        // 影子的偏移坐标
        float shadowOffsetX = 0;
        float shadowOffsetY = 0;
    };
    struct Action3d : FishManage::ActionBase {
        XX_GENCODE_OBJECT_H(Action3d, FishManage::ActionBase)
    };
    // 捕食者( 李逵啥的，接近别的鱼会吞噬对方，倍率相应增加 )
    struct FishEater : FishManage::FishBase {
        XX_GENCODE_OBJECT_H(FishEater, FishManage::FishBase)
        // 允许被吃掉的鱼的名称列表
        std::vector<std::string> fishNames;
    };
}
namespace xx {
	template<>
	struct StringFuncsEx<FishManage::CDCircle, void> {
		static void Append(ObjectHelper &oh, FishManage::CDCircle const& in);
		static void AppendCore(ObjectHelper &oh, FishManage::CDCircle const& in);
    };
	template<>
	struct DataFuncsEx<FishManage::CDCircle, void> {
		static void Write(DataWriterEx& dw, FishManage::CDCircle const& in);
		static int Read(DataReaderEx& dr, FishManage::CDCircle& out);
	};
	template<>
	struct StringFuncsEx<FishManage::LockPoint, void> {
		static void Append(ObjectHelper &oh, FishManage::LockPoint const& in);
		static void AppendCore(ObjectHelper &oh, FishManage::LockPoint const& in);
    };
	template<>
	struct DataFuncsEx<FishManage::LockPoint, void> {
		static void Write(DataWriterEx& dw, FishManage::LockPoint const& in);
		static int Read(DataReaderEx& dr, FishManage::LockPoint& out);
	};
	template<>
	struct StringFuncsEx<FishManage::Data, void> {
		static void Append(ObjectHelper &oh, FishManage::Data const& in);
		static void AppendCore(ObjectHelper &oh, FishManage::Data const& in);
    };
	template<>
	struct DataFuncsEx<FishManage::Data, void> {
		static void Write(DataWriterEx& dw, FishManage::Data const& in);
		static int Read(DataReaderEx& dr, FishManage::Data& out);
	};
	template<>
	struct StringFuncsEx<FishManage::CombineItem, void> {
		static void Append(ObjectHelper &oh, FishManage::CombineItem const& in);
		static void AppendCore(ObjectHelper &oh, FishManage::CombineItem const& in);
    };
	template<>
	struct DataFuncsEx<FishManage::CombineItem, void> {
		static void Write(DataWriterEx& dw, FishManage::CombineItem const& in);
		static int Read(DataReaderEx& dr, FishManage::CombineItem& out);
	};
}