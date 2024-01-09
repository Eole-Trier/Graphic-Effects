#pragma once

#include <initializer_list>
#include "core/maths/vector2.h"

class MatrixM;

class Matrix2x2
{
public:
	Vector2 Row0;
	Vector2 Row1;

#pragma region Constructors
	/// <summary>
	/// Constructs an empty 2x2 Matrix
	/// </summary>
	Matrix2x2();

	/// <summary>
	/// Constructs a 2x2 Matrix filled with "value"
	/// <para>
	/// [ value, value ]
	/// </para>
	/// [ value, value ]
	/// </summary>
	/// <param name="value">Value</param>
	Matrix2x2(const float value);

	/// <summary>
	/// Constructs a 2x2 Matrix using direct component values
	/// <para>
	/// [ r00, r01 ]
	/// </para>
	/// [ r10, r11 ]
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	Matrix2x2(const float r00, const float r01, const float r10, const float r11);

	/// <summary>
	/// Constructs a 2x2 Matrix using a Vector 2 and 2 components
	/// <para>
	/// [ r0.x, r0.y ]
	/// </para>
	/// [ r10,  r11  ]
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r10">m[1, 0] value</param>
	/// <param name="r11">m[1, 1] value</param>
	Matrix2x2(const Vector2 r0, const float r10, const float r11);

	/// <summary>
	/// Constructs a 2x2 Matrix using 2 components and a Vector 2
	/// <para>
	/// [ r00,  r01  ]
	/// </para>
	/// [ r1.x, r1.y ]
	/// </summary>
	/// <param name="r00">m[0, 0] value</param>
	/// <param name="r01">m[0, 1] value</param>
	/// <param name="r1">m[1] Second row</param>
	Matrix2x2(const float r00, const float r01, const Vector2 r1);

	/// <summary>
	/// Constructs a 2x2 Matrix using 2 Vector 2
	/// <para>
	/// [ r0.x, r1.x ]
	/// </para>
	/// [ r1.x, r1.y ]
	/// </summary>
	/// <param name="r0">m[0] First row</param>
	/// <param name="r1">m[1] Second row</param>
	Matrix2x2(const Vector2 r0, const Vector2 r1);

	/// <summary>
	/// Constructs a 2x2 Matrix using an initializer list of floats, [1;4] range of elements
	/// </summary>
	/// <param name="data">Data</param>
	Matrix2x2(const std::initializer_list<float>& data);

	/// <summary>
	/// Constructs a 2x2 Matrix using an initializer list of Vector 2, [1;2] range of elements
	/// </summary>
	/// <param name="data">Data</param>
	Matrix2x2(const std::initializer_list<Vector2>& data);

#pragma endregion

	_NODISCARD Vector2 Diagonal() const;
	_NODISCARD float Trace() const;
	_NODISCARD float Determinant() const;

	void Augment(const MatrixM& in, MatrixM& out) const;

	Matrix2x2& Negate();
	Matrix2x2& Transpose();
	Matrix2x2& Add(const float scalar);
	Matrix2x2& Add(const Matrix2x2& mat);
	Matrix2x2& Multiply(const float scalar);
	Matrix2x2& Multiply(const Matrix2x2& mat);

	Vector2 operator[](int i) const;
	Vector2& operator[](int i);

	void Log() const;

	static const Matrix2x2 Identity;
};
