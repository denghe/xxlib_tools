#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

struct HelloWorld : public cocos2d::Scene, public cocos2d::ui::EditBoxDelegate {
    // 缓存 AppDelegate::designWidth/Height
    float W = 0, H = 0;

    // 公共布局参数
    const float defaultMargin = 10;
    const float defaultFontSize = 24;

    // 临时容器
    std::unordered_map<cocos2d::ui::CheckBox*, std::string> cbNames;
    std::vector<std::string> names;
    std::vector<std::string> frameNames;
    std::vector<cocos2d::ui::EditBox*> editBoxs;
    std::unordered_map<std::string, cocos2d::ui::EditBox*> editBoxMap;


    // 创建 文本( 锚点 左上 )
    cocos2d::Label* CreateLabel(cocos2d::Vec2 const& pos, std::string const& txt, int const& fontSize, cocos2d::Node* const& container = nullptr);

    // 创建 文本 按钮( 锚点 左上 )
    cocos2d::ui::Button* CreateTextButton(cocos2d::Vec2 const& pos, std::string const& txt, int const& fontSize, cocos2d::ccMenuCallback&& callback, cocos2d::Node* const& container = nullptr);

    // 创建 文本 按钮( 锚点 左上 )
    cocos2d::ui::EditBox* CreateEditBox(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& text, std::string const& holderText, int const& fontSize, cocos2d::Node* const& container = nullptr);

    // 创建 某 3d 模型( 锚点 中心 )
    cocos2d::Sprite3D* CreateOrc(cocos2d::Vec2 const& pos, float const& r, cocos2d::Node* const& container = nullptr);

    // 创建 滑动裁剪区( 锚点 左上 )
    cocos2d::ui::ScrollView* CreateSV(cocos2d::Vec2 const& pos, cocos2d::Size const& cutSize, cocos2d::Size const& itemsSize, cocos2d::Node* const& container = nullptr);

    // 创建 全屏背景( 锚点 左下 )
    cocos2d::LayerColor* CreateBG(cocos2d::Node* const& container = nullptr);

    // 创建 2d 图片( 锚点 中 ). 显示为指定 siz 大小
    cocos2d::Sprite* CreateSprite(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& fileName, cocos2d::Node* const& container = nullptr);

    // 创建 2d 帧图( 锚点 中 ). 显示为指定 siz 大小
    cocos2d::Sprite* CreateSpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& spriteFrameName, cocos2d::Node* const& container = nullptr);

    // 创建 checkbox ( 锚点 左下 改不了 )
    cocos2d::ui::CheckBox* CreateCheckBox(cocos2d::Vec2 const& pos, bool const& value, cocos2d::ui::CheckBox::ccCheckBoxCallback&& callback, cocos2d::Node* const& container = nullptr);



    // 辅助排版 横向居左( 锚点 左上 ). 会将自己的 width 加到 offset.x
    template<typename T>
    T* HorizontalLeft(cocos2d::Vec2& offset, float& maxHeight, T* o);

    // 辅助排版 横向居右( 锚点 右下 ). 会从 offset.x 减去自己的 width
    template<typename T>
    T* HorizontalRight(cocos2d::Vec2& offset, float& maxHeight, T* o);

    // 辅助排版 纵向从上往下( 锚点 左上 ). 会将自己的 height 加到 offset.y
    template<typename T>
    T* VerticalTop(cocos2d::Vec2& offset, T* o);



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
