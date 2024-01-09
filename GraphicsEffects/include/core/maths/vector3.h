#pragma once
// no discard macro
#include <memory>

class Vector2;

class Vector3
{
public:
	float x;
	float y;
	float z;

	/// <summary>
	/// Creates a Vector3 object with default values (0)
	/// </summary>
	Vector3();

	/// <summary>
	/// Creates a Vector3 object using the same value for the X, Y and Z components
	/// </summary>
	/// <param name="_xyz">Value</param>
	Vector3(const float _xyz);

	/// <summary>
	/// Creates a Vector3 object using the given components
	/// </summary>
	/// <param name="_x">X value</param>
	/// <param name="_y">Y value</param>
	/// <param name="_z">Z value</param>
	Vector3(const float _x, const float _y, const float _z);

	/// <summary>
	/// Creates a Vector3 object that goes from a to b
	/// </summary>
	/// <param name="a">First vector</param>
	/// <param name="b">Second vector</param>
	Vector3(const Vector3& a, const Vector3& b);

	/// <summary>
	/// Creates a Vector3 object using a vector 2 for the X and Y components
	/// </summary>
	/// <param name="_xy">X/Y vector</param>
	Vector3(const Vector2 _xy);

	/// <summary>
	/// Creates a Vector3 object using a vector 2 for the X and Y components, and a scalar for Z
	/// </summary>
	/// <param name="_xy">X/Y vector</param>
	/// <param name="_z">Z value</param>
	Vector3(const Vector2 _xy, const float _z);

	/// <summary>
	/// Gets the norm/size of the vector
	/// </summary>
	/// <returns>Norm</returns>
	_NODISCARD float Norm() const;

	/// <summary>
	/// Gets the squared norm/size of the vector 3
	/// </summary>
	/// <returns>Squared norm</returns>
	_NODISCARD float NormSquared() const;

	/// <summary>
	/// Gets the normalized representation of the vector
	/// </summary>
	/// <returns>Result</returns>
	_NODISCARD Vector3 Normalize() const;

	/// <summary>
	/// Gets the normalized representation of the vector (checks for 0)
	/// </summary>
	/// <returns>Result</returns>
	_NODISCARD Vector3 NormalizeSafe() const;

	/// <summary>
	/// Rotates a vector 3 around the X axis and the origin
	/// </summary>
	/// <param name="angle">Angle</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 RotateX(const float angle) const;

	/// <summary>
	/// Rotates a vector 3 around the X axis and a specified origin
	/// </summary>
	/// <param name="angle">Angle</param>
	/// <param name="origin">Rotation origin</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 RotateX(const float angle, const Vector3& origin) const;

	/// <summary>
	/// Rotates a vector 3 around the X axis and the origin directly using cos and sin values
	/// </summary>
	/// <param name="c">Cos value</param>
	/// <param name="s">Sin value</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 RotateX(const float c, const float s) const;

	/// <summary>
	/// Rotates a vector 3 around the X axis and a specified axis directly using cos and sin values
	/// </summary>
	/// <param name="c">Cos value</param>
	/// <param name="s">Sin value</param>
	/// <param name="origin">Rotation origin</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 RotateX(const float c, const float s, const Vector3& origin) const;

	/// <summary>
	/// Rotates a vector 3 around the Y axis and the origin
	/// </summary>
	/// <param name="angle">Angle</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 RotateY(const float angle) const;

	/// <summary>
	/// Rotates a vector 3 around the Y axis and a specified origin
	/// </summary>
	/// <param name="angle">Angle</param>
	/// <param name="origin">Rotation origin</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 RotateY(const float angle, const Vector3& origin) const;

	/// <summary>
	/// Rotates a vector 3 around the Y axis and the origin directly using cos and sin values
	/// </summary>
	/// <param name="c">Cos value</param>
	/// <param name="s">Sin value</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 RotateY(const float c, const float s) const;

	/// <summary>
	/// Rotates a vector 3 around the Y axis and a specified axis directly using cos and sin values
	/// </summary>
	/// <param name="c">Cos value</param>
	/// <param name="s">Sin value</param>
	/// <param name="origin">Rotation origin</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 RotateY(const float c, const float s, const Vector3& origin) const;

