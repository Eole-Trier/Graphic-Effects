#include "core/maths/matrix3x3.h"
#include <cmath>
#include <assert.h>
#include "core/maths/matrixM.h"
#include <iostream>

const Matrix3x3 Matrix3x3::Identity = Matrix3x3(
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
);

Matrix3x3::Matrix3x3()
	: Row0(0), Row1(0), Row2(0)
{
}

Matrix3x3::Matrix3x3(const float value)
	: Row0(value), Row1(value), Row2(value)
{
}

Matrix3x3::Matrix3x3(const float r00, const float r01, const float r02, const float r10, const float r11, const float r12, const float r20, const float r21, const float r22)
	: Row0(r00, r01, r02), Row1(r10, r11, r12), Row2(r20, r21, r22)
{
}

Matrix3x3::Matrix3x3(const Vector3& r0, const float r10, const float r11, const float r12, const float r20, const float r21, const float r22)
	: Row0(r0), Row1(r10, r11, r12), Row2(r20, r21, r22)
{
}

Matrix3x3::Matrix3x3(const float r00, const float r01, const float r02, const Vector3& r1, const float r20, const float r21, const float r22)
	: Row0(r00, r01, r02), Row1(r1), Row2(r20, r21, r22)
{
}

Matrix3x3::Matrix3x3(const float r00, const float r01, const float r02, const float r10, const float r11, const float r12, const Vector3& r2)
	: Row0(r00, r01, r02), Row1(r10, r11, r12), Row2(r2)
{
}

Matrix3x3::Matrix3x3(const Vector3& r0, const Vector3& r1, const float r20, const float r21, const float r22)
	: Row0(r0), Row1(r1), Row2(r20, r21, r22)
{
}

Matrix3x3::Matrix3x3(const Vector3& r0, const float r10, const float r11, const float r12, const Vector3& r2)
	: Row0(r0), Row1(r10, r11, r12), Row2(r2)
{
}

Matrix3x3::Matrix3x3(const float r00, const float r01, const float r02, const Vector3& r1, const Vector3& r2)
	: Row0(r00, r01, r02), Row1(r1), Row2(r2)
{
}

Matrix3x3::Matrix3x3(const Vector3& r0, const Vector3& r1, const Vector3& r2)
	: Row0(r0), Row1(r1), Row2(r2)
{
}

Matrix3x3::Matrix3x3(const Matrix2x2& mat)
	: Row0(mat[0][0], mat[0][1], 0), Row1(mat[1][0], mat[1][1], 0), Row2(0)
{
}

Matrix3x3::Matrix3x3(const Matrix2x2& mat, const float r02, const float r12, const float r20, const float r21, const float r22)
	: Row0(mat[0][0], mat[0][1], r02), Row1(mat[1][0], mat[1][1], r12), Row2(r20, r21, r22)
{
}

Matrix3x3::Matrix3x3(const Matrix2x2& mat, const float r02, const float r12, const Vector3& r2)
	: Row0(mat[0][0], mat[0][1], r02), Row1(mat[1][0], mat[1][1], r12), Row2(r2)
{
}

Matrix3x3::Matrix3x3(const std::initializer_list<float>& data)
{
	const size_t nbrElem = sizeof(Matrix3x3) / sizeof(float);
	size_t size = data.size();
	assert(size <= nbrElem && "Cannot construct a Matrix 3x3 with more than 9 (float) values");

	__assume(size <= nbrElem);

	float* dst = &Row0.x;
	const float* src = data.begin();

	size_t i = 0;
	for (i = 0; i < size; i++)
		*dst++ = *src++;

	if (size == nbrElem)
		return;

	while (i++ < nbrElem)
		*dst++ = 0.f;
}

Matrix3x3::Matrix3x3(const std::initializer_list<Vector3>& data)
{
	const size_t nbrElem = sizeof(Matrix3x3) / sizeof(Vector3);
	size_t size = data.size();
	assert(size <= nbrElem && "Cannot construct a Matrix 2x2 with more than 3 (Vector 3) values");

	__assume(size <= nbrElem);
	
	const Vector3* src = data.begin();

	Row0 = src[0];

	if (size >= 2)
		Row1 = src[1];
	else
		Row1 = Vector3(0);

	if (size == 3)
		Row2 = src[2];
	else
		Row2 = Vector3(0);
}

Vector3 Matrix3x3::Diagonal() const
{
	return Vector3(Row0.x, Row1.y, Row2.z);
}

float Matrix3x3::Trace() const
{
	return Row0.x + Row1.y + Row2.z;
}

float Matrix3x3::Determinant() const
{
	const float det0 = Row1[1] * Row2[2] - Row2[1] * Row1[2];
	const float det1 = Row0[1] * Row2[2] - Row2[1] * Row0[2];
	const float det2 = Row0[1] * Row1[2] - Row1[1] * Row0[2];

	return Row0[0] * det0 - Row1[0] * det1 + Row2[0] * det2;
}

