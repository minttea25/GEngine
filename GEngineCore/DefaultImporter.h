#pragma once
#include "CoreHeader.h"
#include "Resource.h"
#include "ResourceImporter.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

NAMESPACE_OPEN(GEngine)

struct DefaultImporterObject : public ImporterObject
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

class DefaultImporter : public ResourceImporter
{
public:
	explicit DefaultImporter();
	~DefaultImporter();

	// Inherited via ResourceImporter
	void Write(std::ofstream& ofs) const override;
	void Read(rapidjson::Value& value) override;
public:
	DefaultImporterObject obj;
};

NAMESPACE_CLOSE;
