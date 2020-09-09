/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainScene.h"

 //Uncomment the following line to use localize manager
 //#include "editor-support/cocostudio/LocalizationManager.h"

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate() {
	//FileUtils::getInstance();
}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// Initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#ifdef _WIN32
		glview = GLViewImpl::createWithRect("Cpp Empty Test", { 0,0, AppDelegate::designWidth, AppDelegate::designHeight }, 1.0f, false);
#else
		glview = GLViewImpl::create("Cpp Empty Test");
#endif
		director->setOpenGLView(glview);
	}
	glview->setIcon("Icon-60@3x.png");

	director->setOpenGLView(glview);

	director->setProjection(Director::Projection::_2D);

	// Set the design resolution
	glview->setDesignResolutionSize(designWidth, designHeight, ResolutionPolicy::NO_BORDER);


	// Turn on display FPS
	director->setDisplayStats(true);

	// Set FPS. the default value is 1.0/60 if you don't call this
	//director->setAnimationInterval(1.0f / 60);
	//director->setAnimationInterval(1.0f / 5);
	director->setAnimationInterval(1.0f / 144);

	//Size frameSize = glview->getFrameSize();

	//director->setContentScaleFactor(resourceSize.height / designSize.height);

	// Create a scene. it's an autorelease object
	auto scene = MainScene::create();

	// Run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	// If you use SimpleAudioEngine, it must be paused
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// This function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// If you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
