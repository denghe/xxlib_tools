#pragma warning disable 0169, 0414
using TemplateLibrary;

/*
资源，泛指包体内非执行文件部分

以文件类型划分：
	声音，图片，动画(2d骨骼, 3d, 序列帧, 组合)，脚本 等( 先跳过 视频 粒子 shader 字体 图标 等 )

以访问层级划分：
	1级: 直接用
	2级: 需要通过 1 级 资源加载后方可使用，例如 plist 里的 小图块
	3级: 需要通过 1 & 2 级 资源组合而来，例如 序列帧
	4级: 需要通过 1 & 2 级 资源组合而来，例如 组合
	5级：间接资源，例如 plist / atlas / c3b 引用到的贴图文件

1 ~ 3 级资源，都需要不同程度的附加一些 跑逻辑所需数据

具体结构：
	声音 (附加播放时长)
		背景音乐
			mp3, ogg, wav
		音效
			mp3, ogg, wav

	图片/纹理/贴图/材质 (附加 碰撞检测 & 锁定数据)
		pkm, webp, png

	图集
		plist
			引用到单图
			包含小图块

	动画 (附加 动作列表: 名字 & 时长 & 宽高 & 帧率 & 每帧的 碰撞检测 & 锁定数据)
		2d骨骼
			spine( atlas, json )
				纹理引用到 图片
		3d
			c3b
				纹理引用到 图片
		序列帧
			配置
				引用到一组 图片 或 小图块
		组合
			配置
				引用到一组 动画(含别的组合)
	脚本
		lua

其中 序列帧, 组合 比较特殊，cocos 并未内置相关物理存储结构，故将其直接创建到 配置 当中

*/



[Desc("整套配置的数据存档. 鱼 = 资源数据 + 逻辑数据")]
struct Data {
	[Desc("所有文件列表. key 为 文件名(带部分路径)")]
	Dict<string, Shared<File>> files;

	[Desc("所有背景音乐资源列表")]
	Dict<string, Shared<ResMusic>> resMusics;
	[Desc("所有音效资源列表")]
	Dict<string, Shared<ResVoice>> resVoices;

	[Desc("所有纹理资源列表")]
	Dict<string, Shared<ResTexture>> resTextures;

	[Desc("所有图集资源列表")]
	Dict<string, Shared<ResPList>> resPLists;
	[Desc("所有图块资源列表( 从 resPlists 汇集 ). key 为 name")]
	Dict<string, Weak<ResFrame>> resFrames;

	[Desc("所有2d骨骼动画资源列表")]
	Dict<string, Shared<ResSpine>> resSpines;
	[Desc("所有3d模型动画资源列表")]
	Dict<string, Shared<Res3d>> res3ds;
	[Desc("所有帧动画资源列表")]
	Dict<string, Shared<ResFrameAnimation>> resFrameAnimations;

	[Desc("所有组合资源列表")]
	Dict<string, Shared<ResCombine>> resCombine;

	[Desc("所有脚本资源列表")]
	Dict<string, Shared<ResScript>> resScripts;

	[Desc("所有鱼列表")]
	Dict<string, Shared<FishBase>> fishs;
}

[Desc("文件扩展名枚举")]
enum FileExtensions {
	mp3, ogg, wav, 
	webp, png, jpg, pkm, tga, bmp, 
	plist, 
	atlas, json, 
	c3b, 
	lua, 
	fnt
}

[TypeId(1), Desc("文件信息")]
class File {
	[Desc("文件名: 相对路径, 目录名 + 文件名 + 扩展名，前面不带'/'")]
	string path;
	[Desc("文件扩展名 / 类型")]
	FileExtensions ext;
	[Desc("文件长度")]
	long length;
	[Desc("校验码")]
	byte[] md5;
	// more?
}

[TypeId(2), Desc("资源基类")]
class ResBase {
	[Desc("资源名( 首次创建时直接以文件名作为资源名使用, 故文件名最好跨目录跨图集打包不重名 )")]
	string name;
}


[TypeId(3), Desc("声音类资源")]
class ResSound : ResBase {
	[Desc("对应哪个物理文件")]
	Weak<File> file;

	[Desc("播放时长")]
	float seconds;
}

[TypeId(4), Desc("声音/背景音乐类资源")]
class ResMusic : ResSound {
}


[TypeId(5), Desc("声音/音效类资源")]
class ResVoice : ResSound {
}

[TypeId(6), Desc("图集类资源")]
class ResPList : ResBase {
	[Desc("对应哪个物理文件")]
	Weak<File> file;

