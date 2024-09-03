#include "pch.h"
#include "Layer.h"

NAMESPACE_OPEN(GEngine)
Layer::Layer(Scene2D* scene, int order)
	: _order(order), _gameObjects{}, _scene(scene)
{

}

Layer::Layer(Scene2D* scene, int order, std::wstring& name)
	: _order(order), _gameObjects{}, _scene(scene), _name(name)
{
}

Layer::~Layer()
{
	_gameObjects.clear();
}

void Layer::Update()
{

}

void Layer::LateUpdate()
{
}

void Layer::Render(HDC hdc)
{
}

void Layer::ChangeOrder(const int order)
{
	_order = order;
}

void Layer::AddGameObject(GameObject* gameObject)
{
	DISCARD _gameObjects.insert({ gameObject->GetOID(), gameObject });
}

void Layer::RemoveGameObject(const uint32_t oid)
{
	DISCARD _gameObjects.erase(oid);
}

void Layer::internal_Update()
{
	Update();
	for (auto& kv : _gameObjects)
	{
		if (auto& go = kv.second)
		{
			go->internal_Update();
		}
	}
}

void Layer::internal_LateUpdate()
{
	LateUpdate();
	for (auto& kv : _gameObjects)
	{
		if (auto& go = kv.second)
		{
			go->internal_LateUpdate();
		}
	}
}

void Layer::internal_Render(HDC hdc)
{
	Render(hdc);
	for (auto& kv : _gameObjects)
	{
		if (auto& go = kv.second)
		{
			go->internal_Render(hdc);
		}
	}
}
NAMESPACE_CLOSE