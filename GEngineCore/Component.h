#pragma once

#include "CoreHeader.h"

NAMESPACE_OPEN(GEngine)

class GameObject;

class Component : public Object
{
public:
	Component();
	virtual ~Component();

	G_ENGINE_CORE_API GameObject* gameObject() { return _gameObject; }

public:
	G_ENGINE_CORE_API virtual void Update() {}
	G_ENGINE_CORE_API virtual void LateUpdate() {}
	G_ENGINE_CORE_API virtual void Render(HDC hdc) {}

private:
	G_ENGINE_CORE_API void set_GameObject(GameObject* go);
private:
	GameObject* _gameObject;

	friend class GameObject;
};

NAMESPACE_CLOSE;