void Matrix3x3::Augment(const MatrixM& in, MatrixM& out) const
{
	assert(in.GetNbrRows() == 3 && "Can't augment 2 matrixs that have a different amount of rows");

	__assume(in.GetNbrRows() == 3);

	out = MatrixM(3 + in.GetNbrColumns(), 3, 0);

	for (uint32_t i = 0; i < 3; i++)
	{
		VectorM& vec = out.GetRow(i);
		const VectorM& srcRight = in.GetRow(i);

		uint32_t j;
		for (j = 0; j < 3; j++)
			vec[j] = (&Row0)[i][j];

		for (uint32_t k = 0; k < in.GetNbrColumns(); k++)
			vec[j++] = srcRight[k];
	}
}

Matrix3x3& Matrix3x3::Negate()
{
	Row0 = -Row0;
	Row1 = -Row1;
	Row2 = -Row2;

	return *this;
}

Matrix3x3& Matrix3x3::Transpose()
{
	std::swap(Row0[1], Row1[0]);
	std::swap(Row0[2], Row2[0]);
	std::swap(Row1[2], Row2[1]);
	return *this;
}

Matrix3x3& Matrix3x3::Add(const float scalar)
{
	Row0 += scalar;
	Row1 += scalar;
	Row2 += scalar;
	return *this;
}

Matrix3x3& Matrix3x3::Add(const Matrix3x3& mat)
{
	Row0 += mat.Row0;
	Row1 += mat.Row1;
	Row2 += mat.Row2;
	return *this;
}

Matrix3x3& Matrix3x3::Multiply(const float scalar)
{
	Row0 *= scalar;
	Row1 *= scalar;
	Row2 *= scalar;
	return *this;
}

Matrix3x3& Matrix3x3::Multiply(const Matrix3x3& mat)
{
	const float r00 = Row0[0] * mat.Row0[0] + Row0[1] * mat.Row1[0] + Row0[2] * mat.Row2[0];
	const float r01 = Row0[0] * mat.Row0[1] + Row0[1] * mat.Row1[1] + Row0[2] * mat.Row2[1];
	const float r02 = Row0[0] * mat.Row0[2] + Row0[1] * mat.Row1[2] + Row0[2] * mat.Row2[2];

	const float r10 = Row1[0] * mat.Row0[0] + Row1[1] * mat.Row1[0] + Row1[2] * mat.Row2[0];
	const float r11 = Row1[0] * mat.Row0[1] + Row1[1] * mat.Row1[1] + Row1[2] * mat.Row2[1];
	const float r12 = Row1[0] * mat.Row0[2] + Row1[1] * mat.Row1[2] + Row1[2] * mat.Row2[2];

	const float r20 = Row2[0] * mat.Row0[0] + Row2[1] * mat.Row1[0] + Row2[2] * mat.Row2[0];
	const float r21 = Row2[0] * mat.Row0[1] + Row2[1] * mat.Row1[1] + Row2[2] * mat.Row2[1];
	const float r22 = Row2[0] * mat.Row0[2] + Row2[1] * mat.Row1[2] + Row2[2] * mat.Row2[2];

	*this = Matrix3x3(r00, r01, r02, r10, r11, r12, r20, r21, r22);

	return *this;
}

Vector3 Matrix3x3::Multiply(const Vector3& vec) const
{
	const float x = vec.x * Row0.x + vec.y * Row0.y + vec.z * Row0.z;
	const float y = vec.x * Row1.x + vec.y * Row1.y + vec.z * Row1.z;
	const float z = vec.x * Row2.x + vec.y * Row2.y + vec.z * Row2.z;

	return Vector3(x, y, z);
}

void Matrix3x3::RotationX(const float angle, Matrix3x3& dst)
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	dst = Matrix3x3(
		1,  0,  0,
		0,  c, -s,
		0,  s,  c
	);
}

void Matrix3x3::RotationY(const float angle, Matrix3x3& dst)
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	dst = Matrix3x3(
		c,  0,  s,
		0,  1,  0,
	   -s,  0,  c
	);
}

void Matrix3x3::RotationZ(const float angle, Matrix3x3& dst)
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	dst = Matrix3x3(
		c, -s,  0,
		s,  c,  0,
		0,  0,  1
	);
}

void Matrix3x3::Rotation(const Vector3& rotation, Matrix3x3& dst)
{
	// Heavily counting on the compiler to optimize this function

	Matrix3x3 rotX;
	Matrix3x3 rotY;
	Matrix3x3 rotZ;

	RotationX(rotation.x, rotX);
	RotationY(rotation.y, rotY);
	RotationZ(rotation.z, rotZ);

	rotZ.Multiply(rotY).Multiply(rotX);
	dst = rotZ;
}


Vector3 Matrix3x3::operator[](int i) const
{
	assert(i == 0 || i == 1 || i == 2 && "Matrix 3x3 subscript out of range");
	__assume(i == 0 || i == 1 || i == 2);

	return (&Row0)[i];
}

Vector3& Matrix3x3::operator[](int i)
{
	assert(i == 0 || i == 1 || i == 2 && "Matrix 3x3 subscript out of range");
	__assume(i == 0 || i == 1 || i == 2);

	return (&Row0)[i];
}

void Matrix3x3::Log() const
{
	std::cout << "[ " << Row0.x << ", " << Row0.y << ", " << Row0.z << " ]" << std::endl;
	std::cout << "[ " << Row1.x << ", " << Row1.y << ", " << Row1.z << " ]" << std::endl;
	std::cout << "[ " << Row2.x << ", " << Row2.y << ", " << Row2.z << " ]" << std::endl << std::endl;
}
