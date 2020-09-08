#include "MainScene.h"
#include "Anim.h"

bool MainScene::init() {
	if (!Scene::init()) return false;

	// 开始每帧 update( 有些功能必须跨帧才能工作 )
	scheduleUpdate();

	// 做点测试
	Init2();

	return true;
}


#define COR_BEGIN		switch (lineNumber) { case 0:
#define COR_YIELD		return __LINE__; case __LINE__:;
#define COR_EXIT		return -1;
#define COR_END			} return -1;

void MainScene::update(float delta) {
	if (lineNumber >= 0) {
		lineNumber = Update(lineNumber, delta);
	}
	else {
		unscheduleUpdate();
	}
}

int MainScene::Update(int lineNumber, float delta) {
	COR_BEGIN;

	W = AppDelegate::designWidth;
	H = AppDelegate::designHeight;
	W_2 = W / 2;
	H_2 = H / 2;

	//{
	//	auto anim = CreateAnimExt("1.frames.ext", this);
	//	if (anim) {
	//		//anim->pathways.emplace_back(xx::PathwayMaker({ 100, 100 }).RotateTo(M_PI_4).Forward(200).RotateTo(M_PI).Forward(100).Loop());
	//		anim->pathways.emplace_back(xx::Pathway::Make(true, {
	//			{ 800.0f, 200.0f, 0.5f, 100 },
	//			{ 1500.0f, 500.0f, 0.5f, 100 },
	//			{ 800.0f, 800.0f, 0.5f, 100 },
	//			{ 100.0f, 500.0f, 0.5f, 100 },
	//			}));
	//		anim->timeScale = 100;
	//		anim->speedScale = -1;
	//		anim->SetPathway(0);
	//	}
	//	anims.push_back(anim);
	//}
	{
		auto anim = CreateAnimExt("1.frames.ext", this);
		if (anim) {
			anim->pathways.emplace_back(xx::PathwayMaker({ 100, 100 }).RotateTo(M_PI_4).Forward(200).RotateTo(M_PI).Forward(100).Loop());
			anim->timeScale = 10;
			anim->SetPathway(0);
		}
		anims.push_back(anim);
	}

	while (true) {
		COR_YIELD;

		if (delta < 0.016) {
			for (size_t i = 0; i < 1000; i++)
			{
				auto anim = CreateAnimExt("1.frames.ext", this);
				if (anim) {
					//anim->pathways.emplace_back(xx::PathwayMaker({ 100, 100 }).RotateTo(M_PI_4).Forward(200).RotateTo(M_PI).Forward(100).Loop());
					anim->pathways.emplace_back(xx::Pathway::Make(true, {
						{ 800.0f, 200.0f, 0.5f, 100 },
						{ 1500.0f, 500.0f, 0.5f, 100 },
						{ 800.0f, 800.0f, 0.5f, 100 },
						{ 100.0f, 500.0f, 0.5f, 100 },
						}));
					anim->timeScale = 10;
					anim->speedScale = -1;
					anim->SetPathway(0);
				}
				anims.push_back(anim);
			}
		}

		for (auto&& anim : anims) {
			if (anim && anim->Update(delta)) {
				anim.reset();
			}
			else {
				anim->Draw();
			}
		}
	}




	//{
	//	auto kbListener = cocos2d::EventListenerKeyboard::create();
	//	kbListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	//		switch (keyCode) {
	//		case cocos2d::EventKeyboard::KeyCode::KEY_C:
	//			if (keyboardCallback_C) {
	//				keyboardCallback_C(nullptr);
	//			}
	//			return;
	//		}

	//		if (!currCircle && !currDraggingRes) return;
	//		if (currCircle) {
	//			currCircle->scheduleUpdate();
	//		}
	//		if (currDraggingRes) {
	//			currDraggingRes->scheduleUpdate();
	//		}
	//		switch (keyCode) {
	//		case cocos2d::EventKeyboard::KeyCode::KEY_PLUS:
	//		case cocos2d::EventKeyboard::KeyCode::KEY_KP_PLUS:
	//			if (currCircle) {
	//				currCircle->rChange = 30;
	//			}
	//			if (currDraggingRes) {
	//				currDraggingRes->rChange = 3;
	//			}
	//			break;
	//		case cocos2d::EventKeyboard::KeyCode::KEY_MINUS:
	//		case cocos2d::EventKeyboard::KeyCode::KEY_KP_MINUS:
	//			if (currCircle) {
	//				currCircle->rChange = -30;
	//			}
	//			if (currDraggingRes) {
	//				currDraggingRes->rChange = -3;
	//			}
	//			break;
	//		}
	//	};
	//	kbListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	//		if (!currCircle && !currDraggingRes) return;
	//		if (currCircle) {
	//			currCircle->rChange = 0;
	//			currCircle->unscheduleUpdate();
	//		}
	//		if (currDraggingRes) {
	//			currDraggingRes->rChange = 0;
	//			currDraggingRes->unscheduleUpdate();
	//		}
	//	};
	//	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kbListener, this);
	//}


	//// 注册存盘文件数据结构
	//FishManage::PkgGenTypes::RegisterTo(oh);

	//// 加载存盘文件( 如果有的话 )
	//LoadData();

	{
		// 定位到 root path
		auto&& sps = cocos2d::FileUtils::getInstance()->getSearchPaths();
		assert(sps.size() == 1);
		resPath = sps[0];
	}

	// 遍历文件，形成 File list，然后和 data.files 对比. 看看是否存在差异. 做差异同步。移除不见了的文件，添加新的文件。同名文件如果内容不同，更新

	//exts =
	//{
	//	{ "mp3", FishManage::FileExtensions::mp3   },
	//	{ "ogg", FishManage::FileExtensions::ogg   },
	//	{ "wav", FishManage::FileExtensions::wav   },

	//	{ "webp", FishManage::FileExtensions::webp  },
	//	{ "png", FishManage::FileExtensions::png   },
	//	{ "pkm", FishManage::FileExtensions::pkm   },
	//	{ "jpg", FishManage::FileExtensions::jpg   },
	//	{ "tga", FishManage::FileExtensions::tga   },
	//	{ "bmp", FishManage::FileExtensions::bmp   },

	//	{ "plist", FishManage::FileExtensions::plist },

	//	{ "atlas", FishManage::FileExtensions::atlas },
	//	{ "json", FishManage::FileExtensions::json  },
	//	{ "skel", FishManage::FileExtensions::skel  },

	//	{ "c3b", FishManage::FileExtensions::c3b   },

	//	{ "lua", FishManage::FileExtensions::lua   },

	//	{ "fnt", FishManage::FileExtensions::fnt   },
	//};

	//{
	//	// 针对 resPath 创建跨目录文件枚举器
	//	std::filesystem::recursive_directory_iterator filesIterator(resPath);
	//	xx::Data d;

	//	// 开始扫文件，创建 File_Real 对象, 填充到 files
	//	for (auto&& item : filesIterator) {
	//		// 不是文件
	//		if (!item.is_regular_file()) continue;

	//		// 没有扩展名
	//		auto&& path = item.path();
	//		if (!path.has_extension()) continue;

	//		// 未知扩展名
	//		auto&& extStr = path.extension().string().substr(1);
	//		auto&& iter = exts.find(extStr);
	//		if (iter == exts.end()) continue;
	//		auto&& ext = iter->second;

	//		// 切割出 短path + name.ext
	//		auto&& name = path.string().substr(resPath.size());

	//		// 根据扩展名路由创建不同的 File_Xxxxxx
	//		std::shared_ptr<FishManage::File_Real> file;
	//		switch (ext) {
	//		case FishManage::FileExtensions::mp3:
	//		case FishManage::FileExtensions::ogg:
	//		case FishManage::FileExtensions::wav: {
	//			auto&& o = xx::Make<FishManage::File_Sound>();
	//			file = o;
	//			//o->seconds = 晚些时候填
	//			soundFileNames.push_back(name);
	//			break;
	//		}
	//		case FishManage::FileExtensions::webp:
	//		case FishManage::FileExtensions::png:
	//		case FishManage::FileExtensions::jpg:
	//		case FishManage::FileExtensions::pkm:
	//		case FishManage::FileExtensions::tga:
	//		case FishManage::FileExtensions::bmp: {
	//			file = xx::Make<FishManage::File_Picture>();
	//			// atPList 不在这里填充
	//			break;
	//		}
	//		case FishManage::FileExtensions::atlas: {
	//			file = xx::Make<FishManage::File_Spine>();
	//			break;
	//		}
	//		case FishManage::FileExtensions::skel:
	//		case FishManage::FileExtensions::json: {
	//			file = xx::Make<FishManage::File_Real>();
	//			break;
	//		}
	//		case FishManage::FileExtensions::c3b: {
	//			file = xx::Make<FishManage::File_C3b>();
	//			break;
	//		}
	//		case FishManage::FileExtensions::plist:
	//		case FishManage::FileExtensions::fnt: {
	//			file = xx::Make<FishManage::File_Bag>();
	//			break;
	//		}
	//		case FishManage::FileExtensions::lua: {
	//			file = xx::Make<FishManage::File_Lua>();
	//			break;
	//		}
	//		default:
	//			throw std::logic_error(xx::ToString("unknown ext type: ", extStr));
	//		}

	//		// 填充 物理文件信息. 别的后续填充
	//		file->name = name;
	//		file->ext = ext;
	//		file->length = item.file_size();
	//		xx::ReadAllBytes(path, d);
	//		file->md5.Resize(16);
	//		CalcMD5(d.buf, d.len, file->md5.buf);
	//		files[name] = file;
	//	}

	//	// 待删除列表
	//	std::vector<std::string> dels;
	//	std::map<std::string, std::string> framePlistMap;

	//	// 归并父子关系的文件. 针对特定扩展名
	//	for (auto&& kv : files) {
	//		auto&& file = kv.second;
	//		auto&& fileName = kv.first;
	//		switch (file->ext) {
	//		case FishManage::FileExtensions::plist: {
	//			// 按贴图名找到 file 归并到 childs
	//			auto&& textureName = GetPListTextureName(fileName).substr(resPath.size());
	//			auto&& textureIter = files.find(textureName);
	//			if (textureIter == files.end()) {
	//				throw std::logic_error(xx::ToString("can't find texture name: ", textureName, " for plist file: ", fileName));
	//			}
	//			xx::As<FishManage::File_Bag>(file)->childs.push_back(textureIter->second);
	//			dels.push_back(textureName);

	//			// 按图块名找到 file 设置其 mapTo
	//			auto&& frames = GetPListItems(fileName);
	//			for (auto&& frame : frames) {
	//				// 跨 plist 将图块名放入字典，以检查是否有重复的存在（cocos sprite frame engine 不支持重复）
	//				if (framePlistMap.find(frame) != framePlistMap.end()) {
	//					throw std::logic_error(xx::ToString("duplicate sprite frame name: ", frame, " at plist file: ", fileName, " with plist file:", framePlistMap[frame]));
	//				}
	//				framePlistMap.emplace(frame, fileName);

	//				// 寻找同名单图并对应
	//				auto&& picIter = files.find(frame);
	//				if (picIter != files.end()) {
	//					xx::As<FishManage::File_Picture>(picIter->second)->atPList = xx::As<FishManage::File_Bag>(file);
	//				}
	//				// else 警告该图块对应的单图找不到？
	//			}
	//			break;
	//		}
	//		case FishManage::FileExtensions::atlas: {
	//			auto&& ns = GetAtlasResNames(fileName);
	//			for (auto&& n : ns) {
	//				auto&& iter = files.find(n);
	//				if (iter == files.end()) {
	//					throw std::logic_error(xx::ToString("can't find name: ", n, " for atlas file: ", fileName));
	//				}
	//				xx::As<FishManage::File_Bag>(file)->childs.push_back(iter->second);
	//				dels.push_back(n);
	//			}

	//			// 找出所有 action 并填充
	//			auto&& f = xx::As<FishManage::File_Spine>(file);
	//			auto&& ns2 = GetSpineAnimationNamesSeconds(f);
	//			for (auto&& o : ns2) {
	//				auto&& a = f->actions.emplace_back();
	//				a.name = o.first;
	//				a.seconds = o.second;
	//			}
	//			break;
	//		}
	//		case FishManage::FileExtensions::c3b: {
	//			auto&& nsas = GetC3bResNamesAnimations(fileName);
	//			auto&& f = xx::As<FishManage::File_C3b>(file);
	//			for (auto&& n : nsas.first) {
	//				auto&& iter = files.find(n);
	//				if (iter == files.end()) {
	//					throw std::logic_error(xx::ToString("can't find name: ", n, " for c3b file: ", fileName));
	//				}
	//				f->childs.push_back(iter->second);
	//				dels.push_back(n);
	//			}

	//			// action 填充
	//			for (auto&& o : nsas.second) {
	//				auto&& a = f->actions.emplace_back();
	//				a.name = o.first;
	//				a.seconds = o.second;
	//			}
	//			break;
	//		}
	//		case FishManage::FileExtensions::fnt: {
	//			auto&& ns = GetFntResNames(fileName);
	//			for (auto&& n : ns) {
	//				auto&& iter = files.find(n);
	//				if (iter == files.end()) {
	//					throw std::logic_error(xx::ToString("can't find name: ", n, " for fnt file: ", fileName));
	//				}
	//				xx::As<FishManage::File_Bag>(file)->childs.push_back(iter->second);
	//				dels.push_back(n);
	//			}
	//			break;
	//		}
	//		}
	//	}

	//	for (auto&& o : dels) {
	//		files.erase(o);
	//	}
	//}

	//// 读取声音长度( wav 似乎无法读取长度，先不支持 )
	//for (i = 0; i < soundFileNames.size(); ++i) {
	//	soundId = cocos2d::experimental::AudioEngine::play2d(soundFileNames[i]);
	//	assert(soundId != -1);
	//	do {
	//		COR_YIELD;
	//		soundDuration = cocos2d::experimental::AudioEngine::getDuration(soundId);
	//	} while (soundDuration == -1);
	//	cocos2d::experimental::AudioEngine::stop(soundId);
	//	xx::As<FishManage::File_Sound>(files[soundFileNames[i]])->seconds = soundDuration;
	//	COR_YIELD;
	//}

	//// files 和 data.files 做对比, 差异更新. 1. 删掉不见了的    2. 更新同名的      3. 添加新增的
	//// 1. 删掉不见了的
	//for (auto&& iter = data.files.begin(); iter != data.files.end();) {
	//	if (files.find(iter->first) != files.end()) {
	//		++iter;
	//	}
	//	else {
	//		iter = data.files.erase(iter);
	//	}
	//}

	//// 2. 更新同名的( 尽量保留配置数据 ）
	//for (auto&& kv : data.files) {
	//	auto&& oldFile = kv.second;
	//	auto&& newFile = files[kv.first];
	//	if (oldFile->GetTypeId() != newFile->GetTypeId()) {
	//		oldFile = newFile;
	//	}
	//	else {
	//		switch (oldFile->ext) {
	//		case FishManage::FileExtensions::mp3:
	//		case FishManage::FileExtensions::ogg:
	//		case FishManage::FileExtensions::wav: {
	//			auto&& o = xx::As<FishManage::File_Sound>(oldFile);
	//			auto&& n = xx::As<FishManage::File_Sound>(newFile);
	//			if (o->length == n->length && o->md5 == n->md5) continue;
	//			o->length = n->length;
	//			o->md5 = n->md5;
	//			// seconds 不覆盖
	//			break;
	//		}
	//		case FishManage::FileExtensions::webp:
	//		case FishManage::FileExtensions::png:
	//		case FishManage::FileExtensions::jpg:
	//		case FishManage::FileExtensions::pkm:
	//		case FishManage::FileExtensions::tga:
	//		case FishManage::FileExtensions::bmp: {
	//			auto&& o = xx::As<FishManage::File_Picture>(oldFile);
	//			auto&& n = xx::As<FishManage::File_Picture>(newFile);
	//			if (o->length == n->length && o->md5 == n->md5) continue;
	//			o->length = n->length;
	//			o->md5 = n->md5;
	//			o->atPList = n->atPList;
	//			break;
	//		}
	//		case FishManage::FileExtensions::atlas: {
	//			auto&& o = xx::As<FishManage::File_Spine>(oldFile);
	//			auto&& n = xx::As<FishManage::File_Spine>(newFile);
	//			if (o->length == n->length && o->md5 == n->md5) continue;
	//			o->length = n->length;
	//			o->md5 = n->md5;
	//			o->childs = n->childs;
	//			// todo: 对比 actions 差异更新
	//			break;
	//		}
	//		case FishManage::FileExtensions::c3b: {
	//			auto&& o = xx::As<FishManage::File_C3b>(oldFile);
	//			auto&& n = xx::As<FishManage::File_C3b>(newFile);
	//			if (o->length == n->length && o->md5 == n->md5) continue;
	//			o->length = n->length;
	//			o->md5 = n->md5;
	//			o->childs = n->childs;
	//			// todo: 对比 actions 差异更新
	//			break;
	//		}
	//		case FishManage::FileExtensions::plist:
	//		case FishManage::FileExtensions::fnt: {
	//			auto&& o = xx::As<FishManage::File_Bag>(oldFile);
	//			auto&& n = xx::As<FishManage::File_Bag>(newFile);
	//			oh.Clone(n, o);
	//			break;
	//		}
	//		case FishManage::FileExtensions::lua: {
	//			auto&& o = xx::As<FishManage::File_Lua>(oldFile);
	//			auto&& n = xx::As<FishManage::File_Lua>(newFile);
	//			oh.Clone(n, o);
	//			break;
	//		}
	//		default:
	//			throw std::logic_error(xx::ToString("unknown ext type: ", (int)oldFile->ext));
	//		}
	//	}
	//}

	//// 3. 添加新增的
	//for (auto&& kv : files) {
	//	data.files.emplace(kv.first, kv.second);
	//}

	//// 存盘
	//SaveData();


	// 加载首页
	//Welcome();

	COR_END;
}
