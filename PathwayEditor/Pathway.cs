#pragma warning disable 0169, 0414
using TemplateLibrary;

[Include, Desc("点")]
struct Point {
    float x, y, z;
    [Desc("张力. 默认 0.3. 值越大, 倒角越圆润, 越小越尖")]
    float tension;
    [Desc("到下一个点的切片数")]
    int numSegments;
}

[Desc("线")]
struct Line {
    [Desc("途经点集合. 2 个点为直线，更多点为曲线串联")]
    List<Point> points;

    [Desc("是否闭合. 直线无法闭合。将于头尾多填2点，绘制后裁切掉以确保曲线形状正确")]
    bool isLoop;
}

[Desc("组: 定位到线的分组依据")]
struct Group {
    [Desc("唯一名称( 编辑时显示用. 也可用于查找 )")]
    string name;

    [Desc("组成员：Data.lines 下标集合")]
    List<int> lineIndexs;
}

[Desc("所有数据")]
struct Data {
    [Desc("线集合")]
    List<Line> lines;

    [Desc("组集合")]
    List<Group> groups;
}
