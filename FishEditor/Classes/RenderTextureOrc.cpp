#include "MainScene.h"
#include "RenderTextureOrc.h"

bool RenderTextureOrc::init() {
	c = cocos2d::Node::create();
	c->retain();

	auto camera = cocos2d::Camera::createPerspective(60, (GLfloat)1900 / 1000, 1.0f, 1000.0f);
	camera->setCameraFlag(cocos2d::CameraFlag::USER1);
	camera->setPosition3D(cocos2d::Vec3(0.0, 100, 100));
	camera->lookAt(cocos2d::Vec3(0.0, 0.0, 0.0), cocos2d::Vec3(0.0, 1.0, 0.0));
	c->addChild(camera);


	_ambientLight = cocos2d::AmbientLight::create(cocos2d::Color3B(200, 200, 200));
	//_ambientLight->retain();
	_ambientLight->setEnabled(true);
	c->addChild(_ambientLight);
	_ambientLight->setCameraMask(1);

	_directionalLight = cocos2d::DirectionLight::create(cocos2d::Vec3(-1.0f, -1.0f, 0.0f), cocos2d::Color3B(200, 200, 200));
	//_directionalLight->retain();
	_directionalLight->setEnabled(true);
	c->addChild(_directionalLight);
	_directionalLight->setCameraMask(2);

	_pointLight = cocos2d::PointLight::create(cocos2d::Vec3(0.0f, 0.0f, 0.0f), cocos2d::Color3B(200, 200, 200), 10000.0f);
	//_pointLight->retain();
	_pointLight->setEnabled(true);
	c->addChild(_pointLight);
	_pointLight->setCameraMask(3);

	_spotLight = cocos2d::SpotLight::create(cocos2d::Vec3(-1.0f, -1.0f, 0.0f), cocos2d::Vec3(0.0f, 0.0f, 0.0f), cocos2d::Color3B(200, 200, 200), 0.0, 0.5, 10000.0f);
	//_spotLight->retain();
	_spotLight->setEnabled(true);
	c->addChild(_spotLight);
	//_spotLight->setCameraMask(4);


	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	//rt = cocos2d::RenderTexture::create(visibleSize.width, visibleSize.height, cocos2d::Texture2D::PixelFormat::RGBA8888, GL_DEPTH24_STENCIL8);
	rt = cocos2d::RenderTexture::create(100, 100, cocos2d::Texture2D::PixelFormat::RGBA8888, GL_DEPTH24_STENCIL8);
	rt->setKeepMatrix(true);
	addChild(rt);
	//rt->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	//lc = cocos2d::LayerColor::create(cocos2d::Color4B::RED);
	//lc->retain();

	//for (int i = 0; i < 10; ++i) {
	//	auto orc = cocos2d::Sprite3D::create("orc.c3b");
	//	auto action = cocos2d::RepeatForever::create(
	//		cocos2d::Animate3D::create(
	//			cocos2d::Animation3D::create("orc.c3b", "Take 001")
	//		)
	//	);
	//	orc->runAction(action);
	//	orc->setForce2DQueue(true);
	//	orc->setScale(40);
	//	orc->setPosition({ (float)cocos2d::random(0, (int)visibleSize.width), (float)cocos2d::random(0,(int)visibleSize.height) });
	//	//orc->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//	orc->retain();
	//	orcs_actions.emplace_back(orc, action);
	//}


	{
		auto orc = cocos2d::Sprite3D::create("orc.c3b");
		auto action = cocos2d::RepeatForever::create(
			cocos2d::Animate3D::create(
				cocos2d::Animation3D::create("orc.c3b", "Take 001")
			)
		);
		orc->runAction(action);
		orc->setForce2DQueue(true);
		orc->setScale(80, 50);
		orc->setPosition(950, 100);
		//orc->setCameraMask(2);
		//orc->setColor(cocos2d::Color3B::RED);
		//orc->retain();
		c->addChild(orc);
		orcs_actions.emplace_back(orc, action);
	}

	//{
	//	auto orc = cocos2d::Sprite3D::create("orc.c3b");
	//	auto action = cocos2d::RepeatForever::create(
	//		cocos2d::Animate3D::create(
	//			cocos2d::Animation3D::create("orc.c3b", "Take 001")
	//		)
	//	);
	//	orc->runAction(action);
	//	orc->setForce2DQueue(true);
	//	orc->setScale(40);
	//	orc->setPosition(visibleSize.width / 2 + 100, visibleSize.height / 2);
	//	orc->setColor(cocos2d::Color3B::RED);
	//	orc->retain();
	//	orcs_actions.emplace_back(orc, action);
	//}

	//{
	//	auto orc = cocos2d::Sprite3D::create("orc.c3b");
	//	auto action = cocos2d::RepeatForever::create(
	//		cocos2d::Animate3D::create(
	//			cocos2d::Animation3D::create("orc.c3b", "Take 001")
	//		)
	//	);
	//	orc->runAction(action);
	//	orc->setForce2DQueue(true);
	//	orc->setScale(40);
	//	orc->setPosition(visibleSize.width / 2 + 200, visibleSize.height / 2);
	//	orc->setColor(cocos2d::Color3B::BLUE);
	//	orc->retain();
	//	orcs_actions.emplace_back(orc, action);
	//}




	scheduleUpdate();
	return true;
}

