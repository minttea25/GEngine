#pragma once

#include "CoreHeader.h"
#include "Object.h"
#include "Resource.h"



NAMESPACE_OPEN(GEngine);

__interface IResourceManager
{
	const Object* Load(const String& file);
};

class Resources
{
public:
	G_ENGINE_CORE_API static void Init(IResourceManager* loader);

	template<typename Res> requires std::derived_from<Res, Resource>
	static const Res* Load(const String& path);
private:
	G_ENGINE_CORE_API const TextureResource* _load(const String& path);

private:
	Resources();
	~Resources();
	static void _init_instance();
private:
	G_ENGINE_CORE_API static Resources* _instance;
	IResourceManager* _manager;
	Map<String, RUID> _map;
	ITextureLoader* _textureLoader;
};



template<typename Res> requires std::derived_from<Res, Resource>
inline const Res* Resources::Load(const String& path)
{
	return nullptr;
	/*if (_instance->_manager == nullptr) return nullptr;

	const auto obj = _instance->_manager->Load(path);
	return static_cast<const Res*>(obj);*/
}

template<>
inline const TextureResource* Resources::Load(const String& path)
{
	return Resources::_instance->_load(path);
}


NAMESPACE_CLOSE