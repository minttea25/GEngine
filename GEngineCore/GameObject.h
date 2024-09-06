#pragma once

NAMESPACE_OPEN(GEngine)

#include "CoreHeader.h"
#include <concepts>

class Component;

class GameObject : public Object
{
	using ID = uint32_t;
public:
	G_ENGINE_CORE_API GameObject();
	G_ENGINE_CORE_API virtual ~GameObject();

	G_ENGINE_CORE_API GameObject* gameObject() { return this; }
	G_ENGINE_CORE_API Transform* transform() { return _transform; }

	G_ENGINE_CORE_API uint32_t GetOID() const { return _oid; }
	G_ENGINE_CORE_API void SetLayerIndex(const uint32_t index) { _layerIndex = index; }
	G_ENGINE_CORE_API int GetLayerIndex() const { return _layerIndex; }

	G_ENGINE_CORE_API void SetPos(const Types::Vector3& position);
	G_ENGINE_CORE_API void SetPos(const float x, const float y, const float z = 0);
	G_ENGINE_CORE_API void SetParent(Transform& parent);

	template<typename Com> requires std::derived_from<Com, Component>
	void AddComponent();

	template<typename Com> requires std::derived_from<Com, Component>
	Com* GetComponent();

	template<typename Com> requires std::derived_from<Com, Component>
	bool TryGetComponent(OUT Com*& component);

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


template<typename Com> requires std::derived_from<Com, Component>
inline void GameObject::AddComponent()
{
	auto idx = std::type_index(typeid(Com));
	auto it = _components.find(idx);
	if (it == _components.end())
	{
		_components.insert(std::make_pair(idx, GNEW_EX(Com, this)));
	}
	else
	{
		// TODO : ignored?
		return;
	}
}

template<typename Com> requires std::derived_from<Com, Component>
inline Com* GameObject::GetComponent()
{
	auto it = _components.find(std::type_index(typeid(Com)));
	if (it != _components.end())
	{
		Com* com = static_cast<Com*>(it->second);
		if (com) return com;
	}
	else return nullptr;
}


template<typename Com> requires std::derived_from<Com, Component>
inline bool GameObject::TryGetComponent(OUT Com*& component)
{
	auto it = _components.find(std::type_index(typeid(Com)));
	if (it == _components.end()) return false;
	else
	{
		component = static_cast<Com*>(it->second);
		return component != nullptr;
	}
}

NAMESPACE_CLOSE
