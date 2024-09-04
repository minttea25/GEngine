#pragma once

#include "CoreHeader.h"

NAMESPACE_OPEN(GEngine)

class GameObject;

enum SceneType
{
	D2, D3
};

class Scene abstract
{
public:
	Scene(const uint16_t index, const SceneType _type);
	virtual ~Scene();

	G_ENGINE_CORE_API void SetName(const String& name) { _name = name; }
	G_ENGINE_CORE_API String& GetName() { return _name; }

	G_ENGINE_CORE_API SceneType GetSceneType() const { return _type; }

	G_ENGINE_CORE_API virtual void Update() {}
	G_ENGINE_CORE_API virtual void LateUpdate() {}
	G_ENGINE_CORE_API virtual void Render(HDC hdc) {}

	G_ENGINE_CORE_API virtual void OnEnter() {}
	G_ENGINE_CORE_API virtual void OnExit() {}

	G_ENGINE_CORE_API virtual void AddGameObject(GameObject* gameObject, const int layerIndex = 0) = 0;

public:
	G_ENGINE_CORE_API virtual void internal_Update() = 0;
	G_ENGINE_CORE_API virtual void internal_LateUpdate() = 0;
	G_ENGINE_CORE_API virtual void internal_Render(HDC hdc) = 0;
protected:
	const uint16_t _sceneIndex;
	String _name;
	const SceneType _type;

	friend class SceneManager;
};

NAMESPACE_CLOSE;

