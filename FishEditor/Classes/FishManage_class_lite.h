#pragma once
#include "xx_object.h"
#include "FishManage_class_lite.h.inc"  // user create it for extend include files
namespace FishManage {
	struct PkgGenMd5 {
		inline static const std::string value = "#*MD5<9be7814f6a2abf3f54283511c9e27887>*#";
    };
	struct PkgGenTypes {
        static void RegisterTo(xx::ObjectHelper& oh);
    };

    struct File;
    struct File_Real;
    struct Res;
    struct File_Bag;
    struct File_Lua;
    struct File_Sound;
    struct Res_Sound;
    struct Res_Script;
    struct FishBase;
    struct File_Picture;
    struct File_Animation;
    struct File_Combine;
    struct File_C3b;
    struct File_Spine;
    struct File_FrameAnimation;
    struct Res_Picture;
    struct Res_FrameAnimation;
    struct Res_Spine;
    struct Res_3d;
    struct Res_Combine;
    struct FishFury;
    struct FishDrill;
    struct FishNormal;
    struct FishCyclone;
    struct FishBomb;
    struct FishEater;
}
namespace xx {
    template<> struct TypeId<FishManage::File> { static const uint16_t value = 1; };
    template<> struct TypeId<FishManage::File_Real> { static const uint16_t value = 25; };
    template<> struct TypeId<FishManage::Res> { static const uint16_t value = 8; };
    template<> struct TypeId<FishManage::File_Bag> { static const uint16_t value = 4; };
    template<> struct TypeId<FishManage::File_Lua> { static const uint16_t value = 26; };
    template<> struct TypeId<FishManage::File_Sound> { static const uint16_t value = 2; };
    template<> struct TypeId<FishManage::Res_Sound> { static const uint16_t value = 10; };
    template<> struct TypeId<FishManage::Res_Script> { static const uint16_t value = 15; };
    template<> struct TypeId<FishManage::FishBase> { static const uint16_t value = 17; };
    template<> struct TypeId<FishManage::File_Picture> { static const uint16_t value = 3; };
    template<> struct TypeId<FishManage::File_Animation> { static const uint16_t value = 5; };
    template<> struct TypeId<FishManage::File_Combine> { static const uint16_t value = 27; };
    template<> struct TypeId<FishManage::File_C3b> { static const uint16_t value = 7; };
    template<> struct TypeId<FishManage::File_Spine> { static const uint16_t value = 6; };
    template<> struct TypeId<FishManage::File_FrameAnimation> { static const uint16_t value = 24; };
    template<> struct TypeId<FishManage::Res_Picture> { static const uint16_t value = 11; };
    template<> struct TypeId<FishManage::Res_FrameAnimation> { static const uint16_t value = 12; };
    template<> struct TypeId<FishManage::Res_Spine> { static const uint16_t value = 13; };
    template<> struct TypeId<FishManage::Res_3d> { static const uint16_t value = 14; };
    template<> struct TypeId<FishManage::Res_Combine> { static const uint16_t value = 16; };
    template<> struct TypeId<FishManage::FishFury> { static const uint16_t value = 21; };
    template<> struct TypeId<FishManage::FishDrill> { static const uint16_t value = 20; };
    template<> struct TypeId<FishManage::FishNormal> { static const uint16_t value = 18; };
    template<> struct TypeId<FishManage::FishCyclone> { static const uint16_t value = 22; };
    template<> struct TypeId<FishManage::FishBomb> { static const uint16_t value = 19; };
    template<> struct TypeId<FishManage::FishEater> { static const uint16_t value = 23; };
}
namespace FishManage {

