#pragma once
#include "xx_datareader.h"
#include "FishManage_class_lite.h.inc"  // user create it for extend include files
namespace FishManage {
	struct PkgGenMd5 {
		inline static const std::string value = "#*MD5<824668f314c774d23b6b7b0c5864a67f>*#";
    };

    struct FishBase {
        std::string fishName;
        // 基数
        int64_t coin1 = 0;
        // == 0: 以coin1作为固定值.     < 0: 取屏幕相同鱼倍率?    > 0: 范围上限
        int64_t coin2 = 0;

        FishBase() = default;
        FishBase(FishBase const&) = default;
        FishBase& operator=(FishBase const&) = default;
        FishBase(FishBase&& o);
        FishBase& operator=(FishBase&& o);
    };
    struct ActionBase {
        std::string actionName;

        ActionBase() = default;
        ActionBase(ActionBase const&) = default;
        ActionBase& operator=(ActionBase const&) = default;
        ActionBase(ActionBase&& o);
        ActionBase& operator=(ActionBase&& o);
    };
    struct FrameBase {
        float moveDistance = 0;

        FrameBase() = default;
        FrameBase(FrameBase const&) = default;
        FrameBase& operator=(FrameBase const&) = default;
        FrameBase(FrameBase&& o);
        FrameBase& operator=(FrameBase&& o);
    };
    struct Fish_2D_Frame : FishManage::FrameBase {
        std::string spriteFrameName;
        std::string plistFileName;

        Fish_2D_Frame() = default;
        Fish_2D_Frame(Fish_2D_Frame const&) = default;
        Fish_2D_Frame& operator=(Fish_2D_Frame const&) = default;
        Fish_2D_Frame(Fish_2D_Frame&& o);
        Fish_2D_Frame& operator=(Fish_2D_Frame&& o);
    };
    struct Fish_2D_Action : FishManage::ActionBase {
        std::vector<FishManage::Fish_2D_Frame> frames;

        Fish_2D_Action() = default;
        Fish_2D_Action(Fish_2D_Action const&) = default;
        Fish_2D_Action& operator=(Fish_2D_Action const&) = default;
        Fish_2D_Action(Fish_2D_Action&& o);
        Fish_2D_Action& operator=(Fish_2D_Action&& o);
    };
    struct Fish_2D : FishManage::FishBase {
        std::vector<FishManage::Fish_2D_Action> actions;

        Fish_2D() = default;
        Fish_2D(Fish_2D const&) = default;
        Fish_2D& operator=(Fish_2D const&) = default;
        Fish_2D(Fish_2D&& o);
        Fish_2D& operator=(Fish_2D&& o);
    };
    struct Fish_Spine_Frame : FishManage::FrameBase {

        Fish_Spine_Frame() = default;
        Fish_Spine_Frame(Fish_Spine_Frame const&) = default;
        Fish_Spine_Frame& operator=(Fish_Spine_Frame const&) = default;
        Fish_Spine_Frame(Fish_Spine_Frame&& o);
        Fish_Spine_Frame& operator=(Fish_Spine_Frame&& o);
    };
    struct Fish_Spine_Action : FishManage::ActionBase {
        std::vector<FishManage::Fish_Spine_Frame> frames;

        Fish_Spine_Action() = default;
        Fish_Spine_Action(Fish_Spine_Action const&) = default;
        Fish_Spine_Action& operator=(Fish_Spine_Action const&) = default;
        Fish_Spine_Action(Fish_Spine_Action&& o);
        Fish_Spine_Action& operator=(Fish_Spine_Action&& o);
    };
    struct Fish_Spine : FishManage::FishBase {
        std::string atlasFileName;
        std::vector<FishManage::Fish_Spine_Action> actions;

        Fish_Spine() = default;
        Fish_Spine(Fish_Spine const&) = default;
        Fish_Spine& operator=(Fish_Spine const&) = default;
        Fish_Spine(Fish_Spine&& o);
        Fish_Spine& operator=(Fish_Spine&& o);
    };
    struct Fish_3D_Frame : FishManage::FrameBase {

        Fish_3D_Frame() = default;
        Fish_3D_Frame(Fish_3D_Frame const&) = default;
        Fish_3D_Frame& operator=(Fish_3D_Frame const&) = default;
        Fish_3D_Frame(Fish_3D_Frame&& o);
        Fish_3D_Frame& operator=(Fish_3D_Frame&& o);
    };
    struct Fish_3D_Action : FishManage::ActionBase {
        std::vector<FishManage::Fish_3D_Frame> frames;

        Fish_3D_Action() = default;
        Fish_3D_Action(Fish_3D_Action const&) = default;
        Fish_3D_Action& operator=(Fish_3D_Action const&) = default;
        Fish_3D_Action(Fish_3D_Action&& o);
        Fish_3D_Action& operator=(Fish_3D_Action&& o);
    };
    struct Fish_3D : FishManage::FishBase {
        std::string c3bFileName;
        float baseScale = 0;
        float baseAngleX = 0;
        float baseAngleY = 0;
        float baseAngleZ = 0;
        std::vector<FishManage::Fish_3D_Action> actions;

