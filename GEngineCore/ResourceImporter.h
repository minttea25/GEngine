#pragma once

#include "CoreHeader.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

NAMESPACE_OPEN(GEngine)

enum class ImporterType
{
	None,
	Default,
	Texture,
	Audio,
	Native, // similar with Scriptable Object of Unity

};

// for editor
class ResourceImporter abstract
{
public:
	static constexpr const wchar_t* META_EXTENSION_W = L".meta";
	static constexpr const char* META_EXTENSION = ".meta";
public:
	ResourceImporter(const ImporterType type) : _extension(nullptr), _rfid(nullptr), _type(type), _isFolder(false) {}
	virtual ~ResourceImporter() {}

	const RESOURCE_FILE_ID& resource_file_id() const { return _rfid; }
	void SetResourceFileId(const RESOURCE_FILE_ID& rfid) { _rfid = rfid; }
	const EXTENSION_TYPE& extension() const { return _extension; }
	void SetExtension(const EXTENSION_TYPE& extension) { _extension = extension; }
	ImporterType type() const { return _type; }
	bool isFolder() const { return _isFolder; }
	void SetFolder() { _isFolder = true; }


	virtual void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const = 0;
	virtual void Read(rapidjson::Value& value) = 0;

	void SaveMetaData(const std::wstring& path) const;

	template<typename Imp> requires std::derived_from<Imp, ResourceImporter>
	static void Read(const ImporterType type, rapidjson::Value& value, OUT Imp*& importer)
	{
		assert(importer == nullptr);

		importer = GNEW(Imp);
		importer->Read(value);
	}

	static ImporterType GetImporterType(const FileType type);

protected:
	void WriteBase(rapidjson::Writer<rapidjson::StringBuffer>& writer) const;
	void ReadBase(rapidjson::Value& value);

protected:
	RESOURCE_FILE_ID _rfid;
	ImporterType _type;
	EXTENSION_TYPE _extension;
	bool _isFolder;
};

class BaseImporter : public ResourceImporter
{
public:
	BaseImporter() : ResourceImporter(ImporterType::None) {}
	~BaseImporter() {}

	// Inherited via Importer
	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
	void Read(rapidjson::Value& value) override;
};

class DefaultImporter : public ResourceImporter
{
public:
	DefaultImporter() : ResourceImporter(ImporterType::Default) {}
	~DefaultImporter() {}

	// Inherited via Importer
	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
	void Read(rapidjson::Value& value) override;
private:

};

class TextureImporter : public ResourceImporter
{
public:
	TextureImporter() : ResourceImporter(ImporterType::Texture), _textureType(TextureType::NONE_Texture) {}
	~TextureImporter() {}

	TextureType textureType() const { return _textureType; }
	void SetTextureType(const TextureType type) { _textureType = type; }

	// Inherited via Importer
	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
	void Read(rapidjson::Value& value) override;

private:
	TextureType _textureType;
};

class AudioImporter : public ResourceImporter
{
public:
	AudioImporter() : ResourceImporter(ImporterType::Audio), _audioType(AudioType::NONE_Audio) {}
	~AudioImporter() {}

	AudioType audioType() const { return _audioType; }
	void SetAudioType(const AudioType type) { _audioType = type; }

	// Inherited via Importer
	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
	void Read(rapidjson::Value& value) override;


private:
	AudioType _audioType;
};

class NativeImporter : public ResourceImporter
{
public:
	NativeImporter() : ResourceImporter(ImporterType::Native), _objectFileId(0) {}
	~NativeImporter() {}

	OBJECT_FILE_ID objectFileId() const { return _objectFileId; }
	void SetObjectFileId(OBJECT_FILE_ID id) { _objectFileId = id; }

	// Inherited via Importer
	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
	void Read(rapidjson::Value& value) override;

private:
	OBJECT_FILE_ID _objectFileId;
};

NAMESPACE_CLOSE;