void RenderTextureOrc::SetColor(cocos2d::Color3B const& c) {
	for (auto&& oa : orcs_actions) {
		oa.first->setColor(c);
	}
}
void RenderTextureOrc::SetPosition(cocos2d::Vec2 const& p) {
	for (auto&& oa : orcs_actions) {
		oa.first->setPosition(p);
	}
}

void RenderTextureOrc::visit(cocos2d::Renderer* renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) {
	this->BaseType::visit(renderer, parentTransform, parentFlags);

	auto&& r = cocos2d::Director::getInstance()->getRenderer();
	rt->beginWithClear(0, 0, 0, 0, 1, 0);

	c->visit(r, cocos2d::Mat4::IDENTITY, 0);
	//lc->visit(r, cocos2d::Mat4::IDENTITY, 0);
	//_ambientLight->visit(r, cocos2d::Mat4::IDENTITY, 0);
	//_directionalLight->visit(r, cocos2d::Mat4::IDENTITY, 0);
	//_pointLight->visit(r, cocos2d::Mat4::IDENTITY, 0);
	//_spotLight->visit(r, cocos2d::Mat4::IDENTITY, 0);
	//for (auto&& oa : orcs_actions) {
	//	oa.first->visit(r, cocos2d::Mat4::IDENTITY, 0);
	//}

	rt->end();
}

void RenderTextureOrc::update(float delta) {
	for (auto&& oa : orcs_actions) {
		oa.second->step(delta);
	}

	static float angleDelta = 0.0;

	if (_directionalLight)
	{
		_directionalLight->setRotation3D(cocos2d::Vec3(-45.0, -CC_RADIANS_TO_DEGREES(angleDelta), 0.0f));
	}

	if (_pointLight)
	{
		_pointLight->setPositionX(100.0f * cosf(angleDelta + 2.0 * delta));
		_pointLight->setPositionY(100.0f);
		_pointLight->setPositionZ(100.0f * sinf(angleDelta + 2.0 * delta));
	}

	if (_spotLight)
	{
		_spotLight->setPositionX(100.0f * cosf(angleDelta + 4.0 * delta));
		_spotLight->setPositionY(100.0f);
		_spotLight->setPositionZ(100.0f * sinf(angleDelta + 4.0 * delta));
		_spotLight->setDirection(-cocos2d::Vec3(cosf(angleDelta + 4.0 * delta), 1.0, sinf(angleDelta + 4.0 * delta)));
	}

	angleDelta += delta;

}

RenderTextureOrc::~RenderTextureOrc() {
	c->release();
	//lc->release();
	//_ambientLight->release();
	//_directionalLight->release();
	//_pointLight->release();
	//_spotLight->release();

	//for (auto&& oa : orcs_actions) {
	//	oa.first->release();
	//}
}
