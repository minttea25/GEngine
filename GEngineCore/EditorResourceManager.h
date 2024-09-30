#pragma once

#include "CoreHeader.h"
#include "ResourceImporter.h"

NAMESPACE_OPEN(GEngine::Editor)

using namespace GEngine;

class EditorResourceManager
{
public:
	static constexpr auto ResourcePath = L"..\\Resources\\";

public:
	G_ENGINE_CORE_API static void Init(const String& path = ResourcePath);

	static void AddNewResource(const String& path);

	G_ENGINE_CORE_API static void TestImport(const String& path);

	//template<typename Imp> requires std::derived_from<Imp, ResourceImporter>
	//static void addNewResource(const String& path, const FileType fType, const RESOURCE_FILE_ID& rfid);


private:
	static RESOURCE_FILE_ID get_Rfid(const String& path);
};


NAMESPACE_CLOSE