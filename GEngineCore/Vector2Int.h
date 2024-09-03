#pragma once

NAMESPACE_OPEN(GEngine::Types)

struct G_ENGINE_CORE_API Vector2Int
{
public:
	Vector2Int() : x(0), y(0) {}
	Vector2Int(const int _x, const int _y)
		: x(_x), y(_y)
	{
	}
	Vector2Int(const Vector2Int& other)
		: x(other.x), y(other.y)
	{
	}
	~Vector2Int() {}

	void Set(const int _x, const int _y)
	{
		x = _x; y = _y;
	}

	void operator=(const Vector2Int& other)
	{
		x = other.x;
		y = other.y;
	}

	float magnitude() const
	{
		return static_cast<float>(sqrt(x * x + y * y));
	}

	int SqrMagnitude() const
	{
		return x * x + y * y;
	}

	void Scale(const Vector2Int& scale)
	{
		x *= scale.x;
		y *= scale.y;
	}

	void Clamp(const Vector2Int& min, const Vector2Int& max)
	{
		// TODO : Vector2Int::Clamp ref UnityEngine
	}

public:
	static float Distance(const Vector2Int& a, const Vector2Int& b);
	static Vector2Int Scale(const Vector2Int& a, const Vector2Int& b);
	static Vector2Int Max(const Vector2Int& lhs, const Vector2Int& rhs);
	static Vector2Int Min(const Vector2Int& lhs, const Vector2Int& rhs);

	static Vector2Int Zero() { return Vector2Int(0, 0); }
	static Vector2Int One() { return Vector2Int(0, 0); }
	static Vector2Int Up() { return Vector2Int(0, 1); }
	static Vector2Int Down() { return Vector2Int(0, -1); }
	static Vector2Int Right() { return Vector2Int(1, 0); }
	static Vector2Int Left() { return Vector2Int(-1, 0); }
public:
	int x;
	int y;

};

static Vector2Int operator+(const Vector2Int& lhs, const Vector2Int& rhs)
{
	return Vector2Int(lhs.x + rhs.x, lhs.y + rhs.y);
}

static Vector2Int operator-(const Vector2Int& lhs, const Vector2Int& rhs)
{
	return Vector2Int(lhs.x - rhs.x, lhs.y - rhs.y);
}

static Vector2Int operator*(const Vector2Int& v, const int d)
{
	return Vector2Int(v.x * d, v.y * d);
}

static Vector2Int operator/(const Vector2Int& v, const int d)
{
	return Vector2Int(v.x / d, v.y / d);
}

static bool operator==(const Vector2Int& lhs, const Vector2Int& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

static bool operator!=(const Vector2Int& lhs, const Vector2Int& rhs)
{
	return !(lhs == rhs);
}

inline float Vector2Int::Distance(const Vector2Int& a, const Vector2Int& b)
{
	int num = a.x - b.x;
	int num2 = a.y - b.y;
#pragma warning(push)
#pragma warning(disable: 4244)
	return sqrt(num * num + num2 * num2);
#pragma warning(pop)
}

inline Vector2Int Vector2Int::Scale(const Vector2Int& a, const Vector2Int& b)
{
	return Vector2Int(a.x * b.x, a.y * b.y);
}

inline Vector2Int Vector2Int::Max(const Vector2Int& lhs, const Vector2Int& rhs)
{
	return Vector2Int((((lhs.x) > (rhs.x)) ? (lhs.x) : (rhs.x)), (((lhs.y) > (rhs.y)) ? (lhs.y) : (rhs.y)));
}

inline Vector2Int Vector2Int::Min(const Vector2Int& lhs, const Vector2Int& rhs)
{
	return Vector2Int((((lhs.x) < (rhs.x)) ? (lhs.x) : (rhs.x)), (((lhs.y) < (rhs.y)) ? (lhs.y) : (rhs.y)));
}

NAMESPACE_CLOSE

