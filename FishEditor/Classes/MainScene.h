#pragma once
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include "spine/spine-cocos2dx.h"
#include "ui/CocosGUI.h"
#include "AppDelegate.h"

#include "FileExts_class_lite.h"
#include "xx_file.h"
#include "xx_math.h"
#include "xx_chrono.h"
#include "xx_lua.h"

#include "ajson.hpp"

//#include "Circle.h"
//#include "DraggingRes.h"


// 加载 json 文件到 o
template<typename T>
static int LoadJson(T& o, std::string const& fn) {
	char const* buf = nullptr;
	size_t len = 0;
#ifdef COCOS2D_VERSION
	auto d = cocos2d::FileUtils::getInstance()->getDataFromFile(fn);
	// 错误检查
	if (d.getSize() == 0) return -1;
	buf = (char*)d.getBytes();
	len = d.getSize();
#else
	xx::Data d;
	// 错误检查
	if (xx::ReadAllBytes(fn, d) || !d.len) return -1;
	buf = d.buf;
	len = d.len;
#endif
	ajson::load_from_buff(o, buf, len); // try catch?
	return 0;
}




struct MainScene : public cocos2d::Scene, public cocos2d::ui::EditBoxDelegate {
	using BaseType = cocos2d::Scene;

	// lua 上下文( engine 内部使用 )
	xx::Lua::State L;

	// 缓存 AppDelegate::designWidth/Height
	float W = 0, H = 0, W_2 = 0, H_2 = 0;

	// 设计尺寸相关
	float DW = 1280, DH = 720, DW_2 = DW / 2, DH_2 = DH / 2;

	// 公共布局参数
	const float fontSize = 24;
	const float margin = fontSize / 3.0f;
	const float lineHeight = fontSize * 1.4f;

	const cocos2d::Color3B yellow = cocos2d::Color3B(255, 207, 64);
	const cocos2d::Color3B blue = cocos2d::Color3B(126, 194, 255);


	// 临时控件引用容器
	std::unordered_map<cocos2d::ui::CheckBox*, std::string> cbNames;
	std::vector<cocos2d::ui::EditBox*> editBoxs;

	// 便于 刷新后恢复 scroll view 的显示位置
	float manageResourcesScrolledPercentVertical = 0;
	float manageFishsScrolledPercentVertical = 0;
	float configSpriteFrameScrolledPercentVertical = 0;
	float editRes2dScrolledPercentVertical = 0;


	//// touch 状态记录
	//cocos2d::Vec2 lastPos;
	//bool touching = false;
	//Circle* currCircle = nullptr;
	//DraggingRes* currDraggingRes = nullptr;

	// 热键函数绑定
	cocos2d::ccMenuCallback keyboardCallback_C;



	//// 所有数据在此
	//FishManage::Data data;
	// 对象帮助器
	xx::ObjectHelper oh;
	//// 存盘文件名
	//const std::string dataFileName = "fishs.data";

	// = cocos2d::FileUtils::getInstance()->getSearchPaths()[0]
	std::string resPath;

	//// 读档
	//void LoadData();
	//// 存档
	//void SaveData();

	// 在屏幕中间弹出一段提示，几秒钟后飞走消失
	void PopupMessage(std::string const& txt, cocos2d::Color3B const& color = cocos2d::Color3B::RED);

	// 创建 文本( 锚点 左中 )
	cocos2d::Label* CreateLabel(cocos2d::Vec2 const& pos, std::string const& txt, cocos2d::Node* const& container = nullptr);

	// 创建 键值对文本. 值颜色 yellow( 锚点 左中 )
	std::pair<cocos2d::Label*, cocos2d::Label*> CreateLabelPair(cocos2d::Vec2 const& pos, std::string const& key, std::string const& value, cocos2d::Node* const& container = nullptr);


	// 创建 文本 按钮( 锚点 左中 )
	cocos2d::ui::Button* CreateButton(cocos2d::Vec2 const& pos, std::string const& txt, cocos2d::ccMenuCallback&& callback, cocos2d::Node* const& container = nullptr);

	// 创建 文本 按钮( 锚点 左中 )
	cocos2d::ui::EditBox* CreateEditBox(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& text, std::string const& holderText, cocos2d::Node* const& container = nullptr);

	// 创建 checkbox ( 锚点 左中 )
	cocos2d::ui::CheckBox* CreateCheckBox(cocos2d::Vec2 const& pos, bool const& value, cocos2d::ui::CheckBox::ccCheckBoxCallback&& callback, cocos2d::Node* const& container = nullptr);



	// 创建 滑动裁剪区( 锚点 左上 )
	cocos2d::ui::ScrollView* CreateSV(cocos2d::Vec2 const& pos, cocos2d::Size const& cutSize, cocos2d::Size const& itemsSize, cocos2d::Node* const& container = nullptr);



	// 创建 全屏背景( 锚点 左下 )
	cocos2d::LayerColor* CreateBG(cocos2d::Node* const& container = nullptr);



	// 创建 2d 图片( 锚点 中心 ). 显示为指定 siz 大小
	cocos2d::Sprite* CreateSprite(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& fileName, cocos2d::Node* const& container = nullptr);

