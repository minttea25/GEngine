#pragma once

NAMESPACE_OPEN(GEngine::Types)

struct G_ENGINE_CORE_API Vector2
{
public:
	static constexpr float kEpsilon = 1e-05f;
	static constexpr float kEpsilonNormalSqrt = 1E-15f;
public:
	Vector2() : x(0), y(0) {}
	Vector2(const float _x, const float _y)
		: x(_x), y(_y)
	{
	}
	Vector2(const Vector2& other)
		: x(other.x), y(other.y)
	{
	}
	~Vector2() {}

	Vector2 Normalized() const { return Normalize(*this); }
	float magnitude() const { return Magnitude(*this); }
	float SqrMagnitude() const { return x * x + y * y; }


	void operator=(const Vector2& other)
	{
		x = other.x;
		y = other.y;
	}
public:
	static Vector2 Normalize(const Vector2& v);
	static float Magnitude(const Vector2& v);
	static Vector2 ClampMagnitude(const Vector2& v, const float maxLength);
	static float Distance(const Vector2& a, const Vector2& b);
	static float Dot(const Vector2& lhs, const Vector2& rhs);
	static Vector2 Reflect(const Vector2& inDirection, const Vector2& inNormal);
	
	static Vector2 Zero() { return Vector2(0.0f, 0.0f); }
	static Vector2 One() { return Vector2(1.0f, 1.0f); }
	static Vector2 Up() { return Vector2(0.0f, 1.0f); }
	static Vector2 Down() { return Vector2(0.0f, -1.0f); }
	static Vector2 Right() { return Vector2(-1.0f, 0.0f); }
	static Vector2 Left() { return Vector2(1.0f, 0.0f); }
public:
	float x;
	float y;

private:
	// Helpers
	/*static Vector2 s_zeroVector;
	static Vector2 s_oneVector;
	static Vector2 s_upVector;
	static Vector2 s_downVector;
	static Vector2 s_rightVector;
	static Vector2 s_leftVector;*/
};

//static Vector2 s_zeroVector(0.0f, 0.0f);
//static Vector2 s_oneVector(1.0f, 1.0f);
//static Vector2 s_upVector(0.0f, 1.0f);
//static Vector2 s_downVector(0.0f, -1.0f);
//static Vector2 s_leftVector(-1.0f, 0.0f);
//static Vector2 s_rightVector(1.0f, 0.0f);

static Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

static Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

static Vector2 operator*(const Vector2& v, const float d)
{
	return Vector2(v.x * d, v.y * d);
}

static Vector2 operator/(const Vector2& v, const float d)
{
	return Vector2(v.x / d, v.y / d);
}

static bool operator==(const Vector2& lhs, const Vector2& rhs)
{
	float num = lhs.x - rhs.x;
	float num2 = lhs.y - rhs.y;
	return num * num + num2 * num2 < 9.99999944E-11f;
}

static bool operator!=(const Vector2& lhs, const Vector2& rhs)
{
	return !(lhs == rhs);
}

inline Vector2 Vector2::Normalize(const Vector2& v)
{
	float num = Magnitude(v);
	if (num > 1E-05f) return Vector2(v.x / num, v.y / num);
	else return Zero();
}

inline float Vector2::Magnitude(const Vector2& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

inline Vector2 Vector2::ClampMagnitude(const Vector2& v, const float maxLength)
{
	float num = v.SqrMagnitude();
	if (num > maxLength * maxLength)
	{
		float num2 = sqrt(num);
		float num3 = v.x / num2;
		float num4 = v.y / num2;
		return Vector2(num3 * maxLength, num4 * maxLength);
	}

	return v;
}

inline float Vector2::Distance(const Vector2& a, const Vector2& b)
{
	float num = a.x - b.x;
	float num2 = a.y - b.y;
	return sqrt(num * num + num2 * num2);
}

inline float Vector2::Dot(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

inline Vector2 Vector2::Reflect(const Vector2& inDirection, const Vector2& inNormal)
{
	float num = -2.0f * Dot(inNormal, inDirection);
	return Vector2(num * inNormal.x + inDirection.x, num * inNormal.y + inDirection.y);
}

NAMESPACE_CLOSE
