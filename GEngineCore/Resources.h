#pragma once

#include "CoreHeader.h"
#include "Object.h"




NAMESPACE_OPEN(GEngine);




class ResourceManager
{
public:
	static constexpr auto ResourcePath = L"..\\Resources";
	static constexpr auto ResourceMetaExtension = ".meta";

private:
	static void Init();

	static const Object* Load(const String& path);
	
	static const Object* Load(const RUID ruid);
	static void UnLoad(const RUID ruid);
	static const Object* Find(const String& path);

	static RUID GetID(const String& path);

	static Object* ReadFile(const String& path, const FileType fType);

private:
	/*************TEMP**********/
	// in editor, create grid with that path
	static Map<String, RUID> s_t_resources; // It is temp
	static RUID s_ruid_issuer;

	static Map<RUID, const Object*> s_resources;


	friend class Resources;
};

class Resources
{
public:
	static void Init();

	template<typename Obj> requires std::derived_from<Obj, Object>
	static const Obj* Load(const String& path);
public:
	Map<String, RUID> _map;
};



template<typename Obj> requires std::derived_from<Obj, Object>
inline const Obj* Resources::Load(const String& path)
{
	const auto obj = ResourceManager::Load(path);
	return obj;
}

NAMESPACE_CLOSE