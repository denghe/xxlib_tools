#include "MainScene.h"
#include "RenderTextureOrc.h"

void MainScene::Init2() {
	//scheduleUpdate();


	//auto camera = cocos2d::Camera::createPerspective(60, (GLfloat)1900 / 1000, 1.0f, 1000.0f);
	//camera->setCameraFlag(cocos2d::CameraFlag::USER1);
	//camera->setPosition3D(cocos2d::Vec3(0.0, 100, 100));
	//camera->lookAt(cocos2d::Vec3(0.0, 0.0, 0.0), cocos2d::Vec3(0.0, 1.0, 0.0));
	//addChild(camera);


	//_ambientLight = cocos2d::AmbientLight::create(cocos2d::Color3B(200, 200, 200));
	////_ambientLight->retain();
	//_ambientLight->setEnabled(true);
	//addChild(_ambientLight);
	////_ambientLight->setCameraMask(2);

	//_directionalLight = cocos2d::DirectionLight::create(cocos2d::Vec3(-1.0f, -1.0f, 0.0f), cocos2d::Color3B(200, 200, 200));
	////_directionalLight->retain();
	//_directionalLight->setEnabled(false);
	//addChild(_directionalLight);
	////_directionalLight->setCameraMask(2);

	//_pointLight = cocos2d::PointLight::create(cocos2d::Vec3(0.0f, 0.0f, 0.0f), cocos2d::Color3B(200, 200, 200), 10000.0f);
	////_pointLight->retain();
	//_pointLight->setEnabled(false);
	//addChild(_pointLight);
	////_pointLight->setCameraMask(2);

	//_spotLight = cocos2d::SpotLight::create(cocos2d::Vec3(-1.0f, -1.0f, 0.0f), cocos2d::Vec3(0.0f, 0.0f, 0.0f), cocos2d::Color3B(200, 200, 200), 0.0, 0.5, 10000.0f);
	////_spotLight->retain();
	//_spotLight->setEnabled(true);
	//addChild(_spotLight);
	////_spotLight->setCameraMask(2);

	//{
	//	auto tintto1 = cocos2d::TintTo::create(4, 0, 0, 255);
	//	auto tintto2 = cocos2d::TintTo::create(4, 0, 255, 0);
	//	auto tintto3 = cocos2d::TintTo::create(4, 255, 0, 0);
	//	auto tintto4 = cocos2d::TintTo::create(4, 255, 255, 255);
	//	auto seq = cocos2d::Sequence::create(tintto1, tintto2, tintto3, tintto4, nullptr);
	//	_ambientLight->runAction(cocos2d::RepeatForever::create(seq));
	//}

	//{
	//	auto tintto1 = cocos2d::TintTo::create(4, 255, 0, 0);
	//	auto tintto2 = cocos2d::TintTo::create(4, 0, 255, 0);
	//	auto tintto3 = cocos2d::TintTo::create(4, 0, 0, 255);
	//	auto tintto4 = cocos2d::TintTo::create(4, 255, 255, 255);
	//	auto seq = cocos2d::Sequence::create(tintto1, tintto2, tintto3, tintto4, nullptr);
	//	_directionalLight->runAction(cocos2d::RepeatForever::create(seq));
	//}

	//{
	//	auto tintto1 = cocos2d::TintTo::create(4, 255, 0, 0);
	//	auto tintto2 = cocos2d::TintTo::create(4, 0, 255, 0);
	//	auto tintto3 = cocos2d::TintTo::create(4, 0, 0, 255);
	//	auto tintto4 = cocos2d::TintTo::create(4, 255, 255, 255);
	//	auto seq = cocos2d::Sequence::create(tintto2, tintto1, tintto3, tintto4, nullptr);
	//	_pointLight->runAction(cocos2d::RepeatForever::create(seq));
	//}

	//{
	//	auto tintto1 = cocos2d::TintTo::create(4, 255, 0, 0);
	//	auto tintto2 = cocos2d::TintTo::create(4, 0, 255, 0);
	//	auto tintto3 = cocos2d::TintTo::create(4, 0, 0, 255);
	//	auto tintto4 = cocos2d::TintTo::create(4, 255, 255, 255);
	//	auto seq = cocos2d::Sequence::create(tintto3, tintto2, tintto1, tintto4, nullptr);
	//	_spotLight->runAction(cocos2d::RepeatForever::create(seq));
	//}


	//auto o = RenderTextureOrc::create();
	//addChild(o);
	//o->setPosition({W_2, H_2});
	//auto rect = o->getBoundingBox();


	//o = RenderTextureOrc::create();
	//addChild(o);
	//o->SetColor(cocos2d::Color3B::BLUE);
	//o->SetPosition({ W_2 + 100, H_2 });

	//o = RenderTextureOrc::create();
	//addChild(o);
	//o->SetColor(cocos2d::Color3B::RED);
	//o->SetPosition({ W_2 + 200, H_2 });


	//auto o = CreateOrc({ W_2, H_2 }, 0);
	//o->setScale(40);
	//o->setGlobalZOrder(1);
	//o->setForce2DQueue(true);

	//o = CreateOrc({ W_2 + 100, H_2 }, 0);
	//o->setScale(40);
	//o->setColor(cocos2d::Color3B::BLUE);
	//o->setGlobalZOrder(1);
	//o->setForce2DQueue(true);

	//o = CreateOrc({ W_2 + 200, H_2 }, 0);
	//o->setScale(40);
	//o->setColor(cocos2d::Color3B::RED);
	//o->setGlobalZOrder(1);
	//o->setForce2DQueue(true);

	//o = RenderTextureOrc::create();
	//addChild(o);
	//o->SetColor(cocos2d::Color3B::BLUE);
	//o->SetPosition({ W_2 + 100, H_2 });

	//o = RenderTextureOrc::create();
	//addChild(o);
	//o->SetColor(cocos2d::Color3B::RED);
	//o->SetPosition({ W_2 + 200, H_2 });

	//for (int i = 0; i < 1; ++i) {
	//	//auto orc = CreateOrc({ (float)cocos2d::random(0, (int)W), (float)cocos2d::random(0,(int)H) }, 0);
	//	//orc->setGlobalZOrder(1);
	//	
	//	auto o = RenderTextureOrc::create();
	//	addChild(o);
	//	//o->setPosition({ (float)cocos2d::random(0, (int)W), (float)cocos2d::random(0,(int)H) });
	//	//o->setPosition({ 10000, 10000 });
	//	o->setPosition({ W_2, H_2 });

	//	o->runAction(cocos2d::CallFunc::create([this, o] {

	//		auto t = o->rt->getSprite()->getTexture();

	//		for (size_t j = 0; j < 50; j++)
	//		{
	//			auto spr = cocos2d::Sprite::createWithTexture(t);
	//			addChild(spr);
	//			spr->setPosition({ (float)cocos2d::random(0, (int)W), (float)cocos2d::random(0,(int)H) });
	//		}

	//		//o->rt->saveToFile("myorc.png", true, [](cocos2d::RenderTexture*, const std::string&) {
	//		//	std::cout << std::endl;
	//		//	});
	//		//})
	//		}
	//	));

	//	//CreateButton({ 100, 100 }, "save", [o](auto) {
	//	//	o->rt->saveToFile("myorc.png", true, [](cocos2d::RenderTexture*, const std::string&) {
	//	//		std::cout << std::endl;
	//	//		});
	//	//	});
	//}
}

MainScene::~MainScene() {
}

//void MainScene::update(float delta) {
//	//static float angleDelta = 0.0;
//
//	//if (_directionalLight)
//	//{
//	//	_directionalLight->setRotation3D(cocos2d::Vec3(-45.0, -CC_RADIANS_TO_DEGREES(angleDelta), 0.0f));
//	//}
//
//	//if (_pointLight)
//	//{
//	//	_pointLight->setPositionX(100.0f * cosf(angleDelta + 2.0 * delta));
//	//	_pointLight->setPositionY(100.0f);
//	//	_pointLight->setPositionZ(100.0f * sinf(angleDelta + 2.0 * delta));
//	//}
//
//	//if (_spotLight)
//	//{
//	//	_spotLight->setPositionX(100.0f * cosf(angleDelta + 4.0 * delta));
//	//	_spotLight->setPositionY(100.0f);
//	//	_spotLight->setPositionZ(100.0f * sinf(angleDelta + 4.0 * delta));
//	//	_spotLight->setDirection(-cocos2d::Vec3(cosf(angleDelta + 4.0 * delta), 1.0, sinf(angleDelta + 4.0 * delta)));
//	//}
//
//	//angleDelta += delta;
//}
