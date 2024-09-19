#pragma once

#include "CoreHeader.h"
#include "ResourceImporter.h"

NAMESPACE_OPEN(GEngine::Editor)

using namespace GEngine;

class EditorResourceManager
{
public:
	static constexpr auto ResourcePath = L"..\\Resources";

public:
	static void Init(const String& path = ResourcePath);

	static void AddNewResource(const String& path);

	template<typename Imp> requires std::derived_from<Imp, ResourceImporter>
	static void addNewResource(const String& path, const FileType fType, const RESOURCE_FILE_ID& rfid);

	template<>
	static void addNewResource<DefaultImporter>(const String& path, const FileType fType, const RESOURCE_FILE_ID& rfid);

	template<>
	static void addNewResource<TextureImporter>(const String& path, const FileType fType, const RESOURCE_FILE_ID& rfid);

	template<>
	static void addNewResource<AudioImporter>(const String& path, const FileType fType, const RESOURCE_FILE_ID& rfid);

	template<>
	static void addNewResource<NativeImporter>(const String& path, const FileType fType, const RESOURCE_FILE_ID& rfid);

private:
	static RESOURCE_FILE_ID get_Rfid(const String& path);
};


template<typename Imp> requires std::derived_from<Imp, ResourceImporter>
inline void EditorResourceManager::addNewResource(const String& path, const FileType fType, const RESOURCE_FILE_ID& rfid)
{
	DefaultImporter importer;
	importer.SetResourceFileId(rfid);
	importer.SetExtension(std::filesystem::path(path).extension().string()); // e.g. ".png")
	importer.SaveMetaData(path);
}

template<>
inline void EditorResourceManager::addNewResource<DefaultImporter>(const String& path, const FileType fType, const RESOURCE_FILE_ID& rfid)
{
	DefaultImporter importer;
	importer.SetResourceFileId(rfid);
	importer.SetExtension(std::filesystem::path(path).extension().string());
	if(fType == FileType::Directory) importer.SetFolder();
	importer.SaveMetaData(path);
}

template<>
inline void EditorResourceManager::addNewResource<TextureImporter>(const String& path, const FileType fType, const RESOURCE_FILE_ID& rfid)
{
	TextureImporter importer;
	importer.SetResourceFileId(rfid);
	importer.SetExtension(std::filesystem::path(path).extension().string());
	importer.SetTextureType(ToTextureType(fType));
	importer.SaveMetaData(path);
}

template<>
inline void EditorResourceManager::addNewResource<AudioImporter>(const String& path, const FileType fType, const RESOURCE_FILE_ID& rfid)
{
	AudioImporter importer;
	importer.SetResourceFileId(rfid);
	importer.SetExtension(std::filesystem::path(path).extension().string());
	importer.SetAudioType(ToAudioType(fType));
	importer.SaveMetaData(path);
}

template<>
inline void EditorResourceManager::addNewResource<NativeImporter>(const String& path, const FileType fType, const RESOURCE_FILE_ID& rfid)
{
	NativeImporter importer;
	importer.SetResourceFileId(rfid);
	importer.SetExtension(std::filesystem::path(path).extension().string());
	// TODO : Connected GameObject Id
	importer.SaveMetaData(path);
}



NAMESPACE_CLOSE