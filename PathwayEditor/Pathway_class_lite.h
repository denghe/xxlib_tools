﻿#pragma once
#include "xx_datareader.h"
#include "Pathway_class_lite.h.inc"  // user create it for extend include files
namespace Pathway {
	struct PkgGenMd5 {
		inline static const std::string value = "#*MD5<75cd629ed6827ca2d50c8137b9ff5f1c>*#";
    };

    // 点
    struct Point {
        float x = 0;
        float y = 0;
        float z = 0;
        // 张力. 默认 0.3. 值越大, 倒角越圆润, 越小越尖
        float tension = 0;
        // 到下一个点的切片数
        int32_t numSegments = 0;

        Point() = default;
        Point(Point const&) = default;
        Point& operator=(Point const&) = default;
        Point(Point&& o);
        Point& operator=(Point&& o);
#include "Pathway_Point.inc"
    };
    // 线
    struct Line {
        // 途经点集合. 2 个点为直线，更多点为曲线串联
        std::vector<Pathway::Point> points;
        // 是否闭合. 直线无法闭合。将于头尾多填2点，绘制后裁切掉以确保曲线形状正确
        bool isLoop = false;

        Line() = default;
        Line(Line const&) = default;
        Line& operator=(Line const&) = default;
        Line(Line&& o);
        Line& operator=(Line&& o);
    };
    // 组: 定位到线的分组依据
    struct Group {
        // 唯一名称( 编辑时显示用. 也可用于查找 )
        std::string name;
        // 组成员：Data.lines 下标集合
        std::vector<int32_t> lineIndexs;

        Group() = default;
        Group(Group const&) = default;
        Group& operator=(Group const&) = default;
        Group(Group&& o);
        Group& operator=(Group&& o);
    };
    // 所有数据
    struct Data {
        // 线集合
        std::vector<Pathway::Line> lines;
        // 组集合
        std::vector<Pathway::Group> groups;

        Data() = default;
        Data(Data const&) = default;
        Data& operator=(Data const&) = default;
        Data(Data&& o);
        Data& operator=(Data&& o);
    };
}
namespace xx {
	template<>
	struct DataFuncs<Pathway::Point, void> {
		static void Write(Data& d, Pathway::Point const& in) noexcept;
		static int Read(DataReader& d, Pathway::Point& out) noexcept;
	};
	template<>
	struct DataFuncs<Pathway::Line, void> {
		static void Write(Data& d, Pathway::Line const& in) noexcept;
		static int Read(DataReader& d, Pathway::Line& out) noexcept;
	};
	template<>
	struct DataFuncs<Pathway::Group, void> {
		static void Write(Data& d, Pathway::Group const& in) noexcept;
		static int Read(DataReader& d, Pathway::Group& out) noexcept;
	};
	template<>
	struct DataFuncs<Pathway::Data, void> {
		static void Write(Data& d, Pathway::Data const& in) noexcept;
		static int Read(DataReader& d, Pathway::Data& out) noexcept;
	};
}