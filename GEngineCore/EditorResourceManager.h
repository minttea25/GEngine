#pragma once

#include "CoreHeader.h"
#include "Resource.h"
#include "ResourceImporter.h"
#include "ResourceMeta.h"
#include "Object.h"
#include "Resources.h"

NAMESPACE_OPEN(GEngine::Editor)

using namespace GEngine;

class EditorResourceManager : public IResourceManager
{
public:
	G_ENGINE_CORE_API EditorResourceManager() {}

	static constexpr auto DefaultResourcePath = L"..\\Resources\\";
	static constexpr auto ResourceMetaExtension = L".meta";
	const Object* Load(const String& file) override;
private:
	template<typename Res, typename Loader> 
		requires std::derived_from<Res, Resource>
	&& std::derived_from<Loader, IResourceLoader>
		static bool load_resource(const String& file, OUT Res*& res);

private:
	Map<const String, const Object*> _resources;

	
};

template<typename Res, typename Loader> 
	requires std::derived_from<Res, Resource>
&& std::derived_from<Loader, IResourceLoader>
inline bool EditorResourceManager::load_resource(const String & file, OUT Res*& res)
{
	return false;
}

template<>
inline bool EditorResourceManager::load_resource<TextureResource, TextureLoaderDefault>(const String& file, OUT TextureResource*& res)
{
	try
	{
		TextureLoaderDefault loader;
		res = new TextureResource(file, &loader);
		return true;
	}
	catch (std::exception& e) { return false; }
}

template<>
inline bool EditorResourceManager::load_resource<DefaultResource, DefaultLoader>(const String& file, OUT DefaultResource*& res)
{
	try
	{
		DefaultLoader loader;
		res = new DefaultResource(file, &loader);
		return true;
	}
	catch (std::exception& e) { return false; }
}


class EditorResourceImporter
{
	friend class Resources;
public:
	G_ENGINE_CORE_API static constexpr auto DefaultResourcePath = L"..\\Resources";
	static constexpr auto ResourceMetaExtension = ".meta";

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
inline bool EditorResourceImporter::import_new_resource(const String& path, const RESOURCE_FILE_ID& rfid)
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
inline bool EditorResourceImporter::import_new_resource<TextureImporter, TextureMetaLoaderDefault>(const String& path, const RESOURCE_FILE_ID& rfid)
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


template<>
inline bool EditorResourceImporter::import_new_resource<DefaultImporter, DefaultMetaLoader>(const String& path, const RESOURCE_FILE_ID& rfid)
{
	try
	{
		DefaultMetaLoader loader;
		DefaultImporter importer(path, rfid, &loader);
		importer.CreateMetaData(path);
	}
	catch (const std::exception& e) { return false; }

	return true;
}

template<>
inline bool EditorResourceImporter::import_new_resource<AudioImporter, AudioMetaLoaderDefault>(const String& path, const RESOURCE_FILE_ID& rfid)
{
	try
	{
		AudioMetaLoaderDefault loader;
		AudioImporter importer(path, rfid, &loader);
		importer.CreateMetaData(path);
	}
	catch (const std::exception& e) { return false; }

	return true;
}

NAMESPACE_CLOSE
