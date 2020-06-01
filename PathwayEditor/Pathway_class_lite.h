#pragma once
#include "xx_data_view.h"
namespace Pathway {
	struct PkgGenMd5 {
		inline static const std::string value = "#*MD5<a42c3f62352d6a4075f86e6f59b52d9a>*#";
    };

    // 线
    struct Line {
        // 途经点集合. 2 个点为直线，更多点为曲线串联
        std::vector<::xx::Point> points;
        // 张力. 默认 0.3. 值越大, 倒角越圆润, 越小越尖
        float tension = 0;
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



namespace Pathway {
    inline Line::Line(Line&& o) {
        this->operator=(std::move(o));
    }
    inline Line& Line::operator=(Line&& o) {
        std::swap(this->points, o.points);
        std::swap(this->tension, o.tension);
        std::swap(this->isLoop, o.isLoop);
        return *this;
    }
    inline Group::Group(Group&& o) {
        this->operator=(std::move(o));
    }
    inline Group& Group::operator=(Group&& o) {
        std::swap(this->name, o.name);
        std::swap(this->lineIndexs, o.lineIndexs);
        return *this;
    }
    inline Data::Data(Data&& o) {
        this->operator=(std::move(o));
    }
    inline Data& Data::operator=(Data&& o) {
        std::swap(this->lines, o.lines);
        std::swap(this->groups, o.groups);
        return *this;
    }
}
namespace xx {
	inline void DataFuncs<Pathway::Line, void>::Write(Data& d, Pathway::Line const& in) noexcept {
        ::xx::Write(d, in.points);
        ::xx::Write(d, in.tension);
        ::xx::Write(d, in.isLoop);
    }
	inline int DataFuncs<Pathway::Line, void>::Read(DataReader& d, Pathway::Line& out) noexcept {
        if (int r = d.Read(out.points)) return r;
        if (int r = d.Read(out.tension)) return r;
        if (int r = d.Read(out.isLoop)) return r;
        return 0;
    }
	inline void DataFuncs<Pathway::Group, void>::Write(Data& d, Pathway::Group const& in) noexcept {
        ::xx::Write(d, in.name);
        ::xx::Write(d, in.lineIndexs);
    }
	inline int DataFuncs<Pathway::Group, void>::Read(DataReader& d, Pathway::Group& out) noexcept {
        if (int r = d.Read(out.name)) return r;
        if (int r = d.Read(out.lineIndexs)) return r;
        return 0;
    }
	inline void DataFuncs<Pathway::Data, void>::Write(Data& d, Pathway::Data const& in) noexcept {
        ::xx::Write(d, in.lines);
        ::xx::Write(d, in.groups);
    }
	inline int DataFuncs<Pathway::Data, void>::Read(DataReader& d, Pathway::Data& out) noexcept {
        if (int r = d.Read(out.lines)) return r;
        if (int r = d.Read(out.groups)) return r;
        return 0;
    }
}
