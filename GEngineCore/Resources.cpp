#include "pch.h"
#include "Resources.h"
#include "ResourceImporter.h"
#include "rapidjson/istreamwrapper.h"

#include <fstream>

NAMESPACE_OPEN(GEngine);


RUID ResourceManager::s_ruid_issuer = 0;
Map<String, RUID> ResourceManager::s_t_resources;
Map<RUID, const Object*> ResourceManager::s_resources;

void Resources::Init()
{
	
	// TODO
}



void ResourceManager::Init()
{
	// TEMP
	s_ruid_issuer = 10000000;
}

const Object* ResourceManager::Load(const String& path)
{
	if (s_t_resources.contains(path))
	{
		return Load(s_t_resources[path]);
	}


}

const Object* ResourceManager::Load(const RUID ruid)
{
	if (s_resources.contains(ruid))
	{
		return s_resources[ruid];
	}
	else return nullptr;
}

void ResourceManager::UnLoad(const RUID ruid)
{
	if (s_resources.contains(ruid))
	{
		auto r = s_resources.at(ruid);
		s_resources.erase(ruid);
		gdelete(r);
	}
}

const Object* ResourceManager::Find(const String& path)
{
	// Note: path should not include extension.

	// check if it exists
	std::filesystem::path resourcePath(ResourcePath + path);
	if (std::filesystem::exists(resourcePath) == false)
	{
		return nullptr;
	}

	std::string metafile = resourcePath.filename().string() + ResourceMetaExtension;
	if (std::filesystem::exists(metafile) == false)
	{
		return nullptr;
	}

	//EXTENSION_TYPE ext = nullptr;
	//ImporterType type;
	//BaseImporter importer;
	//std::ifstream ifs(metafile);
	//if (ifs.is_open())
	//{
	//	rapidjson::IStreamWrapper isw(ifs);
	//	rapidjson::Document doc;
	//	doc.ParseStream(isw);

	//	if (doc.IsObject())
	//	{
	//		importer.Read(doc);

	//		ext = importer.extension();
	//		type = importer.type();
	//	}
	//	else
	//	{
	//		// logic error
	//	}

	//	ifs.close();
	//}
	//else
	//{
	//	// error : can not find meta file
	//}

	//// Read Original
	//auto file = std::filesystem::path()

}

RUID ResourceManager::GetID(const String& path)
{
	if (s_t_resources.contains(path) == false)
	{
		return s_ruid_issuer++;
	}
	else return s_t_resources[path];
}

Object* ResourceManager::ReadFile(const String& path, const FileType fType)
{
	return nullptr;
}

NAMESPACE_CLOSE