	// 创建 2d 帧图( 锚点 中心 ). 显示为指定 siz 大小
	cocos2d::Sprite* CreateSpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& spriteFrameName, cocos2d::Node* const& container = nullptr);

	// 创建 某 3d 模型( 锚点 中心 )
	cocos2d::Sprite3D* CreateOrc(cocos2d::Vec2 const& pos, float const& r, cocos2d::Node* const& container = nullptr);

	//// 创建一个 2d 帧图 动作 预览动画
	//ActionPlayer_SpriteFrame* CreateActionPlayer_SpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, FishManage::FrameAction const& action, cocos2d::Node* const& container = nullptr);

	// return tar->getContentSize().width
	float GetWidth(cocos2d::Node* const& tar);
	float GetWidth(std::pair<cocos2d::Label*, cocos2d::Label*> const& tar);

	//// 创建资源预览( 锚点 中心 ). 显示为指定 siz 大小( 对 spine, 3d 需要取出 bounding box 结合指定 siz 来算 scale )
	//cocos2d::Node* CreateResPreview(cocos2d::Vec2 const& pos, cocos2d::Size siz, std::shared_ptr<FishManage::Res> res, cocos2d::Node* const& container = nullptr);







	// out len == 16
	void CalcMD5(void* const& buf, size_t const& len, void* out);

	// 扫出 plist 里的 texture
	std::string GetPListTextureName(std::string const& plistFileName);

	// 扫出 plist 里的 sprite frame names
	std::vector<std::string> GetPListItems(std::string const& plistFileName);

	// 获取 spine 文件关联的的 .json/.skel 和包含的贴图文件名列表
	std::vector<std::string> GetAtlasResNames(std::string const& atlasFileName);

	// 获取 c3b 包含的贴图文件名列表 & 动作+时长 列表
	std::pair<std::vector<std::string>, std::vector<std::pair<std::string, float>>> GetC3bResNamesAnimations(std::string const& c3bFileName);

	// 获取 fnt 包含的贴图文件名列表
	std::vector<std::string> GetFntResNames(std::string const& fntFileName);

	// 获取 spine 的 animations name & 播放时长
	std::vector<std::pair<std::string, float>> GetSpineAnimationNamesSeconds(std::string const& spineFileName);





	//// 编辑组合鱼
	//void EditResCombine(std::shared_ptr<FishManage::ResCombine> const& resCombine, int const& pageIndex = 0);

	// 欢迎页
	void Welcome();

	//// 资源管理页
	//void ManageResources();

	//// 2d 帧资源编辑页
	//void EditRes2d(std::shared_ptr<FishManage::Res2d> const& res2d);

	//// 选 plist 文件页
	//void ChoosePList(std::shared_ptr<FishManage::Res2d> const& res2d);

	//// 选 sprite frame 页
	//void ChooseSpriteFrame(std::shared_ptr<FishManage::Res2d> const& res2d, std::shared_ptr<FishManage::Action2d> const& action2d);

	//// sprite frame 参数配置 页
	//void ConfigSpriteFrame(std::shared_ptr<FishManage::Res2d> const& res2d, std::shared_ptr<FishManage::Action2d> const& action2d);

	//// 编辑具体某帧的碰撞
	//void EditFrameCD(std::shared_ptr<FishManage::ResBase> const& res, std::shared_ptr<FishManage::ActionBase> const& action, int const& index);

	//// 编辑具体某帧的锁定点/线
	//void EditFrameLock(std::shared_ptr<FishManage::ResBase> const& res, std::shared_ptr<FishManage::ActionBase> const& action, int const& index);


	// todo: EditResSpine
	// todo: ChooseAtlas
	// todo: ConfigSpineFrame

	// todo: EditRes3d
	// todo: ChooseC3b
	// todo: Config3dFrame

	// todo: EditResCombine
	// todo: ChooseRes
	// todo: ConfigCombineRes

	// 鱼管理页
	void ManageFishs();

	//// 鱼编辑页
	//void EditFishNormal(std::shared_ptr<FishManage::FishNormal> const& fish);
	//void EditFishBomb(std::shared_ptr<FishManage::FishBomb> const& fish);
	//void EditFishDrill(std::shared_ptr<FishManage::FishDrill> const& fish);
	//void EditFishFury(std::shared_ptr<FishManage::FishFury> const& fish);
	//void EditFishCyclone(std::shared_ptr<FishManage::FishCyclone> const& fish);
	//void EditFishEater(std::shared_ptr<FishManage::FishEater> const& fish);

	// for edit box delegate
	void editBoxReturn(cocos2d::ui::EditBox* editBox) override;

	// 绘制 欢迎页
	virtual bool init() override;



	// 测试点东西
	void Init2();
	~MainScene() override;
	void update(float delta) override;
	int Update(int lineNumber);
	int lineNumber = 0;
	//// 已知扩展名映射
	//std::unordered_map<std::string, FishManage::FileExtensions> exts;
	//// 根据已知扩展名，先填充文件信息到此
	//std::map<std::string, std::shared_ptr<FishManage::File_Real>> files;
	std::vector<std::string> soundFileNames;
	size_t i = 0;
	int soundId = 0;
	float soundDuration = 0;
	//cocos2d::AmbientLight* _ambientLight = nullptr;
	//cocos2d::DirectionLight* _directionalLight = nullptr;
	//cocos2d::PointLight* _pointLight = nullptr;
	//cocos2d::SpotLight* _spotLight = nullptr;

	CREATE_FUNC(MainScene);
};
