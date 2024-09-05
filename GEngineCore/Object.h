#pragma once

#include "CoreHeader.h"

NAMESPACE_OPEN(GEngine)

class Transform;

class Object
{
public:
	Object();
	virtual ~Object();

	G_ENGINE_CORE_API void SetName(const String& name) { _name = name; }
	G_ENGINE_CORE_API String& name() { return _name; }

	G_ENGINE_CORE_API int GetInstanceID() const { /*TODO: Check MainThread*/ return _instanceID; }
	G_ENGINE_CORE_API int GetHashCode() const { return _instanceID; }

	bool Equals(Object other) const;

	template<Object_t Obj>
	static Obj* Instantiate(const Obj* original, const Types::Vector3& position, Transform& parent, const int layerIndex = 0);
	template<Object_t Obj>
	static Obj* Instantiate(const Obj* original);
	template<Object_t Obj>
	static Obj* Instantiate(const Obj* original, Transform& parent);
	template<Object_t Obj>
	static Obj* Instantiate(const Obj* original, const Types::Vector3& position);

private:
	static bool compareBaseObjects(const Object& lhs, const Object& rhs);
private:
	int _instanceID;
	String _name;
};



template<Object_t Obj>
inline Obj* Object::Instantiate(const Obj* original, const Types::Vector3& position, Transform& parent, const int layerIndex)
{
	// TODO
	return nullptr;
}

template<Object_t Obj>
inline Obj* Object::Instantiate(const Obj* original)
{
	// TODO
	return nullptr;
}

template<Object_t Obj>
inline Obj* Object::Instantiate(const Obj* original, Transform& parent)
{
	// TODO
	return nullptr;
}

template<Object_t Obj>
inline Obj* Object::Instantiate(const Obj* original, const Types::Vector3& position)
{
	// TODO
	return nullptr;
}

NAMESPACE_CLOSE