#pragma once

NAMESPACE_OPEN(GEngine::Types) 

struct G_ENGINE_CORE_API Vector4
{
public:
	const float kEpsilon = 1E-05f;

	Vector4() : x(0), y(0), z(0), w(0) {}
	Vector4(const float _x, const float _y, const float _z, const float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}
	Vector4(const Vector4& other)
		: x(other.x), y(other.y), z(other.z), w(other.w)
	{
	}
	~Vector4() {}

	Vector4 Normalized() const { return Normalize(*this); }
	float Magnitude() const { return Magnitude(*this); }

	void operator=(const Vector4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

public:
	float x;
	float y;
	float z;
	float w;

public:
	static float Dot(const Vector4& a, const Vector4& b);
	static Vector4 Project(const Vector4& a, const Vector4& b);
	static Vector4 Normalize(const Vector4& v);
	static float Distance(const Vector4& a, const Vector4& b);
	static float Magnitude(const Vector4& v);

	static Vector4 Zero() { return Vector4(0.0f, 0.0f, 0.0f, 0.0f); }
	static Vector4 One() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
private:
	//static Vector4 s_zeroVector;
	//static Vector4 s_oneVector;
};

static Vector4 operator +(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

static Vector4 operator -(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

static Vector4 operator -(const Vector4& v)
{
	return Vector4(0.0f - v.x, 0.0f - v.y, 0.0f - v.z, 0.0f - v.w);
}

static Vector4 operator *(const Vector4& v, const float d)
{
	return Vector4(v.x * d, v.y * d, v.z * d, v.w * d);
}

static Vector4 operator *(const float d, const Vector4& v)
{
	return Vector4(v.x * d, v.y * d, v.z * d, v.w * d);
}

static Vector4 operator /(const Vector4& v, const float d)
{
	return Vector4(v.x / d, v.y / d, v.z / d, v.w / d);
}

static bool operator ==(const Vector4& lhs, const Vector4& rhs)
{
	float num = lhs.x - rhs.x;
	float num2 = lhs.y - rhs.y;
	float num3 = lhs.z - rhs.z;
	float num4 = lhs.w - rhs.w;
	float num5 = num * num + num2 * num2 + num3 * num3 + num4 * num4;
	return num5 < 9.99999944E-11f;
}

static bool operator !=(const Vector4& lhs, const Vector4& rhs)
{
	return !(lhs == rhs);
}

inline float Vector4::Dot(const Vector4& a, const Vector4& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline Vector4 Vector4::Project(const Vector4& a, const Vector4& b)
{
	return b * (Dot(a, b) / Dot(b, b));
}

inline Vector4 Vector4::Normalize(const Vector4& v)
{
	float num = Magnitude(v);
	if (num > 1E-05f) return v / num;
	else return Vector4::Zero();
}

inline float Vector4::Distance(const Vector4& a, const Vector4& b)
{
	return Magnitude(a - b);
}

inline float Vector4::Magnitude(const Vector4& v)
{
	return static_cast<float>(sqrt(Dot(v, v)));
}

NAMESPACE_CLOSE