#pragma once

// no discard macro
#include <memory>

class Vector2
{
public:
	float x;
	float y;

	/// <summary>
	/// Creates a Vector2 object with default values (0)
	/// </summary>
	Vector2();

	/// <summary>
	/// Creates a Vector2 object using the same value for the X and Y components
	/// </summary>
	/// <param name="_xy">Value</param>
	Vector2(const float _xy);

	/// <summary>
	/// Creates a Vector2 object using the given components
	/// </summary>
	/// <param name="_x">X value</param>
	/// <param name="_y">Y value</param>
	Vector2(const float _x, const float _y);

	/// <summary>
	/// Creates a Vector2 object that goes from a to b
	/// </summary>
	/// <param name="a">First vector</param>
	/// <param name="b">Second vector</param>
	Vector2(const Vector2 a, const Vector2 b);

	/// <summary>
	/// Gets the norm/size of the vector
	/// </summary>
	/// <returns>Norm</returns>
	_NODISCARD float Norm() const;

	/// <summary>
	/// Gets the squared norm/size of the vector 2
	/// </summary>
	/// <returns>Squared norm</returns>
	_NODISCARD float NormSquared() const;

	/// <summary>
	/// Gets the normalized representation of the vector
	/// </summary>
	/// <returns>Result</returns>
	_NODISCARD Vector2 Normalize() const;

	/// <summary>
	/// Gets the normalized representation of the vector (checks for 0)
	/// </summary>
	/// <returns>Result</returns>
	_NODISCARD Vector2 NormalizeSafe() const;

	/// <summary>
	/// Rotates the vector 2 around the origin
	/// </summary>
	/// <param name="angle">Angle (radians)</param>
	/// <returns>Result</returns>
	_NODISCARD Vector2 Rotate(const float angle) const;

	/// <summary>
	/// Rotates the vector 2 around the origin directly using cos and sin values
	/// </summary>
	/// <param name="c">Cos value</param>
	/// <param name="s">Sin value</param>
	/// <returns>Result</returns>
	_NODISCARD Vector2 Rotate(const float c, const float s) const;

	/// <summary>
	/// Rotates the vector 2 around a point
	/// </summary>
	/// <param name="angle">Angle (radians)</param>
	/// <param name="o">Rotation origin</param>
	/// <returns>Result</returns>
	_NODISCARD Vector2 Rotate(const float angle, const Vector2 o) const;

	/// <summary>
	/// Rotates the vector 2 around a point directly using cos and sin values
	/// </summary>
	/// <param name="c">Cos value</param>
	/// <param name="o">Rotation origin</param>
	/// <param name="o"></param>
	/// <returns>Result</returns>
	_NODISCARD Vector2 Rotate(const float c, const float s, const Vector2 o) const;

	/// <summary>
	/// Gets the angle between the vector and the absolute X axis
	/// </summary>
	/// <returns>Angle (radians)</returns>
	_NODISCARD float Angle() const;

	/// <summary>
	/// Gets the angle between 2 vectors
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Angle (radians)</returns>
	_NODISCARD static float Angle(const Vector2 a, const Vector2 b);

	/// <summary>
	/// Gets the dot product between 2 vectors
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Result</returns>
	_NODISCARD static float DotProduct(const Vector2 a, const Vector2 b);

	/// <summary>
	/// Gets the cross product between 2 vectors
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Result</returns>
	_NODISCARD static float CrossProduct(const Vector2 a, const Vector2 b);

	/// <summary>
	/// Gets the distance between 2 vectors (treated as points)
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Distance</returns>
	_NODISCARD static float Distance(const Vector2 a, const Vector2 b);

	/// <summary>
	/// Gets the squared distance between 2 vectors (treated as points)
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Squared distance</returns>
	_NODISCARD static float DistanceSquared(const Vector2 a, const Vector2 b);

	/// <summary>
	/// Operator Vec2 + Vec2
	/// </summary>
	/// <param name="o">Other</param>
	/// <returns>Result</returns>
	_NODISCARD Vector2 operator+(const Vector2 o) const;

	/// <summary>
	/// Operator Vec2 - Vec2
	/// </summary>
	/// <param name="o">Other</param>
	/// <returns>Result</returns>
	_NODISCARD Vector2 operator-(const Vector2 o) const;

	/// <summary>
	/// Operator Vec2 * Vec2
	/// </summary>
	/// <param name="o">Other</param>
	/// <returns>Result</returns>
	_NODISCARD Vector2 operator*(const Vector2 o) const;

	/// <summary>
	/// Operator Vec2 / Vec2
	/// </summary>
	/// <param name="o">Other</param>
	/// <returns>Result</returns>
	_NODISCARD Vector2 operator/(const Vector2 o) const;


	/// <summary>
	/// Operator -Vec2
	/// </summary>
	/// <returns>Result</returns>
	_NODISCARD Vector2 operator-() const;

	/// <summary>
	/// Operator Vec2 + Scalar
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Result</returns>
	_NODISCARD Vector2 operator+(const float scalar) const;

	/// <summary>
	/// Operator Vec2 - Scalar
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Result</returns>
	_NODISCARD Vector2 operator-(const float scalar) const;

	/// <summary>
	/// Operator Vec2 * Scalar
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Result</returns>
	_NODISCARD Vector2 operator*(const float scalar) const;

	/// <summary>
	/// Operator Vec2 / Scalar
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Result</returns>
	_NODISCARD Vector2 operator/(const float scalar) const;

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

	/// <summary>
	/// Logs the Vector 2 to the console
	/// </summary>
	void Log() const;
};

Vector2& operator+=(Vector2& v, const float scalar);
Vector2& operator+=(Vector2& v, const Vector2 v2);

Vector2& operator*=(Vector2& v, const float scalar);
Vector2& operator*=(Vector2& v, const Vector2 v2);
