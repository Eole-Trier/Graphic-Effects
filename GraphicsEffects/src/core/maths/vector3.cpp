#include "core/maths/vector3.h"
#include "core/maths/vector2.h"
#include <cmath>
#include <iostream>
#include <assert.h>

Vector3::Vector3()
	: x(0), y(0), z(0)
{
}


Vector3::Vector3(const float _xyz)
	: x(_xyz), y(_xyz), z(_xyz)
{
}


Vector3::Vector3(const float _x, const float _y, const float _z)
	: x(_x), y(_y), z(_z)
{
}


Vector3::Vector3(const Vector3& a, const Vector3& b)
	: x(b.x - a.x), y(b.y - a.y), z(b.z - a.z)
{
}

Vector3::Vector3(const Vector2 _xy)
	: x(_xy.x), y(_xy.y), z(0)
{
}


Vector3::Vector3(const Vector2 _xy, const float _z)
	: x(_xy.x), y(_xy.y), z(_z)
{
}

float Vector3::Norm() const
{
	return std::sqrt(x * x + y * y + z * z);
}

float Vector3::NormSquared() const
{
	return x * x + y * y + z * z;
}

Vector3 Vector3::Normalize() const
{
	const float norm = Norm();
	return Vector3(x / norm, y / norm, z / norm);
}

Vector3 Vector3::NormalizeSafe() const
{
	const float norm = Norm();

	if (norm == 0)
		return Vector3();

	return Vector3(x / norm, y / norm, z / norm);
}

Vector3 Vector3::RotateX(const float angle) const
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	return Vector3(x, y * c - z * s, y * s + z * c);
}

Vector3 Vector3::RotateX(const float angle, const Vector3& origin) const
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	const Vector3 translated = *this - origin;
	return translated.RotateX(c, s) + origin;
}

Vector3 Vector3::RotateX(const float c, const float s) const
{
	return Vector3(x, y * c - z * s, y * s + z * c);
}

Vector3 Vector3::RotateX(const float c, const float s, const Vector3& origin) const
{
	const Vector3 translated = *this - origin;

	return translated.RotateX(c, s) + origin;
}


Vector3 Vector3::RotateY(const float angle) const
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	return Vector3(x * c + s * z, y, x * -s + z * c);
}

Vector3 Vector3::RotateY(const float angle, const Vector3& origin) const
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	const Vector3 translated = *this - origin;

	return translated.RotateY(c, s) + origin;
}

Vector3 Vector3::RotateY(const float c, const float s) const
{
	return Vector3(x * c + s * z, y, x * -s + z * c);
}

Vector3 Vector3::RotateY(const float c, const float s, const Vector3& origin) const
{
	const Vector3 translated = *this - origin;

	return translated.RotateY(c, s) + origin;
}


Vector3 Vector3::RotateZ(const float angle) const
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	return Vector3(x * c + y * -s, x * s + y * c, z);
}

Vector3 Vector3::RotateZ(const float angle, const Vector3& origin) const
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	const Vector3 translated = *this - origin;

	return translated.RotateZ(c, s) + origin;
}

Vector3 Vector3::RotateZ(const float c, const float s) const
{
	return Vector3(x * c + y * -s, x * s + y * c, z);
}

Vector3 Vector3::RotateZ(const float c, const float s, const Vector3& origin) const
{
	const Vector3 translated = *this - origin;

	return translated.RotateZ(c, s) + origin;
}

Vector3 Vector3::Reflect(const Vector3& vec, const Vector3& normal)
{
	return vec - normal * (2.0f * Vector3::DotProduct(vec, normal));
}


float Vector3::Angle(const Vector3& a, const Vector3& b)
{
	return std::acos(DotProduct(a, b) / (a.Norm() * b.Norm()));
}


float Vector3::DotProduct(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& b)
{
	const float x = a.y * b.z - a.z * b.y;
	const float y = a.z * b.x - a.x * b.z;
	const float z = a.x * b.y - a.y * b.x;

	return Vector3(x, y, z);
}

float Vector3::Distance(const Vector3& a, const Vector3& b)
{
	return (b - a).Norm();
}

float Vector3::DistanceSquared(const Vector3& a, const Vector3& b)
{
	return (b - a).NormSquared();
}


Vector3 Vector3::operator+(const Vector3& o) const
{
	return Vector3(x + o.x, y + o.y, z + o.z);
}

Vector3 Vector3::operator-(const Vector3& o) const
{
	return Vector3(x - o.x, y - o.y, z - o.z);
}

Vector3 Vector3::operator*(const Vector3& o) const
{
	return Vector3(x * o.x, y * o.y, z * o.z);
}

Vector3 Vector3::operator/(const Vector3& o) const
{
	return Vector3(x / o.x, y / o.y, z / o.z);
}


Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(const float scalar) const
{
	return Vector3(x + scalar, y + scalar, z + scalar);
}

Vector3 Vector3::operator-(const float scalar) const
{
	return Vector3(x - scalar, y - scalar, z - scalar);
}

Vector3 Vector3::operator*(const float scalar) const
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/(const float scalar) const
{
	return Vector3(x / scalar, y / scalar, z / scalar);
}

void Vector3::Log() const
{
	std::cout << "[ " << x << ", " << y << ", " << z << " ]" << std::endl;
}

float& Vector3::operator[](int i)
{
	assert(i == 0 || i == 1 || i == 2 && "Vector 3 subscript out of range");

	return (&x)[i];
}

float Vector3::operator[](int i) const
{
	assert(i == 0 || i == 1 || i == 2 && "Vector 3 subscript out of range");

	return (&x)[i];
}

Vector3& operator+=(Vector3& v, const float scalar)
{
	v.x += scalar;
	v.y += scalar;
	v.z += scalar;
	return v;
}

Vector3& operator+=(Vector3& v, const Vector3 v2)
{
	v.x += v2.x;
	v.y += v2.y;
	v.z += v2.z;
	return v;
}

Vector3& operator-=(Vector3& v, const Vector3 v2)
{
	v.x -= v2.x;
	v.y -= v2.y;
	v.z -= v2.z;
	return v;
}

Vector3& operator*=(Vector3& v, const float scalar)
{
	v.x *= scalar;
	v.y *= scalar;
	v.z *= scalar;
	return v;
}

Vector3& operator*=(Vector3& v, const Vector3 v2)
{
	v.x *= v2.x;
	v.y *= v2.y;
	v.z *= v2.z;
	return v;
}