	/// <summary>
	/// Rotates a vector 3 around the Z axis and the origin
	/// </summary>
	/// <param name="angle">Angle</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 RotateZ(const float angle) const;

	/// <summary>
	/// Rotates a vector 3 around the Z axis and a specified origin
	/// </summary>
	/// <param name="angle">Angle</param>
	/// <param name="origin">Rotation origin</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 RotateZ(const float angle, const Vector3& origin) const;

	/// <summary>
	/// Rotates a vector 3 around the Z axis and the origin directly using cos and sin values
	/// </summary>
	/// <param name="c">Cos value</param>
	/// <param name="s">Sin value</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 RotateZ(const float c, const float s) const;

	/// <summary>
	/// Rotates a vector 3 around the Z axis and a specified axis directly using cos and sin values
	/// </summary>
	/// <param name="c">Cos value</param>
	/// <param name="s">Sin value</param>
	/// <param name="origin">Rotation origin</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 RotateZ(const float c, const float s, const Vector3& origin) const;

	/// <summary>
	/// Reflects a 3D vector around a surface using a normal
	/// </summary>
	/// <param name="vec">Vector to reflect</param>
	/// <param name="normal">Normal of the surface</param>
	/// <returns>Reflected vector</returns>
	_NODISCARD static Vector3 Reflect(const Vector3& vec, const Vector3& normal);

	// _NODISCARD Vector3 Rotate(const float angle, const Vector3& axis) const;
	// _NODISCARD Vector3 Rotate(const float c, const float s, const Vector3& axis) const;

	/// <summary>
	/// Gets the angle between 2 vectors
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Angle (radians)</returns>
	_NODISCARD static float Angle(const Vector3& a, const Vector3& b);

	/// <summary>
	/// Gets the dot product between 2 vectors
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Result</returns>
	_NODISCARD static float DotProduct(const Vector3& a, const Vector3& b);

	/// <summary>
	/// Gets the cross product between 2 vectors
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Result</returns>
	_NODISCARD static Vector3 CrossProduct(const Vector3& a, const Vector3& b);

	/// <summary>
	/// Gets the distance between 2 vectors (treated as points)
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Distance</returns>
	_NODISCARD static float Distance(const Vector3& a, const Vector3& b);

	/// <summary>
	/// Gets the squared distance between 2 vectors (treated as points)
	/// </summary>
	/// <param name="a">Vector A</param>
	/// <param name="b">Vector B</param>
	/// <returns>Squared distance</returns>
	_NODISCARD static float DistanceSquared(const Vector3& a, const Vector3& b);

	/// <summary>
	/// Operator Vec3 + Vec3
	/// </summary>
	/// <param name="o">Other</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 operator+(const Vector3& o) const;

	/// <summary>
	/// Operator Vec3 - Vec3
	/// </summary>
	/// <param name="o">Other</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 operator-(const Vector3& o) const;

	/// <summary>
	/// Operator Vec3 * Vec3
	/// </summary>
	/// <param name="o">Other</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 operator*(const Vector3& o) const;

	/// <summary>
	/// Operator Vec3 / Vec3
	/// </summary>
	/// <param name="o">Other</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 operator/(const Vector3& o) const;


	/// <summary>
	/// Operator -Vec3
	/// </summary>
	/// <returns>Result</returns>
	_NODISCARD Vector3 operator-() const;

	/// <summary>
	/// Operator Vec3 + Scalar
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 operator+(const float scalar) const;

	/// <summary>
	/// Operator Vec3 - Scalar
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 operator-(const float scalar) const;

	/// <summary>
	/// Operator Vec3 * Scalar
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 operator*(const float scalar) const;

	/// <summary>
	/// Operator Vec3 / Scalar
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Result</returns>
	_NODISCARD Vector3 operator/(const float scalar) const;

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
	/// Logs the Vector 3 to the console
	/// </summary>
	void Log() const;
};


Vector3& operator+=(Vector3& v, const float scalar);
Vector3& operator+=(Vector3& v, const Vector3 v2);
Vector3& operator-=(Vector3& v, const Vector3 v2);

Vector3& operator*=(Vector3& v, const float scalar);
Vector3& operator*=(Vector3& v, const Vector3 v2);
