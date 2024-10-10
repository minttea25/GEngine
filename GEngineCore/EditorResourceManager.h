#pragma once

#include "CoreHeader.h"
#include "ResourceImporter.h"
#include "ResourceMeta.h"

NAMESPACE_OPEN(GEngine::Editor)

using namespace GEngine;

class EditorResourceManager
{
public:
	G_ENGINE_CORE_API static constexpr auto DefaultResourcePath = L"..\\Resources";

public:
	G_ENGINE_CORE_API static void Init(const String& path = DefaultResourcePath);
	G_ENGINE_CORE_API const std::wstring& resource_file_path() const { return s_resourceFilePath; }
	/// <summary>
	/// Import new resource and create a meta file of it. 'path' should be a fullpath.
	/// </summary>
	/// <param name="path">fullpath of the resource</param>
	/// <returns>true successful, false otherwise</returns>
	G_ENGINE_CORE_API static bool ImportNewResource(const String& path);

private:

	template<typename Imp, typename Loader> 
		requires std::derived_from<Imp, ResourceImporter> 
		&& std::derived_from<Loader, IMetaLoader>
		&& requires(const String& path, const RESOURCE_FILE_ID& rfid, const Loader* loader) { Imp(path, rfid, loader); Loader(); }
	static bool import_new_resource(const String& path, const RESOURCE_FILE_ID& rfid);

	static const String& fullpath(const String& file) { return s_resourceFilePath + L"\\" + file; }
private:
	static RESOURCE_FILE_ID get_Rfid(const String& path);
private:
	static String s_resourceFilePath;
};

template<typename Imp, typename Loader> 
	requires std::derived_from<Imp, ResourceImporter> 
	&& std::derived_from<Loader, IMetaLoader>
	&& requires(const String& path, const RESOURCE_FILE_ID& rfid, const Loader* loader) { Imp(path, rfid, loader); Loader(); }
inline bool EditorResourceManager::import_new_resource(const String& path, const RESOURCE_FILE_ID& rfid)
{
	return false;
	//throw std::exception("Undefined Import");
	/*try
	{
		Loader loader{};
		Imp importer(path, rfid, loader);
		importer.CreateMetaData(path);
	}
	catch () { return false; }

	return true;*/
}

template<>
inline bool EditorResourceManager::import_new_resource<TextureImporter, TextureMetaLoaderDefault>(const String& path, const RESOURCE_FILE_ID& rfid)
{
	try
	{
		TextureMetaLoaderDefault loader;
		TextureImporter importer(path, rfid, &loader);
		importer.CreateMetaData(path);
	}
	catch (const std::exception& e) { return false; }

	return true;
}

NAMESPACE_CLOSE
