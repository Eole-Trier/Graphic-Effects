#include "core/maths/vector4.h"
#include "core/maths/vector3.h"
#include <assert.h>
#include <cmath>
#include <iostream>

Vector4::Vector4()
	: x(0), y(0), z(0), w(0)
{
}

Vector4::Vector4(float _xyzw)
	: x(_xyzw), y(_xyzw), z(_xyzw), w(_xyzw)
{
}

Vector4::Vector4(float _x, float _y, float _z, float _w)
	: x(_x), y(_y), z(_z), w(_w)
{
}

Vector4::Vector4(const Vector4& a, const Vector4& b)
	: x(b.x - a.x), y(b.y - a.y), z(b.z - a.z), w(b.w - a.z)
{
}

Vector4::Vector4(const Vector3& _xyz)
	: x(_xyz.x), y(_xyz.y), z(_xyz.z), w(0)
{
}

Vector4::Vector4(const Vector3& _xyz, const float _w)
	: x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w)
{
}

float Vector4::Norm() const
{
	return std::sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::NormSquared() const
{
	return x * x + y * y + z * z + w * w;
}

Vector4 Vector4::Normalize() const
{
	return *this / Norm();
}

Vector4 Vector4::NormalizeSafe() const
{
	const float norm = Norm();

	if (norm == 0)
		return *this; // No need to create a new vec because if norm == 0 then every component == 0 as well

	return *this / norm;
}

float Vector4::Angle(const Vector4& a, const Vector4& b)
{
	return DotProduct(a, b) / (a.Norm() * b.Norm());
}

float Vector4::DotProduct(const Vector4& a, const Vector4& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float Vector4::Distance(const Vector4& a, const Vector4& b)
{
	return (b - a).Norm();
}

float Vector4::DistanceSquared(const Vector4& a, const Vector4& b)
{
	return (b - a).NormSquared();
}

Vector4 Vector4::operator+(const Vector4& o) const
{
	return Vector4(x + o.x, y + o.y, z + o.z, w + o.w);
}

Vector4 Vector4::operator-(const Vector4& o) const
{
	return Vector4(x - o.x, y - o.y, z - o.z, w - o.w);
}

Vector4 Vector4::operator*(const Vector4& o) const
{
	return Vector4(x * o.x, y * o.y, z * o.z, w * o.w);
}

Vector4 Vector4::operator/(const Vector4& o) const
{
	return Vector4(x / o.x, y / o.y, z / o.z, w / o.w);
}


Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator+(const float scalar) const
{
	return Vector4(x + scalar, y + scalar, z + scalar, w + scalar);
}

Vector4 Vector4::operator-(const float scalar) const
{
	return Vector4(x - scalar, y - scalar, z - scalar, w - scalar);
}

Vector4 Vector4::operator*(const float scalar) const
{
	return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vector4 Vector4::operator/(const float scalar) const
{
	return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

float& Vector4::operator[](int i)
{
	assert(i >= 0 && i <= 3 && "Vector 4 subscript out of range");

	return (&x)[i];
}

float Vector4::operator[](int i) const
{
	assert(i >= 0 && i <= 3 && "Vector 4 subscript out of range");

	return (&x)[i];
}

void Vector4::Log() const
{
	std::cout << "[ " << x << ", " << y << ", " << z << ", " << w << " ]" << std::endl;
}

Vector4& operator+=(Vector4& v, const float scalar)
{
	v.x += scalar;
	v.y += scalar;
	v.z += scalar;
	v.w += scalar;
	return v;
}

Vector4& operator+=(Vector4& v, const Vector4 v2)
{
	v.x += v2.x;
	v.y += v2.y;
	v.z += v2.z;
	v.w += v2.w;
	return v;
}

Vector4& operator*=(Vector4& v, const float scalar)
{
	v.x *= scalar;
	v.y *= scalar;
	v.z *= scalar;
	v.w *= scalar;
	return v;
}

Vector4& operator*=(Vector4& v, const Vector4 v2)
{
	v.x *= v2.x;
	v.y *= v2.y;
	v.z *= v2.z;
	v.w *= v2.w;
	return v;
}