	[Desc("引用到的纹理资源")]
	Weak<ResTexture> texture;

	[Desc("含有的帧图资源集合")]
	List<Shared<ResFrame>> frames;
}

[TypeId(7), Desc("图片类资源")]
class ResPicture : ResBase {
	[Desc("碰撞检测 & 锁定点线 集合")]
	CDCirclesLockPoints cdclps;
}

[TypeId(8), Desc("图片/纹理类资源")]
class ResTexture : ResPicture {
	[Desc("对应哪个物理文件")]
	Weak<File> file;
}

[TypeId(9), Desc("图片/图块类资源")]
class ResFrame : ResPicture {
	[Desc("所在 plist 资源")]
	Weak<ResPList> owner;
}

[TypeId(10), Desc("动画类资源")]
class ResAnimation : ResBase {
    [Desc("影子显示时的放大系数. 平时与 scale 相等. 部分 boss 影子比身体小")]
    float shadowScale;

    [Desc("影子的偏移坐标")]
    float shadowOffsetX;
    float shadowOffsetY;
}

[TypeId(11), Desc("动画/Spine类资源")]
class ResSpine : ResAnimation {
	[Desc("对应 atlas 文件")]
	Weak<File> atlasFile;

	[Desc("引用到的贴图集合")]
	List<Weak<ResTexture>> textures;

	[Desc("对应 json 文件")]
	Weak<File> jsonFile;

	[Desc("含有的动作列表")]
	List<ActionOthers> actions;
}

[TypeId(12), Desc("动画/3d类资源")]
class Res3d : ResAnimation {
	[Desc("对应 c3b 文件")]
	Weak<File> file;

	[Desc("引用到的贴图集合")]
	List<Weak<ResTexture>> textures;

	[Desc("含有的动作列表")]
	List<ActionOthers> actions;
}

[TypeId(13), Desc("动画/序列帧类资源. actions 的成员为 ActionSpriteFrame 类型")]
class ResFrameAnimation : ResAnimation {
	[Desc("含有的动作列表")]
	List<ActionSpriteFrame> actions;
}

[TypeId(14), Desc("动画/组合类资源")]
class ResCombine : ResAnimation {
	[Desc("成员列表( 运行时其共有的动作名可用 )（绘制保存时，第一个 item 的 offsetXY 将遍历减去，之后置 0, 即 以第一个 item 为中心点）")]
	List<CombineItem> items;
}

[TypeId(22), Desc("脚本类资源")]
class ResScript : ResBase {
	[Desc("对应哪个物理文件")]
	Weak<File> file;

	// todo: 功能？作用？接口？存储？
}



[Struct, Desc("ResCombine 的专用 成员配置")]
class CombineItem {
	[Desc("指向要用到的资源")]
	Weak<ResAnimation> res;

	[Desc("3d: 俯视情况下围绕 z 轴 0 度的 x, y 显示偏移位置")]
	float offsetX;
	float offsetY;

	[Desc("3d 下 angle 指的是 围绕 z 的旋转角度")]
	float baseAngle;

	[Desc("调整缩放比")]
	float baseScale;
}

[Struct, Desc("动作基类")]
class ActionBase {
	[Desc("动作名( 用于播放定位 )")]
	string name;

	[Desc("播放时长")]
	float seconds;

	[Desc("每秒帧率 / 播放速率")]
	float frameRate;

	[Desc("包围盒宽度( 2d sprite frame 默认为图集宽度. spine, 3d, combine 都需要手工设置 )")]
	float width;

	[Desc("包围盒高度( 2d sprite frame 默认为图集高度. spine, 3d, combine 都需要手工设置 )")]
	float height;
}

[Struct, Desc("序列帧的动作：附加帧集合（每帧有自己的 碰撞检测圆 + 锁定点线 的配置）")]
class ActionSpriteFrame : ActionBase {
	[Desc("帧集合")]
	List<Weak<ResPicture>> frames;
}

[Struct, Desc("非序列帧的动作：直接附加 碰撞检测圆 + 锁定点线 集合 的 集合( 对应每一帧的数据)")]
class ActionOthers : ActionBase {
	[Desc("碰撞检测圆 + 锁定点线 集合 的 集合( 对应每一帧的数据)")]
	List<CDCirclesLockPoints> cdclpss;
}

[Struct, Desc("碰撞检测圆")]
class CDCircle {
	[Desc("相对于鱼的中心点的 0 度（俯视向右）坐标系的圆心")]
	float x, y;

