#include "pch.h"
#include "ResourceLoader.h"
#include "gdiplus.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Windows.h"
#include "ResourceImporter.h"

NAMESPACE_OPEN(GEngine)

HRESULT TextureLoaderDefault::CreateStreamOnMemory(const unsigned char* buffer, size_t size, IStream** stream) const {
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, size);
    if (!hGlobal) {
        return E_OUTOFMEMORY;
    }

    void* pData = GlobalLock(hGlobal);
    if (pData) {
        memcpy(pData, buffer, size);
        GlobalUnlock(hGlobal);
    }

    // IStream »ý¼º
    return CreateStreamOnHGlobal(hGlobal, TRUE, stream);
}

Gdiplus::Image* TextureLoaderDefault::Load(const String& path) const
{
    if (std::filesystem::exists(path) == false)
    {
        return nullptr;
    }

	std::ifstream file(path, std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	Vector<unsigned char> buffer(size);
	if (file.read((char*)buffer.data(), size))
	{
		IStream* stream = nullptr;
        if (SUCCEEDED(CreateStreamOnMemory(buffer.data(), buffer.size(), &stream)))
        {
            Gdiplus::Image* image = Gdiplus::Image::FromStream(stream);
            if (image->GetLastStatus() == Gdiplus::Ok) 
            {
                return image;
            } 
            else 
            {
                return nullptr;
            }

        }
	}

    return nullptr;
}

int* DefaultLoader::Load(const String& path) const
{
    return nullptr;
}

NAMESPACE_CLOSE