    // 文件扩展名枚举
    enum class FileExtensions : int32_t {
        mp3 = 0,
        ogg = 1,
        wav = 2,
        webp = 3,
        png = 4,
        jpg = 5,
        pkm = 6,
        tga = 7,
        bmp = 8,
        plist = 9,
        atlas = 10,
        json = 11,
        c3b = 12,
        lua = 13,
        fnt = 14,
        // 虚拟文件扩展名: 帧动画
        frameAnimation = 15,
        // 虚拟文件扩展名: 帧动画
        combine = 16,
    };
    // 锁定点. 多点可连线
    struct LockPoint {
        XX_GENCODE_STRUCT_H(LockPoint)
        // 相对于鱼的中心点的 0 度（俯视向右）坐标系的坐标
        float x = 0;
        // 相对于鱼的中心点的 0 度（俯视向右）坐标系的坐标
        float y = 0;
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
    // 碰撞检测圆 + 锁定点线 集合
    struct CDCirclesLockPoints {
        XX_GENCODE_STRUCT_H(CDCirclesLockPoints)
        // 最大范围碰撞检测圆. 用于首检. 需要覆盖住子圆( 该圆心与子圆心的距离 + 子圆心的直径 < 该圆半径 )
        FishManage::CDCircle maxCDCircle;
        // 子碰撞检测圆集合. 按半径由大到小排序. 服务器如果要省 cpu 可以少算几个后面的
        std::vector<FishManage::CDCircle> cdCircles;
        // 主要锁定点
        FishManage::LockPoint mainLockPoint;
        // 锁定线. 当主要锁定点离开屏幕后，由锁定线与屏幕边缘的交点决定锁定点
        std::vector<FishManage::LockPoint> lockPoints;
    };
    // 动作描述
    struct Action {
        XX_GENCODE_STRUCT_H(Action)
        // 动作名( 用于播放定位 )
        std::string name;
        // 播放时长( 秒 )
        float seconds = 0;
        // 每秒帧率 / 播放速率( 关系到 原始碰撞数据的密度 )
        float frameRate = 60;
        // 包围盒宽度( 2d sprite frame 默认为图集宽度. spine, 3d, combine 都需要手工设置 )
        float width = 0;
        // 包围盒高度( 2d sprite frame 默认为图集高度. spine, 3d, combine 都需要手工设置 )
        float height = 0;
        // 碰撞检测圆 + 锁定点线 集合 的 集合( size() == seconds * frameRate )
        std::vector<FishManage::CDCirclesLockPoints> cdclpss;
    };
    struct FishState {
        XX_GENCODE_STRUCT_H(FishState)
        // 状态名
        std::string name;
        // 对应的动作名
        std::string actionName;
        // 待机 / 移动 的动作的 每帧 在鱼线上 前进的 距离. 如果 0 长, 则认为 距离为 1. 如果长度不足，则延续最后一个( 也就是说, 匀速鱼可以只填 1 个 )
        std::vector<float> moveActionFrameDistances;
        // 默认鱼线组名. 通常是在该组中随机选线
        std::string pathwayGroupName;
    };
    // 动作描述 附带具体每一帧的图的引用
    struct FrameAction : FishManage::Action {
        XX_GENCODE_STRUCT_H(FrameAction)
        // 图片集合
        std::vector<std::weak_ptr<FishManage::File_Picture>> pictures;
    };
    // ResCombine 的专用 成员配置
    struct CombineItem {
        XX_GENCODE_STRUCT_H(CombineItem)
        // 指向要用到的文件( 图片 / 帧动画 / spine / 3d / combine )
        std::weak_ptr<FishManage::File> file;
        // 二次调整 俯视情况下围绕 z 轴 0 度的 x, y 显示偏移位置
        float offsetX = 0;
        float offsetY = 0;
        // 二次调整 围绕 z 的旋转角度
        float angle = 0;
        // 二次调整缩放比
        float scale = 1;
    };
    // 整套配置的数据存档. 鱼 = 资源数据 + 逻辑数据
    struct Data {
        XX_GENCODE_STRUCT_H(Data)
        // 所有 文件 列表. key 为 文件名(带部分路径)
        std::map<std::string, std::shared_ptr<FishManage::File>> files;
        // 所有 脚本 资源列表
        std::map<std::string, std::shared_ptr<FishManage::Res_Script>> resScripts;
        // 所有 背景音乐 & 音效 资源列表
        std::map<std::string, std::shared_ptr<FishManage::Res_Sound>> resSounds;
        // 所有 单图 资源列表
        std::map<std::string, std::shared_ptr<FishManage::Res_Picture>> resPictures;
        // 所有 帧动画 资源列表
        std::map<std::string, std::shared_ptr<FishManage::Res_FrameAnimation>> resFrameAnimations;
        // 所有 2d骨骼动画 资源列表
        std::map<std::string, std::shared_ptr<FishManage::Res_Spine>> resSpines;
        // 所有 3d模型动画 资源列表
        std::map<std::string, std::shared_ptr<FishManage::Res_3d>> res3ds;
        // 所有 组合 资源列表
        std::map<std::string, std::shared_ptr<FishManage::Res_Combine>> resCombines;
        // 所有 鱼 列表
        std::map<std::string, std::shared_ptr<FishManage::FishBase>> fishs;
    };
    // 文件( 可能是 物理存在的 或 虚拟的 )
    struct File : xx::Object {
        XX_GENCODE_OBJECT_H(File, xx::Object)
        // 文件名: 相对路径, 目录名 + 文件名 + 扩展名，前面不带'/'
        std::string name;
        // 文件扩展名 / 类型
        FishManage::FileExtensions ext = (FishManage::FileExtensions)0;
    };
    // 真实文件 附加内容长度 校验码
    struct File_Real : FishManage::File {
        XX_GENCODE_OBJECT_H(File_Real, FishManage::File)
        // 文件长度
        int64_t length = 0;
        // 校验码
        xx::Data md5;
    };
    // 资源基类
    struct Res : xx::Object {
        XX_GENCODE_OBJECT_H(Res, xx::Object)
        // 资源名( 初创时以 path+文件名 为资源名 )
        std::string name;
    };
    // 打包文件信息 附加其他包含子文件( 例如 plist 附带 texture, atlas 附带 json & texture 等 )
    struct File_Bag : FishManage::File_Real {
        XX_GENCODE_OBJECT_H(File_Bag, FishManage::File_Real)
        // 附带文件集. 不被 资源 直接引用
        std::vector<std::shared_ptr<FishManage::File_Real>> childs;
    };
    // lua 脚本文件
    struct File_Lua : FishManage::File_Real {
        XX_GENCODE_OBJECT_H(File_Lua, FishManage::File_Real)
    };
    // 声音文件 附加播放时长
    struct File_Sound : FishManage::File_Real {
        XX_GENCODE_OBJECT_H(File_Sound, FishManage::File_Real)
        // 播放时长( 秒 )
        float seconds = 0;
    };
    // 声音类资源
    struct Res_Sound : FishManage::Res {
        XX_GENCODE_OBJECT_H(Res_Sound, FishManage::Res)
        // 语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是
        std::vector<std::pair<int32_t, FishManage::File_Sound>> files;
    };
    // 脚本类资源
    struct Res_Script : FishManage::Res {
        XX_GENCODE_OBJECT_H(Res_Script, FishManage::Res)
        // 语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是
        std::vector<std::pair<int32_t, FishManage::File_Lua>> files;
    };
    // 鱼基类
    struct FishBase : xx::Object {
        XX_GENCODE_OBJECT_H(FishBase, xx::Object)
        // 鱼名( 用于创建定位 )
        std::string name;
        // 引用到声音资源( 通常死亡的时候有一定概率播放 ). 可空
        std::weak_ptr<FishManage::Res_Sound> resVoiceForDead;
        // 引用到带动画的资源: spine c3b frameAnimation combine. 通常含有两个动作：idle/move, die/dead. 必填
        std::weak_ptr<FishManage::Res> resAnimation;
        // 鱼状态列表( 初始为第一个状态 ). 必填
        std::vector<FishManage::FishState> fishStates;
        // 引用到脚本资源（不填则表示不用）. 可空
        std::weak_ptr<FishManage::Res_Script> resScript;
        // 倍率基数
        int64_t coin1 = 0;
        // 倍率上限( 不可能小于基数。等于基数 则为固定值，大于基数，普通鱼则为随机上限 )
        int64_t coin2 = 0;
        // 最后编辑时间
        int64_t lastUpdateTime = 0;
    };
    // 图片文件信息 附加碰撞等额外数据 以及位于某 plist
    struct File_Picture : FishManage::File_Real {
        XX_GENCODE_OBJECT_H(File_Picture, FishManage::File_Real)
        // 碰撞检测 & 锁定点线 集合
        FishManage::CDCirclesLockPoints cdclps;
        // 基础缩放比例( 默认 1. 如果有降低过图片分辨率 / 精度，但又需要显示到和原先同样大小，则需要设置这个 )
        float baseScale = 1;
        // 围绕 z 轴的 基础旋转角度( 默认 0. 图片逻辑上在坐标系中 正方向为 x 轴+ )
        float baseAngle = 0;
        // 显示坐标偏移调整( 默认 0 )
        float offsetX = 0;
        float offsetY = 0;
        // 影子显示时的放大系数. 平时与 scale 相等. 部分 boss 影子比身体小
        float shadowScale = 1;
        // 影子的偏移坐标
        float shadowOffsetX = 3;
        float shadowOffsetY = 3;
        // 如果文件名和某 plist 的图块名相同，则指向该 plist. 运行时优先从 plist 加载
        std::weak_ptr<FishManage::File_Bag> atPList;
    };
    // 动画打包文件信息 附加 动作数据配置集合
    struct File_Animation : FishManage::File_Bag {
        XX_GENCODE_OBJECT_H(File_Animation, FishManage::File_Bag)
        // 动作数据配置集合
        std::vector<FishManage::Action> actions;
    };
    // 虚拟文件: 组合动画
    struct File_Combine : FishManage::File {
        XX_GENCODE_OBJECT_H(File_Combine, FishManage::File)
        // 成员列表( 运行时其共有的动作名可用 )（绘制保存时，第一个 item 的 offsetXY 将遍历减去，之后置 0, 即 以第一个 item 为中心点）
        std::vector<FishManage::CombineItem> items;
    };
    // spine 动画打包文件信息
    struct File_C3b : FishManage::File_Animation {
        XX_GENCODE_OBJECT_H(File_C3b, FishManage::File_Animation)
        // 基础缩放比例( 默认 1. 如果模型小到看不见或者非常巨大，则需要设置这个 )
        float baseScale = 1;
        // 基础旋转角度( 默认 0. 图片逻辑上在坐标系中 正方向为 趴在x 轴+ )
        float baseAngleX = 0;
        float baseAngleY = 0;
        float baseAngleZ = 0;
        // 显示坐标偏移调整( 默认 0 )
        float offsetX = 0;
        float offsetY = 0;
        float offsetZ = 0;
    };
    // spine 动画打包文件信息
    struct File_Spine : FishManage::File_Animation {
        XX_GENCODE_OBJECT_H(File_Spine, FishManage::File_Animation)
        // 影子显示时的放大系数. 平时与 scale 相等. 部分 boss 影子比身体小
        float shadowScale = 1;
        // 影子的偏移坐标
        float shadowOffsetX = 3;
        float shadowOffsetY = 3;
        // 基础缩放比例( 默认 1. 如果有降低过图片分辨率 / 精度，但又需要显示到和原先同样大小，则需要设置这个 )
        float baseScale = 1;
        // 围绕 z 轴的 基础旋转角度( 默认 0. 图片逻辑上在坐标系中 正方向为 x 轴+ )
        float baseAngle = 0;
        // 显示坐标偏移调整( 默认 0 )
        float offsetX = 0;
        float offsetY = 0;
    };
    // 虚拟文件: 帧动画 含动作数据配置集合
    struct File_FrameAnimation : FishManage::File {
        XX_GENCODE_OBJECT_H(File_FrameAnimation, FishManage::File)
        // 动作数据配置集合
        std::vector<FishManage::FrameAction> actions;
    };
    // 图片类资源
    struct Res_Picture : FishManage::Res {
        XX_GENCODE_OBJECT_H(Res_Picture, FishManage::Res)
        // 语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是
        std::vector<std::pair<int32_t, FishManage::File_Picture>> files;
    };
    // 帧动画类资源
    struct Res_FrameAnimation : FishManage::Res {
        XX_GENCODE_OBJECT_H(Res_FrameAnimation, FishManage::Res)
        // 语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是
        std::vector<std::pair<int32_t, FishManage::File_FrameAnimation>> files;
    };
    // 动画/Spine类资源
    struct Res_Spine : FishManage::Res {
        XX_GENCODE_OBJECT_H(Res_Spine, FishManage::Res)
        // 语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是
        std::vector<std::pair<int32_t, FishManage::File_Spine>> files;
    };
    // 动画/3d类资源
    struct Res_3d : FishManage::Res {
        XX_GENCODE_OBJECT_H(Res_3d, FishManage::Res)
        // 语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是
        std::vector<std::pair<int32_t, FishManage::File_C3b>> files;
    };
    // 动画/组合类资源
    struct Res_Combine : FishManage::Res {
        XX_GENCODE_OBJECT_H(Res_Combine, FishManage::Res)
        // 语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是
        std::vector<std::pair<int32_t, FishManage::File_Combine>> files;
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
    // 普通( 所有 BOSS 也算普通鱼. 从普通鱼派生 )
    struct FishNormal : FishManage::FishBase {
        XX_GENCODE_OBJECT_H(FishNormal, FishManage::FishBase)
    };
    // 旋风( 倍率为同屏所有同类鱼的叠加 )
    struct FishCyclone : FishManage::FishBase {
        XX_GENCODE_OBJECT_H(FishCyclone, FishManage::FishBase)
        // 同类鱼的名字
        std::string sameFishName;
    };
    // 炸弹( 子弹的一种，原地或移动 延迟爆炸 N 次 )
    struct FishBomb : FishManage::FishBase {
        XX_GENCODE_OBJECT_H(FishBomb, FishManage::FishBase)
        // 炸弹: 至少连续爆炸多少次
        int32_t timesFrom = 0;
        // 炸弹: 最多连续爆炸多少次( 范围随机 )
        int32_t timesTo = 0;
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
	struct CloneFuncs<FishManage::LockPoint, void> {
		static void Clone1(ObjectHelper &oh, FishManage::LockPoint const& in, FishManage::LockPoint& out);
		static void Clone2(ObjectHelper &oh, FishManage::LockPoint const& in, FishManage::LockPoint& out);
	};
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
	struct CloneFuncs<FishManage::CDCircle, void> {
		static void Clone1(ObjectHelper &oh, FishManage::CDCircle const& in, FishManage::CDCircle& out);
		static void Clone2(ObjectHelper &oh, FishManage::CDCircle const& in, FishManage::CDCircle& out);
	};
	template<>
	struct StringFuncsEx<FishManage::CDCirclesLockPoints, void> {
		static void Append(ObjectHelper &oh, FishManage::CDCirclesLockPoints const& in);
		static void AppendCore(ObjectHelper &oh, FishManage::CDCirclesLockPoints const& in);
    };
	template<>
	struct DataFuncsEx<FishManage::CDCirclesLockPoints, void> {
		static void Write(DataWriterEx& dw, FishManage::CDCirclesLockPoints const& in);
		static int Read(DataReaderEx& dr, FishManage::CDCirclesLockPoints& out);
	};
    template<>
	struct CloneFuncs<FishManage::CDCirclesLockPoints, void> {
		static void Clone1(ObjectHelper &oh, FishManage::CDCirclesLockPoints const& in, FishManage::CDCirclesLockPoints& out);
		static void Clone2(ObjectHelper &oh, FishManage::CDCirclesLockPoints const& in, FishManage::CDCirclesLockPoints& out);
	};
	template<>
	struct StringFuncsEx<FishManage::Action, void> {
		static void Append(ObjectHelper &oh, FishManage::Action const& in);
		static void AppendCore(ObjectHelper &oh, FishManage::Action const& in);
    };
	template<>
	struct DataFuncsEx<FishManage::Action, void> {
		static void Write(DataWriterEx& dw, FishManage::Action const& in);
		static int Read(DataReaderEx& dr, FishManage::Action& out);
	};
    template<>
	struct CloneFuncs<FishManage::Action, void> {
		static void Clone1(ObjectHelper &oh, FishManage::Action const& in, FishManage::Action& out);
		static void Clone2(ObjectHelper &oh, FishManage::Action const& in, FishManage::Action& out);
	};
	template<>
	struct StringFuncsEx<FishManage::FishState, void> {
		static void Append(ObjectHelper &oh, FishManage::FishState const& in);
		static void AppendCore(ObjectHelper &oh, FishManage::FishState const& in);
    };
	template<>
	struct DataFuncsEx<FishManage::FishState, void> {
		static void Write(DataWriterEx& dw, FishManage::FishState const& in);
		static int Read(DataReaderEx& dr, FishManage::FishState& out);
	};
    template<>
	struct CloneFuncs<FishManage::FishState, void> {
		static void Clone1(ObjectHelper &oh, FishManage::FishState const& in, FishManage::FishState& out);
		static void Clone2(ObjectHelper &oh, FishManage::FishState const& in, FishManage::FishState& out);
	};
	template<>
	struct StringFuncsEx<FishManage::FrameAction, void> {
		static void Append(ObjectHelper &oh, FishManage::FrameAction const& in);
		static void AppendCore(ObjectHelper &oh, FishManage::FrameAction const& in);
    };
	template<>
	struct DataFuncsEx<FishManage::FrameAction, void> {
		static void Write(DataWriterEx& dw, FishManage::FrameAction const& in);
		static int Read(DataReaderEx& dr, FishManage::FrameAction& out);
	};
    template<>
	struct CloneFuncs<FishManage::FrameAction, void> {
		static void Clone1(ObjectHelper &oh, FishManage::FrameAction const& in, FishManage::FrameAction& out);
		static void Clone2(ObjectHelper &oh, FishManage::FrameAction const& in, FishManage::FrameAction& out);
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
    template<>
	struct CloneFuncs<FishManage::CombineItem, void> {
		static void Clone1(ObjectHelper &oh, FishManage::CombineItem const& in, FishManage::CombineItem& out);
		static void Clone2(ObjectHelper &oh, FishManage::CombineItem const& in, FishManage::CombineItem& out);
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
	struct CloneFuncs<FishManage::Data, void> {
		static void Clone1(ObjectHelper &oh, FishManage::Data const& in, FishManage::Data& out);
		static void Clone2(ObjectHelper &oh, FishManage::Data const& in, FishManage::Data& out);
	};
}