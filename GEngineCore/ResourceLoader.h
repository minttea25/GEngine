#pragma once

#include "CoreHeader.h"


NAMESPACE_OPEN(GEngine)

__interface IResourceLoader
{

};

__interface IDefaultLoader : public IResourceLoader
{
	// TEMP: always return nullptr
	int* Load(const String& path) const;
};

struct DefaultLoader : public IDefaultLoader
{
	// Inherited via IDefaultLoader
	int* Load(const String& path) const override;
};


__interface ITextureLoader : public IResourceLoader
{
	Gdiplus::Image* Load(const String& path) const;
};

struct TextureLoaderDefault : public ITextureLoader
{
	HRESULT CreateStreamOnMemory(const unsigned char* buffer, size_t size, IStream** stream) const;
	Gdiplus::Image* Load(const String& path) const override;
};

NAMESPACE_CLOSE
