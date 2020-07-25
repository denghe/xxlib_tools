#include "FishManage_class_lite.h"
#include "FishManage_class_lite.cpp.inc"
namespace FishManage {
	void PkgGenTypes::RegisterTo(xx::ObjectHelper& oh) {
	    oh.Register<FishManage::File>();
	    oh.Register<FishManage::File_FrameAnimation>();
	    oh.Register<FishManage::File_Real>();
	    oh.Register<FishManage::File_Lua>();
	    oh.Register<FishManage::File_Sound>();
	    oh.Register<FishManage::File_Picture>();
	    oh.Register<FishManage::File_Bag>();
	    oh.Register<FishManage::File_Animation>();
	    oh.Register<FishManage::File_Spine>();
	    oh.Register<FishManage::File_C3b>();
	    oh.Register<FishManage::File_Combine>();
	    oh.Register<FishManage::Res>();
	    oh.Register<FishManage::Res_Script>();
	    oh.Register<FishManage::Res_Sound>();
	    oh.Register<FishManage::Res_Picture>();
	    oh.Register<FishManage::Res_FrameAnimation>();
	    oh.Register<FishManage::Res_Spine>();
	    oh.Register<FishManage::Res_3d>();
	    oh.Register<FishManage::Res_Combine>();
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
    void CloneFuncs<FishManage::LockPoint>::Clone1(xx::ObjectHelper &oh, FishManage::LockPoint const& in, FishManage::LockPoint &out) {
        CloneFuncs<float>::Clone1(oh, in.x, out.x);
        CloneFuncs<float>::Clone1(oh, in.y, out.y);
    }
    void CloneFuncs<FishManage::LockPoint>::Clone2(xx::ObjectHelper &oh, FishManage::LockPoint const& in, FishManage::LockPoint &out) {
        CloneFuncs<float>::Clone2(oh, in.x, out.x);
        CloneFuncs<float>::Clone2(oh, in.y, out.y);
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
    void CloneFuncs<FishManage::CDCircle>::Clone1(xx::ObjectHelper &oh, FishManage::CDCircle const& in, FishManage::CDCircle &out) {
        CloneFuncs<float>::Clone1(oh, in.x, out.x);
        CloneFuncs<float>::Clone1(oh, in.y, out.y);
        CloneFuncs<float>::Clone1(oh, in.r, out.r);
    }
    void CloneFuncs<FishManage::CDCircle>::Clone2(xx::ObjectHelper &oh, FishManage::CDCircle const& in, FishManage::CDCircle &out) {
        CloneFuncs<float>::Clone2(oh, in.x, out.x);
        CloneFuncs<float>::Clone2(oh, in.y, out.y);
        CloneFuncs<float>::Clone2(oh, in.r, out.r);
    }
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
    void CloneFuncs<FishManage::CDCirclesLockPoints>::Clone1(xx::ObjectHelper &oh, FishManage::CDCirclesLockPoints const& in, FishManage::CDCirclesLockPoints &out) {
        CloneFuncs<FishManage::CDCircle>::Clone1(oh, in.maxCDCircle, out.maxCDCircle);
        CloneFuncs<std::vector<FishManage::CDCircle>>::Clone1(oh, in.cdCircles, out.cdCircles);
        CloneFuncs<FishManage::LockPoint>::Clone1(oh, in.mainLockPoint, out.mainLockPoint);
        CloneFuncs<std::vector<FishManage::LockPoint>>::Clone1(oh, in.lockPoints, out.lockPoints);
    }
    void CloneFuncs<FishManage::CDCirclesLockPoints>::Clone2(xx::ObjectHelper &oh, FishManage::CDCirclesLockPoints const& in, FishManage::CDCirclesLockPoints &out) {
        CloneFuncs<FishManage::CDCircle>::Clone2(oh, in.maxCDCircle, out.maxCDCircle);
        CloneFuncs<std::vector<FishManage::CDCircle>>::Clone2(oh, in.cdCircles, out.cdCircles);
        CloneFuncs<FishManage::LockPoint>::Clone2(oh, in.mainLockPoint, out.mainLockPoint);
        CloneFuncs<std::vector<FishManage::LockPoint>>::Clone2(oh, in.lockPoints, out.lockPoints);
    }
	void DataFuncsEx<FishManage::CDCirclesLockPoints, void>::Write(DataWriterEx& dw, FishManage::CDCirclesLockPoints const& in) {
        dw.Write(in.maxCDCircle);
        dw.Write(in.cdCircles);
        dw.Write(in.mainLockPoint);
        dw.Write(in.lockPoints);
    }
	int DataFuncsEx<FishManage::CDCirclesLockPoints, void>::Read(DataReaderEx& d, FishManage::CDCirclesLockPoints& out) {
        if (int r = d.Read(out.maxCDCircle)) return r;
        if (int r = d.Read(out.cdCircles)) return r;
        if (int r = d.Read(out.mainLockPoint)) return r;
        if (int r = d.Read(out.lockPoints)) return r;
        return 0;
    }
	void StringFuncsEx<FishManage::CDCirclesLockPoints, void>::Append(ObjectHelper &oh, FishManage::CDCirclesLockPoints const& in) {
        oh.s.push_back('{');
        AppendCore(oh, in);
        oh.s.push_back('}');
    }
	void StringFuncsEx<FishManage::CDCirclesLockPoints, void>::AppendCore(ObjectHelper &oh, FishManage::CDCirclesLockPoints const& in) {
        auto sizeBak = oh.s.size();
        if (sizeBak == oh.s.size()) {
            oh.s.push_back(',');
        }
        xx::AppendEx(oh, "\"maxCDCircle\":", in.maxCDCircle); 
        xx::AppendEx(oh, ",\"cdCircles\":", in.cdCircles);
        xx::AppendEx(oh, ",\"mainLockPoint\":", in.mainLockPoint);
        xx::AppendEx(oh, ",\"lockPoints\":", in.lockPoints);
    }
    void CloneFuncs<FishManage::Action>::Clone1(xx::ObjectHelper &oh, FishManage::Action const& in, FishManage::Action &out) {
        CloneFuncs<std::string>::Clone1(oh, in.name, out.name);
        CloneFuncs<float>::Clone1(oh, in.seconds, out.seconds);
        CloneFuncs<float>::Clone1(oh, in.frameRate, out.frameRate);
        CloneFuncs<float>::Clone1(oh, in.width, out.width);
        CloneFuncs<float>::Clone1(oh, in.height, out.height);
        CloneFuncs<std::vector<FishManage::CDCirclesLockPoints>>::Clone1(oh, in.cdclpss, out.cdclpss);
    }
    void CloneFuncs<FishManage::Action>::Clone2(xx::ObjectHelper &oh, FishManage::Action const& in, FishManage::Action &out) {
        CloneFuncs<std::string>::Clone2(oh, in.name, out.name);
        CloneFuncs<float>::Clone2(oh, in.seconds, out.seconds);
        CloneFuncs<float>::Clone2(oh, in.frameRate, out.frameRate);
        CloneFuncs<float>::Clone2(oh, in.width, out.width);
        CloneFuncs<float>::Clone2(oh, in.height, out.height);
        CloneFuncs<std::vector<FishManage::CDCirclesLockPoints>>::Clone2(oh, in.cdclpss, out.cdclpss);
    }
	void DataFuncsEx<FishManage::Action, void>::Write(DataWriterEx& dw, FishManage::Action const& in) {
        dw.Write(in.name);
        dw.Write(in.seconds);
        dw.Write(in.frameRate);
        dw.Write(in.width);
        dw.Write(in.height);
        dw.Write(in.cdclpss);
    }
	int DataFuncsEx<FishManage::Action, void>::Read(DataReaderEx& d, FishManage::Action& out) {
        if (int r = d.Read(out.name)) return r;
        if (int r = d.Read(out.seconds)) return r;
        if (int r = d.Read(out.frameRate)) return r;
        if (int r = d.Read(out.width)) return r;
        if (int r = d.Read(out.height)) return r;
        if (int r = d.Read(out.cdclpss)) return r;
        return 0;
    }
	void StringFuncsEx<FishManage::Action, void>::Append(ObjectHelper &oh, FishManage::Action const& in) {
        oh.s.push_back('{');
        AppendCore(oh, in);
        oh.s.push_back('}');
    }
	void StringFuncsEx<FishManage::Action, void>::AppendCore(ObjectHelper &oh, FishManage::Action const& in) {
        auto sizeBak = oh.s.size();
        if (sizeBak == oh.s.size()) {
            oh.s.push_back(',');
        }
        xx::AppendEx(oh, "\"name\":", in.name); 
        xx::AppendEx(oh, ",\"seconds\":", in.seconds);
        xx::AppendEx(oh, ",\"frameRate\":", in.frameRate);
        xx::AppendEx(oh, ",\"width\":", in.width);
        xx::AppendEx(oh, ",\"height\":", in.height);
        xx::AppendEx(oh, ",\"cdclpss\":", in.cdclpss);
    }
    void CloneFuncs<FishManage::FishState>::Clone1(xx::ObjectHelper &oh, FishManage::FishState const& in, FishManage::FishState &out) {
        CloneFuncs<std::string>::Clone1(oh, in.name, out.name);
        CloneFuncs<std::string>::Clone1(oh, in.actionName, out.actionName);
        CloneFuncs<std::vector<float>>::Clone1(oh, in.moveActionFrameDistances, out.moveActionFrameDistances);
        CloneFuncs<std::string>::Clone1(oh, in.pathwayGroupName, out.pathwayGroupName);
    }
    void CloneFuncs<FishManage::FishState>::Clone2(xx::ObjectHelper &oh, FishManage::FishState const& in, FishManage::FishState &out) {
        CloneFuncs<std::string>::Clone2(oh, in.name, out.name);
        CloneFuncs<std::string>::Clone2(oh, in.actionName, out.actionName);
        CloneFuncs<std::vector<float>>::Clone2(oh, in.moveActionFrameDistances, out.moveActionFrameDistances);
        CloneFuncs<std::string>::Clone2(oh, in.pathwayGroupName, out.pathwayGroupName);
    }
	void DataFuncsEx<FishManage::FishState, void>::Write(DataWriterEx& dw, FishManage::FishState const& in) {
        dw.Write(in.name);
        dw.Write(in.actionName);
        dw.Write(in.moveActionFrameDistances);
        dw.Write(in.pathwayGroupName);
    }
	int DataFuncsEx<FishManage::FishState, void>::Read(DataReaderEx& d, FishManage::FishState& out) {
        if (int r = d.Read(out.name)) return r;
        if (int r = d.Read(out.actionName)) return r;
        if (int r = d.Read(out.moveActionFrameDistances)) return r;
        if (int r = d.Read(out.pathwayGroupName)) return r;
        return 0;
    }
	void StringFuncsEx<FishManage::FishState, void>::Append(ObjectHelper &oh, FishManage::FishState const& in) {
        oh.s.push_back('{');
        AppendCore(oh, in);
        oh.s.push_back('}');
    }
	void StringFuncsEx<FishManage::FishState, void>::AppendCore(ObjectHelper &oh, FishManage::FishState const& in) {
        auto sizeBak = oh.s.size();
        if (sizeBak == oh.s.size()) {
            oh.s.push_back(',');
        }
        xx::AppendEx(oh, "\"name\":", in.name); 
        xx::AppendEx(oh, ",\"actionName\":", in.actionName);
        xx::AppendEx(oh, ",\"moveActionFrameDistances\":", in.moveActionFrameDistances);
        xx::AppendEx(oh, ",\"pathwayGroupName\":", in.pathwayGroupName);
    }
    void CloneFuncs<FishManage::FrameAction>::Clone1(xx::ObjectHelper &oh, FishManage::FrameAction const& in, FishManage::FrameAction &out) {
        CloneFuncs<FishManage::Action>::Clone1(oh, in, out);
        CloneFuncs<std::vector<std::weak_ptr<FishManage::File_Picture>>>::Clone1(oh, in.pictures, out.pictures);
    }
    void CloneFuncs<FishManage::FrameAction>::Clone2(xx::ObjectHelper &oh, FishManage::FrameAction const& in, FishManage::FrameAction &out) {
        CloneFuncs<FishManage::Action>::Clone2(oh, in, out);
        CloneFuncs<std::vector<std::weak_ptr<FishManage::File_Picture>>>::Clone2(oh, in.pictures, out.pictures);
    }
	void DataFuncsEx<FishManage::FrameAction, void>::Write(DataWriterEx& dw, FishManage::FrameAction const& in) {
        DataFuncsEx<FishManage::Action>::Write(dw, in);
        dw.Write(in.pictures);
    }
	int DataFuncsEx<FishManage::FrameAction, void>::Read(DataReaderEx& d, FishManage::FrameAction& out) {
        if (int r = DataFuncsEx<FishManage::Action>::Read(d, out)) return r;
        if (int r = d.Read(out.pictures)) return r;
        return 0;
    }
	void StringFuncsEx<FishManage::FrameAction, void>::Append(ObjectHelper &oh, FishManage::FrameAction const& in) {
        oh.s.push_back('{');
        AppendCore(oh, in);
        oh.s.push_back('}');
    }
	void StringFuncsEx<FishManage::FrameAction, void>::AppendCore(ObjectHelper &oh, FishManage::FrameAction const& in) {
        auto sizeBak = oh.s.size();
        StringFuncsEx<FishManage::Action>::AppendCore(oh, in);
        if (sizeBak == oh.s.size()) {
            oh.s.push_back(',');
        }
        xx::AppendEx(oh, "\"pictures\":", in.pictures); 
    }
    void CloneFuncs<FishManage::CombineItem>::Clone1(xx::ObjectHelper &oh, FishManage::CombineItem const& in, FishManage::CombineItem &out) {
        CloneFuncs<std::weak_ptr<FishManage::File>>::Clone1(oh, in.file, out.file);
        CloneFuncs<float>::Clone1(oh, in.offsetX, out.offsetX);
        CloneFuncs<float>::Clone1(oh, in.offsetY, out.offsetY);
        CloneFuncs<float>::Clone1(oh, in.angle, out.angle);
        CloneFuncs<float>::Clone1(oh, in.scale, out.scale);
    }
    void CloneFuncs<FishManage::CombineItem>::Clone2(xx::ObjectHelper &oh, FishManage::CombineItem const& in, FishManage::CombineItem &out) {
        CloneFuncs<std::weak_ptr<FishManage::File>>::Clone2(oh, in.file, out.file);
        CloneFuncs<float>::Clone2(oh, in.offsetX, out.offsetX);
        CloneFuncs<float>::Clone2(oh, in.offsetY, out.offsetY);
        CloneFuncs<float>::Clone2(oh, in.angle, out.angle);
        CloneFuncs<float>::Clone2(oh, in.scale, out.scale);
    }
	void DataFuncsEx<FishManage::CombineItem, void>::Write(DataWriterEx& dw, FishManage::CombineItem const& in) {
        dw.Write(in.file);
        dw.Write(in.offsetX);
        dw.Write(in.offsetY);
        dw.Write(in.angle);
        dw.Write(in.scale);
    }
	int DataFuncsEx<FishManage::CombineItem, void>::Read(DataReaderEx& d, FishManage::CombineItem& out) {
        if (int r = d.Read(out.file)) return r;
        if (int r = d.Read(out.offsetX)) return r;
        if (int r = d.Read(out.offsetY)) return r;
        if (int r = d.Read(out.angle)) return r;
        if (int r = d.Read(out.scale)) return r;
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
        xx::AppendEx(oh, "\"file\":", in.file); 
        xx::AppendEx(oh, ",\"offsetX\":", in.offsetX);
        xx::AppendEx(oh, ",\"offsetY\":", in.offsetY);
        xx::AppendEx(oh, ",\"angle\":", in.angle);
        xx::AppendEx(oh, ",\"scale\":", in.scale);
    }
    void CloneFuncs<FishManage::Data>::Clone1(xx::ObjectHelper &oh, FishManage::Data const& in, FishManage::Data &out) {
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::File>>>::Clone1(oh, in.files, out.files);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_Script>>>::Clone1(oh, in.resScripts, out.resScripts);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_Sound>>>::Clone1(oh, in.resSounds, out.resSounds);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_Picture>>>::Clone1(oh, in.resPictures, out.resPictures);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_FrameAnimation>>>::Clone1(oh, in.resFrameAnimations, out.resFrameAnimations);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_Spine>>>::Clone1(oh, in.resSpines, out.resSpines);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_3d>>>::Clone1(oh, in.res3ds, out.res3ds);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_Combine>>>::Clone1(oh, in.resCombines, out.resCombines);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::FishBase>>>::Clone1(oh, in.fishs, out.fishs);
    }
    void CloneFuncs<FishManage::Data>::Clone2(xx::ObjectHelper &oh, FishManage::Data const& in, FishManage::Data &out) {
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::File>>>::Clone2(oh, in.files, out.files);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_Script>>>::Clone2(oh, in.resScripts, out.resScripts);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_Sound>>>::Clone2(oh, in.resSounds, out.resSounds);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_Picture>>>::Clone2(oh, in.resPictures, out.resPictures);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_FrameAnimation>>>::Clone2(oh, in.resFrameAnimations, out.resFrameAnimations);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_Spine>>>::Clone2(oh, in.resSpines, out.resSpines);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_3d>>>::Clone2(oh, in.res3ds, out.res3ds);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res_Combine>>>::Clone2(oh, in.resCombines, out.resCombines);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::FishBase>>>::Clone2(oh, in.fishs, out.fishs);
    }
	void DataFuncsEx<FishManage::Data, void>::Write(DataWriterEx& dw, FishManage::Data const& in) {
        dw.Write(in.files);
        dw.Write(in.resScripts);
        dw.Write(in.resSounds);
        dw.Write(in.resPictures);
        dw.Write(in.resFrameAnimations);
        dw.Write(in.resSpines);
        dw.Write(in.res3ds);
        dw.Write(in.resCombines);
        dw.Write(in.fishs);
    }
	int DataFuncsEx<FishManage::Data, void>::Read(DataReaderEx& d, FishManage::Data& out) {
        if (int r = d.Read(out.files)) return r;
        if (int r = d.Read(out.resScripts)) return r;
        if (int r = d.Read(out.resSounds)) return r;
        if (int r = d.Read(out.resPictures)) return r;
        if (int r = d.Read(out.resFrameAnimations)) return r;
        if (int r = d.Read(out.resSpines)) return r;
        if (int r = d.Read(out.res3ds)) return r;
        if (int r = d.Read(out.resCombines)) return r;
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
        xx::AppendEx(oh, "\"files\":", in.files); 
        xx::AppendEx(oh, ",\"resScripts\":", in.resScripts);
        xx::AppendEx(oh, ",\"resSounds\":", in.resSounds);
        xx::AppendEx(oh, ",\"resPictures\":", in.resPictures);
        xx::AppendEx(oh, ",\"resFrameAnimations\":", in.resFrameAnimations);
        xx::AppendEx(oh, ",\"resSpines\":", in.resSpines);
        xx::AppendEx(oh, ",\"res3ds\":", in.res3ds);
        xx::AppendEx(oh, ",\"resCombines\":", in.resCombines);
        xx::AppendEx(oh, ",\"fishs\":", in.fishs);
    }
}
namespace FishManage {
    File::File(File&& o) noexcept {
        this->operator=(std::move(o));
    }
    File& File::operator=(File&& o) noexcept {
        std::swap(this->name, o.name);
        std::swap(this->ext, o.ext);
        return *this;
    }
    void File::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        auto&& o = xx::As<FishManage::File>(tar);
        xx::CloneFuncs<std::string>::Clone1(oh, this->name, o->name);
        xx::CloneFuncs<FishManage::FileExtensions>::Clone1(oh, this->ext, o->ext);
    }
    void File::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        auto&& o = xx::As<FishManage::File>(tar);
        xx::CloneFuncs<std::string>::Clone2(oh, this->name, o->name);
        xx::CloneFuncs<FishManage::FileExtensions>::Clone2(oh, this->ext, o->ext);
    }
    uint16_t File::GetTypeId() const {
        return xx::TypeId_v<FishManage::File>;
    }
    void File::Serialize(xx::DataWriterEx& dw) const {
        dw.Write(this->name);
        dw.Write(this->ext);
    }
    int File::Deserialize(xx::DataReaderEx& dr) {
        if (int r = dr.Read(this->name)) return r;
        if (int r = dr.Read(this->ext)) return r;
        return 0;
    }
    void File::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void File::ToStringCore(xx::ObjectHelper &oh) const {
        xx::AppendEx(oh, ",\"name\":", this->name);
        xx::AppendEx(oh, ",\"ext\":", this->ext);
    }
    File_Real::File_Real(File_Real&& o) noexcept {
        this->operator=(std::move(o));
    }
    File_Real& File_Real::operator=(File_Real&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->length, o.length);
        std::swap(this->md5, o.md5);
        return *this;
    }
    void File_Real::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::File_Real>(tar);
        xx::CloneFuncs<int64_t>::Clone1(oh, this->length, o->length);
        xx::CloneFuncs<xx::Data>::Clone1(oh, this->md5, o->md5);
    }
    void File_Real::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::File_Real>(tar);
        xx::CloneFuncs<int64_t>::Clone2(oh, this->length, o->length);
        xx::CloneFuncs<xx::Data>::Clone2(oh, this->md5, o->md5);
    }
    uint16_t File_Real::GetTypeId() const {
        return xx::TypeId_v<FishManage::File_Real>;
    }
    void File_Real::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->length);
        dw.Write(this->md5);
    }
    int File_Real::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->length)) return r;
        if (int r = dr.Read(this->md5)) return r;
        return 0;
    }
    void File_Real::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void File_Real::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"length\":", this->length);
        xx::AppendEx(oh, ",\"md5\":", this->md5);
    }
    Res::Res(Res&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res& Res::operator=(Res&& o) noexcept {
        std::swap(this->name, o.name);
        return *this;
    }
    void Res::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        auto&& o = xx::As<FishManage::Res>(tar);
        xx::CloneFuncs<std::string>::Clone1(oh, this->name, o->name);
    }
    void Res::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        auto&& o = xx::As<FishManage::Res>(tar);
        xx::CloneFuncs<std::string>::Clone2(oh, this->name, o->name);
    }
    uint16_t Res::GetTypeId() const {
        return xx::TypeId_v<FishManage::Res>;
    }
    void Res::Serialize(xx::DataWriterEx& dw) const {
        dw.Write(this->name);
    }
    int Res::Deserialize(xx::DataReaderEx& dr) {
        if (int r = dr.Read(this->name)) return r;
        return 0;
    }
    void Res::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Res::ToStringCore(xx::ObjectHelper &oh) const {
        xx::AppendEx(oh, ",\"name\":", this->name);
    }
    LockPoint::LockPoint(LockPoint&& o) noexcept {
        this->operator=(std::move(o));
    }
    LockPoint& LockPoint::operator=(LockPoint&& o) noexcept {
        std::swap(this->x, o.x);
        std::swap(this->y, o.y);
        return *this;
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
    CDCirclesLockPoints::CDCirclesLockPoints(CDCirclesLockPoints&& o) noexcept {
        this->operator=(std::move(o));
    }
    CDCirclesLockPoints& CDCirclesLockPoints::operator=(CDCirclesLockPoints&& o) noexcept {
        std::swap(this->maxCDCircle, o.maxCDCircle);
        std::swap(this->cdCircles, o.cdCircles);
        std::swap(this->mainLockPoint, o.mainLockPoint);
        std::swap(this->lockPoints, o.lockPoints);
        return *this;
    }
    File_Bag::File_Bag(File_Bag&& o) noexcept {
        this->operator=(std::move(o));
    }
    File_Bag& File_Bag::operator=(File_Bag&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->childs, o.childs);
        return *this;
    }
    void File_Bag::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::File_Bag>(tar);
        xx::CloneFuncs<std::vector<std::shared_ptr<FishManage::File_Real>>>::Clone1(oh, this->childs, o->childs);
    }
    void File_Bag::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::File_Bag>(tar);
        xx::CloneFuncs<std::vector<std::shared_ptr<FishManage::File_Real>>>::Clone2(oh, this->childs, o->childs);
    }
    uint16_t File_Bag::GetTypeId() const {
        return xx::TypeId_v<FishManage::File_Bag>;
    }
    void File_Bag::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->childs);
    }
    int File_Bag::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->childs)) return r;
        return 0;
    }
    void File_Bag::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void File_Bag::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"childs\":", this->childs);
    }
    File_Lua::File_Lua(File_Lua&& o) noexcept {
        this->operator=(std::move(o));
    }
    File_Lua& File_Lua::operator=(File_Lua&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        return *this;
    }
    void File_Lua::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::File_Lua>(tar);
    }
    void File_Lua::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::File_Lua>(tar);
    }
    uint16_t File_Lua::GetTypeId() const {
        return xx::TypeId_v<FishManage::File_Lua>;
    }
    void File_Lua::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
    }
    int File_Lua::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        return 0;
    }
    void File_Lua::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void File_Lua::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
    }
    File_Sound::File_Sound(File_Sound&& o) noexcept {
        this->operator=(std::move(o));
    }
    File_Sound& File_Sound::operator=(File_Sound&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->seconds, o.seconds);
        return *this;
    }
    void File_Sound::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::File_Sound>(tar);
        xx::CloneFuncs<float>::Clone1(oh, this->seconds, o->seconds);
    }
    void File_Sound::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::File_Sound>(tar);
        xx::CloneFuncs<float>::Clone2(oh, this->seconds, o->seconds);
    }
    uint16_t File_Sound::GetTypeId() const {
        return xx::TypeId_v<FishManage::File_Sound>;
    }
    void File_Sound::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->seconds);
    }
    int File_Sound::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->seconds)) return r;
        return 0;
    }
    void File_Sound::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void File_Sound::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"seconds\":", this->seconds);
    }
    Action::Action(Action&& o) noexcept {
        this->operator=(std::move(o));
    }
    Action& Action::operator=(Action&& o) noexcept {
        std::swap(this->name, o.name);
        std::swap(this->seconds, o.seconds);
        std::swap(this->frameRate, o.frameRate);
        std::swap(this->width, o.width);
        std::swap(this->height, o.height);
        std::swap(this->cdclpss, o.cdclpss);
        return *this;
    }
    Res_Sound::Res_Sound(Res_Sound&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res_Sound& Res_Sound::operator=(Res_Sound&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->files, o.files);
        return *this;
    }
    void Res_Sound::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::Res_Sound>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_Sound>>>::Clone1(oh, this->files, o->files);
    }
    void Res_Sound::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::Res_Sound>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_Sound>>>::Clone2(oh, this->files, o->files);
    }
    uint16_t Res_Sound::GetTypeId() const {
        return xx::TypeId_v<FishManage::Res_Sound>;
    }
    void Res_Sound::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->files);
    }
    int Res_Sound::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->files)) return r;
        return 0;
    }
    void Res_Sound::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Res_Sound::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"files\":", this->files);
    }
    Res_Script::Res_Script(Res_Script&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res_Script& Res_Script::operator=(Res_Script&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->files, o.files);
        return *this;
    }
    void Res_Script::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::Res_Script>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_Lua>>>::Clone1(oh, this->files, o->files);
    }
    void Res_Script::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::Res_Script>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_Lua>>>::Clone2(oh, this->files, o->files);
    }
    uint16_t Res_Script::GetTypeId() const {
        return xx::TypeId_v<FishManage::Res_Script>;
    }
    void Res_Script::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->files);
    }
    int Res_Script::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->files)) return r;
        return 0;
    }
    void Res_Script::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Res_Script::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"files\":", this->files);
    }
    FishState::FishState(FishState&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishState& FishState::operator=(FishState&& o) noexcept {
        std::swap(this->name, o.name);
        std::swap(this->actionName, o.actionName);
        std::swap(this->moveActionFrameDistances, o.moveActionFrameDistances);
        std::swap(this->pathwayGroupName, o.pathwayGroupName);
        return *this;
    }
    FishBase::FishBase(FishBase&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishBase& FishBase::operator=(FishBase&& o) noexcept {
        std::swap(this->name, o.name);
        std::swap(this->resVoiceForDead, o.resVoiceForDead);
        std::swap(this->resAnimation, o.resAnimation);
        std::swap(this->fishStates, o.fishStates);
        std::swap(this->resScript, o.resScript);
        std::swap(this->coin1, o.coin1);
        std::swap(this->coin2, o.coin2);
        std::swap(this->lastUpdateTime, o.lastUpdateTime);
        return *this;
    }
    void FishBase::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        auto&& o = xx::As<FishManage::FishBase>(tar);
        xx::CloneFuncs<std::string>::Clone1(oh, this->name, o->name);
        xx::CloneFuncs<std::weak_ptr<FishManage::Res_Sound>>::Clone1(oh, this->resVoiceForDead, o->resVoiceForDead);
        xx::CloneFuncs<std::weak_ptr<FishManage::Res>>::Clone1(oh, this->resAnimation, o->resAnimation);
        xx::CloneFuncs<std::vector<FishManage::FishState>>::Clone1(oh, this->fishStates, o->fishStates);
        xx::CloneFuncs<std::weak_ptr<FishManage::Res_Script>>::Clone1(oh, this->resScript, o->resScript);
        xx::CloneFuncs<int64_t>::Clone1(oh, this->coin1, o->coin1);
        xx::CloneFuncs<int64_t>::Clone1(oh, this->coin2, o->coin2);
        xx::CloneFuncs<int64_t>::Clone1(oh, this->lastUpdateTime, o->lastUpdateTime);
    }
    void FishBase::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        auto&& o = xx::As<FishManage::FishBase>(tar);
        xx::CloneFuncs<std::string>::Clone2(oh, this->name, o->name);
        xx::CloneFuncs<std::weak_ptr<FishManage::Res_Sound>>::Clone2(oh, this->resVoiceForDead, o->resVoiceForDead);
        xx::CloneFuncs<std::weak_ptr<FishManage::Res>>::Clone2(oh, this->resAnimation, o->resAnimation);
        xx::CloneFuncs<std::vector<FishManage::FishState>>::Clone2(oh, this->fishStates, o->fishStates);
        xx::CloneFuncs<std::weak_ptr<FishManage::Res_Script>>::Clone2(oh, this->resScript, o->resScript);
        xx::CloneFuncs<int64_t>::Clone2(oh, this->coin1, o->coin1);
        xx::CloneFuncs<int64_t>::Clone2(oh, this->coin2, o->coin2);
        xx::CloneFuncs<int64_t>::Clone2(oh, this->lastUpdateTime, o->lastUpdateTime);
    }
    uint16_t FishBase::GetTypeId() const {
        return xx::TypeId_v<FishManage::FishBase>;
    }
    void FishBase::Serialize(xx::DataWriterEx& dw) const {
        dw.Write(this->name);
        dw.Write(this->resVoiceForDead);
        dw.Write(this->resAnimation);
        dw.Write(this->fishStates);
        dw.Write(this->resScript);
        dw.Write(this->coin1);
        dw.Write(this->coin2);
        dw.Write(this->lastUpdateTime);
    }
    int FishBase::Deserialize(xx::DataReaderEx& dr) {
        if (int r = dr.Read(this->name)) return r;
        if (int r = dr.Read(this->resVoiceForDead)) return r;
        if (int r = dr.Read(this->resAnimation)) return r;
        if (int r = dr.Read(this->fishStates)) return r;
        if (int r = dr.Read(this->resScript)) return r;
        if (int r = dr.Read(this->coin1)) return r;
        if (int r = dr.Read(this->coin2)) return r;
        if (int r = dr.Read(this->lastUpdateTime)) return r;
        return 0;
    }
    void FishBase::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void FishBase::ToStringCore(xx::ObjectHelper &oh) const {
        xx::AppendEx(oh, ",\"name\":", this->name);
        xx::AppendEx(oh, ",\"resVoiceForDead\":", this->resVoiceForDead);
        xx::AppendEx(oh, ",\"resAnimation\":", this->resAnimation);
        xx::AppendEx(oh, ",\"fishStates\":", this->fishStates);
        xx::AppendEx(oh, ",\"resScript\":", this->resScript);
        xx::AppendEx(oh, ",\"coin1\":", this->coin1);
        xx::AppendEx(oh, ",\"coin2\":", this->coin2);
        xx::AppendEx(oh, ",\"lastUpdateTime\":", this->lastUpdateTime);
    }
    File_Picture::File_Picture(File_Picture&& o) noexcept {
        this->operator=(std::move(o));
    }
    File_Picture& File_Picture::operator=(File_Picture&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->cdclps, o.cdclps);
        std::swap(this->baseScale, o.baseScale);
        std::swap(this->baseAngle, o.baseAngle);
        std::swap(this->offsetX, o.offsetX);
        std::swap(this->offsetY, o.offsetY);
        std::swap(this->shadowScale, o.shadowScale);
        std::swap(this->shadowOffsetX, o.shadowOffsetX);
        std::swap(this->shadowOffsetY, o.shadowOffsetY);
        std::swap(this->atPList, o.atPList);
        return *this;
    }
    void File_Picture::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::File_Picture>(tar);
        xx::CloneFuncs<FishManage::CDCirclesLockPoints>::Clone1(oh, this->cdclps, o->cdclps);
        xx::CloneFuncs<float>::Clone1(oh, this->baseScale, o->baseScale);
        xx::CloneFuncs<float>::Clone1(oh, this->baseAngle, o->baseAngle);
        xx::CloneFuncs<float>::Clone1(oh, this->offsetX, o->offsetX);
        xx::CloneFuncs<float>::Clone1(oh, this->offsetY, o->offsetY);
        xx::CloneFuncs<float>::Clone1(oh, this->shadowScale, o->shadowScale);
        xx::CloneFuncs<float>::Clone1(oh, this->shadowOffsetX, o->shadowOffsetX);
        xx::CloneFuncs<float>::Clone1(oh, this->shadowOffsetY, o->shadowOffsetY);
        xx::CloneFuncs<std::weak_ptr<FishManage::File_Bag>>::Clone1(oh, this->atPList, o->atPList);
    }
    void File_Picture::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::File_Picture>(tar);
        xx::CloneFuncs<FishManage::CDCirclesLockPoints>::Clone2(oh, this->cdclps, o->cdclps);
        xx::CloneFuncs<float>::Clone2(oh, this->baseScale, o->baseScale);
        xx::CloneFuncs<float>::Clone2(oh, this->baseAngle, o->baseAngle);
        xx::CloneFuncs<float>::Clone2(oh, this->offsetX, o->offsetX);
        xx::CloneFuncs<float>::Clone2(oh, this->offsetY, o->offsetY);
        xx::CloneFuncs<float>::Clone2(oh, this->shadowScale, o->shadowScale);
        xx::CloneFuncs<float>::Clone2(oh, this->shadowOffsetX, o->shadowOffsetX);
        xx::CloneFuncs<float>::Clone2(oh, this->shadowOffsetY, o->shadowOffsetY);
        xx::CloneFuncs<std::weak_ptr<FishManage::File_Bag>>::Clone2(oh, this->atPList, o->atPList);
    }
    uint16_t File_Picture::GetTypeId() const {
        return xx::TypeId_v<FishManage::File_Picture>;
    }
    void File_Picture::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->cdclps);
        dw.Write(this->baseScale);
        dw.Write(this->baseAngle);
        dw.Write(this->offsetX);
        dw.Write(this->offsetY);
        dw.Write(this->shadowScale);
        dw.Write(this->shadowOffsetX);
        dw.Write(this->shadowOffsetY);
        dw.Write(this->atPList);
    }
    int File_Picture::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->cdclps)) return r;
        if (int r = dr.Read(this->baseScale)) return r;
        if (int r = dr.Read(this->baseAngle)) return r;
        if (int r = dr.Read(this->offsetX)) return r;
        if (int r = dr.Read(this->offsetY)) return r;
        if (int r = dr.Read(this->shadowScale)) return r;
        if (int r = dr.Read(this->shadowOffsetX)) return r;
        if (int r = dr.Read(this->shadowOffsetY)) return r;
        if (int r = dr.Read(this->atPList)) return r;
        return 0;
    }
    void File_Picture::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void File_Picture::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"cdclps\":", this->cdclps);
        xx::AppendEx(oh, ",\"baseScale\":", this->baseScale);
        xx::AppendEx(oh, ",\"baseAngle\":", this->baseAngle);
        xx::AppendEx(oh, ",\"offsetX\":", this->offsetX);
        xx::AppendEx(oh, ",\"offsetY\":", this->offsetY);
        xx::AppendEx(oh, ",\"shadowScale\":", this->shadowScale);
        xx::AppendEx(oh, ",\"shadowOffsetX\":", this->shadowOffsetX);
        xx::AppendEx(oh, ",\"shadowOffsetY\":", this->shadowOffsetY);
        xx::AppendEx(oh, ",\"atPList\":", this->atPList);
    }
    File_Animation::File_Animation(File_Animation&& o) noexcept {
        this->operator=(std::move(o));
    }
    File_Animation& File_Animation::operator=(File_Animation&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->actions, o.actions);
        return *this;
    }
    void File_Animation::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::File_Animation>(tar);
        xx::CloneFuncs<std::vector<FishManage::Action>>::Clone1(oh, this->actions, o->actions);
    }
    void File_Animation::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::File_Animation>(tar);
        xx::CloneFuncs<std::vector<FishManage::Action>>::Clone2(oh, this->actions, o->actions);
    }
    uint16_t File_Animation::GetTypeId() const {
        return xx::TypeId_v<FishManage::File_Animation>;
    }
    void File_Animation::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->actions);
    }
    int File_Animation::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->actions)) return r;
        return 0;
    }
    void File_Animation::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void File_Animation::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"actions\":", this->actions);
    }
    FrameAction::FrameAction(FrameAction&& o) noexcept {
        this->operator=(std::move(o));
    }
    FrameAction& FrameAction::operator=(FrameAction&& o) noexcept {
        this->FishManage::Action::operator=(std::move(o));
        std::swap(this->pictures, o.pictures);
        return *this;
    }
    CombineItem::CombineItem(CombineItem&& o) noexcept {
        this->operator=(std::move(o));
    }
    CombineItem& CombineItem::operator=(CombineItem&& o) noexcept {
        std::swap(this->file, o.file);
        std::swap(this->offsetX, o.offsetX);
        std::swap(this->offsetY, o.offsetY);
        std::swap(this->angle, o.angle);
        std::swap(this->scale, o.scale);
        return *this;
    }
    File_Combine::File_Combine(File_Combine&& o) noexcept {
        this->operator=(std::move(o));
    }
    File_Combine& File_Combine::operator=(File_Combine&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->items, o.items);
        return *this;
    }
    void File_Combine::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::File_Combine>(tar);
        xx::CloneFuncs<std::vector<FishManage::CombineItem>>::Clone1(oh, this->items, o->items);
    }
    void File_Combine::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::File_Combine>(tar);
        xx::CloneFuncs<std::vector<FishManage::CombineItem>>::Clone2(oh, this->items, o->items);
    }
    uint16_t File_Combine::GetTypeId() const {
        return xx::TypeId_v<FishManage::File_Combine>;
    }
    void File_Combine::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->items);
    }
    int File_Combine::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->items)) return r;
        return 0;
    }
    void File_Combine::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void File_Combine::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"items\":", this->items);
    }
    File_C3b::File_C3b(File_C3b&& o) noexcept {
        this->operator=(std::move(o));
    }
    File_C3b& File_C3b::operator=(File_C3b&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->baseScale, o.baseScale);
        std::swap(this->baseAngleX, o.baseAngleX);
        std::swap(this->baseAngleY, o.baseAngleY);
        std::swap(this->baseAngleZ, o.baseAngleZ);
        std::swap(this->offsetX, o.offsetX);
        std::swap(this->offsetY, o.offsetY);
        std::swap(this->offsetZ, o.offsetZ);
        return *this;
    }
    void File_C3b::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::File_C3b>(tar);
        xx::CloneFuncs<float>::Clone1(oh, this->baseScale, o->baseScale);
        xx::CloneFuncs<float>::Clone1(oh, this->baseAngleX, o->baseAngleX);
        xx::CloneFuncs<float>::Clone1(oh, this->baseAngleY, o->baseAngleY);
        xx::CloneFuncs<float>::Clone1(oh, this->baseAngleZ, o->baseAngleZ);
        xx::CloneFuncs<float>::Clone1(oh, this->offsetX, o->offsetX);
        xx::CloneFuncs<float>::Clone1(oh, this->offsetY, o->offsetY);
        xx::CloneFuncs<float>::Clone1(oh, this->offsetZ, o->offsetZ);
    }
    void File_C3b::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::File_C3b>(tar);
        xx::CloneFuncs<float>::Clone2(oh, this->baseScale, o->baseScale);
        xx::CloneFuncs<float>::Clone2(oh, this->baseAngleX, o->baseAngleX);
        xx::CloneFuncs<float>::Clone2(oh, this->baseAngleY, o->baseAngleY);
        xx::CloneFuncs<float>::Clone2(oh, this->baseAngleZ, o->baseAngleZ);
        xx::CloneFuncs<float>::Clone2(oh, this->offsetX, o->offsetX);
        xx::CloneFuncs<float>::Clone2(oh, this->offsetY, o->offsetY);
        xx::CloneFuncs<float>::Clone2(oh, this->offsetZ, o->offsetZ);
    }
    uint16_t File_C3b::GetTypeId() const {
        return xx::TypeId_v<FishManage::File_C3b>;
    }
    void File_C3b::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->baseScale);
        dw.Write(this->baseAngleX);
        dw.Write(this->baseAngleY);
        dw.Write(this->baseAngleZ);
        dw.Write(this->offsetX);
        dw.Write(this->offsetY);
        dw.Write(this->offsetZ);
    }
    int File_C3b::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->baseScale)) return r;
        if (int r = dr.Read(this->baseAngleX)) return r;
        if (int r = dr.Read(this->baseAngleY)) return r;
        if (int r = dr.Read(this->baseAngleZ)) return r;
        if (int r = dr.Read(this->offsetX)) return r;
        if (int r = dr.Read(this->offsetY)) return r;
        if (int r = dr.Read(this->offsetZ)) return r;
        return 0;
    }
    void File_C3b::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void File_C3b::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"baseScale\":", this->baseScale);
        xx::AppendEx(oh, ",\"baseAngleX\":", this->baseAngleX);
        xx::AppendEx(oh, ",\"baseAngleY\":", this->baseAngleY);
        xx::AppendEx(oh, ",\"baseAngleZ\":", this->baseAngleZ);
        xx::AppendEx(oh, ",\"offsetX\":", this->offsetX);
        xx::AppendEx(oh, ",\"offsetY\":", this->offsetY);
        xx::AppendEx(oh, ",\"offsetZ\":", this->offsetZ);
    }
    File_Spine::File_Spine(File_Spine&& o) noexcept {
        this->operator=(std::move(o));
    }
    File_Spine& File_Spine::operator=(File_Spine&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->shadowScale, o.shadowScale);
        std::swap(this->shadowOffsetX, o.shadowOffsetX);
        std::swap(this->shadowOffsetY, o.shadowOffsetY);
        std::swap(this->baseScale, o.baseScale);
        std::swap(this->baseAngle, o.baseAngle);
        std::swap(this->offsetX, o.offsetX);
        std::swap(this->offsetY, o.offsetY);
        return *this;
    }
    void File_Spine::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::File_Spine>(tar);
        xx::CloneFuncs<float>::Clone1(oh, this->shadowScale, o->shadowScale);
        xx::CloneFuncs<float>::Clone1(oh, this->shadowOffsetX, o->shadowOffsetX);
        xx::CloneFuncs<float>::Clone1(oh, this->shadowOffsetY, o->shadowOffsetY);
        xx::CloneFuncs<float>::Clone1(oh, this->baseScale, o->baseScale);
        xx::CloneFuncs<float>::Clone1(oh, this->baseAngle, o->baseAngle);
        xx::CloneFuncs<float>::Clone1(oh, this->offsetX, o->offsetX);
        xx::CloneFuncs<float>::Clone1(oh, this->offsetY, o->offsetY);
    }
    void File_Spine::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::File_Spine>(tar);
        xx::CloneFuncs<float>::Clone2(oh, this->shadowScale, o->shadowScale);
        xx::CloneFuncs<float>::Clone2(oh, this->shadowOffsetX, o->shadowOffsetX);
        xx::CloneFuncs<float>::Clone2(oh, this->shadowOffsetY, o->shadowOffsetY);
        xx::CloneFuncs<float>::Clone2(oh, this->baseScale, o->baseScale);
        xx::CloneFuncs<float>::Clone2(oh, this->baseAngle, o->baseAngle);
        xx::CloneFuncs<float>::Clone2(oh, this->offsetX, o->offsetX);
        xx::CloneFuncs<float>::Clone2(oh, this->offsetY, o->offsetY);
    }
    uint16_t File_Spine::GetTypeId() const {
        return xx::TypeId_v<FishManage::File_Spine>;
    }
    void File_Spine::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->shadowScale);
        dw.Write(this->shadowOffsetX);
        dw.Write(this->shadowOffsetY);
        dw.Write(this->baseScale);
        dw.Write(this->baseAngle);
        dw.Write(this->offsetX);
        dw.Write(this->offsetY);
    }
    int File_Spine::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->shadowScale)) return r;
        if (int r = dr.Read(this->shadowOffsetX)) return r;
        if (int r = dr.Read(this->shadowOffsetY)) return r;
        if (int r = dr.Read(this->baseScale)) return r;
        if (int r = dr.Read(this->baseAngle)) return r;
        if (int r = dr.Read(this->offsetX)) return r;
        if (int r = dr.Read(this->offsetY)) return r;
        return 0;
    }
    void File_Spine::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void File_Spine::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"shadowScale\":", this->shadowScale);
        xx::AppendEx(oh, ",\"shadowOffsetX\":", this->shadowOffsetX);
        xx::AppendEx(oh, ",\"shadowOffsetY\":", this->shadowOffsetY);
        xx::AppendEx(oh, ",\"baseScale\":", this->baseScale);
        xx::AppendEx(oh, ",\"baseAngle\":", this->baseAngle);
        xx::AppendEx(oh, ",\"offsetX\":", this->offsetX);
        xx::AppendEx(oh, ",\"offsetY\":", this->offsetY);
    }
    File_FrameAnimation::File_FrameAnimation(File_FrameAnimation&& o) noexcept {
        this->operator=(std::move(o));
    }
    File_FrameAnimation& File_FrameAnimation::operator=(File_FrameAnimation&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->actions, o.actions);
        return *this;
    }
    void File_FrameAnimation::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::File_FrameAnimation>(tar);
        xx::CloneFuncs<std::vector<FishManage::FrameAction>>::Clone1(oh, this->actions, o->actions);
    }
    void File_FrameAnimation::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::File_FrameAnimation>(tar);
        xx::CloneFuncs<std::vector<FishManage::FrameAction>>::Clone2(oh, this->actions, o->actions);
    }
    uint16_t File_FrameAnimation::GetTypeId() const {
        return xx::TypeId_v<FishManage::File_FrameAnimation>;
    }
    void File_FrameAnimation::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->actions);
    }
    int File_FrameAnimation::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->actions)) return r;
        return 0;
    }
    void File_FrameAnimation::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void File_FrameAnimation::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"actions\":", this->actions);
    }
    Res_Picture::Res_Picture(Res_Picture&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res_Picture& Res_Picture::operator=(Res_Picture&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->files, o.files);
        return *this;
    }
    void Res_Picture::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::Res_Picture>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_Picture>>>::Clone1(oh, this->files, o->files);
    }
    void Res_Picture::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::Res_Picture>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_Picture>>>::Clone2(oh, this->files, o->files);
    }
    uint16_t Res_Picture::GetTypeId() const {
        return xx::TypeId_v<FishManage::Res_Picture>;
    }
    void Res_Picture::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->files);
    }
    int Res_Picture::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->files)) return r;
        return 0;
    }
    void Res_Picture::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Res_Picture::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"files\":", this->files);
    }
    Res_FrameAnimation::Res_FrameAnimation(Res_FrameAnimation&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res_FrameAnimation& Res_FrameAnimation::operator=(Res_FrameAnimation&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->files, o.files);
        return *this;
    }
    void Res_FrameAnimation::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::Res_FrameAnimation>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_FrameAnimation>>>::Clone1(oh, this->files, o->files);
    }
    void Res_FrameAnimation::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::Res_FrameAnimation>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_FrameAnimation>>>::Clone2(oh, this->files, o->files);
    }
    uint16_t Res_FrameAnimation::GetTypeId() const {
        return xx::TypeId_v<FishManage::Res_FrameAnimation>;
    }
    void Res_FrameAnimation::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->files);
    }
    int Res_FrameAnimation::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->files)) return r;
        return 0;
    }
    void Res_FrameAnimation::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Res_FrameAnimation::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"files\":", this->files);
    }
    Res_Spine::Res_Spine(Res_Spine&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res_Spine& Res_Spine::operator=(Res_Spine&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->files, o.files);
        return *this;
    }
    void Res_Spine::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::Res_Spine>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_Spine>>>::Clone1(oh, this->files, o->files);
    }
    void Res_Spine::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::Res_Spine>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_Spine>>>::Clone2(oh, this->files, o->files);
    }
    uint16_t Res_Spine::GetTypeId() const {
        return xx::TypeId_v<FishManage::Res_Spine>;
    }
    void Res_Spine::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->files);
    }
    int Res_Spine::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->files)) return r;
        return 0;
    }
    void Res_Spine::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Res_Spine::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"files\":", this->files);
    }
    Res_3d::Res_3d(Res_3d&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res_3d& Res_3d::operator=(Res_3d&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->files, o.files);
        return *this;
    }
    void Res_3d::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::Res_3d>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_C3b>>>::Clone1(oh, this->files, o->files);
    }
    void Res_3d::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::Res_3d>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_C3b>>>::Clone2(oh, this->files, o->files);
    }
    uint16_t Res_3d::GetTypeId() const {
        return xx::TypeId_v<FishManage::Res_3d>;
    }
    void Res_3d::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->files);
    }
    int Res_3d::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->files)) return r;
        return 0;
    }
    void Res_3d::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Res_3d::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"files\":", this->files);
    }
    Res_Combine::Res_Combine(Res_Combine&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res_Combine& Res_Combine::operator=(Res_Combine&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->files, o.files);
        return *this;
    }
    void Res_Combine::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::Res_Combine>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_Combine>>>::Clone1(oh, this->files, o->files);
    }
    void Res_Combine::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::Res_Combine>(tar);
        xx::CloneFuncs<std::vector<std::pair<int32_t, FishManage::File_Combine>>>::Clone2(oh, this->files, o->files);
    }
    uint16_t Res_Combine::GetTypeId() const {
        return xx::TypeId_v<FishManage::Res_Combine>;
    }
    void Res_Combine::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->files);
    }
    int Res_Combine::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->files)) return r;
        return 0;
    }
    void Res_Combine::ToString(xx::ObjectHelper &oh) const {
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void Res_Combine::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"files\":", this->files);
    }
    FishFury::FishFury(FishFury&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishFury& FishFury::operator=(FishFury&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->numBulletsPerShoot, o.numBulletsPerShoot);
        return *this;
    }
    void FishFury::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::FishFury>(tar);
        xx::CloneFuncs<int64_t>::Clone1(oh, this->numBulletsPerShoot, o->numBulletsPerShoot);
    }
    void FishFury::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::FishFury>(tar);
        xx::CloneFuncs<int64_t>::Clone2(oh, this->numBulletsPerShoot, o->numBulletsPerShoot);
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
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
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
    void FishDrill::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::FishDrill>(tar);
        xx::CloneFuncs<int64_t>::Clone1(oh, this->reserveCoin, o->reserveCoin);
    }
    void FishDrill::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::FishDrill>(tar);
        xx::CloneFuncs<int64_t>::Clone2(oh, this->reserveCoin, o->reserveCoin);
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
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void FishDrill::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"reserveCoin\":", this->reserveCoin);
    }
    Data::Data(Data&& o) noexcept {
        this->operator=(std::move(o));
    }
    Data& Data::operator=(Data&& o) noexcept {
        std::swap(this->files, o.files);
        std::swap(this->resScripts, o.resScripts);
        std::swap(this->resSounds, o.resSounds);
        std::swap(this->resPictures, o.resPictures);
        std::swap(this->resFrameAnimations, o.resFrameAnimations);
        std::swap(this->resSpines, o.resSpines);
        std::swap(this->res3ds, o.res3ds);
        std::swap(this->resCombines, o.resCombines);
        std::swap(this->fishs, o.fishs);
        return *this;
    }
    FishNormal::FishNormal(FishNormal&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishNormal& FishNormal::operator=(FishNormal&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        return *this;
    }
    void FishNormal::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::FishNormal>(tar);
    }
    void FishNormal::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::FishNormal>(tar);
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
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void FishNormal::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
    }
    FishCyclone::FishCyclone(FishCyclone&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishCyclone& FishCyclone::operator=(FishCyclone&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->sameFishName, o.sameFishName);
        return *this;
    }
    void FishCyclone::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::FishCyclone>(tar);
        xx::CloneFuncs<std::string>::Clone1(oh, this->sameFishName, o->sameFishName);
    }
    void FishCyclone::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::FishCyclone>(tar);
        xx::CloneFuncs<std::string>::Clone2(oh, this->sameFishName, o->sameFishName);
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
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
        }
        xx::AppendEx(oh, "{\"#\":", GetTypeId());
        ToStringCore(oh);
        oh.s.push_back('}');
    }
    void FishCyclone::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"sameFishName\":", this->sameFishName);
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
    void FishBomb::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::FishBomb>(tar);
        xx::CloneFuncs<int32_t>::Clone1(oh, this->timesFrom, o->timesFrom);
        xx::CloneFuncs<int32_t>::Clone1(oh, this->timesTo, o->timesTo);
    }
    void FishBomb::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::FishBomb>(tar);
        xx::CloneFuncs<int32_t>::Clone2(oh, this->timesFrom, o->timesFrom);
        xx::CloneFuncs<int32_t>::Clone2(oh, this->timesTo, o->timesTo);
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
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
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
    FishEater::FishEater(FishEater&& o) noexcept {
        this->operator=(std::move(o));
    }
    FishEater& FishEater::operator=(FishEater&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->fishNames, o.fishNames);
        return *this;
    }
    void FishEater::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::FishEater>(tar);
        xx::CloneFuncs<std::vector<std::string>>::Clone1(oh, this->fishNames, o->fishNames);
    }
    void FishEater::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::FishEater>(tar);
        xx::CloneFuncs<std::vector<std::string>>::Clone2(oh, this->fishNames, o->fishNames);
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
        auto&& iter = oh.objOffsets.find((void*)this);
        if (iter != oh.objOffsets.end()) {
        	xx::AppendEx(oh, iter->second);
        	return;
        }
        else {
            oh.objOffsets[(void*)this] = oh.s.size();
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
