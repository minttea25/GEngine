#include "pch.h"
#include "Object.h"
NAMESPACE_OPEN(GEngine)
Object::Object()
	: _name(L""), _instanceID(/*TODO*/0)
{
}

Object::~Object()
{
}

bool Object::Equals(Object other) const
{
	return _instanceID == other._instanceID;
}


bool Object::compareBaseObjects(const Object& lhs, const Object& rhs)
{
	return false;
}

NAMESPACE_CLOSE