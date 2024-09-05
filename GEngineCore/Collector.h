#pragma once

#include "CoreHeader.h"

NAMESPACE_OPEN(GEngine)

class GameObject;
class Scene2D;

class Collector
{
public:
	static void Free_GameObject(GameObject* o);

	static void Free_SceneManager();

	static void Free_Scene2D(Scene2D* o);
};

NAMESPACE_CLOSE
