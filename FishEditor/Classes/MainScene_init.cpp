#include "MainScene.h"
#include "md5.h"

// out len == 16
void CalcMD5(void* const& buf, size_t const& len, void* out) {
	MD5_CTX c;
	MD5_Init(&c);
	MD5_Update(&c, buf, len);
	MD5_Final((unsigned char*)out, &c);
}

// 扫出 plist 里的 sprite frame names
std::vector<std::string> GetPListItems(std::string const& plistFileName, std::string& outTexturePath) {
	std::vector<std::string> names;
	auto&& fu = cocos2d::FileUtils::getInstance();

	// 写法确保与 addSpriteFramesWithFile 函数内部一致
	std::string fullPath = fu->fullPathForFilename(plistFileName);
	auto&& dict = fu->getValueMapFromFile(fullPath);
	auto&& framesDict = dict["frames"].asValueMap();
	for (auto&& iter : framesDict) {
		auto&& frameDict = iter.second.asValueMap();
		names.push_back(iter.first);
	}

	std::string texturePath;
	if (dict.find("metadata") != dict.end()) {
		auto&& metadataDict = dict["metadata"].asValueMap();
		texturePath = metadataDict["textureFileName"].asString();
	}
	if (!texturePath.empty()) {
		texturePath = fu->fullPathFromRelativeFile(texturePath, plistFileName);
	}
	else {
		texturePath = plistFileName;
		size_t startPos = texturePath.find_last_of('.');
		if (startPos != std::string::npos) {
			texturePath = texturePath.erase(startPos);
		}
		texturePath = texturePath.append(".png");
	}
	outTexturePath = fu->fullPathForFilename(texturePath);

	//// 排序( 如果含有数字，以其中的数字部分大小来排 )
	//std::sort(names.begin(), names.end(), [](std::string const& a, std::string const& b)->bool {
	//	return xx::InnerNumberToFixed(a) < xx::InnerNumberToFixed(b);
	//	});

	return names;
}


