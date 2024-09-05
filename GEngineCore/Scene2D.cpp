#include "pch.h"

#include "Layer.h"
#include "GameObject.h"
#include "Scene2D.h"
#include "Collector.h"

NAMESPACE_OPEN(GEngine)

Scene2D::Scene2D(const uint16_t index)
	: Scene::Scene(index, SceneType::D2)
{
}

Scene2D::~Scene2D()
{
	Collector::Free_Scene2D(this);

	_layers.clear();
}

void Scene2D::AddGameObject(GameObject* gameObject, const int layerIndex)
{
	if (gameObject == nullptr) return;
	if (_layers.size() <= layerIndex) return;

	// Note: GetOID() must be unique.
	_gameObjects[gameObject->GetOID()] = gameObject;
	_layers[layerIndex]->AddGameObject(gameObject);
}

void Scene2D::RemoveGameObject(const uint32_t oid)
{
	auto idx = _gameObjects[oid]->GetLayerIndex();
	DISCARD _gameObjects.erase(oid);
	_layers[idx]->RemoveGameObject(oid);
}


void Scene2D::InitLayer(String* names, const int len)
{
	_layers.clear();

	for (int i = 0; i < len; ++i)
	{
		_layers.push_back(new Layer(this, i, names[i]));
	}
}

int Scene2D::AddLayer(String& name)
{
#pragma warning(push)
#pragma warning(disable: 4267)
	const int idx = _layers.size();
#pragma warning(pop)
	_layers.push_back(new Layer(this, idx, name));

	return idx;
}

void Scene2D::internal_Update()
{
	Update();
	for (auto& layer : _layers)
	{
		if (layer)
			layer->internal_Update();
	}
}

void Scene2D::internal_LateUpdate()
{
	LateUpdate();
	for (auto& layer : _layers)
	{
		if (layer)
			layer->internal_LateUpdate();
	}
}

void Scene2D::internal_Render(HDC hdc)
{
	Render(hdc);
	for (auto& layer : _layers)
	{
		if (layer)
			layer->internal_Render(hdc);
	}
}
NAMESPACE_CLOSE