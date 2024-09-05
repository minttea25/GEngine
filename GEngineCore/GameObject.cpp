#include "pch.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "Collector.h"

NAMESPACE_OPEN(GEngine)

GameObject::ID GameObject::s_oid = 0;

GameObject::GameObject()
	:_transform(GNEW(Transform)),
	_oid(++s_oid), _layerIndex(0)
{
}

GameObject::~GameObject()
{
	Collector::Free_GameObject(this);

	_transform = nullptr;
	//_components.clear();
}

void GameObject::SetPos(const Types::Vector3& position)
{
	_transform->SetPosition(position);
}

void GameObject::SetPos(const float x, const float y, const float z)
{
	_transform->SetPosition(Types::Vector3(x, y, z));
}

void GameObject::SetParent(Transform& parent)
{
	if (_transform)
		_transform->SetParent(parent);
}

void GameObject::internal_Update()
{
	Update();
	for (auto& kv : _components)
	{
		kv.second->Update();
	}
}

void GameObject::internal_LateUpdate()
{
	LateUpdate();
	for (auto& kv : _components)
	{
		kv.second->LateUpdate();
	}
}

void GameObject::internal_Render(HDC hdc)
{
	Render(hdc);
	for (auto& kv : _components)
	{
		kv.second->Render(hdc);
	}
}

//template<>
//Transform* GameObject::GetComponent()
//{
//	return _transform;
//}

NAMESPACE_CLOSE