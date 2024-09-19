#include "pch.h"
#include "ResourceImporter.h"
#include "rapidjson/prettywriter.h"
#include <fstream>

NAMESPACE_OPEN(GEngine)

#define __WRITE_KEY(name, type) writer.Key(#name); writer.type(name)
#define __WRITE_KEY_STR(name) writer.Key(#name); writer.String(name.c_str())
#define __READ_KEY(name, type) value.HasMember(#name) && value[#name].Is##type()
#define __GET_VALUE(name, type) name = value[#name].Get##type()
#define __GET_VALUE_ENUM(name, type, casttype) name = (casttype)value[#name].Get##type()

ImporterType ResourceImporter::GetImporterType(const FileType type)
{
	switch (type)
	{
	case FileType::Directory:
	case FileType::Other:
		return ImporterType::Default;
	case FileType::Texture_BMP:
	case FileType::Texture_JPG:
	case FileType::Texture_PNG:
		return ImporterType::Texture;
	case FileType::Audio_FLAC:
	case FileType::Audio_MP3:
	case FileType::Audio_WAV:
		return ImporterType::Audio;
	case FileType::GameObject_Prefab:
		return ImporterType::Native;
	default:
		return ImporterType::Default;
	}
}

void ResourceImporter::WriteBase(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
	__WRITE_KEY_STR(_rfid);
	__WRITE_KEY(_isFolder, Bool);
	__WRITE_KEY_STR(_extension);
	std::string s;
	switch (_type)
	{
	case ImporterType::Default:
		s = "DefaultImporter";
		break;
	case ImporterType::Texture:
		s = "TextureImporter";
		break;
	case ImporterType::Audio:
		s = "AudioImporter";
		break;
	case ImporterType::Native:
		s = "NativeImporter";
		break;
	default:
		s = "DefaultImporter";
		break;
	}
	writer.Key("ImporterType");
	writer.String(s.c_str());
}

void ResourceImporter::ReadBase(rapidjson::Value& value)
{
	if (__READ_KEY(_rfid, String))
	{
		__GET_VALUE(_rfid, String);
	}

	if (__READ_KEY(_extension, String))
	{
		__GET_VALUE(_extension, String);
	}

	if (__READ_KEY(_isFolder, Bool))
	{
		__GET_VALUE(_isFolder, Bool);
	}
}

void ResourceImporter::SaveMetaData(const std::wstring& path) const
{
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

	Write(writer);

	std::filesystem::path original(path);
	std::filesystem::path metaPath = original;
	metaPath.replace_extension(META_EXTENSION_W);

	// JSON을 파일로 저장
	std::ofstream ofs(metaPath);
	if (ofs.is_open())
	{
		ofs << buffer.GetString();
		ofs.close();
	}
}

void DefaultImporter::Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
	writer.StartObject();

	WriteBase(writer);

	writer.EndObject();
}

void DefaultImporter::Read(rapidjson::Value& value)
{

}


void TextureImporter::Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
	writer.StartObject();

	WriteBase(writer);
	__WRITE_KEY(_textureType, Int);

	writer.EndObject();
}

void TextureImporter::Read(rapidjson::Value& value)
{
	if (__READ_KEY(_textureType, Int))
	{
		__GET_VALUE_ENUM(_textureType, Int, TextureType);
	}
}

void AudioImporter::Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
	writer.StartObject();

	WriteBase(writer);
	__WRITE_KEY(_audioType, Int);

	writer.EndObject();
}

void AudioImporter::Read(rapidjson::Value& value)
{
	if (__READ_KEY(_audioType, Int))
	{
		__GET_VALUE_ENUM(_audioType, Int, AudioType);
	}
}

void NativeImporter::Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
	writer.StartObject();

	WriteBase(writer);
	__WRITE_KEY(_objectFileId, Uint64);

	writer.EndObject();
}

void NativeImporter::Read(rapidjson::Value& value)
{
	if (__READ_KEY(_objectFileId, Uint64))
	{
		__GET_VALUE(_objectFileId, Uint64);
	}
}

NAMESPACE_CLOSE;