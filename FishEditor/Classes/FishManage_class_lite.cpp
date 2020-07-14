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
	void PkgGenTypes::RegisterTo(xx::ObjectHelper& oh) {
	    oh.Register<FishManage::ResBase>();
	    oh.Register<FishManage::ActionBase>();
	    oh.Register<FishManage::FrameBase>();
	    oh.Register<FishManage::Res2d>();
	    oh.Register<FishManage::Action2d>();
	    oh.Register<FishManage::Frame2d>();
	    oh.Register<FishManage::ResSpine>();
	    oh.Register<FishManage::ActionSpine>();
	    oh.Register<FishManage::Res3d>();
	    oh.Register<FishManage::Action3d>();
	    oh.Register<FishManage::ResCombine>();
	    oh.Register<FishManage::FishBase>();
	    oh.Register<FishManage::FishNormal>();
	    oh.Register<FishManage::FishBomb>();
	    oh.Register<FishManage::FishDrill>();
	    oh.Register<FishManage::FishFury>();
	    oh.Register<FishManage::FishCyclone>();
	    oh.Register<FishManage::FishEater>();
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
	void StringFuncsEx<FishManage::CDCircle, void>::Append(ObjectHelper &oh, FishManage::CDCircle const& in) {
        oh.s.push_back('{');
        AppendCore(oh, in);
        oh.s.push_back('}');
    }
	void StringFuncsEx<FishManage::CDCircle, void>::AppendCore(ObjectHelper &oh, FishManage::CDCircle const& in) {
        auto sizeBak = oh.s.size();
        if (sizeBak == oh.s.size()) {
            oh.s.push_back(',');
        }
        xx::AppendEx(oh, "\"x\":", in.x); 
        xx::AppendEx(oh, ",\"y\":", in.y);
        xx::AppendEx(oh, ",\"r\":", in.r);
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
	void StringFuncsEx<FishManage::LockPoint, void>::Append(ObjectHelper &oh, FishManage::LockPoint const& in) {
        oh.s.push_back('{');
        AppendCore(oh, in);
        oh.s.push_back('}');
    }
	void StringFuncsEx<FishManage::LockPoint, void>::AppendCore(ObjectHelper &oh, FishManage::LockPoint const& in) {
        auto sizeBak = oh.s.size();
        if (sizeBak == oh.s.size()) {
            oh.s.push_back(',');
        }
        xx::AppendEx(oh, "\"x\":", in.x); 
        xx::AppendEx(oh, ",\"y\":", in.y);
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
	void StringFuncsEx<FishManage::Data, void>::Append(ObjectHelper &oh, FishManage::Data const& in) {
        oh.s.push_back('{');
        AppendCore(oh, in);
        oh.s.push_back('}');
    }
	void StringFuncsEx<FishManage::Data, void>::AppendCore(ObjectHelper &oh, FishManage::Data const& in) {
        auto sizeBak = oh.s.size();
        if (sizeBak == oh.s.size()) {
            oh.s.push_back(',');
        }
        xx::AppendEx(oh, "\"ress\":", in.ress); 
        xx::AppendEx(oh, ",\"fishs\":", in.fishs);
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
	void StringFuncsEx<FishManage::CombineItem, void>::Append(ObjectHelper &oh, FishManage::CombineItem const& in) {
        oh.s.push_back('{');
        AppendCore(oh, in);
        oh.s.push_back('}');
    }
	void StringFuncsEx<FishManage::CombineItem, void>::AppendCore(ObjectHelper &oh, FishManage::CombineItem const& in) {
        auto sizeBak = oh.s.size();
        if (sizeBak == oh.s.size()) {
            oh.s.push_back(',');
        }
        xx::AppendEx(oh, "\"res\":", in.res); 
        xx::AppendEx(oh, ",\"offsetX\":", in.offsetX);
        xx::AppendEx(oh, ",\"offsetY\":", in.offsetY);
        xx::AppendEx(oh, ",\"baseAngle\":", in.baseAngle);
        xx::AppendEx(oh, ",\"baseScale\":", in.baseScale);
    }
}
namespace FishManage {
    FishBase::FishBase(FishBase&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishBase& FishBase::operator=(FishBase&& o) noexcept {
        std::swap(this->name, o.name);
        std::swap(this->res, o.res);
        std::swap(this->coin1, o.coin1);
        std::swap(this->coin2, o.coin2);
        std::swap(this->pathwayGroupName, o.pathwayGroupName);
        std::swap(this->lastUpdateTime, o.lastUpdateTime);
        return *this;
    }
    uint16_t FishBase::GetTypeId() const {
        return xx::TypeId_v<FishManage::FishBase>;
    }
    void FishBase::Serialize(xx::DataWriterEx& dw) const {
        dw.Write(this->name);
        dw.Write(this->res);
        dw.Write(this->coin1);
        dw.Write(this->coin2);
        dw.Write(this->pathwayGroupName);
        dw.Write(this->lastUpdateTime);
    }
    int FishBase::Deserialize(xx::DataReaderEx& dr) {
        if (int r = dr.Read(this->name)) return r;
        if (int r = dr.Read(this->res)) return r;
        if (int r = dr.Read(this->coin1)) return r;
        if (int r = dr.Read(this->coin2)) return r;
        if (int r = dr.Read(this->pathwayGroupName)) return r;
        if (int r = dr.Read(this->lastUpdateTime)) return r;
        return 0;
    }
    void FishBase::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void FishBase::ToStringCore(xx::ObjectHelper &oh) const {
        xx::AppendEx(oh, ",\"name\":", this->name);
        xx::AppendEx(oh, ",\"res\":", this->res);
        xx::AppendEx(oh, ",\"coin1\":", this->coin1);
        xx::AppendEx(oh, ",\"coin2\":", this->coin2);
        xx::AppendEx(oh, ",\"pathwayGroupName\":", this->pathwayGroupName);
        xx::AppendEx(oh, ",\"lastUpdateTime\":", this->lastUpdateTime);
    }
    ResBase::ResBase(ResBase&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResBase& ResBase::operator=(ResBase&& o) noexcept {
        std::swap(this->name, o.name);
        std::swap(this->baseScale, o.baseScale);
        std::swap(this->actions, o.actions);
        std::swap(this->lastUpdateTime, o.lastUpdateTime);
        return *this;
    }
    uint16_t ResBase::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResBase>;
    }
    void ResBase::Serialize(xx::DataWriterEx& dw) const {
        dw.Write(this->name);
        dw.Write(this->baseScale);
        dw.Write(this->actions);
        dw.Write(this->lastUpdateTime);
    }
    int ResBase::Deserialize(xx::DataReaderEx& dr) {
        if (int r = dr.Read(this->name)) return r;
        if (int r = dr.Read(this->baseScale)) return r;
        if (int r = dr.Read(this->actions)) return r;
        if (int r = dr.Read(this->lastUpdateTime)) return r;
        return 0;
    }
    void ResBase::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void ResBase::ToStringCore(xx::ObjectHelper &oh) const {
        xx::AppendEx(oh, ",\"name\":", this->name);
        xx::AppendEx(oh, ",\"baseScale\":", this->baseScale);
        xx::AppendEx(oh, ",\"actions\":", this->actions);
        xx::AppendEx(oh, ",\"lastUpdateTime\":", this->lastUpdateTime);
    }
    ActionBase::ActionBase(ActionBase&& o) noexcept {
        this->operator=(std::move(o));
    }
    ActionBase& ActionBase::operator=(ActionBase&& o) noexcept {
        std::swap(this->name, o.name);
        std::swap(this->frameRate, o.frameRate);
        std::swap(this->width, o.width);
        std::swap(this->height, o.height);
        std::swap(this->frames, o.frames);
        return *this;
    }
    uint16_t ActionBase::GetTypeId() const {
        return xx::TypeId_v<FishManage::ActionBase>;
    }
    void ActionBase::Serialize(xx::DataWriterEx& dw) const {
        dw.Write(this->name);
        dw.Write(this->frameRate);
        dw.Write(this->width);
        dw.Write(this->height);
        dw.Write(this->frames);
    }
    int ActionBase::Deserialize(xx::DataReaderEx& dr) {
        if (int r = dr.Read(this->name)) return r;
        if (int r = dr.Read(this->frameRate)) return r;
        if (int r = dr.Read(this->width)) return r;
        if (int r = dr.Read(this->height)) return r;
        if (int r = dr.Read(this->frames)) return r;
        return 0;
    }
    void ActionBase::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void ActionBase::ToStringCore(xx::ObjectHelper &oh) const {
        xx::AppendEx(oh, ",\"name\":", this->name);
        xx::AppendEx(oh, ",\"frameRate\":", this->frameRate);
        xx::AppendEx(oh, ",\"width\":", this->width);
        xx::AppendEx(oh, ",\"height\":", this->height);
        xx::AppendEx(oh, ",\"frames\":", this->frames);
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
    void FrameBase::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void FrameBase::ToStringCore(xx::ObjectHelper &oh) const {
        xx::AppendEx(oh, ",\"moveDistance\":", this->moveDistance);
        xx::AppendEx(oh, ",\"maxCDCircle\":", this->maxCDCircle);
        xx::AppendEx(oh, ",\"cdCircles\":", this->cdCircles);
        xx::AppendEx(oh, ",\"mainLockPoint\":", this->mainLockPoint);
        xx::AppendEx(oh, ",\"lockPoints\":", this->lockPoints);
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
        this->BaseType::operator=(std::move(o));
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
    void FishFury::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void FishFury::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"numBulletsPerShoot\":", this->numBulletsPerShoot);
    }
    FishDrill::FishDrill(FishDrill&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishDrill& FishDrill::operator=(FishDrill&& o) noexcept {
        this->BaseType::operator=(std::move(o));
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
    void FishDrill::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void FishDrill::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"reserveCoin\":", this->reserveCoin);
    }
    FishBomb::FishBomb(FishBomb&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishBomb& FishBomb::operator=(FishBomb&& o) noexcept {
        this->BaseType::operator=(std::move(o));
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
    void FishBomb::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void FishBomb::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"timesFrom\":", this->timesFrom);
        xx::AppendEx(oh, ",\"timesTo\":", this->timesTo);
    }
    FishNormal::FishNormal(FishNormal&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishNormal& FishNormal::operator=(FishNormal&& o) noexcept {
        this->BaseType::operator=(std::move(o));
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
    void FishNormal::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void FishNormal::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
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
        this->BaseType::operator=(std::move(o));
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
    void ResCombine::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void ResCombine::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"items\":", this->items);
    }
    ActionSpine::ActionSpine(ActionSpine&& o) noexcept {
        this->operator=(std::move(o));
    }
    ActionSpine& ActionSpine::operator=(ActionSpine&& o) noexcept {
        this->BaseType::operator=(std::move(o));
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
    void ActionSpine::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void ActionSpine::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
    }
    Res3d::Res3d(Res3d&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res3d& Res3d::operator=(Res3d&& o) noexcept {
        this->BaseType::operator=(std::move(o));
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
    void Res3d::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Res3d::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"c3bFileName\":", this->c3bFileName);
        xx::AppendEx(oh, ",\"baseAngleX\":", this->baseAngleX);
        xx::AppendEx(oh, ",\"baseAngleY\":", this->baseAngleY);
        xx::AppendEx(oh, ",\"baseAngleZ\":", this->baseAngleZ);
    }
    FishCyclone::FishCyclone(FishCyclone&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishCyclone& FishCyclone::operator=(FishCyclone&& o) noexcept {
        this->BaseType::operator=(std::move(o));
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
    void FishCyclone::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void FishCyclone::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"sameFishName\":", this->sameFishName);
    }
    ResSpine::ResSpine(ResSpine&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResSpine& ResSpine::operator=(ResSpine&& o) noexcept {
        this->BaseType::operator=(std::move(o));
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
    void ResSpine::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void ResSpine::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"atlasFileName\":", this->atlasFileName);
        xx::AppendEx(oh, ",\"shadowScale\":", this->shadowScale);
        xx::AppendEx(oh, ",\"shadowOffsetX\":", this->shadowOffsetX);
        xx::AppendEx(oh, ",\"shadowOffsetY\":", this->shadowOffsetY);
    }
    Frame2d::Frame2d(Frame2d&& o) noexcept {
        this->operator=(std::move(o));
    }
    Frame2d& Frame2d::operator=(Frame2d&& o) noexcept {
        this->BaseType::operator=(std::move(o));
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
    void Frame2d::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Frame2d::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"spriteFrameName\":", this->spriteFrameName);
    }
    Action2d::Action2d(Action2d&& o) noexcept {
        this->operator=(std::move(o));
    }
    Action2d& Action2d::operator=(Action2d&& o) noexcept {
        this->BaseType::operator=(std::move(o));
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
    void Action2d::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Action2d::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
    }
    Res2d::Res2d(Res2d&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res2d& Res2d::operator=(Res2d&& o) noexcept {
        this->BaseType::operator=(std::move(o));
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
    void Res2d::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Res2d::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"plistFileNames\":", this->plistFileNames);
        xx::AppendEx(oh, ",\"shadowScale\":", this->shadowScale);
        xx::AppendEx(oh, ",\"shadowOffsetX\":", this->shadowOffsetX);
        xx::AppendEx(oh, ",\"shadowOffsetY\":", this->shadowOffsetY);
    }
    Action3d::Action3d(Action3d&& o) noexcept {
        this->operator=(std::move(o));
    }
    Action3d& Action3d::operator=(Action3d&& o) noexcept {
        this->BaseType::operator=(std::move(o));
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
    void Action3d::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Action3d::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
    }
    FishEater::FishEater(FishEater&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishEater& FishEater::operator=(FishEater&& o) noexcept {
        this->BaseType::operator=(std::move(o));
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
    void FishEater::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.ptrOffsets.find((void*)this);
        if (iter != oh.ptrOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.ptrOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void FishEater::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"fishNames\":", this->fishNames);
    }
}
