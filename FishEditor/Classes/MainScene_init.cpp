#include "MainScene.h"
#include "md5.h"
#include <regex>

// out len == 16
void CalcMD5(void* const& buf, size_t const& len, void* out) {
	MD5_CTX c;
	MD5_Init(&c);
	MD5_Update(&c, buf, len);
	MD5_Final((unsigned char*)out, &c);
}

// ɨ�� plist ��� texture
std::string GetPListTextureName(std::string const& plistFileName) {
	auto&& fu = cocos2d::FileUtils::getInstance();

	// д��ȷ���� addSpriteFramesWithFile �����ڲ�һ��
	std::string fullPath = fu->fullPathForFilename(plistFileName);
	auto&& dict = fu->getValueMapFromFile(fullPath);

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
	return fu->fullPathForFilename(texturePath);
}

// ɨ�� plist ��� sprite frame names
std::vector<std::string> GetPListItems(std::string const& plistFileName) {
	std::vector<std::string> names;
	auto&& fu = cocos2d::FileUtils::getInstance();

	// д��ȷ���� addSpriteFramesWithFile �����ڲ�һ��
	std::string fullPath = fu->fullPathForFilename(plistFileName);
	auto&& dict = fu->getValueMapFromFile(fullPath);

	auto&& framesDict = dict["frames"].asValueMap();
	for (auto&& iter : framesDict) {
		auto&& frameDict = iter.second.asValueMap();
		names.push_back(iter.first);
	}

	//// ����( ����������֣������е����ֲ��ִ�С���� )
	//std::sort(names.begin(), names.end(), [](std::string const& a, std::string const& b)->bool {
	//	return xx::InnerNumberToFixed(a) < xx::InnerNumberToFixed(b);
	//	});

	return names;
}

// ��ȡ spine �ļ������ĵ� .json �Ͱ�������ͼ�ļ����б�
std::vector<std::string> GetAtlasResNames(std::string const& atlasFileName) {
	std::vector<std::string> rtv;
	// json �ļ����ļ���������ͬ, ��չ����ͬ
	auto&& jsonFileName = rtv.emplace_back();
	jsonFileName.assign(atlasFileName.data(), atlasFileName.size() - 6);
	jsonFileName.append(".json");

	// atlas �ļ����� �� 2 �������õ���ͼƬ�ļ���
	std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(atlasFileName);
	xx::Data d;
	xx::ReadAllBytes(fullPath, d);
	uint32_t from = 0;
	for (; from < d.len; ++from) {
		if (d.buf[from] != '\r' && d.buf[from] != '\n') break;
	}
	uint32_t to = from + 1;
	for (; to < d.len; ++to) {
		if (d.buf[to] == '\r' || d.buf[to] == '\n') break;
	}
	auto&& textureFileName = rtv.emplace_back();
	textureFileName.assign(d.buf + from, to - from);
	return rtv;
}

