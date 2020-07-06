#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FishManage_class_lite.h"

struct HelloWorld : public cocos2d::Scene, public cocos2d::ui::EditBoxDelegate {
    // 缓存 AppDelegate::designWidth/Height
    float W = 0, H = 0;

    // 公共布局参数
    const float margin = 10;
    const float fontSize = 32;

    const cocos2d::Color3B yellow = cocos2d::Color3B(255, 207, 64);
    const cocos2d::Color3B blue = cocos2d::Color3B(126, 194, 255);

    // 临时容器
    std::unordered_map<cocos2d::ui::CheckBox*, std::string> cbNames;
    std::vector<std::string> names;
    std::vector<std::string> frameNames;
    std::vector<cocos2d::ui::EditBox*> editBoxs;
    std::unordered_map<std::string, cocos2d::ui::EditBox*> editBoxMap;


    enum class FishTypes {
        Unknown, _2D, Spine, _3D, Combine
    };

    // 当前正在编辑的 fish 的 类型
    FishTypes currentFishType = FishTypes::Unknown;

    // 当前正在编辑的 fish 的 数组下标( 根据类型在 data 中定位数组 ). 如果为 -1 则表示 new fish
    int currentFishIndex = -1;

    // 所有数据在此
    FishManage::Data data;

    // 创建新鱼的临时数据在此
    FishManage::Fish_2D fish2d;
    FishManage::Fish_Spine fishSpine;
    FishManage::Fish_3D fish3d;
    FishManage::Fish_Combine fishCombine;

    // 读档
    void LoadData();
    // 存档
    void SaveData();



    // 创建 文本( 锚点 左中 )
    cocos2d::Label* CreateLabel(cocos2d::Vec2 const& pos, std::string const& txt, int const& fontSize, cocos2d::Node* const& container = nullptr);

    // 创建 文本 按钮( 锚点 左中 )
    cocos2d::ui::Button* CreateTextButton(cocos2d::Vec2 const& pos, std::string const& txt, int const& fontSize, cocos2d::ccMenuCallback&& callback, cocos2d::Node* const& container = nullptr);

    // 创建 文本 按钮( 锚点 左中 )
    cocos2d::ui::EditBox* CreateEditBox(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& text, std::string const& holderText, int const& fontSize, cocos2d::Node* const& container = nullptr);

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





    template<typename FishType>
    void CreateSVItem(cocos2d::ui::ScrollView* const& sv, float const& itemHeight, cocos2d::Vec2 const& pos, FishType const& fish);

    // 绘制 欢迎页
    void DrawWelcome();

    // 绘制 sprite frame 鱼 初始页
    void DrawFishMenu_SpriteFrame();

    // 提交 sprite frame 鱼 初始页 相关数据
    void SaveFishMenu_SpriteFrame();

    // 绘制 选 plist 文件页
    void DrawPListChoose();

    // 绘制 选 sprite frame 页
    void DrawSpriteFrameChoose();

    // 绘制 sprite frame 参数配置 页
    void DrawSpriteFrameConfig();

    // 提交 sprite frame  参数配置
    void SaveSpriteFrameConfig();






    void editBoxReturn(cocos2d::ui::EditBox* editBox) override;

    // 绘制 欢迎页
    virtual bool init() override;

    CREATE_FUNC(HelloWorld);
};
