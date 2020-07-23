#include "FishManage_class_lite.h"
#include "FishManage_class_lite.cpp.inc"
namespace FishManage {
	void PkgGenTypes::RegisterTo(xx::ObjectHelper& oh) {
	    oh.Register<FishManage::File>();
	    oh.Register<FishManage::ResBase>();
	    oh.Register<FishManage::ResSound>();
	    oh.Register<FishManage::ResMusic>();
	    oh.Register<FishManage::ResVoice>();
	    oh.Register<FishManage::ResPList>();
	    oh.Register<FishManage::ResPicture>();
	    oh.Register<FishManage::ResTexture>();
	    oh.Register<FishManage::ResFrame>();
	    oh.Register<FishManage::ResAnimation>();
	    oh.Register<FishManage::ResSpine>();
	    oh.Register<FishManage::Res3d>();
	    oh.Register<FishManage::ResFrameAnimation>();
	    oh.Register<FishManage::ResCombine>();
	    oh.Register<FishManage::ResScript>();
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
    void CloneFuncs<FishManage::ActionBase>::Clone1(xx::ObjectHelper &oh, FishManage::ActionBase const& in, FishManage::ActionBase &out) {
        CloneFuncs<std::string>::Clone1(oh, in.name, out.name);
        CloneFuncs<float>::Clone1(oh, in.seconds, out.seconds);
        CloneFuncs<float>::Clone1(oh, in.frameRate, out.frameRate);
        CloneFuncs<float>::Clone1(oh, in.width, out.width);
        CloneFuncs<float>::Clone1(oh, in.height, out.height);
    }
    void CloneFuncs<FishManage::ActionBase>::Clone2(xx::ObjectHelper &oh, FishManage::ActionBase const& in, FishManage::ActionBase &out) {
        CloneFuncs<std::string>::Clone2(oh, in.name, out.name);
        CloneFuncs<float>::Clone2(oh, in.seconds, out.seconds);
        CloneFuncs<float>::Clone2(oh, in.frameRate, out.frameRate);
        CloneFuncs<float>::Clone2(oh, in.width, out.width);
        CloneFuncs<float>::Clone2(oh, in.height, out.height);
    }
	void DataFuncsEx<FishManage::ActionBase, void>::Write(DataWriterEx& dw, FishManage::ActionBase const& in) {
        dw.Write(in.name);
        dw.Write(in.seconds);
        dw.Write(in.frameRate);
        dw.Write(in.width);
        dw.Write(in.height);
    }
	int DataFuncsEx<FishManage::ActionBase, void>::Read(DataReaderEx& d, FishManage::ActionBase& out) {
        if (int r = d.Read(out.name)) return r;
        if (int r = d.Read(out.seconds)) return r;
        if (int r = d.Read(out.frameRate)) return r;
        if (int r = d.Read(out.width)) return r;
        if (int r = d.Read(out.height)) return r;
        return 0;
    }
	void StringFuncsEx<FishManage::ActionBase, void>::Append(ObjectHelper &oh, FishManage::ActionBase const& in) {
        oh.s.push_back('{');
        AppendCore(oh, in);
        oh.s.push_back('}');
    }
	void StringFuncsEx<FishManage::ActionBase, void>::AppendCore(ObjectHelper &oh, FishManage::ActionBase const& in) {
        auto sizeBak = oh.s.size();
        if (sizeBak == oh.s.size()) {
            oh.s.push_back(',');
        }
        xx::AppendEx(oh, "\"name\":", in.name); 
        xx::AppendEx(oh, ",\"seconds\":", in.seconds);
        xx::AppendEx(oh, ",\"frameRate\":", in.frameRate);
        xx::AppendEx(oh, ",\"width\":", in.width);
        xx::AppendEx(oh, ",\"height\":", in.height);
    }
    void CloneFuncs<FishManage::ActionOthers>::Clone1(xx::ObjectHelper &oh, FishManage::ActionOthers const& in, FishManage::ActionOthers &out) {
        CloneFuncs<FishManage::ActionBase>::Clone1(oh, in, out);
        CloneFuncs<std::vector<FishManage::CDCirclesLockPoints>>::Clone1(oh, in.cdclpss, out.cdclpss);
    }
    void CloneFuncs<FishManage::ActionOthers>::Clone2(xx::ObjectHelper &oh, FishManage::ActionOthers const& in, FishManage::ActionOthers &out) {
        CloneFuncs<FishManage::ActionBase>::Clone2(oh, in, out);
        CloneFuncs<std::vector<FishManage::CDCirclesLockPoints>>::Clone2(oh, in.cdclpss, out.cdclpss);
    }
	void DataFuncsEx<FishManage::ActionOthers, void>::Write(DataWriterEx& dw, FishManage::ActionOthers const& in) {
        DataFuncsEx<FishManage::ActionBase>::Write(dw, in);
        dw.Write(in.cdclpss);
    }
	int DataFuncsEx<FishManage::ActionOthers, void>::Read(DataReaderEx& d, FishManage::ActionOthers& out) {
        if (int r = DataFuncsEx<FishManage::ActionBase>::Read(d, out)) return r;
        if (int r = d.Read(out.cdclpss)) return r;
        return 0;
    }
	void StringFuncsEx<FishManage::ActionOthers, void>::Append(ObjectHelper &oh, FishManage::ActionOthers const& in) {
        oh.s.push_back('{');
        AppendCore(oh, in);
        oh.s.push_back('}');
    }
	void StringFuncsEx<FishManage::ActionOthers, void>::AppendCore(ObjectHelper &oh, FishManage::ActionOthers const& in) {
        auto sizeBak = oh.s.size();
        StringFuncsEx<FishManage::ActionBase>::AppendCore(oh, in);
        if (sizeBak == oh.s.size()) {
            oh.s.push_back(',');
        }
        xx::AppendEx(oh, "\"cdclpss\":", in.cdclpss); 
    }
    void CloneFuncs<FishManage::CombineItem>::Clone1(xx::ObjectHelper &oh, FishManage::CombineItem const& in, FishManage::CombineItem &out) {
        CloneFuncs<std::weak_ptr<FishManage::ResAnimation>>::Clone1(oh, in.res, out.res);
        CloneFuncs<float>::Clone1(oh, in.offsetX, out.offsetX);
        CloneFuncs<float>::Clone1(oh, in.offsetY, out.offsetY);
        CloneFuncs<float>::Clone1(oh, in.baseAngle, out.baseAngle);
        CloneFuncs<float>::Clone1(oh, in.baseScale, out.baseScale);
    }
    void CloneFuncs<FishManage::CombineItem>::Clone2(xx::ObjectHelper &oh, FishManage::CombineItem const& in, FishManage::CombineItem &out) {
        CloneFuncs<std::weak_ptr<FishManage::ResAnimation>>::Clone2(oh, in.res, out.res);
        CloneFuncs<float>::Clone2(oh, in.offsetX, out.offsetX);
        CloneFuncs<float>::Clone2(oh, in.offsetY, out.offsetY);
        CloneFuncs<float>::Clone2(oh, in.baseAngle, out.baseAngle);
        CloneFuncs<float>::Clone2(oh, in.baseScale, out.baseScale);
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
    void CloneFuncs<FishManage::ActionSpriteFrame>::Clone1(xx::ObjectHelper &oh, FishManage::ActionSpriteFrame const& in, FishManage::ActionSpriteFrame &out) {
        CloneFuncs<FishManage::ActionBase>::Clone1(oh, in, out);
        CloneFuncs<std::vector<std::weak_ptr<FishManage::ResPicture>>>::Clone1(oh, in.frames, out.frames);
    }
    void CloneFuncs<FishManage::ActionSpriteFrame>::Clone2(xx::ObjectHelper &oh, FishManage::ActionSpriteFrame const& in, FishManage::ActionSpriteFrame &out) {
        CloneFuncs<FishManage::ActionBase>::Clone2(oh, in, out);
        CloneFuncs<std::vector<std::weak_ptr<FishManage::ResPicture>>>::Clone2(oh, in.frames, out.frames);
    }
	void DataFuncsEx<FishManage::ActionSpriteFrame, void>::Write(DataWriterEx& dw, FishManage::ActionSpriteFrame const& in) {
        DataFuncsEx<FishManage::ActionBase>::Write(dw, in);
        dw.Write(in.frames);
    }
	int DataFuncsEx<FishManage::ActionSpriteFrame, void>::Read(DataReaderEx& d, FishManage::ActionSpriteFrame& out) {
        if (int r = DataFuncsEx<FishManage::ActionBase>::Read(d, out)) return r;
        if (int r = d.Read(out.frames)) return r;
        return 0;
    }
	void StringFuncsEx<FishManage::ActionSpriteFrame, void>::Append(ObjectHelper &oh, FishManage::ActionSpriteFrame const& in) {
        oh.s.push_back('{');
        AppendCore(oh, in);
        oh.s.push_back('}');
    }
	void StringFuncsEx<FishManage::ActionSpriteFrame, void>::AppendCore(ObjectHelper &oh, FishManage::ActionSpriteFrame const& in) {
        auto sizeBak = oh.s.size();
        StringFuncsEx<FishManage::ActionBase>::AppendCore(oh, in);
        if (sizeBak == oh.s.size()) {
            oh.s.push_back(',');
        }
        xx::AppendEx(oh, "\"frames\":", in.frames); 
    }
    void CloneFuncs<FishManage::Data>::Clone1(xx::ObjectHelper &oh, FishManage::Data const& in, FishManage::Data &out) {
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::File>>>::Clone1(oh, in.files, out.files);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResMusic>>>::Clone1(oh, in.resMusics, out.resMusics);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResVoice>>>::Clone1(oh, in.resVoices, out.resVoices);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResTexture>>>::Clone1(oh, in.resTextures, out.resTextures);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResPList>>>::Clone1(oh, in.resPLists, out.resPLists);
        CloneFuncs<std::map<std::string, std::weak_ptr<FishManage::ResFrame>>>::Clone1(oh, in.resFrames, out.resFrames);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResSpine>>>::Clone1(oh, in.resSpines, out.resSpines);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res3d>>>::Clone1(oh, in.res3ds, out.res3ds);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResFrameAnimation>>>::Clone1(oh, in.resFrameAnimations, out.resFrameAnimations);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResCombine>>>::Clone1(oh, in.resCombine, out.resCombine);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResScript>>>::Clone1(oh, in.resScripts, out.resScripts);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::FishBase>>>::Clone1(oh, in.fishs, out.fishs);
    }
    void CloneFuncs<FishManage::Data>::Clone2(xx::ObjectHelper &oh, FishManage::Data const& in, FishManage::Data &out) {
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::File>>>::Clone2(oh, in.files, out.files);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResMusic>>>::Clone2(oh, in.resMusics, out.resMusics);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResVoice>>>::Clone2(oh, in.resVoices, out.resVoices);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResTexture>>>::Clone2(oh, in.resTextures, out.resTextures);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResPList>>>::Clone2(oh, in.resPLists, out.resPLists);
        CloneFuncs<std::map<std::string, std::weak_ptr<FishManage::ResFrame>>>::Clone2(oh, in.resFrames, out.resFrames);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResSpine>>>::Clone2(oh, in.resSpines, out.resSpines);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::Res3d>>>::Clone2(oh, in.res3ds, out.res3ds);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResFrameAnimation>>>::Clone2(oh, in.resFrameAnimations, out.resFrameAnimations);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResCombine>>>::Clone2(oh, in.resCombine, out.resCombine);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::ResScript>>>::Clone2(oh, in.resScripts, out.resScripts);
        CloneFuncs<std::map<std::string, std::shared_ptr<FishManage::FishBase>>>::Clone2(oh, in.fishs, out.fishs);
    }
	void DataFuncsEx<FishManage::Data, void>::Write(DataWriterEx& dw, FishManage::Data const& in) {
        dw.Write(in.files);
        dw.Write(in.resMusics);
        dw.Write(in.resVoices);
        dw.Write(in.resTextures);
        dw.Write(in.resPLists);
        dw.Write(in.resFrames);
        dw.Write(in.resSpines);
        dw.Write(in.res3ds);
        dw.Write(in.resFrameAnimations);
        dw.Write(in.resCombine);
        dw.Write(in.resScripts);
        dw.Write(in.fishs);
    }
	int DataFuncsEx<FishManage::Data, void>::Read(DataReaderEx& d, FishManage::Data& out) {
        if (int r = d.Read(out.files)) return r;
        if (int r = d.Read(out.resMusics)) return r;
        if (int r = d.Read(out.resVoices)) return r;
        if (int r = d.Read(out.resTextures)) return r;
        if (int r = d.Read(out.resPLists)) return r;
        if (int r = d.Read(out.resFrames)) return r;
        if (int r = d.Read(out.resSpines)) return r;
        if (int r = d.Read(out.res3ds)) return r;
        if (int r = d.Read(out.resFrameAnimations)) return r;
        if (int r = d.Read(out.resCombine)) return r;
        if (int r = d.Read(out.resScripts)) return r;
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
        xx::AppendEx(oh, ",\"resMusics\":", in.resMusics);
        xx::AppendEx(oh, ",\"resVoices\":", in.resVoices);
        xx::AppendEx(oh, ",\"resTextures\":", in.resTextures);
        xx::AppendEx(oh, ",\"resPLists\":", in.resPLists);
        xx::AppendEx(oh, ",\"resFrames\":", in.resFrames);
        xx::AppendEx(oh, ",\"resSpines\":", in.resSpines);
        xx::AppendEx(oh, ",\"res3ds\":", in.res3ds);
        xx::AppendEx(oh, ",\"resFrameAnimations\":", in.resFrameAnimations);
        xx::AppendEx(oh, ",\"resCombine\":", in.resCombine);
        xx::AppendEx(oh, ",\"resScripts\":", in.resScripts);
        xx::AppendEx(oh, ",\"fishs\":", in.fishs);
    }
}
namespace FishManage {
    ResBase::ResBase(ResBase&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResBase& ResBase::operator=(ResBase&& o) noexcept {
        std::swap(this->name, o.name);
        return *this;
    }
    void ResBase::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        auto&& o = xx::As<FishManage::ResBase>(tar);
        xx::CloneFuncs<std::string>::Clone1(oh, this->name, o->name);
    }
    void ResBase::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        auto&& o = xx::As<FishManage::ResBase>(tar);
        xx::CloneFuncs<std::string>::Clone2(oh, this->name, o->name);
    }
    uint16_t ResBase::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResBase>;
    }
    void ResBase::Serialize(xx::DataWriterEx& dw) const {
        dw.Write(this->name);
    }
    int ResBase::Deserialize(xx::DataReaderEx& dr) {
        if (int r = dr.Read(this->name)) return r;
        return 0;
    }
    void ResBase::ToString(xx::ObjectHelper &oh) const {
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
    void ResBase::ToStringCore(xx::ObjectHelper &oh) const {
        xx::AppendEx(oh, ",\"name\":", this->name);
    }
    File::File(File&& o) noexcept {
        this->operator=(std::move(o));
    }
    File& File::operator=(File&& o) noexcept {
        std::swap(this->path, o.path);
        std::swap(this->ext, o.ext);
        std::swap(this->length, o.length);
        std::swap(this->md5, o.md5);
        return *this;
    }
    void File::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        auto&& o = xx::As<FishManage::File>(tar);
        xx::CloneFuncs<std::string>::Clone1(oh, this->path, o->path);
        xx::CloneFuncs<FishManage::FileExtensions>::Clone1(oh, this->ext, o->ext);
        xx::CloneFuncs<int64_t>::Clone1(oh, this->length, o->length);
        xx::CloneFuncs<xx::Data>::Clone1(oh, this->md5, o->md5);
    }
    void File::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        auto&& o = xx::As<FishManage::File>(tar);
        xx::CloneFuncs<std::string>::Clone2(oh, this->path, o->path);
        xx::CloneFuncs<FishManage::FileExtensions>::Clone2(oh, this->ext, o->ext);
        xx::CloneFuncs<int64_t>::Clone2(oh, this->length, o->length);
        xx::CloneFuncs<xx::Data>::Clone2(oh, this->md5, o->md5);
    }
    uint16_t File::GetTypeId() const {
        return xx::TypeId_v<FishManage::File>;
    }
    void File::Serialize(xx::DataWriterEx& dw) const {
        dw.Write(this->path);
        dw.Write(this->ext);
        dw.Write(this->length);
        dw.Write(this->md5);
    }
    int File::Deserialize(xx::DataReaderEx& dr) {
        if (int r = dr.Read(this->path)) return r;
        if (int r = dr.Read(this->ext)) return r;
        if (int r = dr.Read(this->length)) return r;
        if (int r = dr.Read(this->md5)) return r;
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
        xx::AppendEx(oh, ",\"path\":", this->path);
        xx::AppendEx(oh, ",\"ext\":", this->ext);
        xx::AppendEx(oh, ",\"length\":", this->length);
        xx::AppendEx(oh, ",\"md5\":", this->md5);
    }
    ResAnimation::ResAnimation(ResAnimation&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResAnimation& ResAnimation::operator=(ResAnimation&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->shadowScale, o.shadowScale);
        std::swap(this->shadowOffsetX, o.shadowOffsetX);
        std::swap(this->shadowOffsetY, o.shadowOffsetY);
        return *this;
    }
    void ResAnimation::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::ResAnimation>(tar);
        xx::CloneFuncs<float>::Clone1(oh, this->shadowScale, o->shadowScale);
        xx::CloneFuncs<float>::Clone1(oh, this->shadowOffsetX, o->shadowOffsetX);
        xx::CloneFuncs<float>::Clone1(oh, this->shadowOffsetY, o->shadowOffsetY);
    }
    void ResAnimation::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::ResAnimation>(tar);
        xx::CloneFuncs<float>::Clone2(oh, this->shadowScale, o->shadowScale);
        xx::CloneFuncs<float>::Clone2(oh, this->shadowOffsetX, o->shadowOffsetX);
        xx::CloneFuncs<float>::Clone2(oh, this->shadowOffsetY, o->shadowOffsetY);
    }
    uint16_t ResAnimation::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResAnimation>;
    }
    void ResAnimation::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->shadowScale);
        dw.Write(this->shadowOffsetX);
        dw.Write(this->shadowOffsetY);
    }
    int ResAnimation::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->shadowScale)) return r;
        if (int r = dr.Read(this->shadowOffsetX)) return r;
        if (int r = dr.Read(this->shadowOffsetY)) return r;
        return 0;
    }
    void ResAnimation::ToString(xx::ObjectHelper &oh) const {
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
    void ResAnimation::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"shadowScale\":", this->shadowScale);
        xx::AppendEx(oh, ",\"shadowOffsetX\":", this->shadowOffsetX);
        xx::AppendEx(oh, ",\"shadowOffsetY\":", this->shadowOffsetY);
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
    ResSound::ResSound(ResSound&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResSound& ResSound::operator=(ResSound&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->file, o.file);
        std::swap(this->seconds, o.seconds);
        return *this;
    }
    void ResSound::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::ResSound>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone1(oh, this->file, o->file);
        xx::CloneFuncs<float>::Clone1(oh, this->seconds, o->seconds);
    }
    void ResSound::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::ResSound>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone2(oh, this->file, o->file);
        xx::CloneFuncs<float>::Clone2(oh, this->seconds, o->seconds);
    }
    uint16_t ResSound::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResSound>;
    }
    void ResSound::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->file);
        dw.Write(this->seconds);
    }
    int ResSound::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->file)) return r;
        if (int r = dr.Read(this->seconds)) return r;
        return 0;
    }
    void ResSound::ToString(xx::ObjectHelper &oh) const {
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
    void ResSound::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"file\":", this->file);
        xx::AppendEx(oh, ",\"seconds\":", this->seconds);
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
    ResScript::ResScript(ResScript&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResScript& ResScript::operator=(ResScript&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->file, o.file);
        return *this;
    }
    void ResScript::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::ResScript>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone1(oh, this->file, o->file);
    }
    void ResScript::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::ResScript>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone2(oh, this->file, o->file);
    }
    uint16_t ResScript::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResScript>;
    }
    void ResScript::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->file);
    }
    int ResScript::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->file)) return r;
        return 0;
    }
    void ResScript::ToString(xx::ObjectHelper &oh) const {
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
    void ResScript::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"file\":", this->file);
    }
    ResVoice::ResVoice(ResVoice&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResVoice& ResVoice::operator=(ResVoice&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        return *this;
    }
    void ResVoice::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::ResVoice>(tar);
    }
    void ResVoice::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::ResVoice>(tar);
    }
    uint16_t ResVoice::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResVoice>;
    }
    void ResVoice::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
    }
    int ResVoice::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        return 0;
    }
    void ResVoice::ToString(xx::ObjectHelper &oh) const {
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
    void ResVoice::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
    }
    ResPicture::ResPicture(ResPicture&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResPicture& ResPicture::operator=(ResPicture&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->cdclps, o.cdclps);
        return *this;
    }
    void ResPicture::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::ResPicture>(tar);
        xx::CloneFuncs<FishManage::CDCirclesLockPoints>::Clone1(oh, this->cdclps, o->cdclps);
    }
    void ResPicture::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::ResPicture>(tar);
        xx::CloneFuncs<FishManage::CDCirclesLockPoints>::Clone2(oh, this->cdclps, o->cdclps);
    }
    uint16_t ResPicture::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResPicture>;
    }
    void ResPicture::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->cdclps);
    }
    int ResPicture::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->cdclps)) return r;
        return 0;
    }
    void ResPicture::ToString(xx::ObjectHelper &oh) const {
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
    void ResPicture::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"cdclps\":", this->cdclps);
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
        xx::CloneFuncs<std::weak_ptr<FishManage::ResVoice>>::Clone1(oh, this->resVoiceForDead, o->resVoiceForDead);
        xx::CloneFuncs<std::weak_ptr<FishManage::ResAnimation>>::Clone1(oh, this->resAnimation, o->resAnimation);
        xx::CloneFuncs<std::vector<FishManage::FishState>>::Clone1(oh, this->fishStates, o->fishStates);
        xx::CloneFuncs<std::weak_ptr<FishManage::ResScript>>::Clone1(oh, this->resScript, o->resScript);
        xx::CloneFuncs<int64_t>::Clone1(oh, this->coin1, o->coin1);
        xx::CloneFuncs<int64_t>::Clone1(oh, this->coin2, o->coin2);
        xx::CloneFuncs<int64_t>::Clone1(oh, this->lastUpdateTime, o->lastUpdateTime);
    }
    void FishBase::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        auto&& o = xx::As<FishManage::FishBase>(tar);
        xx::CloneFuncs<std::string>::Clone2(oh, this->name, o->name);
        xx::CloneFuncs<std::weak_ptr<FishManage::ResVoice>>::Clone2(oh, this->resVoiceForDead, o->resVoiceForDead);
        xx::CloneFuncs<std::weak_ptr<FishManage::ResAnimation>>::Clone2(oh, this->resAnimation, o->resAnimation);
        xx::CloneFuncs<std::vector<FishManage::FishState>>::Clone2(oh, this->fishStates, o->fishStates);
        xx::CloneFuncs<std::weak_ptr<FishManage::ResScript>>::Clone2(oh, this->resScript, o->resScript);
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
    ActionBase::ActionBase(ActionBase&& o) noexcept {
        this->operator=(std::move(o));
    }
    ActionBase& ActionBase::operator=(ActionBase&& o) noexcept {
        std::swap(this->name, o.name);
        std::swap(this->seconds, o.seconds);
        std::swap(this->frameRate, o.frameRate);
        std::swap(this->width, o.width);
        std::swap(this->height, o.height);
        return *this;
    }
    ResTexture::ResTexture(ResTexture&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResTexture& ResTexture::operator=(ResTexture&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->file, o.file);
        return *this;
    }
    void ResTexture::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::ResTexture>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone1(oh, this->file, o->file);
    }
    void ResTexture::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::ResTexture>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone2(oh, this->file, o->file);
    }
    uint16_t ResTexture::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResTexture>;
    }
    void ResTexture::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->file);
    }
    int ResTexture::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->file)) return r;
        return 0;
    }
    void ResTexture::ToString(xx::ObjectHelper &oh) const {
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
    void ResTexture::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"file\":", this->file);
    }
    ActionOthers::ActionOthers(ActionOthers&& o) noexcept {
        this->operator=(std::move(o));
    }
    ActionOthers& ActionOthers::operator=(ActionOthers&& o) noexcept {
        this->FishManage::ActionBase::operator=(std::move(o));
        std::swap(this->cdclpss, o.cdclpss);
        return *this;
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
    ResFrame::ResFrame(ResFrame&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResFrame& ResFrame::operator=(ResFrame&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->owner, o.owner);
        return *this;
    }
    void ResFrame::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::ResFrame>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::ResPList>>::Clone1(oh, this->owner, o->owner);
    }
    void ResFrame::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::ResFrame>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::ResPList>>::Clone2(oh, this->owner, o->owner);
    }
    uint16_t ResFrame::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResFrame>;
    }
    void ResFrame::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->owner);
    }
    int ResFrame::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->owner)) return r;
        return 0;
    }
    void ResFrame::ToString(xx::ObjectHelper &oh) const {
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
    void ResFrame::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"owner\":", this->owner);
    }
    ResPList::ResPList(ResPList&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResPList& ResPList::operator=(ResPList&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->file, o.file);
        std::swap(this->texture, o.texture);
        std::swap(this->frames, o.frames);
        return *this;
    }
    void ResPList::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::ResPList>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone1(oh, this->file, o->file);
        xx::CloneFuncs<std::weak_ptr<FishManage::ResTexture>>::Clone1(oh, this->texture, o->texture);
        xx::CloneFuncs<std::vector<std::shared_ptr<FishManage::ResFrame>>>::Clone1(oh, this->frames, o->frames);
    }
    void ResPList::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::ResPList>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone2(oh, this->file, o->file);
        xx::CloneFuncs<std::weak_ptr<FishManage::ResTexture>>::Clone2(oh, this->texture, o->texture);
        xx::CloneFuncs<std::vector<std::shared_ptr<FishManage::ResFrame>>>::Clone2(oh, this->frames, o->frames);
    }
    uint16_t ResPList::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResPList>;
    }
    void ResPList::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->file);
        dw.Write(this->texture);
        dw.Write(this->frames);
    }
    int ResPList::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->file)) return r;
        if (int r = dr.Read(this->texture)) return r;
        if (int r = dr.Read(this->frames)) return r;
        return 0;
    }
    void ResPList::ToString(xx::ObjectHelper &oh) const {
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
    void ResPList::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"file\":", this->file);
        xx::AppendEx(oh, ",\"texture\":", this->texture);
        xx::AppendEx(oh, ",\"frames\":", this->frames);
    }
    ActionSpriteFrame::ActionSpriteFrame(ActionSpriteFrame&& o) noexcept {
        this->operator=(std::move(o));
    }
    ActionSpriteFrame& ActionSpriteFrame::operator=(ActionSpriteFrame&& o) noexcept {
        this->FishManage::ActionBase::operator=(std::move(o));
        std::swap(this->frames, o.frames);
        return *this;
    }
    Res3d::Res3d(Res3d&& o) noexcept {
        this->operator=(std::move(o));
    }
    Res3d& Res3d::operator=(Res3d&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->file, o.file);
        std::swap(this->textures, o.textures);
        std::swap(this->actions, o.actions);
        return *this;
    }
    void Res3d::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::Res3d>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone1(oh, this->file, o->file);
        xx::CloneFuncs<std::vector<std::weak_ptr<FishManage::ResTexture>>>::Clone1(oh, this->textures, o->textures);
        xx::CloneFuncs<std::vector<FishManage::ActionOthers>>::Clone1(oh, this->actions, o->actions);
    }
    void Res3d::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::Res3d>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone2(oh, this->file, o->file);
        xx::CloneFuncs<std::vector<std::weak_ptr<FishManage::ResTexture>>>::Clone2(oh, this->textures, o->textures);
        xx::CloneFuncs<std::vector<FishManage::ActionOthers>>::Clone2(oh, this->actions, o->actions);
    }
    uint16_t Res3d::GetTypeId() const {
        return xx::TypeId_v<FishManage::Res3d>;
    }
    void Res3d::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->file);
        dw.Write(this->textures);
        dw.Write(this->actions);
    }
    int Res3d::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->file)) return r;
        if (int r = dr.Read(this->textures)) return r;
        if (int r = dr.Read(this->actions)) return r;
        return 0;
    }
    void Res3d::ToString(xx::ObjectHelper &oh) const {
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
    void Res3d::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"file\":", this->file);
        xx::AppendEx(oh, ",\"textures\":", this->textures);
        xx::AppendEx(oh, ",\"actions\":", this->actions);
    }
    ResCombine::ResCombine(ResCombine&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResCombine& ResCombine::operator=(ResCombine&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->items, o.items);
        return *this;
    }
    void ResCombine::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::ResCombine>(tar);
        xx::CloneFuncs<std::vector<FishManage::CombineItem>>::Clone1(oh, this->items, o->items);
    }
    void ResCombine::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::ResCombine>(tar);
        xx::CloneFuncs<std::vector<FishManage::CombineItem>>::Clone2(oh, this->items, o->items);
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
    void ResCombine::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"items\":", this->items);
    }
    ResFrameAnimation::ResFrameAnimation(ResFrameAnimation&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResFrameAnimation& ResFrameAnimation::operator=(ResFrameAnimation&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->actions, o.actions);
        return *this;
    }
    void ResFrameAnimation::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::ResFrameAnimation>(tar);
        xx::CloneFuncs<std::vector<FishManage::ActionSpriteFrame>>::Clone1(oh, this->actions, o->actions);
    }
    void ResFrameAnimation::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::ResFrameAnimation>(tar);
        xx::CloneFuncs<std::vector<FishManage::ActionSpriteFrame>>::Clone2(oh, this->actions, o->actions);
    }
    uint16_t ResFrameAnimation::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResFrameAnimation>;
    }
    void ResFrameAnimation::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->actions);
    }
    int ResFrameAnimation::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->actions)) return r;
        return 0;
    }
    void ResFrameAnimation::ToString(xx::ObjectHelper &oh) const {
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
    void ResFrameAnimation::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"actions\":", this->actions);
    }
    ResSpine::ResSpine(ResSpine&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResSpine& ResSpine::operator=(ResSpine&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        std::swap(this->atlasFile, o.atlasFile);
        std::swap(this->textures, o.textures);
        std::swap(this->jsonFile, o.jsonFile);
        std::swap(this->actions, o.actions);
        return *this;
    }
    void ResSpine::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::ResSpine>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone1(oh, this->atlasFile, o->atlasFile);
        xx::CloneFuncs<std::vector<std::weak_ptr<FishManage::ResTexture>>>::Clone1(oh, this->textures, o->textures);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone1(oh, this->jsonFile, o->jsonFile);
        xx::CloneFuncs<std::vector<FishManage::ActionOthers>>::Clone1(oh, this->actions, o->actions);
    }
    void ResSpine::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::ResSpine>(tar);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone2(oh, this->atlasFile, o->atlasFile);
        xx::CloneFuncs<std::vector<std::weak_ptr<FishManage::ResTexture>>>::Clone2(oh, this->textures, o->textures);
        xx::CloneFuncs<std::weak_ptr<FishManage::File>>::Clone2(oh, this->jsonFile, o->jsonFile);
        xx::CloneFuncs<std::vector<FishManage::ActionOthers>>::Clone2(oh, this->actions, o->actions);
    }
    uint16_t ResSpine::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResSpine>;
    }
    void ResSpine::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
        dw.Write(this->atlasFile);
        dw.Write(this->textures);
        dw.Write(this->jsonFile);
        dw.Write(this->actions);
    }
    int ResSpine::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        if (int r = dr.Read(this->atlasFile)) return r;
        if (int r = dr.Read(this->textures)) return r;
        if (int r = dr.Read(this->jsonFile)) return r;
        if (int r = dr.Read(this->actions)) return r;
        return 0;
    }
    void ResSpine::ToString(xx::ObjectHelper &oh) const {
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
    void ResSpine::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
        xx::AppendEx(oh, ",\"atlasFile\":", this->atlasFile);
        xx::AppendEx(oh, ",\"textures\":", this->textures);
        xx::AppendEx(oh, ",\"jsonFile\":", this->jsonFile);
        xx::AppendEx(oh, ",\"actions\":", this->actions);
    }
    ResMusic::ResMusic(ResMusic&& o) noexcept {
        this->operator=(std::move(o));
    }
    ResMusic& ResMusic::operator=(ResMusic&& o) noexcept {
        this->BaseType::operator=(std::move(o));
        return *this;
    }
    void ResMusic::Clone1(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone1(oh, tar);
        auto&& o = xx::As<FishManage::ResMusic>(tar);
    }
    void ResMusic::Clone2(xx::ObjectHelper &oh, std::shared_ptr<Object> const &tar) const {
        this->BaseType::Clone2(oh, tar);
        auto&& o = xx::As<FishManage::ResMusic>(tar);
    }
    uint16_t ResMusic::GetTypeId() const {
        return xx::TypeId_v<FishManage::ResMusic>;
    }
    void ResMusic::Serialize(xx::DataWriterEx& dw) const {
        this->BaseType::Serialize(dw);
    }
    int ResMusic::Deserialize(xx::DataReaderEx& dr) {
        if (int r = this->BaseType::Deserialize(dr)) return r;
        return 0;
    }
    void ResMusic::ToString(xx::ObjectHelper &oh) const {
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
    void ResMusic::ToStringCore(xx::ObjectHelper &oh) const {
        this->BaseType::ToStringCore(oh);
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
        std::swap(this->resMusics, o.resMusics);
        std::swap(this->resVoices, o.resVoices);
        std::swap(this->resTextures, o.resTextures);
        std::swap(this->resPLists, o.resPLists);
        std::swap(this->resFrames, o.resFrames);
        std::swap(this->resSpines, o.resSpines);
        std::swap(this->res3ds, o.res3ds);
        std::swap(this->resFrameAnimations, o.resFrameAnimations);
        std::swap(this->resCombine, o.resCombine);
        std::swap(this->resScripts, o.resScripts);
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
