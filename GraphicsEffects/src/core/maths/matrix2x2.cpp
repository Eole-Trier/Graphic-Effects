#include "core/maths/Matrix2x2.h"
#include "core/maths/matrixM.h"
#include <iostream>
#include <assert.h>

const Matrix2x2 Matrix2x2::Identity = Matrix2x2(
	1, 0,
	0, 1
);

Matrix2x2::Matrix2x2()
	: Row0(), Row1()
{
}

Matrix2x2::Matrix2x2(const float value)
	: Row0(value), Row1(value)
{
}

Matrix2x2::Matrix2x2(const float r00, const float r01, const float r10, const float r11)
	: Row0(r00, r01), Row1(r10, r11)
{
}

Matrix2x2::Matrix2x2(const Vector2 r0, const float r10, const float r11)
	: Row0(r0), Row1(r10, r11)
{
}

Matrix2x2::Matrix2x2(const float r00, const float r01, const Vector2 r1)
	: Row0(r00, r01), Row1(r1)
{
}

Matrix2x2::Matrix2x2(const Vector2 r0, const Vector2 r1)
	: Row0(r0), Row1(r1)
{
}

Matrix2x2::Matrix2x2(const std::initializer_list<float>& data)
{
	size_t size = data.size();
	assert(size <= 4 && "Cannot construct a Matrix 2x2 with more than 4 (float) values");

	__assume(size <= 4);

	float* dst = &Row0.x;
	const float* src = data.begin();

	size_t i = 0;
	for (i = 0; i < size; i++)
		*dst++ = *src++;

	if (size == 4)
		return;

	while (i++ < 4)
		*dst++ = 0.f;
}

Matrix2x2::Matrix2x2(const std::initializer_list<Vector2>& data)
{
	size_t size = data.size();
	assert(size <= 2 && "Cannot construct a Matrix 2x2 with more than 2 (Vector2) values");

	__assume(size <= 2);

	const Vector2* src = data.begin();
	Row0 = src[0];
	if (size == 2)
		Row1 = src[1];
	else
		Row1 = Vector2(0);
}

Vector2 Matrix2x2::Diagonal() const
{
	return Vector2(Row0.x, Row1.y);
}

float Matrix2x2::Trace() const
{
	return Row0.x + Row1.y;
}

Matrix2x2& Matrix2x2::Negate()
{
	Row0 = -Row0;
	Row1 = -Row1;

	return *this;
}

Matrix2x2& Matrix2x2::Transpose()
{
	std::swap(Row0.y, Row1.x);

	return *this;
}

Matrix2x2& Matrix2x2::Add(const float scalar)
{
	Row0 += scalar;
	Row1 += scalar;

	return *this;
}

Matrix2x2& Matrix2x2::Add(const Matrix2x2& mat)
{
	Row0 += mat.Row0;
	Row1 += mat.Row1;

	return *this;
}

Matrix2x2& Matrix2x2::Multiply(const float scalar)
{
	Row0 *= scalar;
	Row1 *= scalar;

	return *this;
}

Matrix2x2& Matrix2x2::Multiply(const Matrix2x2& mat)
{
	const float r00 = Row0[0] * mat.Row0[0] + Row0[1] * mat.Row1[0];
	const float r01 = Row0[0] * mat.Row0[1] + Row0[1] * mat.Row1[1];
	const float r10 = Row1[0] * mat.Row0[0] + Row1[1] * mat.Row1[0];
	const float r11 = Row1[0] * mat.Row0[1] + Row1[1] * mat.Row1[1];

	Row0 = Vector2(r00, r01);
	Row1 = Vector2(r10, r11);

	return *this;
}

float Matrix2x2::Determinant() const
{
	return Vector2::CrossProduct(Row0, Row1);
}

void Matrix2x2::Augment(const MatrixM& in, MatrixM& out) const
{
	assert(in.GetNbrRows() == 2 && "Can't augment 2 matrixs that have a different amount of rows");

	__assume(in.GetNbrRows() == 2);

	out = MatrixM(2 + in.GetNbrColumns(), 2, 0);
	

	for (uint32_t i = 0; i < 2; i++)
	{
		VectorM& vec = out.GetRow(i);
		const VectorM& srcRight = in.GetRow(i);

		uint32_t j;
		for (j = 0; j < 2; j++)
			vec[j] = (&Row0)[i][j];

		for (uint32_t k = 0; k < in.GetNbrColumns(); k++)
			vec[j++] = srcRight[k];
	}
}

Vector2 Matrix2x2::operator[](int i) const
{
	assert(i == 0 || i == 1 && "Matrix 2 subscript out of range");

	__assume(i == 0 || i == 1);

	return (&Row0)[i];
}

Vector2& Matrix2x2::operator[](int i)
{
	assert(i == 0 || i == 1 && "Matrix 2 subscript out of range");

	__assume(i == 0 || i == 1);

	return (&Row0)[i];
}

void Matrix2x2::Log() const
{
	std::cout << "[ " << Row0.x << ", " << Row0.y << " ]" << std::endl;
	std::cout << "[ " << Row1.x << ", " << Row1.y << " ]" << std::endl;
}
