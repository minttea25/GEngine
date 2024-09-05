#pragma once

#include "CoreHeader.h"
#include "GameObject.h"

NAMESPACE_OPEN(GEngine)

class Scene2D;
class Layer
{
public:
	Layer(Scene2D* scene, const int order = 0);
	Layer(Scene2D* scene, const int order, String& name);
	~Layer();

	G_ENGINE_CORE_API virtual void Update();
	G_ENGINE_CORE_API virtual void LateUpdate();
	G_ENGINE_CORE_API virtual void Render(HDC hdc);

	G_ENGINE_CORE_API void ChangeOrder(const int order);

	G_ENGINE_CORE_API void AddGameObject(GameObject* gameObject);
	G_ENGINE_CORE_API void RemoveGameObject(const uint32_t oid);

	G_ENGINE_CORE_API String& GetName() { return _name; }
	G_ENGINE_CORE_API void SetName(const String& name) { _name = name; }
public:
	G_ENGINE_CORE_API void internal_Update();
	G_ENGINE_CORE_API void internal_LateUpdate();
	G_ENGINE_CORE_API void internal_Render(HDC hdc);

private:
	String _name;
	Scene2D* _scene;
	int _order;
	Map<uint32_t, GameObject*> _gameObjects;

	friend class Scene2D;
};

NAMESPACE_CLOSE
