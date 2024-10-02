#include "pch.h"
#include "EditorResourceManager.h"
#include "Utils.h"
#include <random>
#include <filesystem>

NAMESPACE_OPEN(GEngine::Editor)

using namespace GEngine;

String EditorResourceManager::s_resourceFilePath = L"";

void EditorResourceManager::Init(const String& path)
{
	s_resourceFilePath = path;

	std::filesystem::path resourcePath(s_resourceFilePath);
	std::unordered_map<String, std::filesystem::path> original;
	std::unordered_map<String, std::filesystem::path> meta;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(resourcePath))
	{
		auto ext = entry.path().extension().wstring();
		auto filename = entry.path().filename().stem().wstring();
		if (ext.compare(ResourceImporter::META_EXTENSION_W) == 0)
		{
			meta[filename] = entry.path();
		}
		else
		{
			original[filename] = entry.path();
		}
	}

	for (const auto& kv : original)
	{
		// if the meta file of original exists, erase and continue the loop
		if (meta.erase(kv.first) == 1) continue;
		// otherwise, create new one
		else
		{
			ImportNewResource(kv.second.wstring());
		}
	}

	// discard un-use meta file with left elements in meta
	for (const auto& kv : meta)
	{
		std::filesystem::remove(kv.second);
	}
}


bool EditorResourceManager::ImportNewResource(const String& path)
{
	// check extension
	FileType fType = GetFileType_x(path);
	if (fType == FileType::NotExist) return false;

	auto rfid = get_Rfid(path);

	switch (fType)
	{
	case GEngine::FileType::Directory:
		return import_new_resource<DefaultImporter>(path, rfid);
	case GEngine::FileType::Texture_PNG:
	case GEngine::FileType::Texture_BMP:
	case GEngine::FileType::Texture_JPG:
		return import_new_resource<TextureImporter>(path, rfid);
	case GEngine::FileType::Audio_MP3:
	case GEngine::FileType::Audio_WAV:
	case GEngine::FileType::Audio_FLAC:
		return import_new_resource<AudioImporter>(path, rfid);
		break;
	case GEngine::FileType::GameObject_Prefab:
		return import_new_resource<NativeImporter>(path, rfid);
		break;
	case GEngine::FileType::Other:
		return import_new_resource<DefaultImporter>(path, rfid);
	case GEngine::FileType::NotExist:
		return false;
	default:
		return false;
	}
}


RESOURCE_FILE_ID EditorResourceManager::get_Rfid(const String& path)
{
	// atode path의 트리 구조에 기반하여 생성
	// TEMP
	std::random_device rd;
	std::mt19937 gen(rd());
	auto a = (unsigned long long) gen();
	return std::to_string(a);

}






NAMESPACE_CLOSE