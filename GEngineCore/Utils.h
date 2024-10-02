#pragma once
#include "CoreHeader.h"

#include "winnt.h"
#include <minwindef.h>
#include <filesystem>
#include <fileapi.h>

NAMESPACE_OPEN(GEngine)

bool IsExtension(const std::wstring& path, const std::wstring& ext)
{
    if (path.length() >= ext.length())
    {
        return (0 == path.compare(path.length() - ext.length(), ext.length(), ext));
    }
    else
    {
        return false;
    }
}

FileType GetFileType_x(const std::wstring& path)
{
    DWORD fileAttr = GetFileAttributesW(path.c_str());

    if (fileAttr == INVALID_FILE_ATTRIBUTES)
    {
        return FileType::NotExist;
    }

    if (fileAttr & FILE_ATTRIBUTE_DIRECTORY)
    {
        return FileType::Directory;
    }

    if (IsExtension(path, L".png"))
    {
        return FileType::Texture_PNG;
    }
    else if (IsExtension(path, L".bmp"))
    {
        return FileType::Texture_BMP;
    }
    else if (IsExtension(path, L".jpg") || IsExtension(path, L".jpeg"))
    {
        return FileType::Texture_JPG;
    }
    else if (IsExtension(path, L".mp3"))
    {
        return FileType::Audio_MP3;
    }
    else if (IsExtension(path, L".wav"))
    {
        return FileType::Audio_WAV;
    }
    else if (IsExtension(path, L".flac"))
    {
        return FileType::Audio_FLAC;
    }
    // Add more here...
    else if (IsExtension(path, L".prefab"))
    {
        return FileType::GameObject_Prefab;
    }
    else
    {
        return FileType::Other;
    }
}

static size_t GenerateHash(const std::wstring& wstr)
{
    // Use std::hash to generate a hash value for the wstring
    std::hash<std::wstring> hasher;
    return hasher(wstr);
}

NAMESPACE_CLOSE