        Fish_3D() = default;
        Fish_3D(Fish_3D const&) = default;
        Fish_3D& operator=(Fish_3D const&) = default;
        Fish_3D(Fish_3D&& o);
        Fish_3D& operator=(Fish_3D&& o);
    };
    struct Fish_Combine_Child {
        // 1: 2d    2: spine   3: 3d
        int32_t fishTypeId = 0;
        // 数组下标. 根据 typeId 对应到 Data 下的相应数组
        int32_t index = 0;
        float offsetX = 0;
        float offsetY = 0;
        float baseAngle = 0;
        float baseScale = 0;

        Fish_Combine_Child() = default;
        Fish_Combine_Child(Fish_Combine_Child const&) = default;
        Fish_Combine_Child& operator=(Fish_Combine_Child const&) = default;
        Fish_Combine_Child(Fish_Combine_Child&& o);
        Fish_Combine_Child& operator=(Fish_Combine_Child&& o);
    };
    struct Fish_Combine_Action : FishManage::ActionBase {

        Fish_Combine_Action() = default;
        Fish_Combine_Action(Fish_Combine_Action const&) = default;
        Fish_Combine_Action& operator=(Fish_Combine_Action const&) = default;
        Fish_Combine_Action(Fish_Combine_Action&& o);
        Fish_Combine_Action& operator=(Fish_Combine_Action&& o);
    };
    struct Fish_Combine : FishManage::FishBase {
        std::vector<FishManage::Fish_Combine_Child> childs;
        std::vector<FishManage::Fish_Combine_Action> actions;

        Fish_Combine() = default;
        Fish_Combine(Fish_Combine const&) = default;
        Fish_Combine& operator=(Fish_Combine const&) = default;
        Fish_Combine(Fish_Combine&& o);
        Fish_Combine& operator=(Fish_Combine&& o);
    };
    struct Data {
        std::vector<FishManage::Fish_2D> fish_2ds;
        std::vector<FishManage::Fish_Spine> fish_spines;
        std::vector<FishManage::Fish_3D> fish_3ds;
        std::vector<FishManage::Fish_Combine> fish_combines;

        Data() = default;
        Data(Data const&) = default;
        Data& operator=(Data const&) = default;
        Data(Data&& o);
        Data& operator=(Data&& o);
    };
}
namespace xx {
	template<>
	struct DataFuncs<FishManage::FishBase, void> {
		static void Write(Data& d, FishManage::FishBase const& in) noexcept;
		static int Read(DataReader& d, FishManage::FishBase& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::ActionBase, void> {
		static void Write(Data& d, FishManage::ActionBase const& in) noexcept;
		static int Read(DataReader& d, FishManage::ActionBase& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::FrameBase, void> {
		static void Write(Data& d, FishManage::FrameBase const& in) noexcept;
		static int Read(DataReader& d, FishManage::FrameBase& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Fish_2D_Frame, void> {
		static void Write(Data& d, FishManage::Fish_2D_Frame const& in) noexcept;
		static int Read(DataReader& d, FishManage::Fish_2D_Frame& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Fish_2D_Action, void> {
		static void Write(Data& d, FishManage::Fish_2D_Action const& in) noexcept;
		static int Read(DataReader& d, FishManage::Fish_2D_Action& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Fish_2D, void> {
		static void Write(Data& d, FishManage::Fish_2D const& in) noexcept;
		static int Read(DataReader& d, FishManage::Fish_2D& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Fish_Spine_Frame, void> {
		static void Write(Data& d, FishManage::Fish_Spine_Frame const& in) noexcept;
		static int Read(DataReader& d, FishManage::Fish_Spine_Frame& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Fish_Spine_Action, void> {
		static void Write(Data& d, FishManage::Fish_Spine_Action const& in) noexcept;
		static int Read(DataReader& d, FishManage::Fish_Spine_Action& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Fish_Spine, void> {
		static void Write(Data& d, FishManage::Fish_Spine const& in) noexcept;
		static int Read(DataReader& d, FishManage::Fish_Spine& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Fish_3D_Frame, void> {
		static void Write(Data& d, FishManage::Fish_3D_Frame const& in) noexcept;
		static int Read(DataReader& d, FishManage::Fish_3D_Frame& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Fish_3D_Action, void> {
		static void Write(Data& d, FishManage::Fish_3D_Action const& in) noexcept;
		static int Read(DataReader& d, FishManage::Fish_3D_Action& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Fish_3D, void> {
		static void Write(Data& d, FishManage::Fish_3D const& in) noexcept;
		static int Read(DataReader& d, FishManage::Fish_3D& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Fish_Combine_Child, void> {
		static void Write(Data& d, FishManage::Fish_Combine_Child const& in) noexcept;
		static int Read(DataReader& d, FishManage::Fish_Combine_Child& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Fish_Combine_Action, void> {
		static void Write(Data& d, FishManage::Fish_Combine_Action const& in) noexcept;
		static int Read(DataReader& d, FishManage::Fish_Combine_Action& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Fish_Combine, void> {
		static void Write(Data& d, FishManage::Fish_Combine const& in) noexcept;
		static int Read(DataReader& d, FishManage::Fish_Combine& out) noexcept;
	};
	template<>
	struct DataFuncs<FishManage::Data, void> {
		static void Write(Data& d, FishManage::Data const& in) noexcept;
		static int Read(DataReader& d, FishManage::Data& out) noexcept;
	};
}