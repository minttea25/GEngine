#pragma once

NAMESPACE_OPEN(GEngine)

#include "CoreHeader.h"
#include "Component.h"
#include <typeinfo>
#include <typeindex>

class Transform;

class GameObject : public Object
{
	using ID = uint32_t;
public:
	GameObject();
	virtual ~GameObject();

	G_ENGINE_CORE_API uint32_t GetOID() const { return _oid; }
	G_ENGINE_CORE_API void SetLayerIndex(const uint32_t index) { _layerIndex = index; }
	G_ENGINE_CORE_API int GetLayerIndex() const { return _layerIndex; }

	G_ENGINE_CORE_API void SetPos(const Types::Vector3& position);
	G_ENGINE_CORE_API void SetPos(const float x, const float y, const float z = 0);
	G_ENGINE_CORE_API void SetParent(Transform& parent);

	G_ENGINE_CORE_API GameObject* gameObject() { return this; }

	//template<Component_t Com>
	//void AddComponent();

	//template<Component_t Com>
	//G_ENGINE_CORE_API Com* GetComponent();

	//template<Component_t Com>
	//bool TryGetComponent(OUT Com*& component);

	//template<>
	//G_ENGINE_CORE_API Transform* GetComponent<Transform>();

public:
	G_ENGINE_CORE_API virtual void Update() {};
	G_ENGINE_CORE_API virtual void LateUpdate() {};
	G_ENGINE_CORE_API virtual void Render(HDC hdc) {};

public:
	int _layerIndex;
	G_ENGINE_CORE_API void internal_Update();
	G_ENGINE_CORE_API void internal_LateUpdate();
	G_ENGINE_CORE_API void internal_Render(HDC hdc);

	static ID s_oid;

private:
	// internal
	ID _oid;
	Transform* _transform;
	Map<std::type_index, Component*> _components;

	friend class Scene;
	friend class Scene2D;
	//friend class Scene3D;
	friend class Layer;
	friend class Collector;
};

//template<Component_t Com>
//inline Com* GameObject::GetComponent()
//{
//	auto it = _components.find(std::type_index(typeid(Com)));
//	if (it != _components.end())
//	{
//		return dynamic_cast<Com*>(it->second);
//		/*Com* com = static_cast<Com*>(it->second);
//		if (com) return com;
//		else return nullptr;*/
//	}
//	else return nullptr;
//}

//template<Component_t Com>
//inline bool GameObject::TryGetComponent(OUT Com*& component)
//{
//	auto it = _components.find(std::type_index(typeid(Com)));
//	if (it == _components.end()) return false;
//	else
//	{
//		component = static_cast<Com*>(it->second);
//		return component != nullptr;
//	}
//}
//
//template<Component_t Com>
//inline void GameObject::AddComponent()
//{
//	auto it = _components.find(std::type_index(typeid(Com)));
//	if (it != _components.end())
//	{
//		// TODO : Error
//		return;
//	}
//
//	Com* com = GNEW(Com);
//	_components[std::type_index(typeid(Com))] = com;
//	com->set_GameObject(this);
//}

NAMESPACE_CLOSE
