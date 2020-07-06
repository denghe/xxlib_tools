#pragma warning disable 0169, 0414
using TemplateLibrary;

[Struct]
class FishBase {
	string fishName;
	[Desc("基数")]
	long coin1;
	[Desc("== 0: 以coin1作为固定值.     < 0: 取屏幕相同鱼倍率?    > 0: 范围上限")]
	long coin2;
	// todo: more props
}
[Struct]
class ActionBase {
	string actionName;
}
[Struct]
class FrameBase {
	float moveDistance;
}






[Struct]
class Fish_2D_Frame : FrameBase {
	string spriteFrameName;
	string plistFileName;
}
[Struct]
class Fish_2D_Action : ActionBase {
	List<Fish_2D_Frame> frames;
}
[Struct]
class Fish_2D : FishBase {
	List<Fish_2D_Action> actions;
}






[Struct]
class Fish_Spine_Frame : FrameBase {
}
[Struct]
class Fish_Spine_Action : ActionBase {
	List<Fish_Spine_Frame> frames;
}
[Struct]
class Fish_Spine : FishBase {
	string atlasFileName;
	List<Fish_Spine_Action> actions;
}







[Struct]
class Fish_3D_Frame : FrameBase {
}
[Struct]
class Fish_3D_Action : ActionBase {
	List<Fish_3D_Frame> frames;
}
[Struct]
class Fish_3D : FishBase {
	string c3bFileName;
	float baseScale;
	float baseAngleX;
	float baseAngleY;
	float baseAngleZ;
	List<Fish_3D_Action> actions;
}








[Struct]
class Fish_Combine_Child {
	[Desc("1: 2d    2: spine   3: 3d")]
	int fishTypeId;
	[Desc("数组下标. 根据 typeId 对应到 Data 下的相应数组")]
	int index;
	float offsetX;
	float offsetY;
	float baseAngle;
	float baseScale;
}
[Struct]
class Fish_Combine_Action : ActionBase {
}
[Struct]
class Fish_Combine : FishBase {
	List<Fish_Combine_Child> childs;
	List<Fish_Combine_Action> actions;
}







[Struct]
class Data {
    List<Fish_2D> fish_2ds;
	List<Fish_Spine> fish_spines;
	List<Fish_3D> fish_3ds;
	List<Fish_Combine> fish_combines;
}
