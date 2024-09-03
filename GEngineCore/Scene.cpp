#include "pch.h"
#include "Scene.h"

NAMESPACE_OPEN(GEngine)
Scene::Scene(const uint16_t index, const SceneType type)
	: _sceneIndex(index), _type(type)
{
}

Scene::~Scene()
{

}

NAMESPACE_CLOSE;