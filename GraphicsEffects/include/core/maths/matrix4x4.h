#pragma once

#include "core/maths/vector4.h"
#include "core/maths/matrix2x2.h"
#include "core/maths/matrix3x3.h"

class MatrixM;

class Matrix4x4
{
public:
	Vector4 Row0;
	Vector4 Row1;
	Vector4 Row2;
	Vector4 Row3;

#pragma region Constructors

	/// <summary>
	/// Constructs an empty 4x4 matrix
	/// <para>
	/// [ 0, 0, 0, 0 ]
	/// </para>
	/// <para>
	/// [ 0, 0, 0, 0 ]
	/// </para>
	/// <para>
	/// [ 0, 0, 0, 0 ]
	/// </para>
	/// <para>
	/// [ 0, 0, 0, 0 ]
	/// </para>
	/// </summary>
	Matrix4x4();

	/// <summary>
	/// Constructs a 4x4 Matrix filled with "value"
	/// <para>
	/// [ value, value, value, value ]
	/// </para>
	/// <para>
	/// [ value, value, value, value ]
	/// </para>
	/// <para>
	/// [ value, value, value, value ]
	/// </para>
	/// <para>
	/// [ value, value, value, value ]
	/// </para>
	/// </summary>
	Matrix4x4(const float value);

