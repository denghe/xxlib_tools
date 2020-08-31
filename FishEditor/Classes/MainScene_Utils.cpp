#include "MainScene.h"
#include "md5.h"
#include <regex>

// out len == 16
void MainScene::CalcMD5(void* const& buf, size_t const& len, void* out) {
	MD5_CTX c;
	MD5_Init(&c);
	MD5_Update(&c, buf, len);
	MD5_Final((unsigned char*)out, &c);
}

// ɨ�� plist ��� texture
std::string MainScene::GetPListTextureName(std::string const& plistFileName) {
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
std::vector<std::string> MainScene::GetPListItems(std::string const& plistFileName) {
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

// ��ȡ spine �ļ������ĵ� .json/.skel �Ͱ�������ͼ�ļ����б�
std::vector<std::string> MainScene::GetAtlasResNames(std::string const& atlasFileName) {
	std::vector<std::string> rtv;
	// json/skel �ļ����ļ���������ͬ, ��չ����ͬ
	std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(atlasFileName);
	auto&& basePath = fullPath.substr(0, fullPath.size() - 5);
	if (std::filesystem::exists(basePath + "json")) {
		rtv.emplace_back(atlasFileName.substr(0, atlasFileName.size() - 5) + "json");
	}
	else if (std::filesystem::exists(basePath + "skel")) {
		rtv.emplace_back(atlasFileName.substr(0, atlasFileName.size() - 5) + "skel");
	}
	else {
		throw std::logic_error(xx::ToString("can't find spine's .json or .skel file: ", atlasFileName));
	}

	// atlas �ļ����� �� 2 �������õ���ͼƬ�ļ���
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

// ��ȡ c3b ��������ͼ�ļ����б� & ����+ʱ�� �б�
std::pair<std::vector<std::string>, std::vector<std::pair<std::string, float>>> MainScene::GetC3bResNamesAnimations(std::string const& c3bFileName) {
	// c3b ���ݸ�ʽ��"C3B\0" + �汾��(1�ֽ�)*2 + ���ø���(4�ֽ�) for( ����id(string:����4�ֽ�+����) + ����(4�ֽ�) + ƫ��(4�ֽ�) )
	// ����ֻ���� ���� == BUNDLE_TYPE_MATERIAL( 16 ), BUNDLE_TYPE_ANIMATIONS( 3 ) �����á�
	// ����16: ֱ����ת����Ӧƫ�� �������������ʸ���(4�ֽ�) for( ����id(string) + float(4�ֽ�)*14 + ��ͼ����(4�ֽ�) for( ��ͼ��ϸ ) )
	// float(4�ֽ�)*14 = diffuse(3) + ambient(3) + emissive(3) + opacity(1) + specular(3) + shininess(1)
	// ��ͼ��ϸ = ��ͼid(string) + ��ͼ�ļ���(string) + uvӳ��(float*4) + GL��ͼ����(string) + wrapS(string) + wrapT(string)
	// ����3: ֱ����ת����Ӧƫ�� ������������������(4�ֽ�) for( ����id(string) + totalTime(float) 
	// + nodeCount(uint) for ( boneName(string) + keyframeCount(uint) for ( keytime(float) + rotate(float*4) + scale(float*3) + position(float*3)
	// todo: ��ͨ�� mesh ���ж������ AABB ( ����Ҫ��ע��mesh ), �������ܹ������ųߴ�. ����ֱ��ͨ�� Bundle3D ������أ�Ȼ����� MeshData ?
	std::pair<std::vector<std::string>, std::vector<std::pair<std::string, float>>> rtv;
	xx::Data d;
	xx::ReadAllBytes(cocos2d::FileUtils::getInstance()->fullPathForFilename(c3bFileName), d);
	xx::DataReader dr(d);
	// Ū�����ִ��ĳ��ú���
	auto&& ReadString = [&](std::string& out)->int {
		uint32_t len = 0;
		if (int r = dr.ReadFixed(len)) return r;
		if (len + dr.offset > dr.len) return -1;
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
						rtv.first.emplace_back(std::move(textureFileName));	// ���뷵������
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
		else if (referenceType == 3) {
			// ���� == BUNDLE_TYPE_ANIMATIONS, ��ʱ����ȥ��, ���ݶ�ȡƫ��
			auto offsetBak = std::exchange(dr.offset, referenceOffset);
			{
				uint32_t animationCount = 0;
				if (dr.ReadFixed(animationCount) || !animationCount) throw std::logic_error("read c3b animation Count error.");
				for (uint32_t j = 0; j < animationCount; ++j) {
					std::string animationId;
					if (ReadString(animationId) || animationId.empty()) throw std::logic_error("read c3b animation Id error.");
					float totalTime = 0;
					if (dr.ReadFixed(totalTime)) throw std::logic_error("read c3b animation totalTime error.");
					rtv.second.emplace_back(animationId, totalTime);
					uint32_t nodeCount = 0;
					if (dr.ReadFixed(nodeCount) || !nodeCount) throw std::logic_error("read c3b animation node Count error.");
					for (uint32_t k = 0; k < nodeCount; ++k) {
						std::string boneName;
						if (ReadString(boneName)) throw std::logic_error("read c3b animation node boneName error.");
						uint32_t keyframeCount = 0;
						if (dr.ReadFixed(keyframeCount)) throw std::logic_error("read c3b animation node keyframeCount error.");
						for (uint32_t L = 0; L < keyframeCount; ++L) {
							float keytime = 0;
							if (dr.ReadFixed(keytime)) throw std::logic_error("read c3b animation node keytime error.");
							float rotate[4]{};
							if (dr.ReadFixed(rotate)) throw std::logic_error("read c3b animation node rotate error.");
							float scale[3]{};
							if (dr.ReadFixed(scale)) throw std::logic_error("read c3b animation node scale error.");
							float position[3]{};
							if (dr.ReadFixed(position)) throw std::logic_error("read c3b animation node position error.");
						}
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
std::vector<std::string> MainScene::GetFntResNames(std::string const& fntFileName) {
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

// ��ȡ spine �� animations name & ����ʱ��
std::vector<std::pair<std::string, float>> MainScene::GetSpineAnimationNamesSeconds(std::string const& spineFileName) {
	//// ���� spine �࣬Ȼ��ͨ�����Դ���������ȡ��Щ��Ϣ
	//spine::SkeletonAnimation* a;
	//if (f->childs[0]->ext == FishManage::FileExtensions::json) {
	//	a = spine::SkeletonAnimation::createWithJsonFile(f->childs[0]->name, f->name);
	//}
	//else {
	//	a = spine::SkeletonAnimation::createWithBinaryFile(f->childs[0]->name, f->name);
	//}
	//if (!a) {
	//	throw std::logic_error(xx::ToString("GetSpineAnimationNamesSeconds create spine failed. fn = ", f->name));
	//}
	std::vector<std::pair<std::string, float>> rtv;
	//for (int i = 0; i < a->getSkeleton()->data->animationsCount; ++i) {
	//	auto&& ani = a->getSkeleton()->data->animations[i];
	//	rtv.emplace_back(ani->name, ani->duration);
	//}
	return rtv;
}
