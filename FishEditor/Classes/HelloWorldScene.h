#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FishManage_class_lite.h"
#include "ActionPlayer_SpriteFrame.h"

struct HelloWorld : public cocos2d::Scene, public cocos2d::ui::EditBoxDelegate {
    // ���� AppDelegate::designWidth/Height
    float W = 0, H = 0;

    // �������ֲ���
    const float fontSize = 32;
    const float margin = fontSize / 3.0f;
    const float lineHeight = fontSize * 1.4f;

    const cocos2d::Color3B yellow = cocos2d::Color3B(255, 207, 64);
    const cocos2d::Color3B blue = cocos2d::Color3B(126, 194, 255);

    const std::string dataFileName = "fishs.data";

    // ��ʱ����
    std::unordered_map<cocos2d::ui::CheckBox*, std::string> cbNames;
    std::vector<cocos2d::ui::EditBox*> editBoxs;


    // ��ǰ���ڱ༭�� fish �� �����±�. ���Ϊ -1 ���ʾ new fish
    int currentFishIndex = -1;

    // ��ǰ���ڱ༭�� fish �� actions �����±�. ���Ϊ -1 ���ʾ new action
    int currentActionIndex = -1;

    // ���� ˢ�º�ָ� scroll view ����ʾλ��
    cocos2d::Vec2 currentScrollBarPos;

    // ���������ڴ�
    FishManage::Data data;

    // �����������ʱ�����ڴ�
    FishManage::Fish_2D fish2d;
    FishManage::Fish_Spine fishSpine;
    FishManage::Fish_3D fish3d;
    FishManage::Fish_Combine fishCombine;
    FishManage::Fish_2D_Action fish2dAction;

    // ����
    void LoadData();
    // �浵
    void SaveData();



    // ���� �ı�( ê�� ���� )
    cocos2d::Label* CreateLabel(cocos2d::Vec2 const& pos, std::string const& txt, int const& fontSize, cocos2d::Node* const& container = nullptr);

    // ���� �ı� ��ť( ê�� ���� )
    cocos2d::ui::Button* CreateTextButton(cocos2d::Vec2 const& pos, std::string const& txt, int const& fontSize, cocos2d::ccMenuCallback&& callback, cocos2d::Node* const& container = nullptr);

    // ���� �ı� ��ť( ê�� ���� )
    cocos2d::ui::EditBox* CreateEditBox(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& text, std::string const& holderText, int const& fontSize, cocos2d::Node* const& container = nullptr);

    // ���� checkbox ( ê�� ���� )
    cocos2d::ui::CheckBox* CreateCheckBox(cocos2d::Vec2 const& pos, bool const& value, cocos2d::ui::CheckBox::ccCheckBoxCallback&& callback, cocos2d::Node* const& container = nullptr);



    // ���� �����ü���( ê�� ���� )
    cocos2d::ui::ScrollView* CreateSV(cocos2d::Vec2 const& pos, cocos2d::Size const& cutSize, cocos2d::Size const& itemsSize, cocos2d::Node* const& container = nullptr);



    // ���� ȫ������( ê�� ���� )
    cocos2d::LayerColor* CreateBG(cocos2d::Node* const& container = nullptr);



    // ���� 2d ͼƬ( ê�� ���� ). ��ʾΪָ�� siz ��С
    cocos2d::Sprite* CreateSprite(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& fileName, cocos2d::Node* const& container = nullptr);

    // ���� 2d ֡ͼ( ê�� ���� ). ��ʾΪָ�� siz ��С
    cocos2d::Sprite* CreateSpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& spriteFrameName, cocos2d::Node* const& container = nullptr);

    // ���� ĳ 3d ģ��( ê�� ���� )
    cocos2d::Sprite3D* CreateOrc(cocos2d::Vec2 const& pos, float const& r, cocos2d::Node* const& container = nullptr);

    // ����һ�� 2d ֡ͼ ���� Ԥ������
    ActionPlayer_SpriteFrame* CreateActionPlayer_SpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::vector<std::string> const& plists, FishManage::Fish_2D_Action const& action, cocos2d::Node* const& container = nullptr);



    template<typename FishType>
    void CreateSVItem(cocos2d::ui::ScrollView* const& sv, float const& itemHeight, cocos2d::Vec2 const& pos, int const& index, FishType const& fish);

    // ���� ��ӭҳ
    void DrawWelcome();

    // ���� sprite frame �� ��ʼҳ
    void DrawFish2DSpriteFrame(FishManage::Fish_2D* const& fish);

    // ���� ѡ plist �ļ�ҳ
    void DrawPListChoose(FishManage::Fish_2D* const& fish);

    // ���� ѡ sprite frame ҳ
    void DrawSpriteFrameChoose(FishManage::Fish_2D* const& fish, FishManage::Fish_2D_Action* const& action);

    // ���� sprite frame �������� ҳ
    void DrawSpriteFrameConfig(FishManage::Fish_2D* const& fish, FishManage::Fish_2D_Action* const& action);







    void editBoxReturn(cocos2d::ui::EditBox* editBox) override;

    // ���� ��ӭҳ
    virtual bool init() override;

    CREATE_FUNC(HelloWorld);
};
