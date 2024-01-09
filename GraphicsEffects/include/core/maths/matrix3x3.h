#pragma once

#include "vector3.h"
#include "core/maths/matrix2x2.h"

class MatrixM;

class Matrix3x3
{
public:
	Vector3 Row0;
	Vector3 Row1;
	Vector3 Row2;

#pragma region Constructors

	/// <summary>
	/// Constructs an empty 3x3 Matrix
	/// </summary>
	Matrix3x3();

	/// <summary>
	/// Constructs a 3x3 Matrix filled with "value"
	/// <para>
	/// [ value, value, value ]
	/// </para>
	/// <para>
	/// [ value, value, value ]
	/// </para>
	/// [ value, value, value ]
	/// </summary>
	/// <param name="value"></param>
	Matrix3x3(const float value);

	/// <summary>
	/// Constructs a 3x3 Matrix using direct component values
	/// <para>
	/// [ r00, r01, r02 ]
	/// </para>
	/// <para>
	/// [ r10, r11, r12 ]
	/// </para>
	/// [ r20, r21, r22 ]
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	Matrix3x3(
		const float r00, const float r01, const float r02,
		const float r10, const float r11, const float r12,
		const float r20, const float r21, const float r22
	);

	/// <summary>
	/// Constructs a 3x3 Matrix using a Vector 3, then direct components
	/// <para>
	/// [ r0.x, r0.y, r0.z ]
	/// </para>
	/// <para>
	/// [ r10, r11, r12 ]
	/// </para>
	/// [ r20, r21, r22 ]
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	Matrix3x3(
		const Vector3& r0,
		const float r10, const float r11, const float r12,
		const float r20, const float r21, const float r22
	);

