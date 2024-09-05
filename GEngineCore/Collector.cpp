#include "pch.h"
#include "Collector.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Scene2D.h"

NAMESPACE_OPEN(GEngine)

void Collector::Free_GameObject(GameObject* o)
{
	/*for (auto& kv : o->_components)
	{
		if (kv.second)
			gdelete(kv.second);
	}
	if (o->_transform) gdelete(o->_transform);*/
}

void Collector::Free_SceneManager()
{
	for (auto& scene : SceneManager::s_scenes)
	{
		if (scene) gdelete(scene);
	}
}

void Collector::Free_Scene2D(Scene2D* o)
{
	for (auto& layer : o->_layers)
	{
		if (layer)
			gdelete(layer);
	}
	for (auto& kv : o->_gameObjects)
	{
		if (kv.second)
			gdelete(kv.second);
	}
}


NAMESPACE_CLOSE