bool MainScene::init() {
	if (!Scene::init()) return false;

	W = AppDelegate::designWidth;
	H = AppDelegate::designHeight;
	W_2 = W / 2;
	H_2 = H / 2;

	auto kbListener = cocos2d::EventListenerKeyboard::create();
	kbListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
		switch (keyCode) {
		case cocos2d::EventKeyboard::KeyCode::KEY_C:
			if (keyboardCallback_C) {
				keyboardCallback_C(nullptr);
			}
			return;
		}

		if (!currCircle && !currDraggingRes) return;
		if (currCircle) {
			currCircle->scheduleUpdate();
		}
		if (currDraggingRes) {
			currDraggingRes->scheduleUpdate();
		}
		switch (keyCode) {
		case cocos2d::EventKeyboard::KeyCode::KEY_PLUS:
		case cocos2d::EventKeyboard::KeyCode::KEY_KP_PLUS:
			if (currCircle) {
				currCircle->rChange = 30;
			}
			if (currDraggingRes) {
				currDraggingRes->rChange = 3;
			}
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_MINUS:
		case cocos2d::EventKeyboard::KeyCode::KEY_KP_MINUS:
			if (currCircle) {
				currCircle->rChange = -30;
			}
			if (currDraggingRes) {
				currDraggingRes->rChange = -3;
			}
			break;
		}
	};
	kbListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
		if (!currCircle && !currDraggingRes) return;
		if (currCircle) {
			currCircle->rChange = 0;
			currCircle->unscheduleUpdate();
		}
		if (currDraggingRes) {
			currDraggingRes->rChange = 0;
			currDraggingRes->unscheduleUpdate();
		}
	};
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kbListener, this);



	// 注册存盘文件数据结构
	FishManage::PkgGenTypes::RegisterTo(oh);

	// 加载存盘文件( 如果有的话 )
	LoadData();

	// 定位到 root path
	auto&& sps = cocos2d::FileUtils::getInstance()->getSearchPaths();
	assert(sps.size() == 1);
	resPath = sps[0];


	// todo: 
	// 遍历文件，形成 File list，然后和 data.files 对比. 看看是否存在差异. 做差异同步。移除不见了的文件，添加新的文件。同名文件如果内容不同，更新

	//std::vector<std::filesystem::path> paths;
	//std::vector<std::string> fns;	// 去掉了 resPath 部分 剩下的

	std::unordered_map<std::string, FishManage::FileExtensions> exts
	{
		{ "mp3", FishManage::FileExtensions::mp3   },
		{ "ogg", FishManage::FileExtensions::ogg   },
		{ "wav", FishManage::FileExtensions::wav   },

		{ "webp", FishManage::FileExtensions::webp  },
		{ "png", FishManage::FileExtensions::png   },
		{ "pkm", FishManage::FileExtensions::pkm   },
		{ "jpg", FishManage::FileExtensions::jpg   },

		{ "plist", FishManage::FileExtensions::plist },

		{ "atlas", FishManage::FileExtensions::atlas },
		{ "json", FishManage::FileExtensions::json  },

		{ "c3b", FishManage::FileExtensions::c3b   },

		{ "lua", FishManage::FileExtensions::lua   },

		{ "fnt", FishManage::FileExtensions::fnt   },
	};

	std::map<std::string, std::shared_ptr<FishManage::File>> files;
	xx::Data d;

	std::filesystem::recursive_directory_iterator filesIterator(resPath);
	for (auto&& item : filesIterator) {
		// 不是文件
		if (!item.is_regular_file()) continue;
		auto&& path = item.path();
		// 没有扩展名
		if (!path.has_extension()) continue;
		auto&& ext = path.extension().string().substr(1);
		// 未知扩展名
		auto&& iter = exts.find(ext);
		if (iter == exts.end()) continue;

		// 创建并填充
		auto&& file = xx::Make<FishManage::File>();
		file->path = path.string().substr(resPath.size());
		file->ext = iter->second;
		file->length = item.file_size();
		xx::ReadAllBytes(path, d);
		file->md5.Resize(16);
		CalcMD5(d.buf, d.len, file->md5.buf);
		files[file->path] = file;
	}

	d.Clear(true);


	// 当 File 失效时，清理相关 Res
	auto&& CleanupRess = [this] {
		// resMusics
		for (auto&& iter = data.resMusics.begin(); iter != data.resMusics.end();) {
			if (iter->second->file.lock()) {
				++iter;
			}
			else {
				iter = data.resMusics.erase(iter);
			}
		}

		// resVoices
		for (auto&& iter = data.resVoices.begin(); iter != data.resVoices.end();) {
			if (iter->second->file.lock()) {
				++iter;
			}
			else {
				iter = data.resVoices.erase(iter);
			}
		}

		// resTextures
		for (auto&& iter = data.resTextures.begin(); iter != data.resTextures.end();) {
			if (iter->second->file.lock()) {
				++iter;
			}
			else {
				iter = data.resTextures.erase(iter);
			}
		}

		// resPLists
		for (auto&& iter = data.resPLists.begin(); iter != data.resPLists.end();) {
			if (iter->second->file.lock()) {
				++iter;
			}
			else {
				iter = data.resPLists.erase(iter);
			}
		}

		// resFrames
		for (auto&& iter = data.resFrames.begin(); iter != data.resFrames.end();) {
			if (iter->second.lock()) {
				++iter;
			}
			else {
				iter = data.resFrames.erase(iter);
			}
		}

		// resSpines
		for (auto&& iter = data.resSpines.begin(); iter != data.resSpines.end();) {
			if (iter->second->atlasFile.lock() && iter->second->jsonFile.lock()) {
				// todo: textures 根据 内容直接重建
				++iter;
			}
			iter = data.resSpines.erase(iter);
		}

		// res3ds
		for (auto&& iter = data.res3ds.begin(); iter != data.res3ds.end();) {
			if (iter->second->file.lock()) {
				// todo: textures 根据 内容直接重建
				++iter;
			}
			iter = data.res3ds.erase(iter);
		}

		// resFrameAnimations
		// todo: plistFiles 根据 actions.frames 相关文件重建

		// todo: resCombine 有效性判断

		// resScripts
		for (auto&& iter = data.resScripts.begin(); iter != data.resScripts.end();) {
			if (iter->second->file.lock()) {
				++iter;
			}
			iter = data.resScripts.erase(iter);
		}
	};

	// files 和 data.files 做对比, 差异更新
	// 步骤：1. 删掉不见了的，2. 更新同名的，3. 添加新增的
	// 1.
	for (auto&& iter = data.files.begin(); iter != data.files.end();) {
		if (files.find(iter->first) != files.end()) {
			++iter;
		}
		else {
			iter = data.files.erase(iter);
		}
	}
	CleanupRess();

	// 2.
	for (auto&& kv : data.files) {
		auto&& a = *kv.second;
		auto&& b = *files[kv.first];
		if (a.length == b.length && a.md5 == b.md5) continue;
		a.length = b.length;
		a.md5 = b.md5;

		// 凡是有引用到别的资源的对象，都需要检查是否发生了改变
		switch (a.ext) {
		case FishManage::FileExtensions::plist:
		{

			break;
		}
		case FishManage::FileExtensions::atlas:
			break;
		case FishManage::FileExtensions::c3b:
			break;
		case FishManage::FileExtensions::fnt:
			break;
		}

		//// 如果是 plist 则看看图块列表是否发生了改变
		//if (a.ext == FishManage::FileExtensions::plist) {
		//	auto&& frameNames = GetPListItems(a.path);
		//	// todo
		//}
	}

	// 3.
	// 先把不依赖别的资源的文件类型弄了
	for (auto&& kv : files) {
		auto&& name = kv.first;
		auto&& file = kv.second;
		if (data.files.find(name) != data.files.end()) continue;
		else {
			// 根据文件类型创建相应的 res
			switch (file->ext) {
			case FishManage::FileExtensions::webp:
			case FishManage::FileExtensions::png:
			case FishManage::FileExtensions::jpg:
			case FishManage::FileExtensions::pkm:
			case FishManage::FileExtensions::tga:
			case FishManage::FileExtensions::bmp:
			{
				auto&& res = xx::Make<FishManage::ResTexture>();
				res->file = file;
				res->name = name;
				assert(data.resTextures.find(name) == data.resTextures.end());
				data.resTextures[name] = res;
				break;
			}
			case FishManage::FileExtensions::mp3:
			{
				auto&& res = xx::Make<FishManage::ResMusic>();
				res->file = file;
				res->name = name;
				// todo: res->seconds = ???? 待填
				assert(data.resMusics.find(name) == data.resMusics.end());
				data.resMusics[name] = res;
				break;
			}
			case FishManage::FileExtensions::ogg:
			case FishManage::FileExtensions::wav:
			{
				auto&& res = xx::Make<FishManage::ResVoice>();
				res->file = file;
				res->name = name;
				// todo: res->seconds = ???? 待填
				assert(data.resVoices.find(name) == data.resVoices.end());
				data.resVoices[name] = res;
				break;
			}
			case FishManage::FileExtensions::lua:
			{
				auto&& res = xx::Make<FishManage::ResScript>();
				res->file = file;
				res->name = name;
				assert(data.resScripts.find(name) == data.resScripts.end());
				data.resScripts[name] = res;
				break;
			}
			default:
				continue;
			}
			data.files[name] = file;
		}
	}

	for (auto&& kv : files) {
		auto&& name = kv.first;
		auto&& file = kv.second;
		if (data.files.find(name) != data.files.end()) continue;
		else {
			data.files[name] = file;

			// 根据文件类型创建相应的 res
			switch (file->ext) {
			case FishManage::FileExtensions::plist:
			{
				std::string texturePath;
				auto&& frameNames = GetPListItems(file->path, texturePath);
				texturePath = texturePath.substr(resPath.size());
				if (files.find(texturePath) == files.end()) {
					throw std::logic_error(xx::ToString("can't find plist texture file: ", texturePath, " at plist file: ", name));
				}
				if (data.resTextures.find(texturePath) == data.resTextures.end()) {
					throw std::logic_error(xx::ToString("can't find texture res name: ", texturePath));
				}
				if (data.resPLists.find(name) != data.resPLists.end()) {
					throw std::logic_error(xx::ToString("duplicate ResPList name: ", name));
				}
				for (auto&& fn : frameNames) {
					if (data.resFrames.find(fn) != data.resFrames.end()) {
						throw std::logic_error(xx::ToString("duplicate sprite frame name: ", fn, " at plist file: ", name));
					}
				}

				auto&& res = xx::Make<FishManage::ResPList>();
				data.resPLists[name] = res;
				res->name = name;
				res->file = file;
				res->texture = data.resTextures[texturePath];
				for (auto&& fn : frameNames) {
					auto&& resFrame = res->frames.emplace_back(xx::Make<FishManage::ResFrame>());
					resFrame->name = fn;
					resFrame->owner = res;
					//if (data.resFrames.find(fn) != data.resFrames.end()) continue;	// 发现有些资源就是重复打包了 先跳
					data.resFrames[fn] = resFrame;
				}
				break;
			}
			case FishManage::FileExtensions::atlas:
				// todo
				break;
			case FishManage::FileExtensions::c3b:
				// todo
				break;
			case FishManage::FileExtensions::fnt:
				// todo
				break;
			}
		}
	}


	// 加载首页
	Welcome();

	// 做点测试
	Init2();

	return true;
}
