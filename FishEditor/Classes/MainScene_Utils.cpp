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

// 扫出 plist 里的 texture
std::string MainScene::GetPListTextureName(std::string const& plistFileName) {
	auto&& fu = cocos2d::FileUtils::getInstance();

	// 写法确保与 addSpriteFramesWithFile 函数内部一致
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

// 扫出 plist 里的 sprite frame names
std::vector<std::string> MainScene::GetPListItems(std::string const& plistFileName) {
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

	//// 排序( 如果含有数字，以其中的数字部分大小来排 )
	//std::sort(names.begin(), names.end(), [](std::string const& a, std::string const& b)->bool {
	//	return xx::InnerNumberToFixed(a) < xx::InnerNumberToFixed(b);
	//	});

	return names;
}

// 获取 spine 文件关联的的 .json/.skel 和包含的贴图文件名列表
std::vector<std::string> MainScene::GetAtlasResNames(std::string const& atlasFileName) {
	std::vector<std::string> rtv;
	// json/skel 文件的文件名部分相同, 扩展名不同
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

	// atlas 文件内容 第 2 行是引用到的图片文件名
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

// 获取 c3b 包含的贴图文件名列表 & 动作+时长 列表
std::pair<std::vector<std::string>, std::vector<std::pair<std::string, float>>> MainScene::GetC3bResNamesAnimations(std::string const& c3bFileName) {
	// c3b 数据格式："C3B\0" + 版本号(1字节)*2 + 引用个数(4字节) for( 引用id(string:长度4字节+内容) + 类型(4字节) + 偏移(4字节) )
	// 这里只关心 类型 == BUNDLE_TYPE_MATERIAL( 16 ), BUNDLE_TYPE_ANIMATIONS( 3 ) 的引用。
	// 类型16: 直接跳转到相应偏移 并继续读：材质个数(4字节) for( 材质id(string) + float(4字节)*14 + 贴图个数(4字节) for( 贴图明细 ) )
	// float(4字节)*14 = diffuse(3) + ambient(3) + emissive(3) + opacity(1) + specular(3) + shininess(1)
	// 贴图明细 = 贴图id(string) + 贴图文件名(string) + uv映射(float*4) + GL贴图类型(string) + wrapS(string) + wrapT(string)
	// 类型3: 直接跳转到相应偏移 并继续读：动画个数(4字节) for( 动画id(string) + totalTime(float) 
	// + nodeCount(uint) for ( boneName(string) + keyframeCount(uint) for ( keytime(float) + rotate(float*4) + scale(float*3) + position(float*3)
	// todo: 可通过 mesh 所有顶点求得 AABB ( 不需要关注子mesh ), 这样就能估算缩放尺寸. 或者直接通过 Bundle3D 组件加载，然后读其 MeshData ?
	std::pair<std::vector<std::string>, std::vector<std::pair<std::string, float>>> rtv;
	xx::Data d;
	xx::ReadAllBytes(cocos2d::FileUtils::getInstance()->fullPathForFilename(c3bFileName), d);
	xx::DataReader dr(d);
	// 弄个读字串的常用函数
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
		// 引用id(string:长度4字节+内容) + 类型(4字节) + 偏移(4字节)
		std::string referenceId;
		if (ReadString(referenceId) || referenceId.empty()) throw std::logic_error("read c3b reference Id error.");
		uint32_t referenceType = 0;
		if (dr.ReadFixed(referenceType)) throw std::logic_error("read c3b reference Type error.");
		uint32_t referenceOffset = 0;
		if (dr.ReadFixed(referenceOffset)) throw std::logic_error("read c3b reference Offset error.");
		if (referenceType == 16) {
			// 类型 == BUNDLE_TYPE_MATERIAL, 临时跳过去读, 备份读取偏移
			auto offsetBak = std::exchange(dr.offset, referenceOffset);
			{
				uint32_t meterialCount = 0;
				if (dr.ReadFixed(meterialCount)) throw std::logic_error("read c3b meterial Count error.");
				for (uint32_t j = 0; j < meterialCount; ++j) {
					// 材质id(string) + float(4字节)*14 + 贴图个数(4字节) for( 贴图明细 )
					std::string meterialId;
					if (ReadString(meterialId) || meterialId.empty()) throw std::logic_error("read c3b meterial Id error.");
					float args[14];
					if (dr.ReadFixed(args)) throw std::logic_error("read c3b meterial( diffuse, ambient, ...... ) error.");
					uint32_t textureCount = 0;
					if (dr.ReadFixed(textureCount)) throw std::logic_error("read c3b texture Count error.");
					for (uint32_t k = 0; k < textureCount; ++k) {
						// 贴图id(string) + 贴图文件名(string) + uv映射(float*4) + GL贴图类型(string) + wrapS(string) + wrapT(string)
						std::string textureId;
						if (ReadString(textureId) || textureId.empty()) throw std::logic_error("read c3b texture Id error.");
						std::string textureFileName;
						if (ReadString(textureFileName) || textureFileName.empty()) throw std::logic_error("read c3b texture FileName error.");
						rtv.first.emplace_back(std::move(textureFileName));	// 放入返回容器
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
			// 还原读取偏移
			dr.offset = offsetBak;
		}
		else if (referenceType == 3) {
			// 类型 == BUNDLE_TYPE_ANIMATIONS, 临时跳过去读, 备份读取偏移
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
			// 还原读取偏移
			dr.offset = offsetBak;
		}
	}
	return rtv;
}


// 获取 fnt 包含的贴图文件名列表
std::vector<std::string> MainScene::GetFntResNames(std::string const& fntFileName) {
	// 从第三行开始，含图片文件名的内容长相如下：( 找出所有 file="" )
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

// 获取 spine 的 animations name & 播放时长
std::vector<std::pair<std::string, float>> MainScene::GetSpineAnimationNamesSeconds(std::string const& spineFileName) {
	//// 创建 spine 类，然后通过它自带函数来获取这些信息
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
