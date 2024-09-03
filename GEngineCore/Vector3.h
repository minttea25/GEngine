#pragma once

NAMESPACE_OPEN(GEngine::Types)

struct G_ENGINE_CORE_API Vector3
{
public:
	static constexpr float kEpsilon = 1e-05f;
	static constexpr float kEpsilonNormalSqrt = 1E-15f;
public:
	Vector3() : x(0), y(0), z(0) {}
	Vector3(const float _x, const float _y, const float _z)
		: x(_x), y(_y), z(_z)
	{
	}
	Vector3(const Vector3& other)	
		: x(other.x), y(other.y), z(other.z)
	{
	}

	~Vector3() noexcept {}


	Vector3 Normalized() const { return Normalize(*this); }
	float Magnitude() const { return Magnitude(*this); }
	float SqrMagnitude() const { return x * x + y * y + z * z; }

	Vector3& operator=(const Vector3&);
	
public:
	static Vector3 Normalize(const Vector3& v);
	static float Magnitude(const Vector3& v);

	static Vector3 Zero() { return Vector3(0.0f, 0.0f, 0.0f); }
	static Vector3 One() { return Vector3(1.0f, 1.0f, 1.0f); }
	static Vector3 Forward() { return Vector3(0.0f, 0.0f, 1.0f); }
	static Vector3 Back() { return Vector3(0.0f, 0.0f, -1.0f); }
	static Vector3 Up() { return Vector3(0.0f, 1.0f, 0.0f); }
	static Vector3 Down() { return Vector3(0.0f, -1.0f, 0.0f); }
	static Vector3 Right() { return Vector3(-1.0f, 0.0f, 0.0f); }
	static Vector3 Left() { return Vector3(1.0f, 0.0f, 0.0f); }
public:
	float x;
	float y;
	float z;

private:
	/*static Vector3 s_zeroVector;
	static Vector3 s_oneVector;
	static Vector3 s_forwardVector;
	static Vector3 s_backVector;
	static Vector3 s_upVector;
	static Vector3 s_downVector;
	static Vector3 s_rightVector;
	static Vector3 s_leftVector;*/
	//static Vector3 s_positiveInfinityVector;
	//static Vector3 s_negativeInfinityVector;
};

static Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

static Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

static Vector3 operator*(const Vector3& v, const float d)
{
	return Vector3(v.x * d, v.y * d, v.z * d);
}

static Vector3 operator/(const Vector3& v, const float d)
{
	return Vector3(v.x / d, v.y / d, v.z / d);
}

static bool operator==(const Vector3& lhs, const Vector3& rhs)
{
	float num = lhs.x - rhs.x;
	float num2 = lhs.y - rhs.y;
	float num3 = lhs.z - rhs.z;
	float num4 = num * num + num2 * num2 + num3 * num3;
	return num4 < 9.99999944E-11f;
}

static bool operator!=(const Vector3& lhs, const Vector3& rhs)
{
	return !(lhs == rhs);
}

inline Vector3& Vector3::operator=(const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

inline Vector3 Vector3::Normalize(const Vector3& v)
{
	float num = Magnitude(v);
	if (num > 1E-05f) return Vector3(v.x / num, v.y / num, v.z / num);
	else return Zero();
}

inline float Vector3::Magnitude(const Vector3& v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

NAMESPACE_CLOSE
