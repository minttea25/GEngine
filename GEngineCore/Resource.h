#pragma once

#include "CoreHeader.h"
#include "ResourceLoader.h"
#include "Object.h"

NAMESPACE_OPEN(GEngine)



class Resource abstract : public Object
{
public:
public:
	Resource(const ResourceType type);
	virtual ~Resource();

	ResourceType type() const { return _type; }

protected:
	const ResourceType _type;
	Vector<unsigned char>* _rawData;
};

class DefaultResource final : public Resource
{
public:
	explicit DefaultResource(const String& path, const IDefaultLoader* loader);
	~DefaultResource();

private:
};

class TextureResource final : public Resource
{
public:
	explicit TextureResource(const String& path, const ITextureLoader* loader);
	~TextureResource();

	const Gdiplus::Image* image() const { return _image; }

private:
	Gdiplus::Image* _image;
};

NAMESPACE_CLOSE
