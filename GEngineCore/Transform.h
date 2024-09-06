#pragma once

#include "CoreHeader.h"
#include "Component.h"

NAMESPACE_OPEN(GEngine)
class Transform final : public Component
{
public:
	Transform();
	~Transform();

	G_ENGINE_CORE_API Transform* parent() { return _parent; };
	G_ENGINE_CORE_API Types::Vector3& position() { return _position; }
	G_ENGINE_CORE_API Types::Vector3& localPosition() { return _localPosition; }
	G_ENGINE_CORE_API Types::Vector3& localScale() { return _localScale; }

	G_ENGINE_CORE_API void SetParent(Transform& parent);
	G_ENGINE_CORE_API bool IsRootObject() const { return _parent == nullptr; }

	G_ENGINE_CORE_API void SetPosition(const Types::Vector3& pos) { /*TODO*/ _position = pos; }
	G_ENGINE_CORE_API void SetLocalPosition(const Types::Vector3& pos) { /*TODO*/ _localPosition = pos; }

private:
	Types::Vector3 get_position_Injected() { /*TODO*/ return _position; }
	void set_position_Injected(const Types::Vector3& pos) { /*TODO*/ }

	Types::Vector3 get_localPosition_Injected() const { /*TODO*/ return _localPosition; }
	void set_localPosition_Injected(const Types::Vector3& pos) { /*TODO*/ }
private:
	Types::Vector3 _position;
	Types::Vector3 _localPosition;
	Types::Vector3 _localScale;
	Transform* _parent;

	// TODO
};


NAMESPACE_CLOSE;
