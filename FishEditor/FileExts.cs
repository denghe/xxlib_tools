﻿#pragma warning disable 0169, 0414
using TemplateLibrary;

/*
帧动画( frames )数据结构：带总时长的时间轴。到达某个时间，就切换成某张图

| pic         pic           pic                             pic
|......|......|......|......|......|......|......|......|......|......|......|...

所有动画类型的动作可能具备下列 3 种时间轴数据：碰撞圈，锁定线，速度变化

| cd                        cd
| lp
| speed       speed             speed  speed  speed  speed
|......|......|......|......|......|......|......|......|......|......|......|...

同一个动作含有的时间轴，因为密度不同，数据存储是分离的。它们结构类似，都是 起始时间点 + 状态数据，总时长依赖于动作本身


运行时播放器接口需求与层级关系：

1. 动画播放器：针对 frames，spine, c3b 的原始存档，能跨类型加载，能切动作，能设置是否循环，能快进/暂停 甚至后退，能指定显示坐标，角度，缩放，隐藏/显示，层级，有播放结束事件
2. 承担部分业务逻辑的移动对象：组合 动画播放器，能加载 ext 附加数据并提供相关功能，能绑移动路径，能在路径上快进/前进/后退/停止. 可设置相对坐标，角度，缩放，有移动结束事件

*/


/*******************************************************************************************/
// 锁定相关
/*******************************************************************************************/

[Struct, Desc("锁定点")]
class LockPoint {
    float x;
    float y;
};

[Struct, Desc("时间点--锁定点线")]
class TimePoint_LockPoints {
    [Desc("起始时间( 秒 )")]
    float time;
    [Desc("主锁定点。如果出屏幕，则锁定 锁定线与屏幕边缘形成的 交点")]
    LockPoint mainLockPoint;
    [Desc("锁定线")]
    List<LockPoint> lockPoints;
};

/*******************************************************************************************/
// 碰撞相关
/*******************************************************************************************/

[Struct, Desc("碰撞圆")]
class CDCircle {
    float x;
    float y;
    float r;
};

[Struct, Desc("时间点--碰撞圆集合")]
class TimePoint_CDCircles {
    [Desc("起始时间( 秒 )")]
    float time;
    [Desc("最大碰撞圆范围（外包围圆），用于碰撞检测粗判")]
    CDCircle maxCDCircle;
    [Desc("具体碰撞圆列表，用于碰撞检测遍历细判")]
    List<CDCircle> cdCircles;
};

/*******************************************************************************************/
// 时间点--速度
/*******************************************************************************************/

[Struct, Desc("时间点--移动速度")]
class TimePoint_Speed {
    [Desc("起始时间( 秒 )")]
    float time;
    [Desc("每秒移动距离(米)")]
    float speed;
};

/*******************************************************************************************/
// 精灵帧
/*******************************************************************************************/

[Struct, Desc("时间点--精灵帧")]
class TimePoint_Frame {
    [Desc("起始时间( 秒 )")]
    float time;
    [Desc("精灵帧名称")]
    string picName;
};

[Struct, Desc("精灵帧动画--动作( 兼容 spine, c3b, frames )")]
class Action_Frames {
    [Desc("动作名")]
    string name;
    [Desc("总时长( 秒 )")]
    float totalSeconds;
    [Desc("时间点--精灵帧 集合")]
    List<TimePoint_Frame> frames;
};

/*******************************************************************************************/
// 精灵帧动画 存盘文件
/*******************************************************************************************/

[Struct, Desc("精灵帧动画 存盘文件")]
class File_Frames {
    [Desc("动作集合")]
    List<Action_Frames> actions;
    [Desc("图位于哪些 plist")]
    List<string> plists;
};

/*******************************************************************************************/
// 动作
/*******************************************************************************************/

[Struct, Desc("针对 atlas/spine, c3b, frames 等动画文件, 附加 移动 & 碰撞 & 锁定 等数据")]
class Action_AnimExt {
    [Desc("动作名")]
    string name;
    [Desc("总时长( 秒 )")]
    float totalSeconds;
    [Desc("时间点--锁定点线 集合")]
    List<TimePoint_LockPoints> lps;
    [Desc("时间点--碰撞圆 集合")]
    List<TimePoint_CDCircles> cds;
    [Desc("时间点--移动速度 集合")]
    List<TimePoint_Speed> ss;
};

/*******************************************************************************************/
// 动画 存盘文件
/*******************************************************************************************/

[Struct, Desc("针对动画的扩展信息 存盘文件( *.frames.ext, *.atlas.ext, *.c3b.ext ")]
class File_AnimExt {
    [Desc("动作集合")]
    List<Action_AnimExt> actions;
};

/*******************************************************************************************/
// 移动路线--点
/*******************************************************************************************/

[Struct, Include, Desc("移动路线--点")]
class PathwayPoint {
    // 坐标
    float x, y;

    [Desc("张力. 默认 0.3. 值越大, 拐角越圆润, 越小越尖")]
    float tension;

    [Desc("到下一个点的切片数")]
    int numSegments;
}

/*******************************************************************************************/
// 移动路线 存盘文件
/*******************************************************************************************/

[Struct, Desc("移动路线 存盘文件 *.pathway")]
class File_pathway {
    [Desc("是否闭合. 直线无法闭合。将于头尾多填2点，绘制后裁切掉以确保曲线形状正确")]
    bool isLoop;

    [Desc("点集合. 2 个点为直线，更多点为曲线串联")]
    List<PathwayPoint> points;
}