	/// <summary>
	/// Constructs a 4x4 Matrix using direct component values
	/// <para>
	/// [ r00, r01, r02, r03 ]
	/// </para>
	/// <para>
	/// [ r10, r11, r12, r13 ]
	/// </para>
	/// <para>
	/// [ r20, r21, r22, r23 ]
	/// </para>
	/// <para>
	/// [ r30, r31, r32, r33 ]
	/// </para>
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r03">m[0, 3] value</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r13">m[1, 3] value</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	/// <param name="r23">m[2, 3] value</param>
	/// <param name="r30">m[3, 0] value</param>
	/// <param name="r31">m[3, 1] value</param>
	/// <param name="r32">m[3, 2] value</param>
	/// <param name="r33">m[3, 3] value</param>
	Matrix4x4(
		const float r00, const float r01, const float r02, const float r03,
		const float r10, const float r11, const float r12, const float r13,
		const float r20, const float r21, const float r22, const float r23,
		const float r30, const float r31, const float r32, const float r33
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using a Vector 4, then component values
	/// <para>
	/// [ r0.x, r0.y, r0.z, r0.w ]
	/// </para>
	/// <para>
	/// [ r10, r11, r12, r13 ]
	/// </para>
	/// <para>
	/// [ r20, r21, r22, r23 ]
	/// </para>
	/// <para>
	/// [ r30, r31, r32, r33 ]
	/// </para>
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r13">m[1, 3] value</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	/// <param name="r23">m[2, 3] value</param>
	/// <param name="r30">m[3, 0] value</param>
	/// <param name="r31">m[3, 1] value</param>
	/// <param name="r32">m[3, 2] value</param>
	/// <param name="r33">m[3, 3] value</param>
	Matrix4x4(
		const Vector4& r0,
		const float r10, const float r11, const float r12, const float r13,
		const float r20, const float r21, const float r22, const float r23,
		const float r30, const float r31, const float r32, const float r33
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using direct components, a Vector 4, then components values
	/// <para>
	/// [ r00, r01, r02, r03 ]
	/// </para>
	/// <para>
	/// [ r1.x, r1.y, r1.z, r1.w ]
	/// </para>
	/// <para>
	/// [ r20, r21, r22, r23 ]
	/// </para>
	/// <para>
	/// [ r30, r31, r32, r33 ]
	/// </para>
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r03">m[0, 3] value</param>
	/// <param name="r1">m[1] Second row</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	/// <param name="r23">m[2, 3] value</param>
	/// <param name="r30">m[3, 0] value</param>
	/// <param name="r31">m[3, 1] value</param>
	/// <param name="r32">m[3, 2] value</param>
	/// <param name="r33">m[3, 3] value</param>
	Matrix4x4(
		const float r00, const float r01, const float r02, const float r03,
		const Vector4& r1,
		const float r20, const float r21, const float r22, const float r23,
		const float r30, const float r31, const float r32, const float r33
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using direct components, a Vector 4, then components values
	/// <para>
	/// [ r00, r01, r02, r03 ]
	/// </para>
	/// <para>
	/// [ r10, r11, r12, r13 ]
	/// </para>
	/// <para>
	/// [ r2.x, r2.y, r2.z, r2.w ]
	/// </para>
	/// <para>
	/// [ r30, r31, r32, r33 ]
	/// </para>
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r03">m[0, 3] value</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r13">m[1, 3] value</param>
	/// <param name="r2">m[2] Third row</param>
	/// <param name="r30">m[3, 0] value</param>
	/// <param name="r31">m[3, 1] value</param>
	/// <param name="r32">m[3, 2] value</param>
	/// <param name="r33">m[3, 3] value</param>
	Matrix4x4(
		const float r00, const float r01, const float r02, const float r03,
		const float r10, const float r11, const float r12, const float r13,
		const Vector4& r2,
		const float r30, const float r31, const float r32, const float r33
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using direct components, then a Vector 4
	/// <para>
	/// [ r00, r01, r02, r03 ]
	/// </para>
	/// <para>
	/// [ r10, r11, r12, r13 ]
	/// </para>
	/// <para>
	/// [ r20, r21, r22, r23 ]
	/// </para>
	/// <para>
	/// [ r3.x, r3.y, r3.z, r3.w ]
	/// </para>
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r03">m[0, 3] value</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r13">m[1, 3] value</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	/// <param name="r23">m[2, 3] value</param>
	/// <param name="r3">m[3] Fourth row</param>
	Matrix4x4(
		const float r00, const float r01, const float r02, const float r03,
		const float r10, const float r11, const float r12, const float r13,
		const float r20, const float r21, const float r22, const float r23,
		const Vector4& r3
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using 2 Vector 4, then direct components
	/// <para>
	/// [ r00, r01, r02, r03 ]
	/// </para>
	/// <para>
	/// [ r10, r11, r12, r13 ]
	/// </para>
	/// <para>
	/// [ r20, r21, r22, r23 ]
	/// </para>
	/// <para>
	/// [ r3.x, r3.y, r3.z, r3.w ]
	/// </para>
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r1">m[1] Second row</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	/// <param name="r23">m[2, 3] value</param>
	/// <param name="r30">m[3, 0] value</param>
	/// <param name="r31">m[3, 1] value</param>
	/// <param name="r32">m[3, 2] value</param>
	/// <param name="r33">m[3, 3] value</param>
	Matrix4x4(
		const Vector4& r0,
		const Vector4& r1,
		const float r20, const float r21, const float r22, const float r23,
		const float r30, const float r31, const float r32, const float r33
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using a Vector 4, direct components, a Vector 4, then direct components
	/// <para>
	/// [ r0.x, r0.y, r0.z, r0.w ]
	/// </para>
	/// <para>
	/// [ r10, r11, r12, r13 ]
	/// </para>
	/// <para>
	/// [ r2.x, r2.y, r2.z, r2.w ]
	/// </para>
	/// <para>
	/// [ r30, r31, r32, r33 ]
	/// </para>
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r13">m[1, 3] value</param>
	/// <param name="r2">m[2] Third row</param>
	/// <param name="r30">m[3, 0] value</param>
	/// <param name="r31">m[3, 1] value</param>
	/// <param name="r32">m[3, 2] value</param>
	/// <param name="r33">m[3, 3] value</param>
	Matrix4x4(
		const Vector4& r0,
		const float r10, const float r11, const float r12, const float r13,
		const Vector4& r2,
		const float r30, const float r31, const float r32, const float r33
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using a Vector 4, direct components, then a Vector 4
	/// <para>
	/// [ r0.x, r0.y, r0.z, r0.w ]
	/// </para>
	/// <para>
	/// [ r10, r11, r12, r13 ]
	/// </para>
	/// <para>
	/// [ r20, r21, r22, r23 ]
	/// </para>
	/// <para>
	/// [ r3.x, r3.y, r3.z, r3.w ]
	/// </para>
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r13">m[1, 3] value</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	/// <param name="r23">m[2, 3] value</param>
	/// <param name="r3">m[3] Fourth row</param>
	Matrix4x4(
		const Vector4& r0,
		const float r10, const float r11, const float r12, const float r13,
		const float r20, const float r21, const float r22, const float r23,
		const Vector4& r3
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using 3 Vector 4, then direct components
	/// <para>
	/// [ r0.x, r0.y, r0.z, r0.w ]
	/// </para>
	/// <para>
	/// [ r1.x, r1.y, r1.z, r1.w ]
	/// </para>
	/// <para>
	/// [ r2.x, r2.y, r2.z, r2.w ]
	/// </para>
	/// <para>
	/// [ r30, r31, r32, r33 ]
	/// </para>
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r1">m[1] Second row</param>
	/// <param name="r2">m[2] Third row</param>
	/// <param name="r30">m[3, 0] value</param>
	/// <param name="r31">m[3, 1] value</param>
	/// <param name="r32">m[3, 2] value</param>
	/// <param name="r33">m[3, 3] value</param>
	Matrix4x4(
		const Vector4& r0,
		const Vector4& r1,
		const Vector4& r2,
		const float r30, const float r31, const float r32, const float r33
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using 2 Vector 4, direct components, then a Vector 4
	/// <para>
	/// [ r0.x, r0.y, r0.z, r0.w ]
	/// </para>
	/// <para>
	/// [ r1.x, r1.y, r1.z, r1.w ]
	/// </para>
	/// <para>
	/// [ r20, r21, r22, r23 ]
	/// </para>
	/// <para>
	/// [ r3.x, r3.y, r3.z, r3.w ]
	/// </para>
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r1">m[1] Second row</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	/// <param name="r23">m[2, 3] value</param>
	/// <param name="r3">m[3] Fourth row</param>
	Matrix4x4(
		const Vector4& r0,
		const Vector4& r1,
		const float r20, const float r21, const float r22, const float r23,
		const Vector4& r3
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using direct components, 2 Vector 4, then direct components
	/// <para>
	/// [ r00, r01, r02, r03 ]
	/// </para>
	/// <para>
	/// [ r1.x, r1.y, r1.z, r1.w ]
	/// </para>
	/// <para>
	/// [ r2.x, r2.y, r2.z, r2.w ]
	/// </para>
	/// <para>
	/// [ r30, r31, r32, r33 ]
	/// </para>
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r03">m[0, 3] value</param>
	/// <param name="r1">m[1] Second row</param>
	/// <param name="r2">m[2] Third row</param>
	/// <param name="r30">m[3, 0] value</param>
	/// <param name="r31">m[3, 1] value</param>
	/// <param name="r32">m[3, 2] value</param>
	/// <param name="r33">m[3, 3] value</param>
	Matrix4x4(
		const float r00, const float r01, const float r02, const float r03,
		const Vector4& r1,
		const Vector4& r2,
		const float r30, const float r31, const float r32, const float r33
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using direct components, a Vector 4, direct components, then a Vector 4,
	/// <para>
	/// [ r00, r01, r02, r03 ]
	/// </para>
	/// <para>
	/// [ r1.x, r1.y, r1.z, r1.w ]
	/// </para>
	/// <para>
	/// [ r20, r21, r22, r23 ]
	/// </para>
	/// <para>
	/// [ r3.x, r3.y, r3.z, r3.w ]
	/// </para>
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r03">m[0, 3] value</param>
	/// <param name="r1">m[1] Second row</param>
	/// <param name="r20">m[2, 0] value</param>
	/// <param name="r21">m[2, 1] value</param>
	/// <param name="r22">m[2, 2] value</param>
	/// <param name="r23">m[2, 3] value</param>
	/// <param name="r3">m[3] Fourth row</param>
	Matrix4x4(
		const float r00, const float r01, const float r02, const float r03,
		const Vector4& r1,
		const float r20, const float r21, const float r22, const float r23,
		const Vector4& r3
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using direct components, a Vector 4, direct components, then a Vector 4
	/// <para>
	/// [ r00, r01, r02, r03 ]
	/// </para>
	/// <para>
	/// [ r10, r11, r12, r13 ]
	/// </para>
	/// <para>
	/// [ r2.x, r2.y, r2.z, r2.w ]
	/// </para>
	/// <para>
	/// [ r3.x, r3.y, r3.z, r3.w ]
	/// </para>
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r02">m[0, 2] value</param>
	/// <param name="r03">m[0, 3] value</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	/// <param name="r12">m[1, 2] value</param>
	/// <param name="r13">m[1, 3] value</param>
	/// <param name="r2">m[2] Third row</param>
	/// <param name="r3">m[3] Fourth row</param>
	Matrix4x4(
		const float r00, const float r01, const float r02, const float r03,
		const float r10, const float r11, const float r12, const float r13,
		const Vector4& r2,
		const Vector4& r3
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using 4 Vector 4
	/// <para>
	/// [ r0.x, r0.y, r0.z, r0.w ]
	/// </para>
	/// <para>
	/// [ r1.x, r1.y, r1.z, r1.w ]
	/// </para>
	/// <para>
	/// [ r2.x, r2.y, r2.z, r2.w ]
	/// </para>
	/// <para>
	/// [ r3.x, r3.y, r3.z, r3.w ]
	/// </para>
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r1">m[1] Second row</param>
	/// <param name="r2">m[2] Third row</param>
	/// <param name="r3">m[3] Fourth row</param>
	Matrix4x4(
		const Vector4& r0,
		const Vector4& r1,
		const Vector4& r2,
		const Vector4& r3
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using a 2x2 Matrix
	/// <para>
	/// [ mat[0, 0], mat[0, 1], 0, 0 ]
	/// </para>
	/// [ mat[1, 0], mat[1, 1], 0, 0 ]
	/// <para>
	/// [ 0, 0, 0, 0 ]
	/// </para>
	/// <para>
	/// [ 0, 0, 0, 0 ]
	/// </para>
	/// </summary>
	/// <param name="mat">Upper left corner values</param>
	Matrix4x4(
		const Matrix2x2& mat
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using 4 2x2 Matrix
	/// <para>
	/// [ mat0[0, 0], mat0[0, 1], mat1[0, 0], mat1[0, 1] ]
	/// </para>
	/// [ mat0[1, 0], mat0[1, 1], mat1[1, 0], mat1[1, 1] ]
	/// <para>
	/// [ mat2[0, 0], mat2[0, 1], mat3[0, 0], mat3[0, 1] ]
	/// </para>
	/// <para>
	/// [ mat2[1, 0], mat2[1, 1], mat3[1, 0], mat3[1, 1] ]
	/// </para>
	/// </summary>
	/// <param name="mat0">Upper left corner values</param>
	/// <param name="mat1">Upper right corner values</param>
	/// <param name="mat2">Lower left corner values</param>
	/// <param name="mat3">Lower right corner values</param>
	Matrix4x4(
		const Matrix2x2& mat0, const Matrix2x2& mat1,
		const Matrix2x2& mat2, const Matrix2x2& mat3
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using a 3x3 Matrix
	/// <para>
	/// [ mat[0, 0], mat[0, 1], mat[0, 2], 0 ]
	/// </para>
	/// [ mat[1, 0], mat[1, 1], mat[1, 2], 0 ]
	/// <para>
	/// [ mat[2, 0], mat[2, 1], mat[2, 2], 0 ]
	/// </para>
	/// <para>
	/// [ 0, 0, 0, 0 ]
	/// </para>
	/// </summary>
	/// <param name="mat">Upper left corner values</param>
	Matrix4x4(
		const Matrix3x3& mat
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using a 3x3 Matrix and direct components
	/// <para>
	/// [ mat[0, 0], mat[0, 1], mat[0, 2], r03 ]
	/// </para>
	/// [ mat[1, 0], mat[1, 1], mat[1, 2], r13 ]
	/// <para>
	/// [ mat[2, 0], mat[2, 1], mat[2, 2], r23 ]
	/// </para>
	/// <para>
	/// [ r30, r31, r32, r33 ]
	/// </para>
	/// </summary>
	/// <param name="mat">Upper left corner values</param>
	/// <param name="r03">m[0, 3] value</param>
	/// <param name="r13">m[1, 3] value</param>
	/// <param name="r23">m[2, 3] value</param>
	/// <param name="r30">m[3, 0] value</param>
	/// <param name="r31">m[3, 1] value</param>
	/// <param name="r32">m[3, 2] value</param>
	/// <param name="r33">m[3, 3] value</param>
	Matrix4x4(
		const Matrix3x3& mat, const float r03,
		const float r13,
		const float r23,
		const float r30, const float r31, const float r32, const float r33
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using a 3x3 Matrix, direct components and a Vector 3
	/// <para>
	/// [ mat[0, 0], mat[0, 1], mat[0, 2], r03 ]
	/// </para>
	/// [ mat[1, 0], mat[1, 1], mat[1, 2], r13 ]
	/// <para>
	/// [ mat[2, 0], mat[2, 1], mat[2, 2], r23 ]
	/// </para>
	/// <para>
	/// [ r3.x, r3.y, r3.z, r3.w ]
	/// </para>
	/// </summary>
	/// <param name="mat">Upper left corner values</param>
	/// <param name="r03">m[0, 3] value</param>
	/// <param name="r13">m[1, 3] value</param>
	/// <param name="r23">m[2, 3] value</param>
	/// <param name="r3">m[3] Fourth row</param>
	Matrix4x4(
		const Matrix3x3& mat, const float r03,
		const float r13,
		const float r23,
		const Vector4& r3
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using an initializer list of floats, [1;16] range of elements
	/// </summary>
	/// <param name="data">Data</param>
	Matrix4x4(
		const std::initializer_list<float>& data
	);

	/// <summary>
	/// Constructs a 4x4 Matrix using an initializer list of Vector 4, [1;4] range of elements
	/// </summary>
	/// <param name="data">Data</param>
	Matrix4x4(
		const std::initializer_list<Vector4>& data
	);
#pragma endregion

	_NODISCARD Vector4 Diagonal() const;
	_NODISCARD float Trace() const;
	_NODISCARD float Determinant() const;

	void Augment(const MatrixM& in, MatrixM& out) const;

	Matrix4x4& Negate();
	Matrix4x4& Transpose();
	Matrix4x4& Add(const float scalar);
	Matrix4x4& Add(const Matrix4x4& mat);
	Matrix4x4& Multiply(const float scalar);
	Vector4 Multiply(const Vector4& vec);
	Matrix4x4& Multiply(const Matrix4x4& mat);
	static void Multiply(const Matrix4x4& left, const Matrix4x4& right, Matrix4x4& dst);

	static void Translation(const Vector3& translation, Matrix4x4& dst);
	static void Rotation(const Vector3& rotation, Matrix4x4& dst);
	static void Rotation(const float angle, const Vector3& axis, Matrix4x4& dst);
	static void Scaling(const Vector3& scaling, Matrix4x4& dst);

	static void TRS(const Vector3& translation, const float angle, const Vector3& axis, const Vector3& scaling, Matrix4x4& dst);
	static void TRS(const Vector3& translation, const Vector3& rotation, const Vector3& scaling, Matrix4x4& dst);
	static void TRS(const Vector3& translation, const Matrix3x3& rotation, const Vector3& scaling, Matrix4x4& dst);

	/// <summary>
	/// Creates a 4x4 view matrix
	/// </summary>
	/// <param name="eye">Eye (camera) position</param>
	/// <param name="center">Center of the view</param>
	/// <param name="up">Up direction</param>
	/// <param name="dst">Destination matrix</param>
	static void View(
		const Vector3& eye, const Vector3& center, const Vector3& up, Matrix4x4& dst
	);

	/// <summary>
	/// Creates a 4x4 perspective matrix with a symmetric frustum
	/// </summary>
	/// <param name="fovY">Field of view</param>
	/// <param name="aspectRatio">Aspect ratio</param>
	/// <param name="depthNear">Depth near plane</param>
	/// <param name="depthFar">Depth far plane</param>
	/// <param name="dst">Destination matrix</param>
	static void Projection(
		const float fovY, const float aspectRatio, const float zNear, const float zFar, Matrix4x4& dst
	);

	/// <summary>
	/// Creates a 4x4 perspective matrix with a custom frustum
	/// </summary>
	/// <param name="left">Left frustum</param>
	/// <param name="right">Right frustum</param>
	/// <param name="bottom">Bottom frustum</param>
	/// <param name="top">Top frustum</param>
	/// <param name="depthNear">Depth near plane</param>
	/// <param name="depthFar">Depth far plane</param>
	/// <param name="dst">Destination matrix</param>
	static void Projection(
		const float left, const float right, const float bottom, const float top,
		const float zNear, const float zFar, Matrix4x4& dst
	);

	/// <summary>
	/// Creates a 4x4 perspective matrix with an orthographic projection
	/// </summary>
	/// <param name="fovY">Field of view</param>
	/// <param name="left">Left frustum</param>
	/// <param name="right">Right frustum</param>
	/// <param name="bottom">Bottom frustum</param>
	/// <param name="top">Top frustum</param>
	/// <param name="depthNear">Depth near plane</param>
	/// <param name="depthFar">Depth far plane</param>
	/// <param name="dst">Destination matrix</param>
	static void ProjectionOrtho(
		const float left, const float right, const float bottom,
		const float top, const float zNear, const float zFar, Matrix4x4& dst
	);
	
	Vector4 operator[](int i) const;
	Vector4& operator[](int i);

	void Log() const;

	static const Matrix4x4 Identity;
};
