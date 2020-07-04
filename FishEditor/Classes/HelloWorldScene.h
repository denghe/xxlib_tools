#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

struct HelloWorld : public cocos2d::Scene, public cocos2d::ui::EditBoxDelegate {
    // ���� AppDelegate::designWidth/Height
    float W = 0, H = 0;

    // �������ֲ���
    const float defaultMargin = 10;
    const float defaultFontSize = 24;

    // ��ʱ����
    std::unordered_map<cocos2d::ui::CheckBox*, std::string> cbNames;
    std::vector<std::string> names;
    std::vector<std::string> frameNames;
    std::vector<cocos2d::ui::EditBox*> editBoxs;
    std::unordered_map<std::string, cocos2d::ui::EditBox*> editBoxMap;


    // ���� �ı�( ê�� ���� )
    cocos2d::Label* CreateLabel(cocos2d::Vec2 const& pos, std::string const& txt, int const& fontSize, cocos2d::Node* const& container = nullptr);

    // ���� �ı� ��ť( ê�� ���� )
    cocos2d::ui::Button* CreateTextButton(cocos2d::Vec2 const& pos, std::string const& txt, int const& fontSize, cocos2d::ccMenuCallback&& callback, cocos2d::Node* const& container = nullptr);

    // ���� �ı� ��ť( ê�� ���� )
    cocos2d::ui::EditBox* CreateEditBox(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& text, std::string const& holderText, int const& fontSize, cocos2d::Node* const& container = nullptr);

    // ���� ĳ 3d ģ��( ê�� ���� )
    cocos2d::Sprite3D* CreateOrc(cocos2d::Vec2 const& pos, float const& r, cocos2d::Node* const& container = nullptr);

    // ���� �����ü���( ê�� ���� )
    cocos2d::ui::ScrollView* CreateSV(cocos2d::Vec2 const& pos, cocos2d::Size const& cutSize, cocos2d::Size const& itemsSize, cocos2d::Node* const& container = nullptr);

    // ���� ȫ������( ê�� ���� )
    cocos2d::LayerColor* CreateBG(cocos2d::Node* const& container = nullptr);

    // ���� 2d ͼƬ( ê�� �� ). ��ʾΪָ�� siz ��С
    cocos2d::Sprite* CreateSprite(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& fileName, cocos2d::Node* const& container = nullptr);

    // ���� 2d ֡ͼ( ê�� �� ). ��ʾΪָ�� siz ��С
    cocos2d::Sprite* CreateSpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& spriteFrameName, cocos2d::Node* const& container = nullptr);

    // ���� checkbox ( ê�� ���� �Ĳ��� )
    cocos2d::ui::CheckBox* CreateCheckBox(cocos2d::Vec2 const& pos, bool const& value, cocos2d::ui::CheckBox::ccCheckBoxCallback&& callback, cocos2d::Node* const& container = nullptr);



    // �����Ű� �������( ê�� ���� ). �Ὣ�Լ��� width �ӵ� offset.x
    template<typename T>
    T* HorizontalLeft(cocos2d::Vec2& offset, float& maxHeight, T* o);

    // �����Ű� �������( ê�� ���� ). ��� offset.x ��ȥ�Լ��� width
    template<typename T>
    T* HorizontalRight(cocos2d::Vec2& offset, float& maxHeight, T* o);

    // �����Ű� �����������( ê�� ���� ). �Ὣ�Լ��� height �ӵ� offset.y
    template<typename T>
    T* VerticalTop(cocos2d::Vec2& offset, T* o);



    // ���� ��ӭҳ
    void DrawWelcome();

    // ���� sprite frame �� ��ʼҳ
    void DrawFishMenu_SpriteFrame();

    // �ύ sprite frame �� ��ʼҳ �������
    void SaveFishMenu_SpriteFrame();

    // ���� ѡ plist �ļ�ҳ
    void DrawPListChoose();

    // ���� ѡ sprite frame ҳ
    void DrawSpriteFrameChoose();

    // ���� sprite frame �������� ҳ
    void DrawSpriteFrameConfig();

    // �ύ sprite frame  ��������
    void SaveSpriteFrameConfig();






    void editBoxReturn(cocos2d::ui::EditBox* editBox) override;

    // ���� ��ӭҳ
    virtual bool init() override;

    CREATE_FUNC(HelloWorld);
};
