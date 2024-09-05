#pragma once

#include "SceneManager.h"
#include "Player.h"
#include <concepts>

void LoadScene()
{
	auto titleScene = GEngine::SceneManager::CreateScene2D(L"TitleScene");
	std::wstring layers[] = {L"L1", L"L2"};
	titleScene->InitLayer(layers, 2);
	GEngine::SceneManager::LoadScene(titleScene->index());
}

void AddPlayer()
{
	auto titleScene = GEngine::SceneManager::GetScene2D(L"TitleScene");
	if (titleScene != nullptr)
	{
		auto go = new EGameObject();
		/*auto a = std::is_base_of_v<GEngine::Component, Player>;
		auto b = std::derived_from<Player, GEngine::Component>;
		auto c = std::derived_from<Player, GEngine::MonoBehaviour>;
		auto d = std::is_convertible_v<Player, GEngine::Component>;
		auto e = std::is_convertible_v<Player, GEngine::MonoBehaviour>;*/
		go->AddComponent<Player>();
		titleScene->AddGameObject(go, 0);
	}
}
