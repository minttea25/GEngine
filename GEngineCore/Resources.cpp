#include "pch.h"
#include "Resources.h"
#include "ResourceImporter.h"
#include "rapidjson/istreamwrapper.h"

#include <fstream>

NAMESPACE_OPEN(GEngine);

Resources* Resources::_instance = nullptr;

void Resources::Init(IResourceManager* manager)
{
	if (manager == nullptr) throw std::exception("FATAL: ResourceManager is not assigned.");
	_init_instance();
	_instance->_manager = manager;
	_instance->_textureLoader = new TextureLoaderDefault();
	
}

Resources::Resources()
	:_manager(nullptr), _textureLoader(nullptr)
{
	
}

Resources::~Resources()
{
	if (_manager != nullptr) delete _manager;
	if (_textureLoader != nullptr) delete _textureLoader;
}

void Resources::_init_instance()
{
	_instance = new Resources();
}

const TextureResource * Resources::_load_texture(const String & path)
{
	if (_instance->_manager == nullptr) return nullptr;

	const auto obj = _instance->_manager->Load(path);
	return static_cast<const TextureResource*>(obj);
}

G_ENGINE_CORE_API const DefaultResource* Resources::_load_default(const String& path)
{

	if (_instance->_manager == nullptr) return nullptr;

	const auto obj = _instance->_manager->Load(path);
	return static_cast<const DefaultResource*>(obj);
}


NAMESPACE_CLOSE
