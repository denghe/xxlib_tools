#pragma once
#include "xx_object.h"
#include "FishManage_class_lite.h.inc"  // user create it for extend include files
namespace FishManage {
	struct PkgGenMd5 {
		inline static const std::string value = "#*MD5<b2072398ee4e29dae56bdc03071c3590>*#";
    };
	struct PkgGenTypes {
        static void RegisterTo(xx::ObjectHelper& oh);
    };

    struct ResBase;
    struct File;
    struct ResAnimation;
    struct ResSound;
    struct ResScript;
    struct ResVoice;
    struct ResPicture;
    struct FishBase;
    struct ResTexture;
    struct ResFrame;
    struct ResPList;
    struct Res3d;
    struct ResCombine;
    struct ResFrameAnimation;
    struct ResSpine;
    struct ResMusic;
    struct FishFury;
    struct FishDrill;
    struct FishNormal;
    struct FishCyclone;
    struct FishBomb;
    struct FishEater;
}
namespace xx {
    template<> struct TypeId<FishManage::ResBase> { static const uint16_t value = 2; };
    template<> struct TypeId<FishManage::File> { static const uint16_t value = 1; };
    template<> struct TypeId<FishManage::ResAnimation> { static const uint16_t value = 10; };
    template<> struct TypeId<FishManage::ResSound> { static const uint16_t value = 3; };
    template<> struct TypeId<FishManage::ResScript> { static const uint16_t value = 22; };
    template<> struct TypeId<FishManage::ResVoice> { static const uint16_t value = 5; };
    template<> struct TypeId<FishManage::ResPicture> { static const uint16_t value = 7; };
    template<> struct TypeId<FishManage::FishBase> { static const uint16_t value = 15; };
    template<> struct TypeId<FishManage::ResTexture> { static const uint16_t value = 8; };
    template<> struct TypeId<FishManage::ResFrame> { static const uint16_t value = 9; };
    template<> struct TypeId<FishManage::ResPList> { static const uint16_t value = 6; };
    template<> struct TypeId<FishManage::Res3d> { static const uint16_t value = 12; };
    template<> struct TypeId<FishManage::ResCombine> { static const uint16_t value = 14; };
    template<> struct TypeId<FishManage::ResFrameAnimation> { static const uint16_t value = 13; };
    template<> struct TypeId<FishManage::ResSpine> { static const uint16_t value = 11; };
    template<> struct TypeId<FishManage::ResMusic> { static const uint16_t value = 4; };
    template<> struct TypeId<FishManage::FishFury> { static const uint16_t value = 19; };
    template<> struct TypeId<FishManage::FishDrill> { static const uint16_t value = 18; };
    template<> struct TypeId<FishManage::FishNormal> { static const uint16_t value = 16; };
    template<> struct TypeId<FishManage::FishCyclone> { static const uint16_t value = 20; };
    template<> struct TypeId<FishManage::FishBomb> { static const uint16_t value = 17; };
    template<> struct TypeId<FishManage::FishEater> { static const uint16_t value = 21; };
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
    // 动作基类
    struct ActionBase {
        XX_GENCODE_STRUCT_H(ActionBase)
        // 动作名( 用于播放定位 )
        std::string name;
        // 播放时长
        float seconds = 0;
        // 每秒帧率 / 播放速率
        float frameRate = 0;
        // 包围盒宽度( 2d sprite frame 默认为图集宽度. spine, 3d, combine 都需要手工设置 )
        float width = 0;
        // 包围盒高度( 2d sprite frame 默认为图集高度. spine, 3d, combine 都需要手工设置 )
        float height = 0;
    };
    // 非序列帧的动作：直接附加 碰撞检测圆 + 锁定点线 集合 的 集合( 对应每一帧的数据)
    struct ActionOthers : FishManage::ActionBase {
        XX_GENCODE_STRUCT_H(ActionOthers)
        // 碰撞检测圆 + 锁定点线 集合 的 集合( 对应每一帧的数据)
        std::vector<FishManage::CDCirclesLockPoints> cdclpss;
    };
    // ResCombine 的专用 成员配置
    struct CombineItem {
        XX_GENCODE_STRUCT_H(CombineItem)
        // 指向要用到的资源
        std::weak_ptr<FishManage::ResAnimation> res;
        // 3d: 俯视情况下围绕 z 轴 0 度的 x, y 显示偏移位置
        float offsetX = 0;
        float offsetY = 0;
        // 3d 下 angle 指的是 围绕 z 的旋转角度
        float baseAngle = 0;
        // 调整缩放比
        float baseScale = 0;
    };
    // 序列帧的动作：附加帧集合（每帧有自己的 碰撞检测圆 + 锁定点线 的配置）
    struct ActionSpriteFrame : FishManage::ActionBase {
        XX_GENCODE_STRUCT_H(ActionSpriteFrame)
        // 帧集合
        std::vector<std::weak_ptr<FishManage::ResPicture>> frames;
    };
    // 整套配置的数据存档. 鱼 = 资源数据 + 逻辑数据
    struct Data {
        XX_GENCODE_STRUCT_H(Data)
        // 所有文件列表. key 为 文件名(带部分路径)
        std::map<std::string, std::shared_ptr<FishManage::File>> files;
        // 所有背景音乐资源列表
        std::map<std::string, std::shared_ptr<FishManage::ResMusic>> resMusics;
        // 所有音效资源列表
        std::map<std::string, std::shared_ptr<FishManage::ResVoice>> resVoices;
        // 所有纹理资源列表
        std::map<std::string, std::shared_ptr<FishManage::ResTexture>> resTextures;
        // 所有图集资源列表
        std::map<std::string, std::shared_ptr<FishManage::ResPList>> resPLists;
        // 所有图块资源列表( 从 resPlists 汇集 ). key 为 name
        std::map<std::string, std::weak_ptr<FishManage::ResFrame>> resFrames;
        // 所有2d骨骼动画资源列表
        std::map<std::string, std::shared_ptr<FishManage::ResSpine>> resSpines;
        // 所有3d模型动画资源列表
        std::map<std::string, std::shared_ptr<FishManage::Res3d>> res3ds;
        // 所有帧动画资源列表
        std::map<std::string, std::shared_ptr<FishManage::ResFrameAnimation>> resFrameAnimations;
        // 所有组合资源列表
        std::map<std::string, std::shared_ptr<FishManage::ResCombine>> resCombine;
        // 所有脚本资源列表
        std::map<std::string, std::shared_ptr<FishManage::ResScript>> resScripts;
        // 所有鱼列表
        std::map<std::string, std::shared_ptr<FishManage::FishBase>> fishs;
    };
    // 资源基类
    struct ResBase : xx::Object {
        XX_GENCODE_OBJECT_H(ResBase, xx::Object)
        // 资源名( 首次创建时直接以文件名作为资源名使用, 故文件名最好跨目录跨图集打包不重名 )
        std::string name;
    };
    // 文件信息
    struct File : xx::Object {
        XX_GENCODE_OBJECT_H(File, xx::Object)
        // 文件名: 相对路径, 目录名 + 文件名 + 扩展名，前面不带'/'
        std::string path;
        // 文件扩展名 / 类型
        FishManage::FileExtensions ext = (FishManage::FileExtensions)0;
        // 文件长度
        int64_t length = 0;
        // 校验码
        xx::Data md5;
    };
    // 动画类资源
    struct ResAnimation : FishManage::ResBase {
        XX_GENCODE_OBJECT_H(ResAnimation, FishManage::ResBase)
        // 影子显示时的放大系数. 平时与 scale 相等. 部分 boss 影子比身体小
        float shadowScale = 0;
        // 影子的偏移坐标
        float shadowOffsetX = 0;
        float shadowOffsetY = 0;
    };
    // 声音类资源
    struct ResSound : FishManage::ResBase {
        XX_GENCODE_OBJECT_H(ResSound, FishManage::ResBase)
        // 对应哪个物理文件
        std::weak_ptr<FishManage::File> file;
        // 播放时长
        float seconds = 0;
    };
    // 脚本类资源
    struct ResScript : FishManage::ResBase {
        XX_GENCODE_OBJECT_H(ResScript, FishManage::ResBase)
        // 对应哪个物理文件
        std::weak_ptr<FishManage::File> file;
    };
    // 声音/音效类资源
    struct ResVoice : FishManage::ResSound {
        XX_GENCODE_OBJECT_H(ResVoice, FishManage::ResSound)
    };
    // 图片类资源
    struct ResPicture : FishManage::ResBase {
        XX_GENCODE_OBJECT_H(ResPicture, FishManage::ResBase)
        // 碰撞检测 & 锁定点线 集合
        FishManage::CDCirclesLockPoints cdclps;
    };
    // 鱼基类
    struct FishBase : xx::Object {
        XX_GENCODE_OBJECT_H(FishBase, xx::Object)
        // 鱼名( 用于创建定位 )
        std::string name;
        // 引用到声音资源( 通常死亡的时候有一定概率播放 ). 可空
        std::weak_ptr<FishManage::ResVoice> resVoiceForDead;
        // 引用到动画资源( 通常含有两个动作：idle/move, die/dead ). 必填
        std::weak_ptr<FishManage::ResAnimation> resAnimation;
        // 鱼状态列表( 初始为第一个状态 ). 必填
        std::vector<FishManage::FishState> fishStates;
        // 引用到脚本资源（不填则表示不用）. 可空
        std::weak_ptr<FishManage::ResScript> resScript;
        // 倍率基数
        int64_t coin1 = 0;
        // 倍率上限( 不可能小于基数。等于基数 则为固定值，大于基数，普通鱼则为随机上限 )
        int64_t coin2 = 0;
        // 最后编辑时间
        int64_t lastUpdateTime = 0;
    };
    // 图片/纹理类资源
    struct ResTexture : FishManage::ResPicture {
        XX_GENCODE_OBJECT_H(ResTexture, FishManage::ResPicture)
        // 对应哪个物理文件
        std::weak_ptr<FishManage::File> file;
    };
    // 图片/图块类资源
    struct ResFrame : FishManage::ResPicture {
        XX_GENCODE_OBJECT_H(ResFrame, FishManage::ResPicture)
        // 所在 plist 资源
        std::weak_ptr<FishManage::ResPList> owner;
    };
    // 图集类资源
    struct ResPList : FishManage::ResBase {
        XX_GENCODE_OBJECT_H(ResPList, FishManage::ResBase)
        // 对应哪个物理文件
        std::weak_ptr<FishManage::File> file;
        // 引用到的纹理资源
        std::weak_ptr<FishManage::ResTexture> texture;
        // 含有的帧图资源集合
        std::vector<std::shared_ptr<FishManage::ResFrame>> frames;
    };
    // 动画/3d类资源
    struct Res3d : FishManage::ResAnimation {
        XX_GENCODE_OBJECT_H(Res3d, FishManage::ResAnimation)
        // 对应 c3b 文件
        std::weak_ptr<FishManage::File> file;
        // 引用到的贴图集合
        std::vector<std::weak_ptr<FishManage::ResTexture>> textures;
        // 含有的动作列表
        std::vector<FishManage::ActionOthers> actions;
    };
    // 动画/组合类资源
    struct ResCombine : FishManage::ResAnimation {
        XX_GENCODE_OBJECT_H(ResCombine, FishManage::ResAnimation)
        // 成员列表( 运行时其共有的动作名可用 )（绘制保存时，第一个 item 的 offsetXY 将遍历减去，之后置 0, 即 以第一个 item 为中心点）
        std::vector<FishManage::CombineItem> items;
    };
    // 动画/序列帧类资源. actions 的成员为 ActionSpriteFrame 类型
    struct ResFrameAnimation : FishManage::ResAnimation {
        XX_GENCODE_OBJECT_H(ResFrameAnimation, FishManage::ResAnimation)
        // 含有的动作列表
        std::vector<FishManage::ActionSpriteFrame> actions;
    };
    // 动画/Spine类资源
    struct ResSpine : FishManage::ResAnimation {
        XX_GENCODE_OBJECT_H(ResSpine, FishManage::ResAnimation)
        // 对应 atlas 文件
        std::weak_ptr<FishManage::File> atlasFile;
        // 引用到的贴图集合
        std::vector<std::weak_ptr<FishManage::ResTexture>> textures;
        // 对应 json 文件
        std::weak_ptr<FishManage::File> jsonFile;
        // 含有的动作列表
        std::vector<FishManage::ActionOthers> actions;
    };
    // 声音/背景音乐类资源
    struct ResMusic : FishManage::ResSound {
        XX_GENCODE_OBJECT_H(ResMusic, FishManage::ResSound)
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
	struct StringFuncsEx<FishManage::ActionBase, void> {
		static void Append(ObjectHelper &oh, FishManage::ActionBase const& in);
		static void AppendCore(ObjectHelper &oh, FishManage::ActionBase const& in);
    };
	template<>
	struct DataFuncsEx<FishManage::ActionBase, void> {
		static void Write(DataWriterEx& dw, FishManage::ActionBase const& in);
		static int Read(DataReaderEx& dr, FishManage::ActionBase& out);
	};
    template<>
	struct CloneFuncs<FishManage::ActionBase, void> {
		static void Clone1(ObjectHelper &oh, FishManage::ActionBase const& in, FishManage::ActionBase& out);
		static void Clone2(ObjectHelper &oh, FishManage::ActionBase const& in, FishManage::ActionBase& out);
	};
	template<>
	struct StringFuncsEx<FishManage::ActionOthers, void> {
		static void Append(ObjectHelper &oh, FishManage::ActionOthers const& in);
		static void AppendCore(ObjectHelper &oh, FishManage::ActionOthers const& in);
    };
	template<>
	struct DataFuncsEx<FishManage::ActionOthers, void> {
		static void Write(DataWriterEx& dw, FishManage::ActionOthers const& in);
		static int Read(DataReaderEx& dr, FishManage::ActionOthers& out);
	};
    template<>
	struct CloneFuncs<FishManage::ActionOthers, void> {
		static void Clone1(ObjectHelper &oh, FishManage::ActionOthers const& in, FishManage::ActionOthers& out);
		static void Clone2(ObjectHelper &oh, FishManage::ActionOthers const& in, FishManage::ActionOthers& out);
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
	struct StringFuncsEx<FishManage::ActionSpriteFrame, void> {
		static void Append(ObjectHelper &oh, FishManage::ActionSpriteFrame const& in);
		static void AppendCore(ObjectHelper &oh, FishManage::ActionSpriteFrame const& in);
    };
	template<>
	struct DataFuncsEx<FishManage::ActionSpriteFrame, void> {
		static void Write(DataWriterEx& dw, FishManage::ActionSpriteFrame const& in);
		static int Read(DataReaderEx& dr, FishManage::ActionSpriteFrame& out);
	};
    template<>
	struct CloneFuncs<FishManage::ActionSpriteFrame, void> {
		static void Clone1(ObjectHelper &oh, FishManage::ActionSpriteFrame const& in, FishManage::ActionSpriteFrame& out);
		static void Clone2(ObjectHelper &oh, FishManage::ActionSpriteFrame const& in, FishManage::ActionSpriteFrame& out);
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