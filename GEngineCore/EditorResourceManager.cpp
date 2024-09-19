#include "pch.h"
#include "EditorResourceManager.h"
#include "Utils.h"
#include <random>

NAMESPACE_OPEN(GEngine::Editor)

using namespace GEngine;

void EditorResourceManager::Init(const String& path)
{
	std::filesystem::path resourcePath(ResourcePath);
	std::unordered_map<std::string, std::filesystem::path> original;
	std::unordered_map<std::string, std::filesystem::path> meta;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(resourcePath))
	{
		auto ext = entry.path().extension().string();
		auto filename = entry.path().filename().string();

		if (ext.compare(ResourceImporter::META_EXTENSION) == 0)
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
			AddNewResource(kv.second.wstring());
		}
	}

	// discard un-use meta file with left elements in meta
	for (const auto& kv : meta)
	{
		std::filesystem::remove(kv.second);
	}
}

void EditorResourceManager::AddNewResource(const String& path)
{
	// check extension
	FileType fType = GetFileType_x(path);
	if (fType == FileType::NotExist) return;

	ImporterType iType = ResourceImporter::GetImporterType(fType);
	auto rfid = get_Rfid(path);

	switch (fType)
	{
	case GEngine::FileType::Directory:
		addNewResource<DefaultImporter>(path, fType, rfid);
		break;
	case GEngine::FileType::Texture_PNG:
	case GEngine::FileType::Texture_BMP:
	case GEngine::FileType::Texture_JPG:
		addNewResource<TextureImporter>(path, fType, rfid);
		break;
	case GEngine::FileType::Audio_MP3:
	case GEngine::FileType::Audio_WAV:
	case GEngine::FileType::Audio_FLAC:
		addNewResource<AudioImporter>(path, fType, rfid);
		break;
	case GEngine::FileType::GameObject_Prefab:
		addNewResource<NativeImporter>(path, fType, rfid);
		break;
	case GEngine::FileType::Other:
	case GEngine::FileType::NotExist:
	default:
		break;
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