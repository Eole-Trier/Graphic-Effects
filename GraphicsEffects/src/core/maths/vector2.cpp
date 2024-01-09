#include "core/maths/vector2.h"
#include <cmath>
#include <iostream>
#include <assert.h>

Vector2::Vector2()
	: x(0), y(0)
{
}


Vector2::Vector2(const float _xy)
	: x(_xy), y(_xy)
{
}


Vector2::Vector2(const float _x, const float _y)
	: x(_x), y(_y)
{
}


Vector2::Vector2(const Vector2 a, const Vector2 b)
	: x(b.x - a.x), y(b.y - a.y)
{
}

float Vector2::Norm() const
{
	return std::sqrt(x * x + y * y);
}

float Vector2::NormSquared() const
{
	return x * x + y * y;
}

Vector2 Vector2::Normalize() const
{
	const float norm = Norm();
	return Vector2(x / norm, y / norm);
}

Vector2 Vector2::NormalizeSafe() const
{
	const float norm = Norm();

	if (norm == 0)
		return Vector2();

	return Vector2(x / norm, y / norm);
}

Vector2 Vector2::Rotate(const float angle) const
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	return Vector2(x * c - y * s, x * s + y * c);
}

Vector2 Vector2::Rotate(const float c, const float s) const
{
	return Vector2(x * c - y * s, x * s + y * c);
}

Vector2 Vector2::Rotate(const float angle, const Vector2 o) const
{
	const Vector2 translated = *this - o;

	return translated.Rotate(angle) + o;
}

Vector2 Vector2::Rotate(const float c, const float s, const Vector2 o) const
{
	const Vector2 translated = *this - o;

	return translated.Rotate(c, s) + o;
}


float Vector2::Angle() const
{
	return std::atan2(y, x);
}

float Vector2::Angle(const Vector2 a, const Vector2 b)
{
	float angle = std::acos(DotProduct(a, b) / (a.Norm() * b.Norm()));

	if (CrossProduct(a, b) < 0)
		angle = -angle;

	return angle;
}


float Vector2::DotProduct(const Vector2 a, const Vector2 b)
{
	return a.x * b.x + a.y * b.y;
}

float Vector2::CrossProduct(const Vector2 a, const Vector2 b)
{
	return a.x * b.y - b.x * a.y;
}

float Vector2::Distance(const Vector2 a, const Vector2 b)
{
	return (b - a).Norm();
}

float Vector2::DistanceSquared(const Vector2 a, const Vector2 b)
{
	return (b - a).NormSquared();
}


Vector2 Vector2::operator+(const Vector2 o) const
{
	return Vector2(x + o.x, y + o.y);
}

Vector2 Vector2::operator-(const Vector2 o) const
{
	return Vector2(x - o.x, y - o.y);
}

Vector2 Vector2::operator*(const Vector2 o) const
{
	return Vector2(x * o.x, y * o.y);
}

Vector2 Vector2::operator/(const Vector2 o) const
{
	return Vector2(x / o.x, y / o.y);
}


Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const float scalar) const
{
	return Vector2(x + scalar, y + scalar);
}

Vector2 Vector2::operator-(const float scalar) const
{
	return Vector2(x - scalar, y - scalar);
}

Vector2 Vector2::operator*(const float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(const float scalar) const
{
	return Vector2(x / scalar, y / scalar);
}


float& Vector2::operator[](int i)
{
	assert(i == 0 || i == 1 && "Vector 2 subscript out of range");

	return (&x)[i];
}

float Vector2::operator[](int i) const
{
	assert(i == 0 || i == 1 && "Vector 2 subscript out of range");

	return (&x)[i];
}

void Vector2::Log() const
{
	std::cout << "[ " << x << ", " << y << " ]" << std::endl;
}

Vector2& operator+=(Vector2& v, const float scalar)
{
	v.x += scalar;
	v.y += scalar;
	return v;
}

Vector2& operator+=(Vector2& v, const Vector2 v2)
{
	v.x += v2.x;
	v.y += v2.y;
	return v;
}

Vector2& operator*=(Vector2& v, const float scalar)
{
	v.x *= scalar;
	v.y *= scalar;
	return v;
}

Vector2& operator*=(Vector2& v, const Vector2 v2)
{
	v.x *= v2.x;
	v.y *= v2.y;
	return v;
}
