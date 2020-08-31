#pragma once
#include "xx_object.h"
#include "FileExts_class_lite.h.inc"  // user create it for extend include files
namespace FileExts {
	struct PkgGenMd5 {
		inline static const std::string value = "#*MD5<f9a23c14cfb89685b624ac2272c526a4>*#";
    };
	struct PkgGenTypes {
        static void RegisterTo(xx::ObjectHelper& oh);
    };

}
namespace xx {
}
namespace FileExts {

    // 锁定点
    struct LockPoint {
        XX_GENCODE_STRUCT_H(LockPoint)
        float x = 0;
        float y = 0;
    };
    // 碰撞圆
    struct CDCircle {
        XX_GENCODE_STRUCT_H(CDCircle)
        float x = 0;
        float y = 0;
        float r = 0;
    };
    // 时间点--锁定点线
    struct TimePoint_LockPoints {
        XX_GENCODE_STRUCT_H(TimePoint_LockPoints)
        // 起始时间( 秒 )
        float time = 0;
        // 主锁定点。如果出屏幕，则锁定 锁定线与屏幕边缘形成的 交点
        FileExts::LockPoint mainLockPoint;
        // 锁定线
        std::vector<FileExts::LockPoint> lockPoints;
    };
    // 时间点--碰撞圆集合
    struct TimePoint_CDCircles {
        XX_GENCODE_STRUCT_H(TimePoint_CDCircles)
        // 起始时间( 秒 )
        float time = 0;
        // 最大碰撞圆范围（外包围圆），用于碰撞检测粗判
        FileExts::CDCircle maxCDCircle;
        // 具体碰撞圆列表，用于碰撞检测遍历细判
        std::vector<FileExts::CDCircle> cdCircles;
    };
    // 时间点--移动速度
    struct TimePoint_Speed {
        XX_GENCODE_STRUCT_H(TimePoint_Speed)
        // 起始时间( 秒 )
        float time = 0;
        // 每秒移动距离(米)
        float speed = 0;
    };
    // 时间点--精灵帧
    struct TimePoint_Frame {
        XX_GENCODE_STRUCT_H(TimePoint_Frame)
        // 起始时间( 秒 )
        float time = 0;
        // 精灵帧名称
        std::string picName;
    };
    // 动作( 兼容 spine, c3b, frames )
    struct Action {
        XX_GENCODE_STRUCT_H(Action)
        // 动作名
        std::string name;
        // 总时长( 秒 )
        float totalSeconds = 0;
        // 时间点--锁定点线 集合
        std::vector<FileExts::TimePoint_LockPoints> lps;
        // 时间点--碰撞圆 集合
        std::vector<FileExts::TimePoint_CDCircles> cds;
        // 时间点--速度 集合
        std::vector<FileExts::TimePoint_Speed> ss;
        // 时间点--精灵帧 集合( spine, c3b 时该集合为 0 长 )
        std::vector<FileExts::TimePoint_Frame> fs;
    };
    // 动画 配置文件基类
    struct File_Anim {
        XX_GENCODE_STRUCT_H(File_Anim)
        // 目标文件名
        std::string fileName;
        // 动作集合
        std::vector<FileExts::Action> actions;
    };
    // 移动路线--点
    struct PathwayPoint {
        XX_GENCODE_STRUCT_H(PathwayPoint)
        float x = 0;
        float y = 0;
        // 张力. 默认 0.3. 值越大, 拐角越圆润, 越小越尖
        float tension = 0;
        // 到下一个点的切片数
        int32_t numSegments = 0;
#include "FileExts_PathwayPoint.inc"
    };
    // 精灵帧动画 配置文件( *.frames )
    struct File_frames : FileExts::File_Anim {
        XX_GENCODE_STRUCT_H(File_frames)
    };
    // spine 配置文件( *.atlas.ext )
    struct File_atlas_ext : FileExts::File_Anim {
        XX_GENCODE_STRUCT_H(File_atlas_ext)
    };
    // c3b 配置文件( *.c3b.ext )
    struct File_c3b_ext : FileExts::File_Anim {
        XX_GENCODE_STRUCT_H(File_c3b_ext)
    };
    // 移动路线 配置文件 *.pathway
    struct File_pathway {
        XX_GENCODE_STRUCT_H(File_pathway)
        // 是否闭合. 直线无法闭合。将于头尾多填2点，绘制后裁切掉以确保曲线形状正确
        bool isLoop = false;
        // 点集合. 2 个点为直线，更多点为曲线串联
        std::vector<FileExts::PathwayPoint> points;
    };
}
namespace xx {
	template<>
	struct StringFuncsEx<FileExts::LockPoint, void> {
		static void Append(ObjectHelper &oh, FileExts::LockPoint const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::LockPoint const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::LockPoint, void> {
		static void Write(DataWriterEx& dw, FileExts::LockPoint const& in);
		static int Read(DataReaderEx& dr, FileExts::LockPoint& out);
	};
    template<>
	struct CloneFuncs<FileExts::LockPoint, void> {
		static void Clone1(ObjectHelper &oh, FileExts::LockPoint const& in, FileExts::LockPoint& out);
		static void Clone2(ObjectHelper &oh, FileExts::LockPoint const& in, FileExts::LockPoint& out);
	};
	template<>
	struct StringFuncsEx<FileExts::CDCircle, void> {
		static void Append(ObjectHelper &oh, FileExts::CDCircle const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::CDCircle const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::CDCircle, void> {
		static void Write(DataWriterEx& dw, FileExts::CDCircle const& in);
		static int Read(DataReaderEx& dr, FileExts::CDCircle& out);
	};
    template<>
	struct CloneFuncs<FileExts::CDCircle, void> {
		static void Clone1(ObjectHelper &oh, FileExts::CDCircle const& in, FileExts::CDCircle& out);
		static void Clone2(ObjectHelper &oh, FileExts::CDCircle const& in, FileExts::CDCircle& out);
	};
	template<>
	struct StringFuncsEx<FileExts::TimePoint_LockPoints, void> {
		static void Append(ObjectHelper &oh, FileExts::TimePoint_LockPoints const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::TimePoint_LockPoints const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::TimePoint_LockPoints, void> {
		static void Write(DataWriterEx& dw, FileExts::TimePoint_LockPoints const& in);
		static int Read(DataReaderEx& dr, FileExts::TimePoint_LockPoints& out);
	};
    template<>
	struct CloneFuncs<FileExts::TimePoint_LockPoints, void> {
		static void Clone1(ObjectHelper &oh, FileExts::TimePoint_LockPoints const& in, FileExts::TimePoint_LockPoints& out);
		static void Clone2(ObjectHelper &oh, FileExts::TimePoint_LockPoints const& in, FileExts::TimePoint_LockPoints& out);
	};
	template<>
	struct StringFuncsEx<FileExts::TimePoint_CDCircles, void> {
		static void Append(ObjectHelper &oh, FileExts::TimePoint_CDCircles const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::TimePoint_CDCircles const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::TimePoint_CDCircles, void> {
		static void Write(DataWriterEx& dw, FileExts::TimePoint_CDCircles const& in);
		static int Read(DataReaderEx& dr, FileExts::TimePoint_CDCircles& out);
	};
    template<>
	struct CloneFuncs<FileExts::TimePoint_CDCircles, void> {
		static void Clone1(ObjectHelper &oh, FileExts::TimePoint_CDCircles const& in, FileExts::TimePoint_CDCircles& out);
		static void Clone2(ObjectHelper &oh, FileExts::TimePoint_CDCircles const& in, FileExts::TimePoint_CDCircles& out);
	};
	template<>
	struct StringFuncsEx<FileExts::TimePoint_Speed, void> {
		static void Append(ObjectHelper &oh, FileExts::TimePoint_Speed const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::TimePoint_Speed const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::TimePoint_Speed, void> {
		static void Write(DataWriterEx& dw, FileExts::TimePoint_Speed const& in);
		static int Read(DataReaderEx& dr, FileExts::TimePoint_Speed& out);
	};
    template<>
	struct CloneFuncs<FileExts::TimePoint_Speed, void> {
		static void Clone1(ObjectHelper &oh, FileExts::TimePoint_Speed const& in, FileExts::TimePoint_Speed& out);
		static void Clone2(ObjectHelper &oh, FileExts::TimePoint_Speed const& in, FileExts::TimePoint_Speed& out);
	};
	template<>
	struct StringFuncsEx<FileExts::TimePoint_Frame, void> {
		static void Append(ObjectHelper &oh, FileExts::TimePoint_Frame const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::TimePoint_Frame const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::TimePoint_Frame, void> {
		static void Write(DataWriterEx& dw, FileExts::TimePoint_Frame const& in);
		static int Read(DataReaderEx& dr, FileExts::TimePoint_Frame& out);
	};
    template<>
	struct CloneFuncs<FileExts::TimePoint_Frame, void> {
		static void Clone1(ObjectHelper &oh, FileExts::TimePoint_Frame const& in, FileExts::TimePoint_Frame& out);
		static void Clone2(ObjectHelper &oh, FileExts::TimePoint_Frame const& in, FileExts::TimePoint_Frame& out);
	};
	template<>
	struct StringFuncsEx<FileExts::Action, void> {
		static void Append(ObjectHelper &oh, FileExts::Action const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::Action const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::Action, void> {
		static void Write(DataWriterEx& dw, FileExts::Action const& in);
		static int Read(DataReaderEx& dr, FileExts::Action& out);
	};
    template<>
	struct CloneFuncs<FileExts::Action, void> {
		static void Clone1(ObjectHelper &oh, FileExts::Action const& in, FileExts::Action& out);
		static void Clone2(ObjectHelper &oh, FileExts::Action const& in, FileExts::Action& out);
	};
	template<>
	struct StringFuncsEx<FileExts::File_Anim, void> {
		static void Append(ObjectHelper &oh, FileExts::File_Anim const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::File_Anim const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::File_Anim, void> {
		static void Write(DataWriterEx& dw, FileExts::File_Anim const& in);
		static int Read(DataReaderEx& dr, FileExts::File_Anim& out);
	};
    template<>
	struct CloneFuncs<FileExts::File_Anim, void> {
		static void Clone1(ObjectHelper &oh, FileExts::File_Anim const& in, FileExts::File_Anim& out);
		static void Clone2(ObjectHelper &oh, FileExts::File_Anim const& in, FileExts::File_Anim& out);
	};
	template<>
	struct StringFuncsEx<FileExts::PathwayPoint, void> {
		static void Append(ObjectHelper &oh, FileExts::PathwayPoint const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::PathwayPoint const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::PathwayPoint, void> {
		static void Write(DataWriterEx& dw, FileExts::PathwayPoint const& in);
		static int Read(DataReaderEx& dr, FileExts::PathwayPoint& out);
	};
    template<>
	struct CloneFuncs<FileExts::PathwayPoint, void> {
		static void Clone1(ObjectHelper &oh, FileExts::PathwayPoint const& in, FileExts::PathwayPoint& out);
		static void Clone2(ObjectHelper &oh, FileExts::PathwayPoint const& in, FileExts::PathwayPoint& out);
	};
	template<>
	struct StringFuncsEx<FileExts::File_frames, void> {
		static void Append(ObjectHelper &oh, FileExts::File_frames const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::File_frames const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::File_frames, void> {
		static void Write(DataWriterEx& dw, FileExts::File_frames const& in);
		static int Read(DataReaderEx& dr, FileExts::File_frames& out);
	};
    template<>
	struct CloneFuncs<FileExts::File_frames, void> {
		static void Clone1(ObjectHelper &oh, FileExts::File_frames const& in, FileExts::File_frames& out);
		static void Clone2(ObjectHelper &oh, FileExts::File_frames const& in, FileExts::File_frames& out);
	};
	template<>
	struct StringFuncsEx<FileExts::File_atlas_ext, void> {
		static void Append(ObjectHelper &oh, FileExts::File_atlas_ext const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::File_atlas_ext const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::File_atlas_ext, void> {
		static void Write(DataWriterEx& dw, FileExts::File_atlas_ext const& in);
		static int Read(DataReaderEx& dr, FileExts::File_atlas_ext& out);
	};
    template<>
	struct CloneFuncs<FileExts::File_atlas_ext, void> {
		static void Clone1(ObjectHelper &oh, FileExts::File_atlas_ext const& in, FileExts::File_atlas_ext& out);
		static void Clone2(ObjectHelper &oh, FileExts::File_atlas_ext const& in, FileExts::File_atlas_ext& out);
	};
	template<>
	struct StringFuncsEx<FileExts::File_c3b_ext, void> {
		static void Append(ObjectHelper &oh, FileExts::File_c3b_ext const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::File_c3b_ext const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::File_c3b_ext, void> {
		static void Write(DataWriterEx& dw, FileExts::File_c3b_ext const& in);
		static int Read(DataReaderEx& dr, FileExts::File_c3b_ext& out);
	};
    template<>
	struct CloneFuncs<FileExts::File_c3b_ext, void> {
		static void Clone1(ObjectHelper &oh, FileExts::File_c3b_ext const& in, FileExts::File_c3b_ext& out);
		static void Clone2(ObjectHelper &oh, FileExts::File_c3b_ext const& in, FileExts::File_c3b_ext& out);
	};
	template<>
	struct StringFuncsEx<FileExts::File_pathway, void> {
		static void Append(ObjectHelper &oh, FileExts::File_pathway const& in);
		static void AppendCore(ObjectHelper &oh, FileExts::File_pathway const& in);
    };
	template<>
	struct DataFuncsEx<FileExts::File_pathway, void> {
		static void Write(DataWriterEx& dw, FileExts::File_pathway const& in);
		static int Read(DataReaderEx& dr, FileExts::File_pathway& out);
	};
    template<>
	struct CloneFuncs<FileExts::File_pathway, void> {
		static void Clone1(ObjectHelper &oh, FileExts::File_pathway const& in, FileExts::File_pathway& out);
		static void Clone2(ObjectHelper &oh, FileExts::File_pathway const& in, FileExts::File_pathway& out);
	};
}