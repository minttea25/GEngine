#include "pch.h"
#include "ResourceImporter.h"
#include "Resource.h"

#include "DefaultImporter.h"

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
	ImporterBase(const ImporterType& type)
		: importer_version(ResourceImporter::ImporterVersion),
		rfid(""), extension("")
	{
	}
public:
	/*void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
	{
		__WRITE_KEY_STR(rfid);
		__WRITE_KEY(isFolder, Bool);
		__WRITE_KEY_STR(extension);
		std::string s;
		switch (type)
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

	void Read(rapidjson::Value& value)
	{
		if (__READ_KEY(rfid, String))
		{
			__GET_VALUE(rfid, String);
		}

		if (__READ_KEY(extension, String))
		{
			__GET_VALUE(extension, String);
		}

		if (__READ_KEY(isFolder, Bool))
		{
			__GET_VALUE(isFolder, Bool);
		}
	}*/

public:
	unsigned long long importer_version;
	RESOURCE_FILE_ID rfid;
	EXTENSION_TYPE extension;
};

ResourceImporter::ResourceImporter(const ImporterType type)
	: _type(type), _obj(new ImporterBase(type))
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

void ResourceImporter::SaveMetaData(const std::wstring& path) const
{
	//rapidjson::StringBuffer buffer;
	//rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

	//writer.StartObject();

	//// 1. Write resource importer object
	//_obj->Write(writer);
	//// 2. Wrtie specified importer object
	//Write(writer);

	//writer.EndObject();

	std::filesystem::path original(path);
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


//struct TextureImporter::TextureImporterObject : public ImporterObject
//{
//public:
//	TextureImporterObject() : ImporterObject(), res() {}
//	~TextureImporterObject() {}
//
//	// Inherited via ImporterObject
//	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override
//	{
//		writer.Key("texture_type");
//		writer.Int(res.textureType());
//	}
//	void Read(rapidjson::Value& value) override
//	{
//		if (value.HasMember("texture_type") && value["texture_type"].IsInt())
//		{
//			res.SetTextureType((TextureType)value["texture_type"].GetInt());
//		}
//	}
//
//public:
//	TextureResource res;
//};
//
//TextureImporter::TextureImporter()
//	: ResourceImporter(ImporterType::Texture), _objImpl(new TextureImporterObject())
//{
//}
//
//TextureImporter::~TextureImporter()
//{
//	delete _objImpl;
//}
//
//TextureType TextureImporter::textureType() const
//{
//	return _objImpl->res.textureType();
//}
//
//void TextureImporter::SetTextureType(const TextureType type)
//{
//	_objImpl->res.SetTextureType(type);
//}
//
//void TextureImporter::Write(std::ofstream& ofs) const
//{
//	_objImpl->Write(writer);
//}
//
//void TextureImporter::Read(rapidjson::Value& value)
//{
//	_objImpl->Read(value);
//}
//
//struct AudioImporter::AudioImporterObject : public ImporterObject
//{
//
//public:
//	AudioImporterObject()
//		: ImporterObject(), res()
//	{
//	}
//
//	~AudioImporterObject() {}
//
//	// Inherited via ImporterObject
//	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override
//	{
//		writer.Key("audio_type"); writer.Int(res.audioType());
//	}
//	void Read(rapidjson::Value& value) override
//	{
//		if (value.HasMember("audio_type") && value["audio_type"].IsInt())
//		{
//			res.SetAudioType((AudioType)value["audio_type"].GetInt());
//		}
//	}
//public:
//	AudioResource res;
//};
//
//AudioImporter::AudioImporter()
//	: ResourceImporter(ImporterType::Audio), _objImpl(new AudioImporterObject())
//{
//
//}
//
//AudioImporter::~AudioImporter()
//{
//	delete _objImpl;
//}
//
//AudioType AudioImporter::audioType() const
//{
//	return _objImpl->res.audioType();
//}
//
//void AudioImporter::SetAudioType(const AudioType type)
//{
//	_objImpl->res.SetAudioType(type);
//}
//
//void AudioImporter::Write(std::ofstream& ofs) const
//{
//	_objImpl->Write(writer);
//}
//
//void AudioImporter::Read(rapidjson::Value& value)
//{
//	_objImpl->Read(value);
//}
//
//
//struct NativeImporter::NativeImporterObject : public ImporterObject
//{
//public:
//	NativeImporterObject() : ImporterObject(), res() {}
//	~NativeImporterObject() {}
//
//	// Inherited via ImporterObject
//	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override
//	{
//		__WRITE_KEY(objectFileId, Uint64);
//	}
//	void Read(rapidjson::Value& value) override
//	{
//		if (value.HasMember("objectFileId") && value["objectFileId"].IsUint64())
//		{
//			objectFileId = value["objectFileId"].GetUint64();
//		}
//	}
//public:
//	OBJECT_FILE_ID objectFileId;
//};
//
//NativeImporter::NativeImporter()
//	: ResourceImporter(ImporterType::Native), _objImpl(new NativeImporterObject())
//{
//}
//
//NativeImporter::~NativeImporter()
//{
//	delete _objImpl;
//}
//
//OBJECT_FILE_ID NativeImporter::objectFileId() const
//{
//	return _objImpl->objectFileId;
//}
//
//void NativeImporter::SetObjectFileId(OBJECT_FILE_ID id)
//{
//	_objImpl->objectFileId = id;
//}
//
//void NativeImporter::Write(std::ofstream& ofs) const
//{
//	_objImpl->Write(writer);
//}
//
//void NativeImporter::Read(rapidjson::Value& value)
//{
//	_objImpl->Read(value);
//}

NAMESPACE_CLOSE;