// ��ȡ c3b ��������ͼ�ļ����б�
std::vector<std::string> GetC3bResNames(std::string const& c3bFileName) {
	// c3b ���ݸ�ʽ��"C3B\0" + �汾��(1�ֽ�)*2 + ���ø���(4�ֽ�) for( ����id(string:����4�ֽ�+����) + ����(4�ֽ�) + ƫ��(4�ֽ�) )
	// ����ֻ���� ���� == BUNDLE_TYPE_MATERIAL( 16 ) �����á�
	// ֱ����ת����Ӧƫ�� �������������ʸ���(4�ֽ�) for( ����id(string) + float(4�ֽ�)*14 + ��ͼ����(4�ֽ�) for( ��ͼ��ϸ ) )
	// float(4�ֽ�)*14 = diffuse(3) + ambient(3) + emissive(3) + opacity(1) + specular(3) + shininess(1)
	// ��ͼ��ϸ = ��ͼid(string) + ��ͼ�ļ���(string) + uvӳ��(float*4) + GL��ͼ����(string) + wrapS(string) + wrapT(string)
	std::vector<std::string> rtv;
	xx::Data d;
	xx::ReadAllBytes(cocos2d::FileUtils::getInstance()->fullPathForFilename(c3bFileName), d);
	xx::DataReader dr(d);
	// Ū�����ִ��ĳ��ú���
	auto&& ReadString = [&](std::string& out)->int {
		uint32_t len = 0;
		if (int r = dr.ReadFixed(len)) return r;
		out.resize(len);
		return dr.ReadBuf(out.data(), len);
	};
	char head[4];
	if (dr.ReadFixed(head) || memcmp(head, "C3B", sizeof(head))) throw std::logic_error("read c3b header error.");
	char ver[2];
	if (dr.ReadFixed(ver) || ver[0] != 0 || ver[1] != 3) throw std::logic_error("read c3b version error.");
	uint32_t referenceCount = 0;
	if (dr.ReadFixed(referenceCount)) throw std::logic_error("read c3b reference Count error.");
	for (uint32_t i = 0; i < referenceCount; ++i) {
		// ����id(string:����4�ֽ�+����) + ����(4�ֽ�) + ƫ��(4�ֽ�)
		std::string referenceId;
		if (ReadString(referenceId) || referenceId.empty()) throw std::logic_error("read c3b reference Id error.");
		uint32_t referenceType = 0;
		if (dr.ReadFixed(referenceType)) throw std::logic_error("read c3b reference Type error.");
		uint32_t referenceOffset = 0;
		if (dr.ReadFixed(referenceOffset)) throw std::logic_error("read c3b reference Offset error.");
		if (referenceType == 16) {
			// ���� == BUNDLE_TYPE_MATERIAL, ��ʱ����ȥ��, ���ݶ�ȡƫ��
			auto offsetBak = std::exchange(dr.offset, referenceOffset);
			{
				uint32_t meterialCount = 0;
				if (dr.ReadFixed(meterialCount)) throw std::logic_error("read c3b meterial Count error.");
				for (uint32_t j = 0; j < meterialCount; ++j) {
					// ����id(string) + float(4�ֽ�)*14 + ��ͼ����(4�ֽ�) for( ��ͼ��ϸ )
					std::string meterialId;
					if (ReadString(meterialId) || meterialId.empty()) throw std::logic_error("read c3b meterial Id error.");
					float args[14];
					if (dr.ReadFixed(args)) throw std::logic_error("read c3b meterial( diffuse, ambient, ...... ) error.");
					uint32_t textureCount = 0;
					if (dr.ReadFixed(textureCount)) throw std::logic_error("read c3b texture Count error.");
					for (uint32_t k = 0; k < textureCount; ++k) {
						// ��ͼid(string) + ��ͼ�ļ���(string) + uvӳ��(float*4) + GL��ͼ����(string) + wrapS(string) + wrapT(string)
						std::string textureId;
						if (ReadString(textureId) || textureId.empty()) throw std::logic_error("read c3b texture Id error.");
						std::string textureFileName;
						if (ReadString(textureFileName) || textureFileName.empty()) throw std::logic_error("read c3b texture FileName error.");
						rtv.emplace_back(std::move(textureFileName));	// ���뷵������
						float textureUV[4];
						if (dr.ReadFixed(textureUV)) throw std::logic_error("read c3b texture uvmapping error.");
						std::string textureGLType;
						if (ReadString(textureGLType) || textureGLType.empty()) throw std::logic_error("read c3b texture GLType error.");
						std::string textureWrapS;
						if (ReadString(textureWrapS) || textureWrapS.empty()) throw std::logic_error("read c3b texture wrapS error.");
						std::string textureWrapT;
						if (ReadString(textureWrapT) || textureWrapT.empty()) throw std::logic_error("read c3b texture wrapT error.");
					}
				}
			}
			// ��ԭ��ȡƫ��
			dr.offset = offsetBak;
		}
	}
	return rtv;
}


