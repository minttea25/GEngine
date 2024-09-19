#pragma once

namespace GEngine
{
    enum TextureType : int
    {
        NONE_Texture, PNG, BMP, JPG
    };

    enum AudioType : int
    {
        NONE_Audio, MP3, WAV, FLAC
    };

    enum class FileType
    {
        Directory,

        Texture_PNG,
        Texture_BMP,
        Texture_JPG,

        Audio_MP3,
        Audio_WAV,
        Audio_FLAC,

        GameObject_Prefab,

        Other,

        NotExist
    };

    static TextureType ToTextureType(const FileType type)
    {
        switch (type)
        {
        case FileType::Texture_PNG:
            return TextureType::PNG;
        case FileType::Texture_BMP:
            return TextureType::BMP;
        case FileType::Texture_JPG:
            return TextureType::JPG;
        default:
            return TextureType::NONE_Texture;
        }
    }

    static AudioType ToAudioType(const FileType type)
    {
        switch (type)
        {
        case FileType::Audio_MP3:
            return AudioType::MP3;
        case FileType::Audio_WAV:
            return AudioType::WAV;
        case FileType::Audio_FLAC:
            return AudioType::FLAC;
        default:
            return AudioType::NONE_Audio;
        }
    }
}