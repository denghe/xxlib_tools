#include "Pathway_class_lite.h"
#include "Pathway_class_lite.cpp.inc"
namespace Pathway {
    Point::Point(Point&& o) {
        this->operator=(std::move(o));
    }
    Point& Point::operator=(Point&& o) {
        std::swap(this->x, o.x);
        std::swap(this->y, o.y);
        std::swap(this->z, o.z);
        std::swap(this->tension, o.tension);
        std::swap(this->numSegments, o.numSegments);
        return *this;
    }
    Line::Line(Line&& o) {
        this->operator=(std::move(o));
    }
    Line& Line::operator=(Line&& o) {
        std::swap(this->name, o.name);
        std::swap(this->isLoop, o.isLoop);
        std::swap(this->points, o.points);
        return *this;
    }
    Group::Group(Group&& o) {
        this->operator=(std::move(o));
    }
    Group& Group::operator=(Group&& o) {
        std::swap(this->name, o.name);
        std::swap(this->lineIndexs, o.lineIndexs);
        return *this;
    }
    Data::Data(Data&& o) {
        this->operator=(std::move(o));
    }
    Data& Data::operator=(Data&& o) {
        std::swap(this->designWidth, o.designWidth);
        std::swap(this->designHeight, o.designHeight);
        std::swap(this->safeLength, o.safeLength);
        std::swap(this->lines, o.lines);
        std::swap(this->groups, o.groups);
        return *this;
    }
}
namespace xx {
	void DataFuncs<Pathway::Point, void>::Write(Data& d, Pathway::Point const& in) noexcept {
        ::xx::Write(d, in.x);
        ::xx::Write(d, in.y);
        ::xx::Write(d, in.z);
        ::xx::Write(d, in.tension);
        ::xx::Write(d, in.numSegments);
    }
	int DataFuncs<Pathway::Point, void>::Read(DataReader& d, Pathway::Point& out) noexcept {
        if (int r = d.Read(out.x)) return r;
        if (int r = d.Read(out.y)) return r;
        if (int r = d.Read(out.z)) return r;
        if (int r = d.Read(out.tension)) return r;
        if (int r = d.Read(out.numSegments)) return r;
        return 0;
    }
	void DataFuncs<Pathway::Line, void>::Write(Data& d, Pathway::Line const& in) noexcept {
        ::xx::Write(d, in.name);
        ::xx::Write(d, in.isLoop);
        ::xx::Write(d, in.points);
    }
	int DataFuncs<Pathway::Line, void>::Read(DataReader& d, Pathway::Line& out) noexcept {
        if (int r = d.Read(out.name)) return r;
        if (int r = d.Read(out.isLoop)) return r;
        if (int r = d.Read(out.points)) return r;
        return 0;
    }
	void DataFuncs<Pathway::Group, void>::Write(Data& d, Pathway::Group const& in) noexcept {
        ::xx::Write(d, in.name);
        ::xx::Write(d, in.lineIndexs);
    }
	int DataFuncs<Pathway::Group, void>::Read(DataReader& d, Pathway::Group& out) noexcept {
        if (int r = d.Read(out.name)) return r;
        if (int r = d.Read(out.lineIndexs)) return r;
        return 0;
    }
	void DataFuncs<Pathway::Data, void>::Write(Data& d, Pathway::Data const& in) noexcept {
        ::xx::Write(d, in.designWidth);
        ::xx::Write(d, in.designHeight);
        ::xx::Write(d, in.safeLength);
        ::xx::Write(d, in.lines);
        ::xx::Write(d, in.groups);
    }
	int DataFuncs<Pathway::Data, void>::Read(DataReader& d, Pathway::Data& out) noexcept {
        if (int r = d.Read(out.designWidth)) return r;
        if (int r = d.Read(out.designHeight)) return r;
        if (int r = d.Read(out.safeLength)) return r;
        if (int r = d.Read(out.lines)) return r;
        if (int r = d.Read(out.groups)) return r;
        return 0;
    }
}
