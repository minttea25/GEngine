#pragma once

#include "CoreHeader.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "Windows.h"
#include "gdiplus.h"

NAMESPACE_OPEN(GEngine)

__interface IResourceMeta
{

};

__interface ITextureMeta : IResourceMeta
{
	uint32_t width() const;
	uint32_t height() const;
	int pixel_format() const;
	const std::string& raw_format() const;
#ifdef _DEBUG
	void info(std::ostream& os);
#endif // _DEBUG

};

struct TextureMeta : ITextureMeta
{
public:
	TextureMeta(const uint32_t& m_width, const uint32_t& m_height, const Gdiplus::PixelFormat& m_pixelFormat, const GUID& m_rawFormat)
		: m_width(m_width), m_height(m_height), m_pixelFormat(m_pixelFormat), m_rawFormat(m_rawFormat), m_rawFormat_str("")
	{
		if (m_rawFormat == Gdiplus::ImageFormatJPEG) m_rawFormat_str = "JPEG";
		else if (m_rawFormat == Gdiplus::ImageFormatPNG) m_rawFormat_str = "PNG";
		else if (m_rawFormat == Gdiplus::ImageFormatBMP) m_rawFormat_str = "BMP";
		else if (m_rawFormat == Gdiplus::ImageFormatGIF) m_rawFormat_str = "GIF";
		else m_rawFormat_str = "Other";
	}
	~TextureMeta() {}

	const uint32_t m_width;
	const uint32_t m_height;
	const Gdiplus::PixelFormat m_pixelFormat;
	const GUID m_rawFormat;
	std::string m_rawFormat_str;
public:
	uint32_t width() const override
	{
		return m_width;
	};
	uint32_t height() const override
	{
		return m_height;
	}
	int pixel_format() const override
	{
		return m_pixelFormat;
	}
	const std::string& raw_format() const override
	{
		return m_rawFormat_str;
	}
#ifdef _DEBUG
	void info(std::ostream& os) override;
#endif // _DEBUG

	
};

__interface IMetaLoader
{

};

__interface ITextureMetaLoader : public IMetaLoader
{
	ITextureMeta* Load(const String& path) const;
};

struct TextureMetaLoaderDefault : public ITextureMetaLoader
{
	// Inherited via ITextureMetaLoader
	ITextureMeta* Load(const String& path) const override;
};

NAMESPACE_CLOSE
