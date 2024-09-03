#include "pch.h"
#include "Transform.h"

NAMESPACE_OPEN(GEngine)

Transform::Transform()
	: _position(), _localPosition(), _localScale(1, 1, 1), _parent(nullptr)
{
}

Transform::~Transform()
{
	_parent = nullptr;
}

void Transform::SetParent(Transform& parent)
{
	_parent = &parent;
}

NAMESPACE_CLOSE