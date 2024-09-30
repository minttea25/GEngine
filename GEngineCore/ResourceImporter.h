#pragma once

#include "CoreHeader.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

NAMESPACE_OPEN(GEngine)

enum class ImporterType
{
	Default,
	Texture,
	Audio,
	Native, // similar with Scriptable Object of Unity
	Prefab,
};

struct ImporterObject
{
public:
	explicit ImporterObject() {}
	virtual ~ImporterObject() {}
public:
	virtual void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const = 0;
	virtual void Read(rapidjson::Value& value) = 0;
	virtual const char* ToString() = 0;
};

// for editor
class ResourceImporter abstract
{
	static constexpr const auto ImporterVersion = 1;
public:
	static constexpr const wchar_t* META_EXTENSION_W = L".meta";
	static constexpr const char* META_EXTENSION = ".meta";
public:
	ResourceImporter(const ImporterType type);
	virtual ~ResourceImporter();

	const unsigned long long importer_version() const;
	const RESOURCE_FILE_ID& resource_file_id() const;
	const EXTENSION_TYPE& extension() const;
	void SetData(const RESOURCE_FILE_ID& rfid, const EXTENSION_TYPE& ext);

	ImporterType type() const { return _type; }


	void SaveMetaData(const std::wstring& path) const;
	void WriteBase(std::ofstream& ofs) const;
protected:
	virtual void Write(std::ofstream& ofs) const = 0;
	virtual void Read(rapidjson::Value& value) = 0;
protected:
	const ImporterType _type;
private:
	struct ImporterBase;
	ImporterBase* _obj;

public:
	template<typename Imp> requires std::derived_from<Imp, ResourceImporter>
	static bool Read(const ImporterType type, rapidjson::Value& value, OUT Imp*& importer)
	{
		if (importer != nullptr) return false;

		importer = GNEW(Imp);
		importer->Read(value);

		return true;
	}

	static ImporterType GetImporterType(const FileType type);
};

//class TextureImporter : public ResourceImporter
//{
//public:
//	TextureImporter();
//	~TextureImporter();
//
//	TextureType textureType() const;
//	void SetTextureType(const TextureType type);
//
//private:
//	// Inherited via Importer
//	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
//	void Read(rapidjson::Value& value) override;
//
//private:
//	struct TextureImporterObject;
//	TextureImporterObject* _objImpl;
//};
//
//class AudioImporter : public ResourceImporter
//{
//public:
//	AudioImporter();
//	~AudioImporter();
//
//	AudioType audioType() const;
//	void SetAudioType(const AudioType type);
//
//private:
//	// Inherited via Importer
//	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
//	void Read(rapidjson::Value& value) override;
//
//private:
//	struct AudioImporterObject;
//	AudioImporterObject* _objImpl;
//};
//
//class NativeImporter : public ResourceImporter
//{
//public:
//	NativeImporter();
//	~NativeImporter();
//
//	OBJECT_FILE_ID objectFileId() const;
//	void SetObjectFileId(OBJECT_FILE_ID id);
//
//private:
//	// Inherited via Importer
//	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
//	void Read(rapidjson::Value& value) override;
//
//private:
//	struct NativeImporterObject;
//	NativeImporterObject* _objImpl;
//};

NAMESPACE_CLOSE;