#pragma once
#include "cocos2d.h"

struct RenderTextureOrc : public cocos2d::Node {
	CREATE_FUNC(RenderTextureOrc);
	using BaseType = cocos2d::Node;
	using BaseType::BaseType;

	cocos2d::AmbientLight* _ambientLight = nullptr;
	cocos2d::DirectionLight* _directionalLight = nullptr;
	cocos2d::PointLight* _pointLight = nullptr;
	cocos2d::SpotLight* _spotLight = nullptr;
	//cocos2d::LayerColor* lc = nullptr;
	cocos2d::Node* c = nullptr;
	cocos2d::RenderTexture* rt = nullptr;
	std::vector<std::pair<cocos2d::Sprite3D*, cocos2d::Action*>> orcs_actions;

	void SetColor(cocos2d::Color3B const& c);
	void SetPosition(cocos2d::Vec2 const& p);

	bool init() override;
	void visit(cocos2d::Renderer* renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;
	void update(float delta) override;
	~RenderTextureOrc() override;
};
