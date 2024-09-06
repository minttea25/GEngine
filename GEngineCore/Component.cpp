#include "pch.h"
#include "Component.h"

NAMESPACE_OPEN(GEngine)

Component::Component()
	: _gameObject(nullptr)
{

}

Component::Component(GameObject* gameObject)
	: _gameObject(gameObject)
{

}

Component::~Component()
{
	_gameObject = nullptr;
}

void Component::set_GameObject(GameObject* go)
{
	_gameObject = go;
}

NAMESPACE_CLOSE