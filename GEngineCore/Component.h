#pragma once

#include "CoreHeader.h"

NAMESPACE_OPEN(GEngine)

class GameObject;

class G_ENGINE_CORE_API Component : public Object
{
public:
	Component();
	Component(GameObject* gameObject);
	virtual ~Component();

	GameObject* gameObject() { return _gameObject; }

public:
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void Render(HDC hdc) {}

protected:
	void set_GameObject(GameObject* go);
private:
	GameObject* _gameObject;

	friend class GameObject;
};

NAMESPACE_CLOSE;

