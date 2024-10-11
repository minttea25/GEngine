#include "pch.h"
#include "Resource.h"

#include <fstream>
#include <codecvt>

NAMESPACE_OPEN(GEngine)

Resource::Resource(const ResourceType type)
	: _type(type), _rawData(nullptr)
{
}

Resource::~Resource()
{
}



TextureResource::TextureResource(const String& path, const ITextureLoader* loader)
	: Resource(ResourceType::Texture), _image(loader->Load(path))
{
	if (_image == nullptr)
	{
		throw std::exception("Read failed.");
		// error
	}
}


TextureResource::~TextureResource()
{
	if (_image != nullptr) delete _image;
}












NAMESPACE_CLOSE