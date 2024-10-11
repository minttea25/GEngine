#pragma once

#include "CoreHeader.h"
#include "ResourceMeta.h"

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
	explicit ResourceImporter(const ImporterType type, const RESOURCE_FILE_ID& rfid, const EXTENSION_TYPE& ext);
	virtual ~ResourceImporter();

	const unsigned long long importer_version() const;
	const RESOURCE_FILE_ID& resource_file_id() const;
	const EXTENSION_TYPE& extension() const;
	void SetData(const RESOURCE_FILE_ID& rfid, const EXTENSION_TYPE& ext);

	ImporterType type() const { return _type; }

	/// <summary>
	/// Create meta data file about the resource.
	/// </summary>
	/// <param name="fullpath">full path of the resource</param>
	void CreateMetaData(const std::wstring & fullpath) const;
	void WriteBase(std::ofstream& ofs) const;
	static bool ReadBase(const String& metapath, OUT ResourceType& resType, OUT RESOURCE_FILE_ID& rfid, OUT EXTENSION_TYPE& ext);
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

		// TODO

		return true;
	}

	static ResourceType GetResourceType(const char* importername);

	static ImporterType GetImporterType(const FileType type);
};

struct DefaultImporterObject final : public ImporterObject
{
public:
	DefaultImporterObject(const String& path, const IDefaultMetaLoader* loader);
	~DefaultImporterObject();

	// Inherited via ImporterObject
	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
	void Read(rapidjson::Value& value) override;
	const char* ToString() override;
public:
	IDefaultMeta* meta;
};

class DefaultImporter final : public ResourceImporter
{
public:
	explicit DefaultImporter(const String& file, const RESOURCE_FILE_ID& rfid, const IDefaultMetaLoader* loader);
	~DefaultImporter();

	// Inherited via ResourceImporter
	void Write(std::ofstream& ofs) const override;
	void Read(rapidjson::Value& value) override;
public:
	DefaultImporterObject obj;
};

struct TextureImporterObject final : public ImporterObject
{
public:
	TextureImporterObject(const String& path, const ITextureMetaLoader* loader);
	~TextureImporterObject();

	// Inherited via ImporterObject
	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
	void Read(rapidjson::Value& value) override;
	const char* ToString() override;
public:
	ITextureMeta* meta; // managed here
};

class TextureImporter : public ResourceImporter
{
public:
	explicit TextureImporter(const String& file, const RESOURCE_FILE_ID& rfid, const ITextureMetaLoader* loader);
	~TextureImporter();

	// Inherited via ResourceImporter
	void Write(std::ofstream& ofs) const override;
	void Read(rapidjson::Value& value) override;
public:
	TextureImporterObject obj;
};

struct AudioImporterObject : public ImporterObject
{
public:
	AudioImporterObject(const String& path, const IAudioMetaLoader* loader);
	~AudioImporterObject();

	// Inherited via ImporterObject
	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
	void Read(rapidjson::Value& value) override;
	const char* ToString() override;
public:
	IAudioMeta* meta;
};

class AudioImporter final : public ResourceImporter
{
public:
	explicit AudioImporter(const String& file, const RESOURCE_FILE_ID& rfid, const IAudioMetaLoader* loader);
	~AudioImporter();

	// Inherited via ResourceImporter
	void Write(std::ofstream& ofs) const override;
	void Read(rapidjson::Value& value) override;
public:
	AudioImporterObject obj;
};

struct NativeImporterObject : public ImporterObject
{
public:
	NativeImporterObject() : ImporterObject() {}
	~NativeImporterObject() {}

	// Inherited via ImporterObject
	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
	void Read(rapidjson::Value& value) override;
	const char* ToString() override;
};

class NativeImporter final : public ResourceImporter
{
public:
	explicit NativeImporter(const String& file, const RESOURCE_FILE_ID& rfid);
	~NativeImporter();

public:
	NativeImporterObject obj;

	// Inherited via ResourceImporter
	void Write(std::ofstream& ofs) const override;
	void Read(rapidjson::Value& value) override;
};

NAMESPACE_CLOSE;