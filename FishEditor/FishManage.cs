#pragma warning disable 0169, 0414
using System;
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

1 ~ 4 级资源，都需要不同程度的附加一些 跑逻辑所需数据

以物理/逻辑划分：
	物理：真实存在的文件
	逻辑：虚拟文件

具体结构：
	声音 (附加播放时长)
		背景音乐
			mp3, ogg, wav
		音效
			mp3, ogg, wav

	单图( 附加 碰撞检测 & 锁定数据 )
		pkm, webp, png

	图集
		plist
			引用到单图
			包含小图块

	动画 (附加 动作列表: 名字 & 时长 & 宽高 & 帧率 & 每帧的 碰撞检测 & 锁定数据)
		2d骨骼
			spine( atlas, json/skel )
				纹理引用到 单图
		3d
			c3b
				纹理引用到 单图
		序列帧
			frameAnimation（虚拟文件）
				引用到一组 单图 或 小图块( 通过单图的附加信息定位 )
		组合
			combine（虚拟文件）
				多子多级嵌套动画
	脚本
		lua（附加实现的什么接口的说明）

其中 序列帧, 组合 比较特殊，cocos 并未内置相关物理存储结构，故将其直接创建到 配置 当中
plist 文件类型不被视作固定资源, 只是为单图的替代做简单映射


考虑到多语言的情况，所有资源和文件的对应，均通过 字典 来实现一对多。代码中只针对 资源名，不触碰物理文件名
*/



[Desc("整套配置的数据存档. 鱼 = 资源数据 + 逻辑数据")]
struct Data {
	[Desc("所有 文件 列表. key 为 文件名(带部分路径)")]
	Dict<string, Shared<File>> files;



	[Desc("所有 脚本 资源列表")]
	Dict<string, Shared<Res_Script>> resScripts;

	[Desc("所有 背景音乐 & 音效 资源列表")]
	Dict<string, Shared<Res_Sound>> resSounds;

	[Desc("所有 单图 资源列表")]
	Dict<string, Shared<Res_Picture>> resPictures;

	[Desc("所有 帧动画 资源列表")]
	Dict<string, Shared<Res_FrameAnimation>> resFrameAnimations;

	[Desc("所有 2d骨骼动画 资源列表")]
	Dict<string, Shared<Res_Spine>> resSpines;

	[Desc("所有 3d模型动画 资源列表")]
	Dict<string, Shared<Res_3d>> res3ds;

	[Desc("所有 组合 资源列表")]
	Dict<string, Shared<Res_Combine>> resCombines;



	[Desc("所有 鱼 列表")]
	Dict<string, Shared<FishBase>> fishs;
}

[Desc("文件扩展名枚举")]
enum FileExtensions {
	mp3, ogg, wav, 
	webp, png, jpg, pkm, tga, bmp, 
	plist, 
	atlas, json, skel,
	c3b, 
	lua, 
	fnt,
	[Desc("虚拟文件扩展名: 帧动画")]
	frameAnimation,
	[Desc("虚拟文件扩展名: 帧动画")]
	combine
}

[TypeId(1), Desc("文件( 可能是 物理存在的 或 虚拟的 )")]
class File {
	[Desc("文件名: 相对路径, 目录名 + 文件名 + 扩展名，前面不带'/'")]
	string name;

	[Desc("文件扩展名 / 类型")]
	FileExtensions ext;
}

[TypeId(24), Desc("虚拟文件: 帧动画 含动作数据配置集合")]
class File_FrameAnimation : File {
    [Desc("动作数据配置集合")]
    List<FrameAction> actions;
}

[TypeId(25), Desc("真实文件 附加内容长度 校验码")]
class File_Real : File {
	[Desc("文件长度")]
	long length;

	[Desc("校验码")]
	byte[] md5;
}

[TypeId(26), Desc("lua 脚本文件")]
class File_Lua : File_Real {
	// todo: 附加 实现了何种接口的描述?? 以方便 选择 bind ?
}


[TypeId(2), Desc("声音文件 附加播放时长")]
class File_Sound : File_Real {
	[Desc("播放时长( 秒 )")]
	float seconds;

	// todo: 可以增加时间点 trigger 配置. 播放到某个时长时产生某名称事件
}

[TypeId(3), Desc("图片文件信息 附加碰撞等额外数据 以及位于某 plist")]
class File_Picture : File_Real {
	[Desc("碰撞检测 & 锁定点线 集合")]
	CDCirclesLockPoints cdclps;