// ��ȡ fnt ��������ͼ�ļ����б�
std::vector<std::string> GetFntResNames(std::string const& fntFileName) {
	// �ӵ����п�ʼ����ͼƬ�ļ��������ݳ������£�( �ҳ����� file="" )
	// page id=0 file="a_0.png"
	// page id=1 file="a_1.png"
	std::vector<std::string> rtv;
	xx::Data d;
	xx::ReadAllBytes(cocos2d::FileUtils::getInstance()->fullPathForFilename(fntFileName), d);
	std::string s(d.buf, d.len);
	std::regex r("file=\"(.*)\"");
	std::smatch m;
	for (auto&& iter = s.cbegin(); std::regex_search(iter, s.cend(), m, r); iter = m[0].second) {
		rtv.push_back(m[1]);
	}
	return rtv;
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



	// ע������ļ����ݽṹ
	FishManage::PkgGenTypes::RegisterTo(oh);

	// ���ش����ļ�( ����еĻ� )
	LoadData();

	// ��λ�� root path
	auto&& sps = cocos2d::FileUtils::getInstance()->getSearchPaths();
	assert(sps.size() == 1);
	resPath = sps[0];


	// �����ļ����γ� File list��Ȼ��� data.files �Ա�. �����Ƿ���ڲ���. ������ͬ�����Ƴ������˵��ļ�������µ��ļ���ͬ���ļ�������ݲ�ͬ������

	// ��֪��չ��ӳ��
	std::unordered_map<std::string, FishManage::FileExtensions> exts
	{
		{ "mp3", FishManage::FileExtensions::mp3   },
		{ "ogg", FishManage::FileExtensions::ogg   },
		{ "wav", FishManage::FileExtensions::wav   },

		{ "webp", FishManage::FileExtensions::webp  },
		{ "png", FishManage::FileExtensions::png   },
		{ "pkm", FishManage::FileExtensions::pkm   },
		{ "jpg", FishManage::FileExtensions::jpg   },
		{ "tga", FishManage::FileExtensions::tga   },
		{ "bmp", FishManage::FileExtensions::bmp   },

		{ "plist", FishManage::FileExtensions::plist },

		{ "atlas", FishManage::FileExtensions::atlas },
		{ "json", FishManage::FileExtensions::json  },

		{ "c3b", FishManage::FileExtensions::c3b   },

		{ "lua", FishManage::FileExtensions::lua   },

		{ "fnt", FishManage::FileExtensions::fnt   },
	};

	// ������֪��չ����������ļ���Ϣ����
	std::map<std::string, std::shared_ptr<FishManage::File_Real>> files;
	xx::Data d;

	// ��� resPath ������Ŀ¼�ļ�ö����
	std::filesystem::recursive_directory_iterator filesIterator(resPath);

	// ��ʼɨ�ļ������� File_Real ����, ��䵽 files
	for (auto&& item : filesIterator) {
		// �����ļ�
		if (!item.is_regular_file()) continue;

		// û����չ��
		auto&& path = item.path();
		if (!path.has_extension()) continue;

		// δ֪��չ��
		auto&& extStr = path.extension().string().substr(1);
		auto&& iter = exts.find(extStr);
		if (iter == exts.end()) continue;
		auto&& ext = iter->second;

		// �и�� ��path + name.ext
		auto&& name = path.string().substr(resPath.size());

		// ������չ��·�ɴ�����ͬ�� File_Xxxxxx
		std::shared_ptr<FishManage::File_Real> file;
		switch (ext) {
		case FishManage::FileExtensions::mp3:
		case FishManage::FileExtensions::ogg:
		case FishManage::FileExtensions::wav: {
			auto&& o = xx::Make<FishManage::File_Sound>();
			file = o;
			// o->seconds = ????
			break;
		}
		case FishManage::FileExtensions::webp:
		case FishManage::FileExtensions::png:
		case FishManage::FileExtensions::jpg:
		case FishManage::FileExtensions::pkm:
		case FishManage::FileExtensions::tga:
		case FishManage::FileExtensions::bmp: {
			file = xx::Make<FishManage::File_Picture>();
			// atPList �����������
			break;
		}
		case FishManage::FileExtensions::atlas: {
			file = xx::Make<FishManage::File_Spine>();
			break;
		}
		case FishManage::FileExtensions::json: {
			file = xx::Make<FishManage::File_Real>();
			break;
		}
		case FishManage::FileExtensions::c3b: {
			file = xx::Make<FishManage::File_C3b>();
			break;
		}
		case FishManage::FileExtensions::plist:
		case FishManage::FileExtensions::fnt: {
			file = xx::Make<FishManage::File_Bag>();
			break;
		}
		case FishManage::FileExtensions::lua: {
			file = xx::Make<FishManage::File_Lua>();
			break;
		}
		default:
			throw std::logic_error(xx::ToString("unknown ext type: ", extStr));
		}

		// ��� �����ļ���Ϣ. ��ĺ������
		file->name = name;
		file->ext = ext;
		file->length = item.file_size();
		xx::ReadAllBytes(path, d);
		file->md5.Resize(16);
		CalcMD5(d.buf, d.len, file->md5.buf);
		files[name] = file;
	}
	d.Clear(true);

	// ��ɾ���б�
	std::vector<std::string> dels;
	std::map<std::string, std::string> framePlistMap;

	// �鲢���ӹ�ϵ���ļ�. ����ض���չ��
	for (auto&& kv : files) {
		auto&& file = kv.second;
		auto&& fileName = kv.first;
		switch (file->ext) {
		case FishManage::FileExtensions::plist: {
			// ����ͼ���ҵ� file �鲢�� childs
			auto&& textureName = GetPListTextureName(fileName).substr(resPath.size());
			auto&& textureIter = files.find(textureName);
			if (textureIter == files.end()) {
				throw std::logic_error(xx::ToString("can't find texture name: ", textureName, " for plist file: ", fileName));
			}
			xx::As<FishManage::File_Bag>(file)->childs.push_back(textureIter->second);
			dels.push_back(textureName);

			// ��ͼ�����ҵ� file ������ mapTo
			auto&& frames = GetPListItems(fileName);
			for (auto&& frame : frames) {
				// �� plist ��ͼ���������ֵ䣬�Լ���Ƿ����ظ��Ĵ��ڣ�cocos sprite frame engine ��֧���ظ���
				if (framePlistMap.find(frame) != framePlistMap.end()) {
					throw std::logic_error(xx::ToString("duplicate sprite frame name: ", frame, " at plist file: ", fileName, " with plist file:", framePlistMap[frame]));
				}
				framePlistMap.emplace(frame, fileName);

				// Ѱ��ͬ����ͼ����Ӧ
				auto&& picIter = files.find(frame);
				if (picIter != files.end()) {
					xx::As<FishManage::File_Picture>(picIter->second)->atPList = xx::As<FishManage::File_Bag>(file);
				}
				// else �����ͼ���Ӧ�ĵ�ͼ�Ҳ�����
			}
			break;
		}
		case FishManage::FileExtensions::atlas: {
			auto&& ns = GetAtlasResNames(fileName);
			for (auto&& n : ns) {
				auto&& iter = files.find(n);
				if (iter == files.end()) {
					throw std::logic_error(xx::ToString("can't find name: ", n, " for atlas file: ", fileName));
				}
				xx::As<FishManage::File_Bag>(file)->childs.push_back(iter->second);
				dels.push_back(n);
			}
			break;
		}
		case FishManage::FileExtensions::c3b: {
			auto&& ns = GetC3bResNames(fileName);
			for (auto&& n : ns) {
				auto&& iter = files.find(n);
				if (iter == files.end()) {
					throw std::logic_error(xx::ToString("can't find name: ", n, " for c3b file: ", fileName));
				}
				xx::As<FishManage::File_Bag>(file)->childs.push_back(iter->second);
				dels.push_back(n);
			}
			break;
		}
		case FishManage::FileExtensions::fnt: {
			auto&& ns = GetFntResNames(fileName);
			for (auto&& n : ns) {
				auto&& iter = files.find(n);
				if (iter == files.end()) {
					throw std::logic_error(xx::ToString("can't find name: ", n, " for fnt file: ", fileName));
				}
				xx::As<FishManage::File_Bag>(file)->childs.push_back(iter->second);
				dels.push_back(n);
			}
			break;
		}
		}
	}

	for (auto&& o : dels) {
		files.erase(o);
	}
	dels.clear();

	// files �� data.files ���Ա�, �������. 1. ɾ�������˵�    2. ����ͬ����      3. ���������
	// 1. ɾ�������˵�
	for (auto&& iter = data.files.begin(); iter != data.files.end();) {
		if (files.find(iter->first) != files.end()) {
			++iter;
		}
		else {
			iter = data.files.erase(iter);
		}
	}

	// 2. ����ͬ����( ���������������� ��
	for (auto&& kv : data.files) {
		auto&& oldFile = kv.second;
		auto&& newFile = files[kv.first];
		if (oldFile->GetTypeId() != newFile->GetTypeId()) {
			oldFile = newFile;
		}
		else {
			switch (oldFile->ext) {
			case FishManage::FileExtensions::mp3:
			case FishManage::FileExtensions::ogg:
			case FishManage::FileExtensions::wav: {
				auto&& o = xx::As<FishManage::File_Sound>(oldFile);
				auto&& n = xx::As<FishManage::File_Sound>(newFile);
				if (o->length == n->length && o->md5 == n->md5) continue;
				o->length = n->length;
				o->md5 = n->md5;
				// seconds ������
				break;
			}
			case FishManage::FileExtensions::webp:
			case FishManage::FileExtensions::png:
			case FishManage::FileExtensions::jpg:
			case FishManage::FileExtensions::pkm:
			case FishManage::FileExtensions::tga:
			case FishManage::FileExtensions::bmp: {
				auto&& o = xx::As<FishManage::File_Picture>(oldFile);
				auto&& n = xx::As<FishManage::File_Picture>(newFile);
				if (o->length == n->length && o->md5 == n->md5) continue;
				o->length = n->length;
				o->md5 = n->md5;
				o->atPList = n->atPList;
				break;
			}
			case FishManage::FileExtensions::atlas: {
				auto&& o = xx::As<FishManage::File_Spine>(oldFile);
				auto&& n = xx::As<FishManage::File_Spine>(newFile);
				if (o->length == n->length && o->md5 == n->md5) continue;
				o->length = n->length;
				o->md5 = n->md5;
				o->childs = n->childs;
				// todo: �Ա� actions �������
				break;
			}
			case FishManage::FileExtensions::json: {
				auto&& o = xx::As<FishManage::File_Real>(oldFile);
				auto&& n = xx::As<FishManage::File_Real>(newFile);
				oh.Clone(n, o);
				break;
			}
			case FishManage::FileExtensions::c3b: {
				auto&& o = xx::As<FishManage::File_C3b>(oldFile);
				auto&& n = xx::As<FishManage::File_C3b>(newFile);
				if (o->length == n->length && o->md5 == n->md5) continue;
				o->length = n->length;
				o->md5 = n->md5;
				o->childs = n->childs;
				// todo: �Ա� actions �������
				break;
			}
			case FishManage::FileExtensions::plist:
			case FishManage::FileExtensions::fnt: {
				auto&& o = xx::As<FishManage::File_Bag>(oldFile);
				auto&& n = xx::As<FishManage::File_Bag>(newFile);
				oh.Clone(n, o);
				break;
			}
			case FishManage::FileExtensions::lua: {
				auto&& o = xx::As<FishManage::File_Lua>(oldFile);
				auto&& n = xx::As<FishManage::File_Lua>(newFile);
				oh.Clone(n, o);
				break;
			}
			default:
				throw std::logic_error(xx::ToString("unknown ext type: ", (int)oldFile->ext));
			}
		}
	}

	// 3. ���������
	for (auto&& kv : files) {
		data.files.emplace(kv.first, kv.second);
	}

	// ����
	SaveData();


	// ������ҳ
	Welcome();

	// �������
	Init2();

	return true;
}
