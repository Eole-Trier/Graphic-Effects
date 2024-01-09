#pragma once

class Vector3;
// no discard macro
#include <memory>
#include "ImGui/imgui.h"

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	/// <summary>
	/// Creates a Vector4 object with default values (0)
	/// </summary>
	Vector4();

	/// <summary>
	/// Creates a Vector4 object using the same value for the X, Y, Z and W components
	/// </summary>
	/// <param name=")">Value</param>
	Vector4(float _xyzw);

	/// <summary>
	/// Creates a Vector4 object using the given components
	/// </summary>
	/// <param name="_x">X value</param>
	/// <param name="_y">Y value</param>
	/// <param name="_z">Z value</param>
	/// <param name="_w">Z value</param>
	Vector4(float _x, float _y, float _z, float _w);

	/// <summary>
	/// Creates a Vector4 object that goes from a to b
	/// </summary>
	/// <param name="a">First vector</param>
	/// <param name="b">Second vector</param>
	Vector4(const Vector4& a, const Vector4& b);

	/// <summary>
	/// Creates a Vector4 object using a vector 3 for the X, Y and Z components
	/// </summary>
	/// <param name="_xyz">X/Y/Z vector</param>
	Vector4(const Vector3& _xyz);

	/// <summary>
	/// Creates a Vector4 object using a vector 2 for the X and Y components, and a scalar for Z
	/// </summary>
	/// <param name="_xyz">X/Y/Z vector</param>
	/// <param name="_w">W value</param>
	Vector4(const Vector3& _xyz, const float _w);

	/// <summary>
	/// Gets the norm/size of the vector
	/// </summary>
	/// <returns>Norm</returns>
	_NODISCARD float Norm() const;

	/// <summary>
	/// Gets the squared norm/size of the vector
	/// </summary>
	/// <returns>Squared norm</returns>
	_NODISCARD float NormSquared() const;

	/// <summary>
	/// Gets the normalized representation of the vector
	/// </summary>
	/// <returns>Result</returns>
	_NODISCARD Vector4 Normalize() const;

	/// <summary>
	/// Gets the normalized representation of the vector (checks for 0)
	/// </summary>
	/// <returns>Result</returns>
	_NODISCARD Vector4 NormalizeSafe() const;
	
	/// <summary>
	/// Gets the angle between 2 vectors
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Angle (radians)</returns>
	_NODISCARD static float Angle(const Vector4& a, const Vector4& b);

	/// <summary>
	/// Gets the dot product between 2 vectors
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Result</returns>
	_NODISCARD static float DotProduct(const Vector4& a, const Vector4& b);

	/// <summary>
	/// Gets the distance between 2 vectors (treated as points)
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Distance</returns>
	_NODISCARD static float Distance(const Vector4& a, const Vector4& b);

	/// <summary>
	/// Gets the squared distance between 2 vectors (treated as points)
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Squared distance</returns>
	_NODISCARD static float DistanceSquared(const Vector4& a, const Vector4& b);

	/// <summary>
	/// Logs the Vector 4 to the console
	/// </summary>
	void Log() const;

	/// <summary>
	/// Operator Vec3 + Vec3
	/// </summary>
	/// <param name="o">Other</param>
	/// <returns>Result</returns>
	_NODISCARD Vector4 operator+(const Vector4& o) const;

	/// <summary>
	/// Operator Vec3 - Vec3
	/// </summary>
	/// <param name="o">Other</param>
	/// <returns>Result</returns>
	_NODISCARD Vector4 operator-(const Vector4& o) const;

	/// <summary>
	/// Operator Vec3 * Vec3
	/// </summary>
	/// <param name="o">Other</param>
	/// <returns>Result</returns>
	_NODISCARD Vector4 operator*(const Vector4& o) const;

	/// <summary>
	/// Operator Vec3 / Vec3
	/// </summary>
	/// <param name="o">Other</param>
	/// <returns>Result</returns>
	_NODISCARD Vector4 operator/(const Vector4& o) const;


	/// <summary>
	/// Operator -Vec3
	/// </summary>
	/// <returns>Result</returns>
	_NODISCARD Vector4 operator-() const;

	/// <summary>
	/// Operator Vec3 + Scalar
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Result</returns>
	_NODISCARD Vector4 operator+(const float scalar) const;

	/// <summary>
	/// Operator Vec3 - Scalar
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Result</returns>
	_NODISCARD Vector4 operator-(const float scalar) const;

	/// <summary>
	/// Operator Vec3 * Scalar
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Result</returns>
	_NODISCARD Vector4 operator*(const float scalar) const;

	/// <summary>
	/// Operator Vec3 / Scalar
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Result</returns>
	_NODISCARD Vector4 operator/(const float scalar) const;

	/// <summary>
	/// Setter for the vector via array indexing
	/// </summary>
	/// <param name="i">Index</param>
	/// <returns>Reference to the value</returns>
	_NODISCARD float& operator[](int i);

	/// <summary>
	/// Getter for the vector via array indexing
	/// </summary>
	/// <param name="i">Index</param>
	/// <returns>Value</returns>
	_NODISCARD float  operator[](int i) const;

	operator ImVec4() { return ImVec4(x, y, z, w); }
};


Vector4& operator+=(Vector4& v, const float scalar);
Vector4& operator+=(Vector4& v, const Vector4 v2);

Vector4& operator*=(Vector4& v, const float scalar);
Vector4& operator*=(Vector4& v, const Vector4 v2);
