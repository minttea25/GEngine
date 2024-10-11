#pragma once

#include "CoreHeader.h"


NAMESPACE_OPEN(GEngine)

__interface IResourceLoader
{

};

struct ResourceLoader
{
	static constexpr auto ResourceMetaExtension = L".meta";
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
