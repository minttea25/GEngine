#pragma once

#include <typeindex>
#include "Windows.h"
#include "Object.h"
#include "MonoBehaviour.h"
#include "GameObject.h"

class Player :
    public GEngine::MonoBehaviour
{
public:
    Player(GEngine::GameObject* go) : MonoBehaviour(go), _speed(200.0f) {}
public:
    void Update() override;
    void LateUpdate() override;
    void Render(HDC hdc) override;

private:
    float _speed;
};

class EGameObject : public GEngine::GameObject
{
public:
    EGameObject() {}
    ~EGameObject() {}
};

//template __declspec(dllimport) void GEngine::GameObject::AddComponent<Player>();