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