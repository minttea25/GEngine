#include "pch.h"
#include "Behaviour.h"

NAMESPACE_OPEN(GEngine)

Behaviour::Behaviour(GameObject* gameObject)
	: Component(gameObject)
{
}

Behaviour::~Behaviour()
{
}

NAMESPACE_CLOSE
