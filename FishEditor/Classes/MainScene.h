#pragma once
#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"
#include "ui/CocosGUI.h"
#include "FishManage_class_lite.h"
#include "ActionPlayer_SpriteFrame.h"
#include "Circle.h"
#include "DraggingRes.h"
#include "AppDelegate.h"
#include "xx_file.h"
#include "xx_math.h"
#include "xx_chrono.h"

struct MainScene : public cocos2d::Scene, public cocos2d::ui::EditBoxDelegate {
    using BaseType = cocos2d::Scene;

    // ���� AppDelegate::designWidth/Height
    float W = 0, H = 0, W_2 = 0, H_2 = 0;
    
    // ��Ƴߴ����
    float DW = 1280, DH = 720, DW_2 = DW / 2, DH_2 = DH / 2;

    // �������ֲ���
    const float fontSize = 24;
    const float margin = fontSize / 3.0f;
    const float lineHeight = fontSize * 1.4f;

    const cocos2d::Color3B yellow = cocos2d::Color3B(255, 207, 64);
    const cocos2d::Color3B blue = cocos2d::Color3B(126, 194, 255);


    // ��ʱ�ؼ���������
    std::unordered_map<cocos2d::ui::CheckBox*, std::string> cbNames;
    std::vector<cocos2d::ui::EditBox*> editBoxs;

    // ���� ˢ�º�ָ� scroll view ����ʾλ��
    float manageResourcesScrolledPercentVertical = 0;
    float manageFishsScrolledPercentVertical = 0;
    float configSpriteFrameScrolledPercentVertical = 0;
    float editRes2dScrolledPercentVertical = 0;


    // touch ״̬��¼
    cocos2d::Vec2 lastPos;
    bool touching = false;
    Circle* currCircle = nullptr;
    DraggingRes* currDraggingRes = nullptr;

    // �ȼ�������
    cocos2d::ccMenuCallback keyboardCallback_C;


    // ���������ڴ�
    FishManage::Data data;
    // ���������
    xx::ObjectHelper oh;
    // �����ļ���
    const std::string dataFileName = "fishs.data";

    // = cocos2d::FileUtils::getInstance()->getSearchPaths()[0]
    std::string resPath;

    // ����
    void LoadData();
    // �浵
    void SaveData();

    // ����Ļ�м䵯��һ����ʾ�������Ӻ������ʧ
    void PopupMessage(std::string const& txt, cocos2d::Color3B const& color = cocos2d::Color3B::RED);

    // ���� �ı�( ê�� ���� )
    cocos2d::Label* CreateLabel(cocos2d::Vec2 const& pos, std::string const& txt, cocos2d::Node* const& container = nullptr);

    // ���� ��ֵ���ı�. ֵ��ɫ yellow( ê�� ���� )
    std::pair<cocos2d::Label*, cocos2d::Label*> CreateLabelPair(cocos2d::Vec2 const& pos, std::string const& key, std::string const& value, cocos2d::Node* const& container = nullptr);


    // ���� �ı� ��ť( ê�� ���� )
    cocos2d::ui::Button* CreateButton(cocos2d::Vec2 const& pos, std::string const& txt, cocos2d::ccMenuCallback&& callback, cocos2d::Node* const& container = nullptr);

    // ���� �ı� ��ť( ê�� ���� )
    cocos2d::ui::EditBox* CreateEditBox(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, std::string const& text, std::string const& holderText, cocos2d::Node* const& container = nullptr);

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
    ActionPlayer_SpriteFrame* CreateActionPlayer_SpriteFrame(cocos2d::Vec2 const& pos, cocos2d::Size const& siz, FishManage::FrameAction const& action, cocos2d::Node* const& container = nullptr);

    // return tar->getContentSize().width
    float GetWidth(cocos2d::Node* const& tar);
    float GetWidth(std::pair<cocos2d::Label*, cocos2d::Label*> const& tar);

    // ������ԴԤ��( ê�� ���� ). ��ʾΪָ�� siz ��С( �� spine, 3d ��Ҫȡ�� bounding box ���ָ�� siz ���� scale )
    cocos2d::Node* CreateResPreview(cocos2d::Vec2 const& pos, cocos2d::Size siz, std::shared_ptr<FishManage::Res> res, cocos2d::Node* const& container = nullptr);




    //// �༭�����
    //void EditResCombine(std::shared_ptr<FishManage::ResCombine> const& resCombine, int const& pageIndex = 0);

    // ��ӭҳ
    void Welcome();

    //// ��Դ����ҳ
    //void ManageResources();

    //// 2d ֡��Դ�༭ҳ
    //void EditRes2d(std::shared_ptr<FishManage::Res2d> const& res2d);

    //// ѡ plist �ļ�ҳ
    //void ChoosePList(std::shared_ptr<FishManage::Res2d> const& res2d);

    //// ѡ sprite frame ҳ
    //void ChooseSpriteFrame(std::shared_ptr<FishManage::Res2d> const& res2d, std::shared_ptr<FishManage::Action2d> const& action2d);

    //// sprite frame �������� ҳ
    //void ConfigSpriteFrame(std::shared_ptr<FishManage::Res2d> const& res2d, std::shared_ptr<FishManage::Action2d> const& action2d);

    //// �༭����ĳ֡����ײ
    //void EditFrameCD(std::shared_ptr<FishManage::ResBase> const& res, std::shared_ptr<FishManage::ActionBase> const& action, int const& index);

    //// �༭����ĳ֡��������/��
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

    // �����ҳ
    void ManageFishs();

    // ��༭ҳ
    void EditFishNormal(std::shared_ptr<FishManage::FishNormal> const& fish);
    void EditFishBomb(std::shared_ptr<FishManage::FishBomb> const& fish);
    void EditFishDrill(std::shared_ptr<FishManage::FishDrill> const& fish);
    void EditFishFury(std::shared_ptr<FishManage::FishFury> const& fish);
    void EditFishCyclone(std::shared_ptr<FishManage::FishCyclone> const& fish);
    void EditFishEater(std::shared_ptr<FishManage::FishEater> const& fish);

    // for edit box delegate
    void editBoxReturn(cocos2d::ui::EditBox* editBox) override;

    // ���� ��ӭҳ
    virtual bool init() override;



    // ���Ե㶫��
    void Init2();
    ~MainScene() override;
    void update(float delta) override;
    //cocos2d::AmbientLight* _ambientLight = nullptr;
    //cocos2d::DirectionLight* _directionalLight = nullptr;
    //cocos2d::PointLight* _pointLight = nullptr;
    //cocos2d::SpotLight* _spotLight = nullptr;

    CREATE_FUNC(MainScene);
};
