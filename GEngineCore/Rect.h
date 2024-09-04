#pragma once

#include "CoreHeader.h"

NAMESPACE_OPEN(GEngine::Types)

struct G_ENGINE_CORE_API Rect
{
public:
	Rect() : x(0), y(0), width(0), height(0) {}
	Rect(const float _x, const float _y, const float _width, const float _height)
		: x(_x), y(_y), width(_width), height(_height)
	{
	}
	Rect(const Vector2& position, const Vector2& size)
		: x(position.x), y(position.y), width(size.x), height(size.y)
	{
	}
	Rect(const Rect& other)
		: x(other.x), y(other.y), width(other.width), height(other.height)
	{
	}
	~Rect() {}

	void Set(const float _x, const float _y, const float _width, const float _height)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
	}

	Vector2 Position() const { return Vector2(x, y); }
	void SetPosition(const float _x, const float _y) { x = _x; y = _x; }

	Vector2 Center() const { return Vector2(x + width / 2.0f, y + height / 2.0f); }
	void SetCenter(const Vector2& v) { x = v.x - width / 2.0f; y = v.y - height / 2.0f; }

	Vector2 Size() const { return Vector2(width, height); }
	void SetSize(const Vector2& v) { width = v.x; height = v.y; }

	float GetXMax() const { return width + x; }
	void SetXMax(const float _x) { width = _x - x; }
	float GetYMax() const { return  height + y; }
	void SetYMax(const float _y) { height = _y - y; }

	bool Contains(const Vector2& point) const
	{
		return point.x >= x && point.x < GetXMax() && point.y >= y && point.y < GetYMax();
	}

	static Rect Zero() { return Rect(0, 0, 0, 0); }
	static Rect MinMaxRect(const float xMin, const float yMin, const float xMax, const float yMax)
	{
		return Rect(xMin, yMin, xMax - xMin, yMax - yMin);
	}

public:
	float x;
	float y;
	float width;
	float height;
};

static bool operator ==(const Rect& lhs, const Rect& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.width == rhs.width && lhs.height == rhs.height;
}

static bool operator !=(const Rect& lhs, const Rect& rhs)
{
	return !(lhs == rhs);
}

NAMESPACE_CLOSE