	[Desc("基础缩放比例( 默认 1. 如果有降低过图片分辨率 / 精度，但又需要显示到和原先同样大小，则需要设置这个 )")]
	float baseScale = 1;

	[Desc("围绕 z 轴的 基础旋转角度( 默认 0. 图片逻辑上在坐标系中 正方向为 x 轴+ )")]
	float baseAngle;

	[Desc("显示坐标偏移调整( 默认 0 )")]
	float offsetX;
	float offsetY;

	[Desc("影子显示时的放大系数. 平时与 scale 相等. 部分 boss 影子比身体小")]
	float shadowScale = 1;

	[Desc("影子的偏移坐标")]
	float shadowOffsetX = 3;
	float shadowOffsetY = 3;

	[Desc("如果文件名和某 plist 的图块名相同，则指向该 plist. 运行时优先从 plist 加载")]
	Weak<File_Bag> atPList;
}

[TypeId(4), Desc("打包文件信息 附加其他包含子文件( 例如 plist 附带 texture, atlas 附带 json/skel & texture 等 )")]
class File_Bag : File_Real {
	[Desc("附带文件集. 不被 资源 直接引用")]
	List<Shared<File_Real>> childs;
}

[TypeId(5), Desc("动画打包文件信息 附加 动作数据配置集合")]
class File_Animation : File_Bag {
	[Desc("动作数据配置集合")]
	List<Action> actions;
}

[TypeId(6), Desc("spine 动画打包文件信息")]
class File_Spine : File_Animation {
	[Desc("影子显示时的放大系数. 平时与 scale 相等. 部分 boss 影子比身体小")]
	float shadowScale = 1;

	[Desc("影子的偏移坐标")]
	float shadowOffsetX = 3;
	float shadowOffsetY = 3;

	[Desc("基础缩放比例( 默认 1. 如果有降低过图片分辨率 / 精度，但又需要显示到和原先同样大小，则需要设置这个 )")]
	float baseScale = 1;

	[Desc("围绕 z 轴的 基础旋转角度( 默认 0. 图片逻辑上在坐标系中 正方向为 x 轴+ )")]
	float baseAngle;

	[Desc("显示坐标偏移调整( 默认 0 )")]
	float offsetX;
	float offsetY;
}

[TypeId(7), Desc("spine 动画打包文件信息")]
class File_C3b : File_Animation {
	[Desc("基础缩放比例( 默认 1. 如果模型小到看不见或者非常巨大，则需要设置这个 )")]
	float baseScale = 1;

	[Desc("基础旋转角度( 默认 0. 图片逻辑上在坐标系中 正方向为 趴在x 轴+ )")]
	float baseAngleX;
	float baseAngleY;
	float baseAngleZ;

	[Desc("显示坐标偏移调整( 默认 0 )")]
	float offsetX;
	float offsetY;
	float offsetZ;
}

[TypeId(27), Desc("虚拟文件: 组合动画")]
class File_Combine : File {
	[Desc("成员列表( 运行时其共有的动作名可用 )（绘制保存时，第一个 item 的 offsetXY 将遍历减去，之后置 0, 即 以第一个 item 为中心点）")]
	List<CombineItem> items;
}

[Struct, Desc("ResCombine 的专用 成员配置")]
class CombineItem {
	[Desc("指向要用到的文件( 图片 / 帧动画 / spine / 3d / combine )")]
	Weak<File> file;

	[Desc("二次调整 俯视情况下围绕 z 轴 0 度的 x, y 显示偏移位置")]
	float offsetX;
	float offsetY;

	[Desc("二次调整 围绕 z 的旋转角度")]
	float angle;

	[Desc("二次调整缩放比")]
	float scale = 1;
}

[Struct, Desc("动作描述")]
class Action {
	[Desc("动作名( 用于播放定位 )")]
	string name;

	[Desc("播放时长( 秒 )")]
	float seconds;

	[Desc("每秒帧率 / 播放速率( 关系到 原始碰撞数据的密度 )")]
	float frameRate = 60;

	[Desc("包围盒宽度( 2d sprite frame 默认为图集宽度. spine, 3d, combine 都需要手工设置 )")]
	float width;

	[Desc("包围盒高度( 2d sprite frame 默认为图集高度. spine, 3d, combine 都需要手工设置 )")]
	float height;

	[Desc("碰撞检测圆 + 锁定点线 集合 的 集合( size() == seconds * frameRate )")]
	List<CDCirclesLockPoints> cdclpss;

