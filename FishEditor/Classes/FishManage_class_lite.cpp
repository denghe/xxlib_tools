#include "FishManage_class_lite.h"
#include "FishManage_class_lite.cpp.inc"
namespace FishManage {
    FishBase::FishBase(FishBase&& o) {
        this->operator=(std::move(o));
    }
    FishBase& FishBase::operator=(FishBase&& o) {
        std::swap(this->fishName, o.fishName);
        std::swap(this->baseScale, o.baseScale);
        std::swap(this->coin1, o.coin1);
        std::swap(this->coin2, o.coin2);
        return *this;
    }
    ActionBase::ActionBase(ActionBase&& o) {
        this->operator=(std::move(o));
    }
    ActionBase& ActionBase::operator=(ActionBase&& o) {
        std::swap(this->actionName, o.actionName);
        return *this;
    }
    FrameBase::FrameBase(FrameBase&& o) {
        this->operator=(std::move(o));
    }
    FrameBase& FrameBase::operator=(FrameBase&& o) {
        std::swap(this->moveDistance, o.moveDistance);
        return *this;
    }
    Fish_2D_Frame::Fish_2D_Frame(Fish_2D_Frame&& o) {
        this->operator=(std::move(o));
    }
    Fish_2D_Frame& Fish_2D_Frame::operator=(Fish_2D_Frame&& o) {
        this->FishManage::FrameBase::operator=(std::move(o));
        std::swap(this->spriteFrameName, o.spriteFrameName);
        return *this;
    }
    Fish_2D_Action::Fish_2D_Action(Fish_2D_Action&& o) {
        this->operator=(std::move(o));
    }
    Fish_2D_Action& Fish_2D_Action::operator=(Fish_2D_Action&& o) {
        this->FishManage::ActionBase::operator=(std::move(o));
        std::swap(this->frames, o.frames);
        return *this;
    }
    Fish_2D::Fish_2D(Fish_2D&& o) {
        this->operator=(std::move(o));
    }
    Fish_2D& Fish_2D::operator=(Fish_2D&& o) {
        this->FishManage::FishBase::operator=(std::move(o));
        std::swap(this->actions, o.actions);
        std::swap(this->plistFileNames, o.plistFileNames);
        return *this;
    }
    Fish_Spine_Frame::Fish_Spine_Frame(Fish_Spine_Frame&& o) {
        this->operator=(std::move(o));
    }
    Fish_Spine_Frame& Fish_Spine_Frame::operator=(Fish_Spine_Frame&& o) {
        this->FishManage::FrameBase::operator=(std::move(o));
        return *this;
    }
    Fish_Spine_Action::Fish_Spine_Action(Fish_Spine_Action&& o) {
        this->operator=(std::move(o));
    }
    Fish_Spine_Action& Fish_Spine_Action::operator=(Fish_Spine_Action&& o) {
        this->FishManage::ActionBase::operator=(std::move(o));
        std::swap(this->frames, o.frames);
        return *this;
    }
    Fish_Spine::Fish_Spine(Fish_Spine&& o) {
        this->operator=(std::move(o));
    }
    Fish_Spine& Fish_Spine::operator=(Fish_Spine&& o) {
        this->FishManage::FishBase::operator=(std::move(o));
        std::swap(this->atlasFileName, o.atlasFileName);
        std::swap(this->actions, o.actions);
        return *this;
    }
    Fish_3D_Frame::Fish_3D_Frame(Fish_3D_Frame&& o) {
        this->operator=(std::move(o));
    }
    Fish_3D_Frame& Fish_3D_Frame::operator=(Fish_3D_Frame&& o) {
        this->FishManage::FrameBase::operator=(std::move(o));
        return *this;
    }
    Fish_3D_Action::Fish_3D_Action(Fish_3D_Action&& o) {
        this->operator=(std::move(o));
    }
    Fish_3D_Action& Fish_3D_Action::operator=(Fish_3D_Action&& o) {
        this->FishManage::ActionBase::operator=(std::move(o));
        std::swap(this->frames, o.frames);
        return *this;
    }
    Fish_3D::Fish_3D(Fish_3D&& o) {
        this->operator=(std::move(o));
    }
    Fish_3D& Fish_3D::operator=(Fish_3D&& o) {
        this->FishManage::FishBase::operator=(std::move(o));
        std::swap(this->c3bFileName, o.c3bFileName);
        std::swap(this->baseAngleX, o.baseAngleX);
        std::swap(this->baseAngleY, o.baseAngleY);
        std::swap(this->baseAngleZ, o.baseAngleZ);
        std::swap(this->actions, o.actions);
        return *this;
    }
    Fish_Combine_Child::Fish_Combine_Child(Fish_Combine_Child&& o) {
        this->operator=(std::move(o));
    }
    Fish_Combine_Child& Fish_Combine_Child::operator=(Fish_Combine_Child&& o) {
        std::swap(this->fishTypeId, o.fishTypeId);
        std::swap(this->index, o.index);
        std::swap(this->offsetX, o.offsetX);
        std::swap(this->offsetY, o.offsetY);
        std::swap(this->baseAngle, o.baseAngle);
        std::swap(this->baseScale, o.baseScale);
        return *this;
    }
    Fish_Combine_Action::Fish_Combine_Action(Fish_Combine_Action&& o) {
        this->operator=(std::move(o));
    }
    Fish_Combine_Action& Fish_Combine_Action::operator=(Fish_Combine_Action&& o) {
        this->FishManage::ActionBase::operator=(std::move(o));
        return *this;
    }
    Fish_Combine::Fish_Combine(Fish_Combine&& o) {
        this->operator=(std::move(o));
    }
    Fish_Combine& Fish_Combine::operator=(Fish_Combine&& o) {
        this->FishManage::FishBase::operator=(std::move(o));
        std::swap(this->childs, o.childs);
        std::swap(this->actions, o.actions);
        return *this;
    }
    Data::Data(Data&& o) {
        this->operator=(std::move(o));
    }
    Data& Data::operator=(Data&& o) {
        std::swap(this->fish_2ds, o.fish_2ds);
        std::swap(this->fish_spines, o.fish_spines);
        std::swap(this->fish_3ds, o.fish_3ds);
        std::swap(this->fish_combines, o.fish_combines);
        return *this;
    }
}
namespace xx {
	void DataFuncs<FishManage::FishBase, void>::Write(Data& d, FishManage::FishBase const& in) noexcept {
        ::xx::Write(d, in.fishName);
        ::xx::Write(d, in.baseScale);
        ::xx::Write(d, in.coin1);
        ::xx::Write(d, in.coin2);
    }
	int DataFuncs<FishManage::FishBase, void>::Read(DataReader& d, FishManage::FishBase& out) noexcept {
        if (int r = d.Read(out.fishName)) return r;
        if (int r = d.Read(out.baseScale)) return r;
        if (int r = d.Read(out.coin1)) return r;
        if (int r = d.Read(out.coin2)) return r;
        return 0;
    }
	void DataFuncs<FishManage::ActionBase, void>::Write(Data& d, FishManage::ActionBase const& in) noexcept {
        ::xx::Write(d, in.actionName);
    }
	int DataFuncs<FishManage::ActionBase, void>::Read(DataReader& d, FishManage::ActionBase& out) noexcept {
        if (int r = d.Read(out.actionName)) return r;
        return 0;
    }
	void DataFuncs<FishManage::FrameBase, void>::Write(Data& d, FishManage::FrameBase const& in) noexcept {
        ::xx::Write(d, in.moveDistance);
    }
	int DataFuncs<FishManage::FrameBase, void>::Read(DataReader& d, FishManage::FrameBase& out) noexcept {
        if (int r = d.Read(out.moveDistance)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Fish_2D_Frame, void>::Write(Data& d, FishManage::Fish_2D_Frame const& in) noexcept {
        DataFuncs<FishManage::FrameBase>::Write(d, in);
        ::xx::Write(d, in.spriteFrameName);
    }
	int DataFuncs<FishManage::Fish_2D_Frame, void>::Read(DataReader& d, FishManage::Fish_2D_Frame& out) noexcept {
        if (int r = DataFuncs<FishManage::FrameBase>::Read(d, out)) return r;
        if (int r = d.Read(out.spriteFrameName)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Fish_2D_Action, void>::Write(Data& d, FishManage::Fish_2D_Action const& in) noexcept {
        DataFuncs<FishManage::ActionBase>::Write(d, in);
        ::xx::Write(d, in.frames);
    }
	int DataFuncs<FishManage::Fish_2D_Action, void>::Read(DataReader& d, FishManage::Fish_2D_Action& out) noexcept {
        if (int r = DataFuncs<FishManage::ActionBase>::Read(d, out)) return r;
        if (int r = d.Read(out.frames)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Fish_2D, void>::Write(Data& d, FishManage::Fish_2D const& in) noexcept {
        DataFuncs<FishManage::FishBase>::Write(d, in);
        ::xx::Write(d, in.actions);
        ::xx::Write(d, in.plistFileNames);
    }
	int DataFuncs<FishManage::Fish_2D, void>::Read(DataReader& d, FishManage::Fish_2D& out) noexcept {
        if (int r = DataFuncs<FishManage::FishBase>::Read(d, out)) return r;
        if (int r = d.Read(out.actions)) return r;
        if (int r = d.Read(out.plistFileNames)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Fish_Spine_Frame, void>::Write(Data& d, FishManage::Fish_Spine_Frame const& in) noexcept {
        DataFuncs<FishManage::FrameBase>::Write(d, in);
    }
	int DataFuncs<FishManage::Fish_Spine_Frame, void>::Read(DataReader& d, FishManage::Fish_Spine_Frame& out) noexcept {
        if (int r = DataFuncs<FishManage::FrameBase>::Read(d, out)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Fish_Spine_Action, void>::Write(Data& d, FishManage::Fish_Spine_Action const& in) noexcept {
        DataFuncs<FishManage::ActionBase>::Write(d, in);
        ::xx::Write(d, in.frames);
    }
	int DataFuncs<FishManage::Fish_Spine_Action, void>::Read(DataReader& d, FishManage::Fish_Spine_Action& out) noexcept {
        if (int r = DataFuncs<FishManage::ActionBase>::Read(d, out)) return r;
        if (int r = d.Read(out.frames)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Fish_Spine, void>::Write(Data& d, FishManage::Fish_Spine const& in) noexcept {
        DataFuncs<FishManage::FishBase>::Write(d, in);
        ::xx::Write(d, in.atlasFileName);
        ::xx::Write(d, in.actions);
    }
	int DataFuncs<FishManage::Fish_Spine, void>::Read(DataReader& d, FishManage::Fish_Spine& out) noexcept {
        if (int r = DataFuncs<FishManage::FishBase>::Read(d, out)) return r;
        if (int r = d.Read(out.atlasFileName)) return r;
        if (int r = d.Read(out.actions)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Fish_3D_Frame, void>::Write(Data& d, FishManage::Fish_3D_Frame const& in) noexcept {
        DataFuncs<FishManage::FrameBase>::Write(d, in);
    }
	int DataFuncs<FishManage::Fish_3D_Frame, void>::Read(DataReader& d, FishManage::Fish_3D_Frame& out) noexcept {
        if (int r = DataFuncs<FishManage::FrameBase>::Read(d, out)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Fish_3D_Action, void>::Write(Data& d, FishManage::Fish_3D_Action const& in) noexcept {
        DataFuncs<FishManage::ActionBase>::Write(d, in);
        ::xx::Write(d, in.frames);
    }
	int DataFuncs<FishManage::Fish_3D_Action, void>::Read(DataReader& d, FishManage::Fish_3D_Action& out) noexcept {
        if (int r = DataFuncs<FishManage::ActionBase>::Read(d, out)) return r;
        if (int r = d.Read(out.frames)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Fish_3D, void>::Write(Data& d, FishManage::Fish_3D const& in) noexcept {
        DataFuncs<FishManage::FishBase>::Write(d, in);
        ::xx::Write(d, in.c3bFileName);
        ::xx::Write(d, in.baseAngleX);
        ::xx::Write(d, in.baseAngleY);
        ::xx::Write(d, in.baseAngleZ);
        ::xx::Write(d, in.actions);
    }
	int DataFuncs<FishManage::Fish_3D, void>::Read(DataReader& d, FishManage::Fish_3D& out) noexcept {
        if (int r = DataFuncs<FishManage::FishBase>::Read(d, out)) return r;
        if (int r = d.Read(out.c3bFileName)) return r;
        if (int r = d.Read(out.baseAngleX)) return r;
        if (int r = d.Read(out.baseAngleY)) return r;
        if (int r = d.Read(out.baseAngleZ)) return r;
        if (int r = d.Read(out.actions)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Fish_Combine_Child, void>::Write(Data& d, FishManage::Fish_Combine_Child const& in) noexcept {
        ::xx::Write(d, in.fishTypeId);
        ::xx::Write(d, in.index);
        ::xx::Write(d, in.offsetX);
        ::xx::Write(d, in.offsetY);
        ::xx::Write(d, in.baseAngle);
        ::xx::Write(d, in.baseScale);
    }
	int DataFuncs<FishManage::Fish_Combine_Child, void>::Read(DataReader& d, FishManage::Fish_Combine_Child& out) noexcept {
        if (int r = d.Read(out.fishTypeId)) return r;
        if (int r = d.Read(out.index)) return r;
        if (int r = d.Read(out.offsetX)) return r;
        if (int r = d.Read(out.offsetY)) return r;
        if (int r = d.Read(out.baseAngle)) return r;
        if (int r = d.Read(out.baseScale)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Fish_Combine_Action, void>::Write(Data& d, FishManage::Fish_Combine_Action const& in) noexcept {
        DataFuncs<FishManage::ActionBase>::Write(d, in);
    }
	int DataFuncs<FishManage::Fish_Combine_Action, void>::Read(DataReader& d, FishManage::Fish_Combine_Action& out) noexcept {
        if (int r = DataFuncs<FishManage::ActionBase>::Read(d, out)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Fish_Combine, void>::Write(Data& d, FishManage::Fish_Combine const& in) noexcept {
        DataFuncs<FishManage::FishBase>::Write(d, in);
        ::xx::Write(d, in.childs);
        ::xx::Write(d, in.actions);
    }
	int DataFuncs<FishManage::Fish_Combine, void>::Read(DataReader& d, FishManage::Fish_Combine& out) noexcept {
        if (int r = DataFuncs<FishManage::FishBase>::Read(d, out)) return r;
        if (int r = d.Read(out.childs)) return r;
        if (int r = d.Read(out.actions)) return r;
        return 0;
    }
	void DataFuncs<FishManage::Data, void>::Write(Data& d, FishManage::Data const& in) noexcept {
        ::xx::Write(d, in.fish_2ds);
        ::xx::Write(d, in.fish_spines);
        ::xx::Write(d, in.fish_3ds);
        ::xx::Write(d, in.fish_combines);
    }
	int DataFuncs<FishManage::Data, void>::Read(DataReader& d, FishManage::Data& out) noexcept {
        if (int r = d.Read(out.fish_2ds)) return r;
        if (int r = d.Read(out.fish_spines)) return r;
        if (int r = d.Read(out.fish_3ds)) return r;
        if (int r = d.Read(out.fish_combines)) return r;
        return 0;
    }
}
