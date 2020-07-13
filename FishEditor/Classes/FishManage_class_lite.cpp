#include "FishManage_class_lite.h"
#include "FishManage_class_lite.cpp.inc"
namespace xx {
    template<> struct TypeId<FishManage::FishBase> { static const uint16_t value = 9; };
    template<> struct TypeId<FishManage::ResBase> { static const uint16_t value = 1; };
    template<> struct TypeId<FishManage::ActionBase> { static const uint16_t value = 2; };
    template<> struct TypeId<FishManage::FrameBase> { static const uint16_t value = 3; };
    template<> struct TypeId<FishManage::FishFury> { static const uint16_t value = 13; };
    template<> struct TypeId<FishManage::FishDrill> { static const uint16_t value = 12; };
    template<> struct TypeId<FishManage::FishBomb> { static const uint16_t value = 11; };
    template<> struct TypeId<FishManage::FishNormal> { static const uint16_t value = 10; };
    template<> struct TypeId<FishManage::ResCombine> { static const uint16_t value = 8; };
    template<> struct TypeId<FishManage::ActionSpine> { static const uint16_t value = 16; };
    template<> struct TypeId<FishManage::Res3d> { static const uint16_t value = 7; };
    template<> struct TypeId<FishManage::FishCyclone> { static const uint16_t value = 14; };
    template<> struct TypeId<FishManage::ResSpine> { static const uint16_t value = 6; };
    template<> struct TypeId<FishManage::Frame2d> { static const uint16_t value = 5; };
    template<> struct TypeId<FishManage::Action2d> { static const uint16_t value = 18; };
    template<> struct TypeId<FishManage::Res2d> { static const uint16_t value = 4; };
    template<> struct TypeId<FishManage::Action3d> { static const uint16_t value = 17; };
    template<> struct TypeId<FishManage::FishEater> { static const uint16_t value = 15; };
}
namespace FishManage {
	void PkgGenTypes::RegisterTo(xx::ObjectCreators& oc) {
	    oc.Register<FishManage::ResBase>();
	    oc.Register<FishManage::ActionBase>();
	    oc.Register<FishManage::FrameBase>();
	    oc.Register<FishManage::Res2d>();
	    oc.Register<FishManage::Action2d>();
	    oc.Register<FishManage::Frame2d>();
	    oc.Register<FishManage::ResSpine>();
	    oc.Register<FishManage::ActionSpine>();
	    oc.Register<FishManage::Res3d>();
	    oc.Register<FishManage::Action3d>();
	    oc.Register<FishManage::ResCombine>();
	    oc.Register<FishManage::FishBase>();
	    oc.Register<FishManage::FishNormal>();
	    oc.Register<FishManage::FishBomb>();
	    oc.Register<FishManage::FishDrill>();
	    oc.Register<FishManage::FishFury>();
	    oc.Register<FishManage::FishCyclone>();
	    oc.Register<FishManage::FishEater>();
	}
}

