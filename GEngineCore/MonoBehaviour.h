#pragma once

#include "CoreHeader.h"
#include "Behaviour.h"

NAMESPACE_OPEN(GEngine)
class G_ENGINE_CORE_API MonoBehaviour : public Behaviour
{
public:
	MonoBehaviour(GameObject* gameObject);
	virtual ~MonoBehaviour();

	// TODO : work with coroutine like Unity
private:
};
NAMESPACE_CLOSE