	// todo: 可以增加时间点 trigger 配置. 播放到某个时长时产生某名称事件
}

[Struct, Desc("动作描述 附带具体每一帧的图的引用")]
class FrameAction : Action {
	[Desc("图片集合")]
	List<Weak<File_Picture>> pictures;
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




[TypeId(8), Desc("资源基类")]
class Res {
	[Desc("资源名( 初创时以 path+文件名 为资源名 )")]
	string name;
}

[TypeId(15), Desc("脚本类资源")]
class Res_Script : Res {
	[Desc("语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是")]
	List<Pair<int, File_Lua>> files;
}

[TypeId(10), Desc("声音类资源")]
class Res_Sound : Res {
	[Desc("语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是")]
	List<Pair<int, File_Sound>> files;
}

[TypeId(11), Desc("图片类资源")]
class Res_Picture : Res {
	[Desc("语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是")]
	List<Pair<int, File_Picture>> files;
}

[TypeId(12), Desc("帧动画类资源")]
class Res_FrameAnimation : Res {
	[Desc("语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是")]
	List<Pair<int, File_FrameAnimation>> files;
}

[TypeId(13), Desc("动画/Spine类资源")]
class Res_Spine : Res {
	[Desc("语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是")]
	List<Pair<int, File_Spine>> files;
}

[TypeId(14), Desc("动画/3d类资源")]
class Res_3d : Res {
	[Desc("语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是")]
	List<Pair<int, File_C3b>> files;
}

[TypeId(16), Desc("动画/组合类资源")]
class Res_Combine : Res {
	[Desc("语言id & 文件. 至少有一条 语言 id == 0 的数据. 应该第一条就是")]
	List<Pair<int, File_Combine>> files;
}








[TypeId(17), Desc("鱼基类")]
class FishBase {
	[Desc("鱼名( 用于创建定位 )")]
	string name;

	[Desc("引用到声音资源( 通常死亡的时候有一定概率播放 ). 可空")]
	Weak<Res_Sound> resVoiceForDead;

	[Desc("引用到带动画的资源: spine c3b frameAnimation combine. 通常含有两个动作：idle/move, die/dead. 必填")]
	Weak<Res> resAnimation;

	[Desc("鱼状态列表( 初始为第一个状态 ). 必填")]
	List<FishState> fishStates;

	// todo: 应该提供一个 lua 运行的同步内存区间. 如果环境变量存在 cpp 端，lua 每次通过映射函数获取，性能如何，需要测试看看
	// lua 可通过映射函数获取当前鱼的数据? 以及读取整个场景的数据? 可以修改鱼的坐标？朝向？缩放？切状态？暂停/继续播放动画？

	[Desc("引用到脚本资源（不填则表示不用）. 可空")]
	Weak<Res_Script> resScript;

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

[TypeId(18), Desc("普通( 所有 BOSS 也算普通鱼. 从普通鱼派生 )")]
class FishNormal : FishBase {
}


[TypeId(19), Desc("炸弹( 子弹的一种，原地或移动 延迟爆炸 N 次 )")]
class FishBomb : FishBase {
	[Desc("炸弹: 至少连续爆炸多少次")]
    int timesFrom;

    [Desc("炸弹: 最多连续爆炸多少次( 范围随机 )")]
    int timesTo;
}

[TypeId(20), Desc("钻头( 子弹的一种，先变为图标飞向炮台，再经由炮台选角度一次性发射 )")]
class FishDrill : FishBase {
    [Desc("保留多少倍率用于爆炸")]
    long reserveCoin;
}

[TypeId(21), Desc("烈焰风暴( 子弹的一种，先变为图标飞向炮台，再经由炮台不断发射，威力比普通子弹大 )")]
class FishFury : FishBase {
	[Desc("烈焰风暴: 每次发射的子弹的倍率系数( 以体现威力大 ). 最后一发剩多少算多少")]
	long numBulletsPerShoot;
}

[TypeId(22), Desc("旋风( 倍率为同屏所有同类鱼的叠加 )")]
class FishCyclone : FishBase {
	[Desc("同类鱼的名字")]
	string sameFishName;
}

[TypeId(23), Desc("捕食者( 李逵啥的，接近别的鱼会吞噬对方，倍率相应增加 )")]
class FishEater : FishBase {
	[Desc("允许被吃掉的鱼的名称列表")]
	List<string> fishNames;
}