	[Desc("半径")]
	float r;
}

[Struct, Desc("锁定点. 多点可连线")]
class LockPoint {
	[Desc("相对于鱼的中心点的 0 度（俯视向右）坐标系的坐标")]
	float x, y;
}

[Struct, Desc("碰撞检测圆 + 锁定点线 集合")]
class CDCirclesLockPoints {
	[Desc("最大范围碰撞检测圆. 用于首检. 需要覆盖住子圆( 该圆心与子圆心的距离 + 子圆心的直径 < 该圆半径 )")]
	CDCircle maxCDCircle;
	[Desc("子碰撞检测圆集合. 按半径由大到小排序. 服务器如果要省 cpu 可以少算几个后面的")]
	List<CDCircle> cdCircles;

	[Desc("主要锁定点")]
	LockPoint mainLockPoint;
	[Desc("锁定线. 当主要锁定点离开屏幕后，由锁定线与屏幕边缘的交点决定锁定点")]
	List<LockPoint> lockPoints;
}











[TypeId(15), Desc("鱼基类")]
class FishBase {
	[Desc("鱼名( 用于创建定位 )")]
	string name;

	[Desc("引用到声音资源( 通常死亡的时候有一定概率播放 ). 可空")]
	Weak<ResVoice> resVoiceForDead;

	[Desc("引用到动画资源( 通常含有两个动作：idle/move, die/dead ). 必填")]
	Weak<ResAnimation> resAnimation;

	[Desc("鱼状态列表( 初始为第一个状态 ). 必填")]
	List<FishState> fishStates;

	// todo: 应该提供一个 lua 运行的同步内存区间. 如果环境变量存在 cpp 端，lua 每次通过映射函数获取，性能如何，需要测试看看
	// lua 可通过映射函数获取当前鱼的数据? 以及读取整个场景的数据? 可以修改鱼的坐标？朝向？缩放？切状态？暂停/继续播放动画？

	[Desc("引用到脚本资源（不填则表示不用）. 可空")]
	Weak<ResScript> resScript;

	[Desc("倍率基数")]
	long coin1;

	[Desc("倍率上限( 不可能小于基数。等于基数 则为固定值，大于基数，普通鱼则为随机上限 )")]
	long coin2;

	[Desc("最后编辑时间")]
	long lastUpdateTime;
}

[Struct]
class FishState {
	[Desc("状态名")]
	string name;

	[Desc("对应的动作名")]
	string actionName;

	[Desc("待机 / 移动 的动作的 每帧 在鱼线上 前进的 距离. 如果 0 长, 则认为 距离为 1. 如果长度不足，则延续最后一个( 也就是说, 匀速鱼可以只填 1 个 )")]
	List<float> moveActionFrameDistances;

	[Desc("默认鱼线组名. 通常是在该组中随机选线")]
	string pathwayGroupName;
}

[TypeId(16), Desc("普通( 所有 BOSS 也算普通鱼. 从普通鱼派生 )")]
class FishNormal : FishBase {
}


[TypeId(17), Desc("炸弹( 子弹的一种，原地或移动 延迟爆炸 N 次 )")]
class FishBomb : FishBase {
	[Desc("炸弹: 至少连续爆炸多少次")]
    int timesFrom;

    [Desc("炸弹: 最多连续爆炸多少次( 范围随机 )")]
    int timesTo;
}

[TypeId(18), Desc("钻头( 子弹的一种，先变为图标飞向炮台，再经由炮台选角度一次性发射 )")]
class FishDrill : FishBase {
    [Desc("保留多少倍率用于爆炸")]
    long reserveCoin;
}

[TypeId(19), Desc("烈焰风暴( 子弹的一种，先变为图标飞向炮台，再经由炮台不断发射，威力比普通子弹大 )")]
class FishFury : FishBase {
	[Desc("烈焰风暴: 每次发射的子弹的倍率系数( 以体现威力大 ). 最后一发剩多少算多少")]
	long numBulletsPerShoot;
}

[TypeId(20), Desc("旋风( 倍率为同屏所有同类鱼的叠加 )")]
class FishCyclone : FishBase {
	[Desc("同类鱼的名字")]
	string sameFishName;
}

[TypeId(21), Desc("捕食者( 李逵啥的，接近别的鱼会吞噬对方，倍率相应增加 )")]
class FishEater : FishBase {
	[Desc("允许被吃掉的鱼的名称列表")]
	List<string> fishNames;
}