namespace xx {
	void DataFuncsEx<FishManage::CDCircle, void>::Write(DataWriterEx& dw, FishManage::CDCircle const& in) {
        dw.Write(in.x);
        dw.Write(in.y);
        dw.Write(in.r);
    }
	int DataFuncsEx<FishManage::CDCircle, void>::Read(DataReaderEx& d, FishManage::CDCircle& out) {
        if (int r = d.Read(out.x)) return r;
        if (int r = d.Read(out.y)) return r;
        if (int r = d.Read(out.r)) return r;
        return 0;
    }
	void StringFuncs<FishManage::CDCircle, void>::Append(std::string& s, FishManage::CDCircle const& in) {
        s.push_back('{');
        AppendCore(s, in);
        s.push_back('}');
    }
	void StringFuncs<FishManage::CDCircle, void>::AppendCore(std::string& s, FishManage::CDCircle const& in) {
        auto sizeBak = s.size();
        if (sizeBak == s.size()) {
            s.push_back(',');
        }
        xx::Append(s, "\"x\":", in.x); 
        xx::Append(s, ",\"y\":", in.y);
        xx::Append(s, ",\"r\":", in.r);
    }
	void DataFuncsEx<FishManage::LockPoint, void>::Write(DataWriterEx& dw, FishManage::LockPoint const& in) {
        dw.Write(in.x);
        dw.Write(in.y);
    }
	int DataFuncsEx<FishManage::LockPoint, void>::Read(DataReaderEx& d, FishManage::LockPoint& out) {
        if (int r = d.Read(out.x)) return r;
        if (int r = d.Read(out.y)) return r;
        return 0;
    }
	void StringFuncs<FishManage::LockPoint, void>::Append(std::string& s, FishManage::LockPoint const& in) {
        s.push_back('{');
        AppendCore(s, in);
        s.push_back('}');
    }
	void StringFuncs<FishManage::LockPoint, void>::AppendCore(std::string& s, FishManage::LockPoint const& in) {
        auto sizeBak = s.size();
        if (sizeBak == s.size()) {
            s.push_back(',');
        }
        xx::Append(s, "\"x\":", in.x); 
        xx::Append(s, ",\"y\":", in.y);
    }
	void DataFuncsEx<FishManage::Data, void>::Write(DataWriterEx& dw, FishManage::Data const& in) {
        dw.Write(in.ress);
        dw.Write(in.fishs);
    }
	int DataFuncsEx<FishManage::Data, void>::Read(DataReaderEx& d, FishManage::Data& out) {
        if (int r = d.Read(out.ress)) return r;
        if (int r = d.Read(out.fishs)) return r;
        return 0;
    }
	void StringFuncs<FishManage::Data, void>::Append(std::string& s, FishManage::Data const& in) {
        s.push_back('{');
        AppendCore(s, in);
        s.push_back('}');
    }
	void StringFuncs<FishManage::Data, void>::AppendCore(std::string& s, FishManage::Data const& in) {
        auto sizeBak = s.size();
        if (sizeBak == s.size()) {
            s.push_back(',');
        }
        xx::Append(s, "\"ress\":", in.ress); 
        xx::Append(s, ",\"fishs\":", in.fishs);
    }
	void DataFuncsEx<FishManage::CombineItem, void>::Write(DataWriterEx& dw, FishManage::CombineItem const& in) {
        dw.Write(in.res);
        dw.Write(in.offsetX);
        dw.Write(in.offsetY);
        dw.Write(in.baseAngle);
        dw.Write(in.baseScale);
    }
	int DataFuncsEx<FishManage::CombineItem, void>::Read(DataReaderEx& d, FishManage::CombineItem& out) {
        if (int r = d.Read(out.res)) return r;
        if (int r = d.Read(out.offsetX)) return r;
        if (int r = d.Read(out.offsetY)) return r;
        if (int r = d.Read(out.baseAngle)) return r;
        if (int r = d.Read(out.baseScale)) return r;
        return 0;
    }
	void StringFuncs<FishManage::CombineItem, void>::Append(std::string& s, FishManage::CombineItem const& in) {
        s.push_back('{');
        AppendCore(s, in);
        s.push_back('}');
    }
	void StringFuncs<FishManage::CombineItem, void>::AppendCore(std::string& s, FishManage::CombineItem const& in) {
        auto sizeBak = s.size();
        if (sizeBak == s.size()) {
            s.push_back(',');
        }
        xx::Append(s, "\"res\":", in.res); 
        xx::Append(s, ",\"offsetX\":", in.offsetX);
        xx::Append(s, ",\"offsetY\":", in.offsetY);
        xx::Append(s, ",\"baseAngle\":", in.baseAngle);
        xx::Append(s, ",\"baseScale\":", in.baseScale);
    }
}
namespace FishManage {
    FishBase::FishBase(FishBase&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishBase& FishBase::operator=(FishBase&& o) noexcept {
        std::swap(this->fishName, o.fishName);
        std::swap(this->coin1, o.coin1);
        std::swap(this->coin2, o.coin2);
        std::swap(this->pathwayGroupName, o.pathwayGroupName);
        std::swap(this->res, o.res);
        return *this;
    }
    uint16_t FishBase::GetTypeId() const {
        return xx::TypeId_v<FishManage::FishBase>;
    }
    void FishBase::Serialize(xx::DataWriterEx& dw) const {
        dw.Write(this->fishName);
        dw.Write(this->coin1);
        dw.Write(this->coin2);
        dw.Write(this->pathwayGroupName);
        dw.Write(this->res);
    }
    int FishBase::Deserialize(xx::DataReaderEx& dr) {
        if (int r = dr.Read(this->fishName)) return r;
        if (int r = dr.Read(this->coin1)) return r;
        if (int r = dr.Read(this->coin2)) return r;
        if (int r = dr.Read(this->pathwayGroupName)) return r;
        if (int r = dr.Read(this->res)) return r;
        return 0;
    }
    void FishBase::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((FishBase*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((FishBase*)this)->toStringFlag = false;
    }
    void FishBase::ToStringCore(std::string& s) const {
        xx::Append(s, ",\"fishName\":", this->fishName);
        xx::Append(s, ",\"coin1\":", this->coin1);
        xx::Append(s, ",\"coin2\":", this->coin2);
        xx::Append(s, ",\"pathwayGroupName\":", this->pathwayGroupName);
        xx::Append(s, ",\"res\":", this->res);
    }
    ResBase::ResBase(ResBase&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResBase& ResBase::operator=(ResBase&& o) noexcept {
        std::swap(this->name, o.name);
        std::swap(this->baseScale, o.baseScale);
        std::swap(this->actions, o.actions);
        return *this;
    }
    uint16_t ResBase::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResBase>;
    }
    void ResBase::Serialize(xx::DataWriterEx& dw) const {
        dw.Write(this->name);
        dw.Write(this->baseScale);
        dw.Write(this->actions);
    }
    int ResBase::Deserialize(xx::DataReaderEx& dr) {
        if (int r = dr.Read(this->name)) return r;
        if (int r = dr.Read(this->baseScale)) return r;
        if (int r = dr.Read(this->actions)) return r;
        return 0;
    }
    void ResBase::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((ResBase*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((ResBase*)this)->toStringFlag = false;
    }
    void ResBase::ToStringCore(std::string& s) const {
        xx::Append(s, ",\"name\":", this->name);
        xx::Append(s, ",\"baseScale\":", this->baseScale);
        xx::Append(s, ",\"actions\":", this->actions);
    }
    ActionBase::ActionBase(ActionBase&& o) noexcept {
        this->operator=(std::move(o));
    }
    ActionBase& ActionBase::operator=(ActionBase&& o) noexcept {
        std::swap(this->name, o.name);
        std::swap(this->frameRate, o.frameRate);
        std::swap(this->frames, o.frames);
        return *this;
    }
    uint16_t ActionBase::GetTypeId() const {
        return xx::TypeId_v<FishManage::ActionBase>;
    }
    void ActionBase::Serialize(xx::DataWriterEx& dw) const {
        dw.Write(this->name);
        dw.Write(this->frameRate);
        dw.Write(this->frames);
    }
    int ActionBase::Deserialize(xx::DataReaderEx& dr) {
        if (int r = dr.Read(this->name)) return r;
        if (int r = dr.Read(this->frameRate)) return r;
        if (int r = dr.Read(this->frames)) return r;
        return 0;
    }
    void ActionBase::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((ActionBase*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((ActionBase*)this)->toStringFlag = false;
    }
    void ActionBase::ToStringCore(std::string& s) const {
        xx::Append(s, ",\"name\":", this->name);
        xx::Append(s, ",\"frameRate\":", this->frameRate);
        xx::Append(s, ",\"frames\":", this->frames);
    }
    CDCircle::CDCircle(CDCircle&& o) noexcept {
        this->operator=(std::move(o));
    }
    CDCircle& CDCircle::operator=(CDCircle&& o) noexcept {
        std::swap(this->x, o.x);
        std::swap(this->y, o.y);
        std::swap(this->r, o.r);
        return *this;
    }
    LockPoint::LockPoint(LockPoint&& o) noexcept {
        this->operator=(std::move(o));
    }
    LockPoint& LockPoint::operator=(LockPoint&& o) noexcept {
        std::swap(this->x, o.x);
        std::swap(this->y, o.y);
        return *this;
    }
    FrameBase::FrameBase(FrameBase&& o) noexcept {
        this->operator=(std::move(o));
    }
    FrameBase& FrameBase::operator=(FrameBase&& o) noexcept {
        std::swap(this->moveDistance, o.moveDistance);
        std::swap(this->maxCDCircle, o.maxCDCircle);
        std::swap(this->cdCircles, o.cdCircles);
        std::swap(this->mainLockPoint, o.mainLockPoint);
        std::swap(this->lockPoints, o.lockPoints);
        return *this;
    }
    uint16_t FrameBase::GetTypeId() const {
        return xx::TypeId_v<FishManage::FrameBase>;
    }
    void FrameBase::Serialize(xx::DataWriterEx& dw) const {
        dw.Write(this->moveDistance);
        dw.Write(this->maxCDCircle);
        dw.Write(this->cdCircles);
        dw.Write(this->mainLockPoint);
        dw.Write(this->lockPoints);
    }
    int FrameBase::Deserialize(xx::DataReaderEx& dr) {
        if (int r = dr.Read(this->moveDistance)) return r;
        if (int r = dr.Read(this->maxCDCircle)) return r;
        if (int r = dr.Read(this->cdCircles)) return r;
        if (int r = dr.Read(this->mainLockPoint)) return r;
        if (int r = dr.Read(this->lockPoints)) return r;
        return 0;
    }
    void FrameBase::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((FrameBase*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((FrameBase*)this)->toStringFlag = false;
    }
    void FrameBase::ToStringCore(std::string& s) const {
        xx::Append(s, ",\"moveDistance\":", this->moveDistance);
        xx::Append(s, ",\"maxCDCircle\":", this->maxCDCircle);
        xx::Append(s, ",\"cdCircles\":", this->cdCircles);
        xx::Append(s, ",\"mainLockPoint\":", this->mainLockPoint);
        xx::Append(s, ",\"lockPoints\":", this->lockPoints);
    }
    Data::Data(Data&& o) noexcept {
        this->operator=(std::move(o));
    }
    Data& Data::operator=(Data&& o) noexcept {
        std::swap(this->ress, o.ress);
        std::swap(this->fishs, o.fishs);
        return *this;
    }
    FishFury::FishFury(FishFury&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishFury& FishFury::operator=(FishFury&& o) noexcept {
        this->FishManage::FishBase::operator=(std::move(o));
        std::swap(this->numBulletsPerShoot, o.numBulletsPerShoot);
        return *this;
    }
    uint16_t FishFury::GetTypeId() const {
        return xx::TypeId_v<FishManage::FishFury>;
    }
    void FishFury::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->numBulletsPerShoot);
    }
    int FishFury::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->numBulletsPerShoot)) return r;
        return 0;
    }
    void FishFury::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((FishFury*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((FishFury*)this)->toStringFlag = false;
    }
    void FishFury::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
        xx::Append(s, ",\"numBulletsPerShoot\":", this->numBulletsPerShoot);
    }
    FishDrill::FishDrill(FishDrill&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishDrill& FishDrill::operator=(FishDrill&& o) noexcept {
        this->FishManage::FishBase::operator=(std::move(o));
        std::swap(this->reserveCoin, o.reserveCoin);
        return *this;
    }
    uint16_t FishDrill::GetTypeId() const {
        return xx::TypeId_v<FishManage::FishDrill>;
    }
    void FishDrill::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->reserveCoin);
    }
    int FishDrill::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->reserveCoin)) return r;
        return 0;
    }
    void FishDrill::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((FishDrill*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((FishDrill*)this)->toStringFlag = false;
    }
    void FishDrill::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
        xx::Append(s, ",\"reserveCoin\":", this->reserveCoin);
    }
    FishBomb::FishBomb(FishBomb&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishBomb& FishBomb::operator=(FishBomb&& o) noexcept {
        this->FishManage::FishBase::operator=(std::move(o));
        std::swap(this->timesFrom, o.timesFrom);
        std::swap(this->timesTo, o.timesTo);
        return *this;
    }
    uint16_t FishBomb::GetTypeId() const {
        return xx::TypeId_v<FishManage::FishBomb>;
    }
    void FishBomb::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->timesFrom);
        dw.Write(this->timesTo);
    }
    int FishBomb::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->timesFrom)) return r;
        if (int r = dr.Read(this->timesTo)) return r;
        return 0;
    }
    void FishBomb::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((FishBomb*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((FishBomb*)this)->toStringFlag = false;
    }
    void FishBomb::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
        xx::Append(s, ",\"timesFrom\":", this->timesFrom);
        xx::Append(s, ",\"timesTo\":", this->timesTo);
    }
    FishNormal::FishNormal(FishNormal&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishNormal& FishNormal::operator=(FishNormal&& o) noexcept {
        this->FishManage::FishBase::operator=(std::move(o));
        return *this;
    }
    uint16_t FishNormal::GetTypeId() const {
        return xx::TypeId_v<FishManage::FishNormal>;
    }
    void FishNormal::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
    }
    int FishNormal::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        return 0;
    }
    void FishNormal::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((FishNormal*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((FishNormal*)this)->toStringFlag = false;
    }
    void FishNormal::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
    }
    CombineItem::CombineItem(CombineItem&& o) noexcept {
        this->operator=(std::move(o));
    }
    CombineItem& CombineItem::operator=(CombineItem&& o) noexcept {
        std::swap(this->res, o.res);
        std::swap(this->offsetX, o.offsetX);
        std::swap(this->offsetY, o.offsetY);
        std::swap(this->baseAngle, o.baseAngle);
        std::swap(this->baseScale, o.baseScale);
        return *this;
    }
    ResCombine::ResCombine(ResCombine&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResCombine& ResCombine::operator=(ResCombine&& o) noexcept {
        this->FishManage::ResBase::operator=(std::move(o));
        std::swap(this->items, o.items);
        return *this;
    }
    uint16_t ResCombine::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResCombine>;
    }
    void ResCombine::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->items);
    }
    int ResCombine::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->items)) return r;
        return 0;
    }
    void ResCombine::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((ResCombine*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((ResCombine*)this)->toStringFlag = false;
    }
    void ResCombine::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
        xx::Append(s, ",\"items\":", this->items);
    }
    ActionSpine::ActionSpine(ActionSpine&& o) noexcept {
        this->operator=(std::move(o));
    }
    ActionSpine& ActionSpine::operator=(ActionSpine&& o) noexcept {
        this->FishManage::ActionBase::operator=(std::move(o));
        return *this;
    }
    uint16_t ActionSpine::GetTypeId() const {
        return xx::TypeId_v<FishManage::ActionSpine>;
    }
    void ActionSpine::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
    }
    int ActionSpine::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        return 0;
    }
    void ActionSpine::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((ActionSpine*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((ActionSpine*)this)->toStringFlag = false;
    }
    void ActionSpine::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
    }
    Res3d::Res3d(Res3d&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res3d& Res3d::operator=(Res3d&& o) noexcept {
        this->FishManage::ResBase::operator=(std::move(o));
        std::swap(this->c3bFileName, o.c3bFileName);
        std::swap(this->baseAngleX, o.baseAngleX);
        std::swap(this->baseAngleY, o.baseAngleY);
        std::swap(this->baseAngleZ, o.baseAngleZ);
        return *this;
    }
    uint16_t Res3d::GetTypeId() const {
        return xx::TypeId_v<FishManage::Res3d>;
    }
    void Res3d::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->c3bFileName);
        dw.Write(this->baseAngleX);
        dw.Write(this->baseAngleY);
        dw.Write(this->baseAngleZ);
    }
    int Res3d::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->c3bFileName)) return r;
        if (int r = dr.Read(this->baseAngleX)) return r;
        if (int r = dr.Read(this->baseAngleY)) return r;
        if (int r = dr.Read(this->baseAngleZ)) return r;
        return 0;
    }
    void Res3d::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((Res3d*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((Res3d*)this)->toStringFlag = false;
    }
    void Res3d::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
        xx::Append(s, ",\"c3bFileName\":", this->c3bFileName);
        xx::Append(s, ",\"baseAngleX\":", this->baseAngleX);
        xx::Append(s, ",\"baseAngleY\":", this->baseAngleY);
        xx::Append(s, ",\"baseAngleZ\":", this->baseAngleZ);
    }
    FishCyclone::FishCyclone(FishCyclone&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishCyclone& FishCyclone::operator=(FishCyclone&& o) noexcept {
        this->FishManage::FishBase::operator=(std::move(o));
        std::swap(this->sameFishName, o.sameFishName);
        return *this;
    }
    uint16_t FishCyclone::GetTypeId() const {
        return xx::TypeId_v<FishManage::FishCyclone>;
    }
    void FishCyclone::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->sameFishName);
    }
    int FishCyclone::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->sameFishName)) return r;
        return 0;
    }
    void FishCyclone::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((FishCyclone*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((FishCyclone*)this)->toStringFlag = false;
    }
    void FishCyclone::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
        xx::Append(s, ",\"sameFishName\":", this->sameFishName);
    }
    ResSpine::ResSpine(ResSpine&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResSpine& ResSpine::operator=(ResSpine&& o) noexcept {
        this->FishManage::ResBase::operator=(std::move(o));
        std::swap(this->atlasFileName, o.atlasFileName);
        std::swap(this->shadowScale, o.shadowScale);
        std::swap(this->shadowOffsetX, o.shadowOffsetX);
        std::swap(this->shadowOffsetY, o.shadowOffsetY);
        return *this;
    }
    uint16_t ResSpine::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResSpine>;
    }
    void ResSpine::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->atlasFileName);
        dw.Write(this->shadowScale);
        dw.Write(this->shadowOffsetX);
        dw.Write(this->shadowOffsetY);
    }
    int ResSpine::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->atlasFileName)) return r;
        if (int r = dr.Read(this->shadowScale)) return r;
        if (int r = dr.Read(this->shadowOffsetX)) return r;
        if (int r = dr.Read(this->shadowOffsetY)) return r;
        return 0;
    }
    void ResSpine::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((ResSpine*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((ResSpine*)this)->toStringFlag = false;
    }
    void ResSpine::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
        xx::Append(s, ",\"atlasFileName\":", this->atlasFileName);
        xx::Append(s, ",\"shadowScale\":", this->shadowScale);
        xx::Append(s, ",\"shadowOffsetX\":", this->shadowOffsetX);
        xx::Append(s, ",\"shadowOffsetY\":", this->shadowOffsetY);
    }
    Frame2d::Frame2d(Frame2d&& o) noexcept {
        this->operator=(std::move(o));
    }
    Frame2d& Frame2d::operator=(Frame2d&& o) noexcept {
        this->FishManage::FrameBase::operator=(std::move(o));
        std::swap(this->spriteFrameName, o.spriteFrameName);
        return *this;
    }
    uint16_t Frame2d::GetTypeId() const {
        return xx::TypeId_v<FishManage::Frame2d>;
    }
    void Frame2d::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->spriteFrameName);
    }
    int Frame2d::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->spriteFrameName)) return r;
        return 0;
    }
    void Frame2d::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((Frame2d*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((Frame2d*)this)->toStringFlag = false;
    }
    void Frame2d::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
        xx::Append(s, ",\"spriteFrameName\":", this->spriteFrameName);
    }
    Action2d::Action2d(Action2d&& o) noexcept {
        this->operator=(std::move(o));
    }
    Action2d& Action2d::operator=(Action2d&& o) noexcept {
        this->FishManage::ActionBase::operator=(std::move(o));
        return *this;
    }
    uint16_t Action2d::GetTypeId() const {
        return xx::TypeId_v<FishManage::Action2d>;
    }
    void Action2d::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
    }
    int Action2d::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        return 0;
    }
    void Action2d::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((Action2d*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((Action2d*)this)->toStringFlag = false;
    }
    void Action2d::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
    }
    Res2d::Res2d(Res2d&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res2d& Res2d::operator=(Res2d&& o) noexcept {
        this->FishManage::ResBase::operator=(std::move(o));
        std::swap(this->plistFileNames, o.plistFileNames);
        std::swap(this->shadowScale, o.shadowScale);
        std::swap(this->shadowOffsetX, o.shadowOffsetX);
        std::swap(this->shadowOffsetY, o.shadowOffsetY);
        return *this;
    }
    uint16_t Res2d::GetTypeId() const {
        return xx::TypeId_v<FishManage::Res2d>;
    }
    void Res2d::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->plistFileNames);
        dw.Write(this->shadowScale);
        dw.Write(this->shadowOffsetX);
        dw.Write(this->shadowOffsetY);
    }
    int Res2d::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->plistFileNames)) return r;
        if (int r = dr.Read(this->shadowScale)) return r;
        if (int r = dr.Read(this->shadowOffsetX)) return r;
        if (int r = dr.Read(this->shadowOffsetY)) return r;
        return 0;
    }
    void Res2d::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((Res2d*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((Res2d*)this)->toStringFlag = false;
    }
    void Res2d::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
        xx::Append(s, ",\"plistFileNames\":", this->plistFileNames);
        xx::Append(s, ",\"shadowScale\":", this->shadowScale);
        xx::Append(s, ",\"shadowOffsetX\":", this->shadowOffsetX);
        xx::Append(s, ",\"shadowOffsetY\":", this->shadowOffsetY);
    }
    Action3d::Action3d(Action3d&& o) noexcept {
        this->operator=(std::move(o));
    }
    Action3d& Action3d::operator=(Action3d&& o) noexcept {
        this->FishManage::ActionBase::operator=(std::move(o));
        return *this;
    }
    uint16_t Action3d::GetTypeId() const {
        return xx::TypeId_v<FishManage::Action3d>;
    }
    void Action3d::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
    }
    int Action3d::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        return 0;
    }
    void Action3d::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((Action3d*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((Action3d*)this)->toStringFlag = false;
    }
    void Action3d::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
    }
    FishEater::FishEater(FishEater&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishEater& FishEater::operator=(FishEater&& o) noexcept {
        this->FishManage::FishBase::operator=(std::move(o));
        std::swap(this->fishNames, o.fishNames);
        return *this;
    }
    uint16_t FishEater::GetTypeId() const {
        return xx::TypeId_v<FishManage::FishEater>;
    }
    void FishEater::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->fishNames);
    }
    int FishEater::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->fishNames)) return r;
        return 0;
    }
    void FishEater::ToString(std::string& s) const {
        if (this->toStringFlag) {
        	xx::Append(s, "{}");
        	return;
        }
        else {
            ((FishEater*)this)->toStringFlag = true;
        }
        xx::Append(s, "{\"#\":", GetTypeId());
        ToStringCore(s);
        s.push_back('}');
        ((FishEater*)this)->toStringFlag = false;
    }
    void FishEater::ToStringCore(std::string& s) const {
        this->BaseType::ToStringCore(s);
        xx::Append(s, ",\"fishNames\":", this->fishNames);
    }
}
