#pragma once

NAMESPACE_OPEN(GEngine::Types)

struct G_ENGINE_CORE_API Color
{
public:
	Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
	Color(const float _r, const float _g, const float _b, const float _a = 1.0f)
		: r(_r), g(_g), b(_b), a(_a)
	{
	}
	Color(const Color& other) : r(other.r), g(other.g), b(other.b), a(other.a) {}

	~Color() {}
public:
	float r;
	float g;
	float b;
	float a;

public:
	static Color red() { return Color(1, 0, 0); }
	static Color green() { return Color(0, 1, 0); }
	static Color blue() { return Color(0, 0, 1); }
	static Color white() { return Color(1, 1, 1); }
	static Color black() { return Color(0, 0, 0); }
	static Color yellow() { return Color(1.0f, 47.0f / 51.0f, 0.0156862754f); }
	static Color cyan() { return Color(0, 1, 1); }
	static Color magenta() { return Color(1, 0, 1); }
	static Color gray() { return Color(0.5f, 0.5f, 0.5f); }
	static Color transparent() { return Color(0, 0, 0, 0); }
};

NAMESPACE_CLOSE