	/// <summary>
	/// Constructs a 3x3 Matrix using 3 components, a Vector 3, then 3 components
	/// <para>
	/// [ r00, r01, r02 ]
	/// </para>
	/// <para>
	/// [ r1.x, r1.y, r1.z ]
	/// </para>
	/// [ r20, r21, r22 ]
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r1">m[1] Second row</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	Matrix3x3(
		const float r00, const float r01, const float r02,
		const Vector3& r1,
		const float r20, const float r21, const float r22
	);

	/// <summary>
	/// Constructs a 3x3 Matrix using components, then a Vector 3
	/// <para>
	/// [ r00, r01, r02 ]
	/// </para>
	/// <para>
	/// [ r10, r11, r12 ]
	/// </para>
	/// [ r2.x, r2.y, r2.z ]
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r1">m[2] Third row</param>
	Matrix3x3(
		const float r00, const float r01, const float r02,
		const float r10, const float r11, const float r12,
		const Vector3& r2
	);

	/// <summary>
	/// Constructs a 3x3 Matrix using 2 Vector 3, then components
	/// <para>
	/// [ r0.x, r0.y, r0.z ]
	/// </para>
	/// [ r1.x, r1.y, r1.z ]
	/// <para>
	/// [ r20, r21, r22 ]
	/// </para>
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r0">m[1] Second row</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	Matrix3x3(
		const Vector3& r0,
		const Vector3& r1,
		const float r20, const float r21, const float r22
	);

	/// <summary>
	/// Constructs a 3x3 Matrix using a Vector 3, components, then a Vector 3
	/// <para>
	/// [ r0.x, r0.y, r0.z ]
	/// </para>
	/// [ r10, r11, r12 ]
	/// <para>
	/// [ r2.x, r2.y, r2.z ]
	/// </para>
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r2">m[2] Third row</param>
	Matrix3x3(
		const Vector3& r0,
		const float r10, const float r11, const float r12,
		const Vector3& r2
	);

	/// <summary>
	/// Constructs a 3x3 Matrix using components, then 2 Vector 3
	/// <para>
	/// [ r00, r01, r02 ]
	/// </para>
	/// [ r1.x, r1.y, r1.z ]
	/// <para>
	/// [ r2.x, r2.y, r2.z ]
	/// </para>
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r1">m[1] Second row</param>
	/// <param name="r2">m[2] Third row</param>
	Matrix3x3(
		const float r00, const float r01, const float r02,
		const Vector3& r1,
		const Vector3& r2
	);

	/// <summary>
	/// Constructs a 3x3 Matrix using 3 Vector 3
	/// <para>
	/// [ r0.x, r0.y, r0.z ]
	/// </para>
	/// [ r1.x, r1.y, r1.z ]
	/// <para>
	/// [ r2.x, r2.y, r2.z ]
	/// </para>
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r1">m[1] Second row</param>
	/// <param name="r2">m[2] Third row</param>
	Matrix3x3(
		const Vector3& r0,
		const Vector3& r1,
		const Vector3& r2
	);

	/// <summary>
	/// Constructs a 3x3 Matrix using a 2x2 Matrix
	/// <para>
	/// [ mat[0, 0], mat[0, 1], 0 ]
	/// </para>
	/// [ mat[1, 0], mat[1, 1], 0 ]
	/// <para>
	/// [ 0, 0, 0 ]
	/// </para>
	/// </summary>
	/// <param name="mat">Upper left corner values</param>
	Matrix3x3(
		const Matrix2x2& mat
	);

	/// <summary>
	/// Constructs a 3x3 Matrix using a 2x2 Matrix, and then components
	/// <para>
	/// [ mat[0, 0], mat[0, 1], r02 ]
	/// </para>
	/// [ mat[1, 0], mat[1, 1], r12 ]
	/// <para>
	/// [ r20, r21, r22 ]
	/// </para>
	/// </summary>
	/// <param name="mat">Upper left corner values</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	Matrix3x3(
		const Matrix2x2& mat, const float r02,
		const float r12,
		const float r20, const float r21, const float r22
	);

	/// <summary>
	/// Constructs a 3x3 Matrix using a 2x2 Matrix, components, and a Vector 3
	/// <para>
	/// [ mat[0, 0], mat[0, 1], r02 ]
	/// </para>
	/// [ mat[1, 0], mat[1, 1], r12 ]
	/// <para>
	/// [ r2.x, r2.y, r2.z ]
	/// </para>
	/// </summary>
	/// <param name="mat">Upper left corner values</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r2">m[2] Third row</param>
	Matrix3x3(
		const Matrix2x2& mat, const float r02,
		const float r12,
		const Vector3& r2
	);

	/// <summary>
	/// Constructs a 3x3 Matrix using an initializer list of floats, [1;9] range of elements
	/// </summary>
	/// <param name="data">Data</param>
	Matrix3x3(const std::initializer_list<float>& data);

	/// <summary>
	/// Constructs a 3x3 Matrix using an initializer list of Vector 2, [1;3] range of elements
	/// </summary>
	/// <param name="data">Data</param>
	Matrix3x3(const std::initializer_list<Vector3>& data);

#pragma endregion

	_NODISCARD Vector3 Diagonal() const;
	_NODISCARD float Trace() const;
	_NODISCARD float Determinant() const;

	void Augment(const MatrixM& in, MatrixM& out) const;

	Matrix3x3& Negate();
	Matrix3x3& Transpose();
	Matrix3x3& Add(const float scalar);
	Matrix3x3& Add(const Matrix3x3& mat);
	Matrix3x3& Multiply(const float scalar);
	Matrix3x3& Multiply(const Matrix3x3& mat);
	Vector3 Multiply(const Vector3& vec) const;

	static void RotationX(const float angle, Matrix3x3& dst);
	static void RotationY(const float angle, Matrix3x3& dst);
	static void RotationZ(const float angle, Matrix3x3& dst);
	static void Rotation(const Vector3& rotation, Matrix3x3& dst);

	Vector3 operator[](int i) const;
	Vector3& operator[](int i);

	void Log() const;

	static const Matrix3x3 Identity;
};

