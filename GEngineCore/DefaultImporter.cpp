#include "pch.h"
#include "DefaultImporter.h"

#include "rapidjson/prettywriter.h"
#include <fstream>

NAMESPACE_OPEN(GEngine)

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

DefaultImporter::DefaultImporter()
	: ResourceImporter(ImporterType::Default)
{
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



NAMESPACE_CLOSE;