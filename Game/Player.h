#pragma once

#include "Windows.h"
#include "Object.h"
#include "MonoBehaviour.h"
#include "GameObject.h"

class Player :
    public GEngine::MonoBehaviour
{
public:
    void Update() override;
    void LateUpdate() override;
    void Render(HDC hdc) override;
};

class EGameObject : public GEngine::GameObject
{
public:

};