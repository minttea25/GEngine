#pragma once

#include "CoreMacro.h"
#include "concepts.h"
#include "Types.h"
#include "Scene.h"

NAMESPACE_OPEN(GEngine)

class SceneManager
{
public:
	G_ENGINE_CORE_API static void Init();
	G_ENGINE_CORE_API static void Clear();

	template<Scene_t Sc>
	static uint16_t CreateScene(const String& name);

	G_ENGINE_CORE_API static void LoadScene(const String& name);
	G_ENGINE_CORE_API static void LoadScene(const uint16_t sceneIndex);

#pragma warning(push)
#pragma warning(disable: 4267)
	G_ENGINE_CORE_API static int32_t SceneCount() { return s_scenes.size(); }
#pragma warning(pop)
	G_ENGINE_CORE_API static Scene* currentScene() { return s_activeScene; }

	G_ENGINE_CORE_API static Scene* GetScene(const uint16_t sceneIndex)
	{
		if (sceneIndex < s_scenes.size()) return s_scenes[sceneIndex];
		else return nullptr;
	}


	G_ENGINE_CORE_API static void Update();
	G_ENGINE_CORE_API static void LateUpdate();
	G_ENGINE_CORE_API static void Render(HDC hdc);

	G_ENGINE_CORE_API static Delegate<Scene*> SceneLoaded;
	G_ENGINE_CORE_API static Delegate<Scene*> SceneUnloaded;
	G_ENGINE_CORE_API static Delegate2<Scene*, Scene* > SceneChanged;
private:
	static Scene* s_activeScene;
	static std::vector<Scene*> s_scenes;

	friend class Collector;
};

template<Scene_t Sc>
inline uint16_t SceneManager::CreateScene(const String& name)
{
#pragma warning(push)
#pragma warning(disable: 4267)
	const int n = s_scenes.size();
#pragma warning(pop)
	Sc* scene = GNEW_EX(Sc, n);
	if (auto s = static_cast<Scene*>(scene))
	{
		s->SetName(name);
		s_scenes.push_back(scene);

		return n;
	}
	else
	{
		// TODO : Error
		return 0xFFFF;
	}
}

inline void SceneManager::LoadScene(const std::wstring& name)
{
	for (int i = 0; i < s_scenes.size(); ++i)
	{
		if (name.compare(s_scenes[i]->GetName()) == 0)
		{
			LoadScene(i);
			return;
		}
	}
	// TODO : error
}

inline void SceneManager::LoadScene(const uint16_t sceneIndex)
{
	if (sceneIndex < s_scenes.size())
	{
		// TODO : modify load method

		if (SceneUnloaded)
		{
			SceneUnloaded(s_activeScene);
		}

		if (SceneChanged)
		{
			SceneChanged(s_activeScene, s_scenes[sceneIndex]);
		}

		if (s_activeScene) s_activeScene->OnExit();
		s_activeScene = s_scenes[sceneIndex];
		s_activeScene->OnEnter();

		if (SceneLoaded)
		{
			SceneLoaded(s_activeScene);
		}
	}
	else
	{
		// TODO : error
	}
}

NAMESPACE_CLOSE

