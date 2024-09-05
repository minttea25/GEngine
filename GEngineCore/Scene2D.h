#pragma once

#include "CoreHeader.h"
#include "Scene.h"
#include "Windows.h"

NAMESPACE_OPEN(GEngine)

class GameObject;
class Layer;

class Scene2D :
    public Scene
{
public:
    Scene2D(const uint16_t index);
    virtual ~Scene2D();

    G_ENGINE_CORE_API void AddGameObject(GameObject* gameObject, const int layerIndex) override;
    G_ENGINE_CORE_API void RemoveGameObject(const uint32_t oid);

    G_ENGINE_CORE_API void InitLayer(String* names, const int len);
    G_ENGINE_CORE_API int AddLayer(String& name);
private:
    G_ENGINE_CORE_API void internal_Update() override;
    G_ENGINE_CORE_API void internal_LateUpdate() override;
    G_ENGINE_CORE_API void internal_Render(HDC hdc) override;
private:
    Map<uint32_t, GameObject*> _gameObjects;
    Vector<Layer*> _layers;

    friend class Collector;
};
NAMESPACE_CLOSE

