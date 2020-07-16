#pragma warning disable 0169, 0414
using TemplateLibrary;

// TypeId 用到了 18

[Desc("整套配置的数据存档. 鱼 = 资源数据 + 逻辑数据")]
struct Data {
	List<Shared<ResBase>> ress;
	List<Shared<FishBase>> fishs;
}

[TypeId(1), Desc("资源基类")]
class ResBase {
	[Desc("资源名")]
	string name;

	[Desc("基础缩放比例")]
	float baseScale;

	[Desc("动作集合")]
	List<Shared<ActionBase>> actions;

	[Desc("最后编辑时间")]
	long lastUpdateTime;
}

[TypeId(2), Desc("动作基类")]
class ActionBase {
	[Desc("动作名( 用于播放定位 )")]
	string name;

	[Desc("每秒帧率 / 播放速率. 每条鱼的每个动作都可以配置不同帧率. spine/3d 同样受影响")]
	float frameRate;

	[Desc("总宽度( 2d sprite frame 默认为图集宽度. spine, 3d, combine 都需要手工设置 )")]
	float width;

	[Desc("总高度( 2d sprite frame 默认为图集高度. spine, 3d, combine 都需要手工设置 )")]
	float height;

	[Desc("帧集合")]
	List<Shared<FrameBase>> frames;
}

[Desc("碰撞检测圆")]
struct CDCircle {
	[Desc("相对于鱼的中心点的 0 度（俯视向右）坐标系的圆心")]
	float x, y;

	[Desc("半径")]
	float r;
}

[Desc("锁定点. 多点可连线")]
struct LockPoint {
	[Desc("相对于鱼的中心点的 0 度（俯视向右）坐标系的坐标")]
	float x, y;
}

[TypeId(3), Desc("帧基类")]
class FrameBase {
	[Desc("在默认鱼线上的默认移动距离( 鱼阵代码可能忽略该数据 )")]
	float moveDistance;

	[Desc("最大范围碰撞检测圆. 用于首检. 需要覆盖住子圆( 该圆心与子圆心的距离 + 子圆心的直径 < 该圆半径 )")]
	CDCircle maxCDCircle;
	[Desc("子碰撞检测圆集合. 按半径由大到小排序. 服务器如果要省 cpu 可以少算几个后面的")]
	List<CDCircle> cdCircles;

	[Desc("主要锁定点")]
	LockPoint mainLockPoint;
	[Desc("锁定线. 当主要锁定点离开屏幕后，由锁定线与屏幕边缘的交点决定锁定点")]
	List<LockPoint> lockPoints;
}



[TypeId(4), Desc("ResBase 的派生类, 特化 2d 帧图 资源数据")]
class Res2d : ResBase {
	[Desc("所有 action 用到的 sprite frames 所在所有 plist 文件名列表")]
	List<string> plistFileNames;

	[Desc("影子显示时的放大系数. 平时与 scale 相等. 部分 boss 影子比身体小")]
	float shadowScale;

	[Desc("影子的偏移坐标")]
	float shadowOffsetX;
	float shadowOffsetY;
}

[TypeId(18)]
class Action2d : ActionBase { }

[TypeId(5), Desc("Res2d 的专用 动作帧")]
class Frame2d : FrameBase {
	[Desc("精灵帧名")]
	string spriteFrameName;
}

[TypeId(6), Desc("ResBase 的派生类, 特化 spine 资源数据")]
class ResSpine : ResBase {
	[Desc("spine 资源主文件名")]
	string atlasFileName;

	[Desc("影子显示时的放大系数. 平时与 scale 相等. 部分 boss 影子比身体小")]
	float shadowScale;

	[Desc("影子的偏移坐标")]
	float shadowOffsetX;
	float shadowOffsetY;
}

[TypeId(16)]
class ActionSpine : ActionBase { }

[TypeId(7), Desc("ResBase 的派生类, 特化 3d 模型 资源数据")]
class Res3d : ResBase {
	[Desc("3d 资源主文件名")]
	string c3bFileName;

	[Desc("针对 3d 模型资源的角度调整，令其俯卧并朝向 x 正方向")]
	float baseAngleX;
	float baseAngleY;
	float baseAngleZ;
}

[TypeId(17)]
class Action3d : ActionBase { }

[TypeId(8), Desc("ResBase 的派生类, 特化 组合 模型 资源数据")]
class ResCombine : ResBase {
	List<CombineItem> items;
}

[Desc("ResCombine 的专用 成员配置")]
struct CombineItem {
	[Desc("指向要用到的资源")]
	Shared<ResBase> res;

	[Desc("俯视情况下围绕 z 轴 0 度的 x, y 显示偏移位置")]
	float offsetX;
	float offsetY;

	[Desc("3d 下 angle 指的是 围绕 z 的旋转角度")]
	float baseAngle;

	[Desc("再次调整缩放比( 组合鱼里面的鱼的体积可能小于个体 )")]
	float baseScale;
}




[TypeId(9), Desc("鱼基类")]
class FishBase {
	[Desc("鱼名( 用于创建定位 )")]
	string name;

	[Desc("所用资源")]
	Weak<ResBase> res;

	[Desc("倍率基数")]
	long coin1;

	[Desc("倍率上限( 不可能小于基数。等于基数 则为固定值，大于基数，普通鱼则为随机上限 )")]
	long coin2;

	[Desc("默认鱼线组名")]
	string pathwayGroupName;

	[Desc("最后编辑时间")]
	long lastUpdateTime;
}

[TypeId(10), Desc("普通( 所有 BOSS 也算普通鱼. 从普通鱼派生 )")]
class FishNormal : FishBase {
}

[TypeId(11), Desc("炸弹( 子弹的一种，原地或移动 延迟爆炸 N 次 )")]
class FishBomb : FishBase {
	[Desc("炸弹: 至少连续爆炸多少次")]
    int timesFrom;

    [Desc("炸弹: 最多连续爆炸多少次( 范围随机 )")]
    int timesTo;
}

[TypeId(12), Desc("钻头( 子弹的一种，先变为图标飞向炮台，再经由炮台选角度一次性发射 )")]
class FishDrill : FishBase {
    [Desc("保留多少倍率用于爆炸")]
    long reserveCoin;
}

[TypeId(13), Desc("烈焰风暴( 子弹的一种，先变为图标飞向炮台，再经由炮台不断发射，威力比普通子弹大 )")]
class FishFury : FishBase {
	[Desc("烈焰风暴: 每次发射的子弹的倍率系数( 以体现威力大 ). 最后一发剩多少算多少")]
	long numBulletsPerShoot;
}

[TypeId(14), Desc("旋风( 倍率为同屏所有同类鱼的叠加 )")]
class FishCyclone : FishBase {
	[Desc("同类鱼的名字")]
	string sameFishName;
}

[TypeId(15), Desc("捕食者( 李逵啥的，接近别的鱼会吞噬对方，倍率相应增加 )")]
class FishEater : FishBase {
	[Desc("允许被吃掉的鱼的名称列表")]
	List<string> fishNames;
}
