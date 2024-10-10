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
	ResourceImporter(const ImporterType type, const RESOURCE_FILE_ID& rfid, const EXTENSION_TYPE& ext);
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

struct DefaultImporterObject final : public ImporterObject
{
public:
	DefaultImporterObject() : ImporterObject(), is_folder(false) {}
	~DefaultImporterObject() {}

	// Inherited via ImporterObject
	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
	void Read(rapidjson::Value& value) override;
	const char* ToString() override;
public:
	bool is_folder;
};

class DefaultImporter final : public ResourceImporter
{
public:
	explicit DefaultImporter(const String& file, const RESOURCE_FILE_ID& rfid);
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
	~TextureImporterObject() { if (meta != nullptr) delete meta; }

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
	AudioImporterObject() : ImporterObject() {}
	~AudioImporterObject() {}

	// Inherited via ImporterObject
	void Write(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;
	void Read(rapidjson::Value& value) override;
	const char* ToString() override;
public:
};

class AudioImporter final : public ResourceImporter
{
public:
	explicit AudioImporter(const String& file, const RESOURCE_FILE_ID& rfid);
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