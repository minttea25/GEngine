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

struct ResourceImporter::ImporterBase
{
public:
	ImporterBase(const RESOURCE_FILE_ID& _rfid, const EXTENSION_TYPE& _ext)
		: importer_version(ResourceImporter::ImporterVersion),
		rfid(_rfid), extension(_ext)
	{
	}
public:
	unsigned long long importer_version;
	RESOURCE_FILE_ID rfid;
	EXTENSION_TYPE extension;
};

ResourceImporter::ResourceImporter(const ImporterType type, const RESOURCE_FILE_ID& rfid, const EXTENSION_TYPE& ext)
	: _type(type), _obj(new ImporterBase(rfid, ext))
{
}

ResourceImporter::~ResourceImporter()
{
	delete _obj;
}

const unsigned long long ResourceImporter::importer_version() const
{
	return _obj->importer_version;
}

const RESOURCE_FILE_ID& ResourceImporter::resource_file_id() const
{
	return _obj->rfid;
}

const EXTENSION_TYPE& ResourceImporter::extension() const
{
	return _obj->extension;
}

void ResourceImporter::SetData(const RESOURCE_FILE_ID& rfid, const EXTENSION_TYPE& ext)
{
	_obj->rfid = rfid;
	_obj->extension = ext;
}

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

void ResourceImporter::CreateMetaData(const std::wstring & fullpath) const
{
	std::filesystem::path original(fullpath);
	std::filesystem::path metaPath = original;
	metaPath.replace_extension(META_EXTENSION_W);

	// save file as json
	std::ofstream ofs(metaPath);
	if (ofs.is_open())
	{
		WriteBase(ofs);
		ofs << '\n';
		Write(ofs);
		ofs.close();
	}
}

void ResourceImporter::WriteBase(std::ofstream& ofs) const
{
	ofs << "ImporterVersion: " << _obj->importer_version
		<< "\nResourceFileId: " << _obj->rfid
		<< "\nExtension: " << _obj->extension;
}

void DefaultImporterObject::Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
	writer.Key("is_folder");
	writer.Bool(is_folder);
}

void DefaultImporterObject::Read(rapidjson::Value& value)
{
	if (value.HasMember("is_folder") && value["is_folder"].IsBool())
	{
		is_folder = value["is_folder"].GetBool();
	}
}

const char* DefaultImporterObject::ToString()
{
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

	writer.StartObject();
	Write(writer);
	writer.EndObject();

	return buffer.GetString();
}


DefaultImporter::DefaultImporter(const String& file, const RESOURCE_FILE_ID& rfid)
	: ResourceImporter(ImporterType::Default, rfid, std::filesystem::path(file).string())
{
	DWORD attr = GetFileAttributesW(file.c_str());
	if (attr & FILE_ATTRIBUTE_DIRECTORY)
	{
		obj.is_folder = true;
	}
}

DefaultImporter::~DefaultImporter()
{
}

void DefaultImporter::Write(std::ofstream& ofs) const
{
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

	ofs << "DefaultImporter: \n";

	writer.StartObject();
	obj.Write(writer);
	writer.EndObject();

	ofs << buffer.GetString();
}

void DefaultImporter::Read(rapidjson::Value& value)
{
}

TextureImporter::TextureImporter(const String& file, const RESOURCE_FILE_ID& rfid, const ITextureMetaLoader* loader)
	:ResourceImporter(ImporterType::Texture, rfid, std::filesystem::path(file).extension().string()), obj(file, loader)
{
}

TextureImporter::~TextureImporter()
{
}


void TextureImporter::Write(std::ofstream& ofs) const
{
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

	ofs << "TextureImporter: \n";

	writer.StartObject();
	obj.Write(writer);
	writer.EndObject();

	ofs << buffer.GetString();
}

void TextureImporter::Read(rapidjson::Value& value)
{
}

TextureImporterObject::TextureImporterObject(const String& path, const ITextureMetaLoader* loader)
	: ImporterObject(), meta(loader->Load(path))
{
}

void TextureImporterObject::Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
	writer.Key("m_width");
	writer.Uint(meta->width());
	writer.Key("m_height");
	writer.Uint(meta->height());
	writer.Key("m_pixelFormat");
	writer.Int(meta->pixel_format());
	writer.Key("m_rawFormat");
	writer.String(meta->raw_format().c_str());
}

void TextureImporterObject::Read(rapidjson::Value& value)
{
}

const char* TextureImporterObject::ToString()
{
	return nullptr;
}

void AudioImporterObject::Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{

}

void AudioImporterObject::Read(rapidjson::Value& value)
{
}

const char* AudioImporterObject::ToString()
{
	return nullptr;
}

AudioImporter::AudioImporter(const String& file, const RESOURCE_FILE_ID& rfid)
	: ResourceImporter(ImporterType::Audio, rfid, std::filesystem::path(file).extension().string())
{
}

AudioImporter::~AudioImporter()
{
}


void AudioImporter::Write(std::ofstream& ofs) const
{
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

	ofs << "AudioImporter: \n";

	writer.StartObject();
	obj.Write(writer);
	writer.EndObject();

	ofs << buffer.GetString();
}

void AudioImporter::Read(rapidjson::Value& value)
{
}

void NativeImporterObject::Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{

}

void NativeImporterObject::Read(rapidjson::Value& value)
{
}

const char* NativeImporterObject::ToString()
{
	return nullptr;
}

NativeImporter::NativeImporter(const String& file, const RESOURCE_FILE_ID& rfid)
	: ResourceImporter(ImporterType::Native, rfid, std::filesystem::path(file).extension().string())
{
}

NativeImporter::~NativeImporter()
{
}


void NativeImporter::Write(std::ofstream& ofs) const
{
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

	ofs << "NativeImporter: \n";

	writer.StartObject();
	obj.Write(writer);
	writer.EndObject();

	ofs << buffer.GetString();
}

void NativeImporter::Read(rapidjson::Value& value)
{
}

NAMESPACE_CLOSE;