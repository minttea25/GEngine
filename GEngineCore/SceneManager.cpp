#include "pch.h"
#include "SceneManager.h"
#include "Collector.h"

NAMESPACE_OPEN(GEngine)

Scene* SceneManager::s_activeScene = nullptr;
std::vector<Scene*> SceneManager::s_scenes = {};
Delegate<Scene*> SceneManager::SceneUnloaded;
Delegate2<Scene*, Scene*> SceneManager::SceneChanged;
Delegate<Scene*> SceneManager::SceneLoaded;

void SceneManager::Init()
{
}

void SceneManager::Clear()
{
	Collector::Free_SceneManager();

	s_activeScene = nullptr;
	s_scenes.clear();
}

G_ENGINE_CORE_API Scene* SceneManager::GetScene(const String& name)
{
	for (int i = 0; i < s_scenes.size(); ++i)
	{
		if (name.compare(s_scenes[i]->GetName()) == 0)
		{
			return s_scenes[i];
		}
	}
	return nullptr;
}

G_ENGINE_CORE_API Scene2D* SceneManager::GetScene2D(const String& name)
{
	auto s = GetScene(name);
	return s == nullptr ? nullptr : static_cast<Scene2D*>(s);
}

void SceneManager::Update()
{
	if (s_activeScene) s_activeScene->internal_Update();
}

void SceneManager::LateUpdate()
{
	if (s_activeScene) s_activeScene->internal_LateUpdate();
}

void SceneManager::Render(HDC hdc)
{
	if (s_activeScene) s_activeScene->internal_Render(hdc);
}

NAMESPACE_CLOSE