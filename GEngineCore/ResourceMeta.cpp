#include "pch.h"
#include "ResourceMeta.h"

#pragma comment (lib,"gdiplus.lib")

NAMESPACE_OPEN(GEngine)

#ifdef _DEBUG
void TextureMeta::info(std::ostream& os)
{
	using namespace Gdiplus;

	os << "width: " << m_width << ' '
		<< "height: " << m_height << ' '
		<< "pixel_format: ";
	switch (m_pixelFormat) {
	case PixelFormat24bppRGB:
		os << "24bpp RGB" << ' ';
		break;
	case PixelFormat32bppARGB:
		os << "32bpp ARGB" << ' ';
		break;
	case PixelFormat8bppIndexed:
		os << "8bpp Indexed" << ' ';
		break;
	default:
		os << "Unknown" << ' ';
	}
	os << "raw_format: ";
	if (m_rawFormat == ImageFormatJPEG) {
		os << "JPEG" << ' ';
	} else if (m_rawFormat == ImageFormatPNG) {
		os << "PNG" << ' ';
	} else if (m_rawFormat == ImageFormatBMP) {
		os << "BMP" << ' ';
	} else if (m_rawFormat == ImageFormatGIF) {
		os << "GIF" << ' ';
	} else {
		os << "Unknown" << ' ';
	}
}
#endif // _DEBUG


ITextureMeta* TextureMetaLoaderDefault::Load(const String& path) const
{
	using namespace Gdiplus;

	Image* image = Image::FromFile(path.c_str(), FALSE);


	if (image->GetLastStatus() != Ok)
	{
		std::wstring s(L"Can not find or open file as IMAGE: " + path);
		std::string e;
		e.assign(s.begin(), s.end());
		throw std::runtime_error(e);
		return nullptr;
	}
	GUID rawFormat{};
	image->GetRawFormat(&rawFormat);
	TextureMeta* meta = new TextureMeta
	(
		image->GetWidth(),
		image->GetHeight(),
		image->GetPixelFormat(),
		rawFormat
	);
	
	delete image;

	return static_cast<ITextureMeta*>(meta); // TODO return local var.
}
NAMESPACE_CLOSE