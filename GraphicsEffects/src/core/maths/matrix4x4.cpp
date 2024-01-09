#include "core/maths/matrix4x4.h"
#include "core/maths/matrixM.h"
#include <assert.h>
#include <cmath>
#include <iostream>

const Matrix4x4 Matrix4x4::Identity = Matrix4x4(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
);

Matrix4x4::Matrix4x4()
	: Row0(0), Row1(0), Row2(0), Row3(0)
{
}

Matrix4x4::Matrix4x4(const float value)
	: Row0(value), Row1(value), Row2(value), Row3(value)
{
}

Matrix4x4::Matrix4x4(const float r00, const float r01, const float r02, const float r03, const float r10, const float r11, const float r12, const float r13, const float r20, const float r21, const float r22, const float r23, const float r30, const float r31, const float r32, const float r33)
	: Row0(r00, r01, r02, r03), Row1(r10, r11, r12, r13), Row2(r20, r21, r22, r23), Row3(r30, r31, r32, r33)
{
}

Matrix4x4::Matrix4x4(const Vector4& r0, const float r10, const float r11, const float r12, const float r13, const float r20, const float r21, const float r22, const float r23, const float r30, const float r31, const float r32, const float r33)
	: Row0(r0), Row1(r10, r11, r12, r13), Row2(r20, r21, r22, r23), Row3(r30, r31, r32, r33)
{
}

Matrix4x4::Matrix4x4(const float r00, const float r01, const float r02, const float r03, const Vector4& r1, const float r20, const float r21, const float r22, const float r23, const float r30, const float r31, const float r32, const float r33)
	: Row0(r00, r01, r02, r03), Row1(r1), Row2(r20, r21, r22, r23), Row3(r30, r31, r32, r33)
{
}

Matrix4x4::Matrix4x4(const float r00, const float r01, const float r02, const float r03, const float r10, const float r11, const float r12, const float r13, const Vector4& r2, const float r30, const float r31, const float r32, const float r33)
	: Row0(r00, r01, r02, r03), Row1(r10, r11, r12, r13), Row2(r2), Row3(r30, r31, r32, r33)
{
}

Matrix4x4::Matrix4x4(const float r00, const float r01, const float r02, const float r03, const float r10, const float r11, const float r12, const float r13, const float r20, const float r21, const float r22, const float r23, const Vector4& r3)
	: Row0(r00, r01, r02, r03), Row1(r10, r11, r12, r13), Row2(r20, r21, r22, r23), Row3(r3)
{
}

Matrix4x4::Matrix4x4(const Vector4& r0, const Vector4& r1, const float r20, const float r21, const float r22, const float r23, const float r30, const float r31, const float r32, const float r33)
	: Row0(r0), Row1(r1), Row2(r20, r21, r22, r23), Row3(r30, r31, r32, r33)
{
}

Matrix4x4::Matrix4x4(const Vector4& r0, const float r10, const float r11, const float r12, const float r13, const Vector4& r2, const float r30, const float r31, const float r32, const float r33)
	: Row0(r0), Row1(r10, r11, r12, r13), Row2(r2), Row3(r30, r31, r32, r33)
{
}

Matrix4x4::Matrix4x4(const Vector4& r0, const float r10, const float r11, const float r12, const float r13, const float r20, const float r21, const float r22, const float r23, const Vector4& r3)
	: Row0(r0), Row1(r10, r11, r12, r13), Row2(r20, r21, r22, r23), Row3(r3)
{
}

Matrix4x4::Matrix4x4(const Vector4& r0, const Vector4& r1, const Vector4& r2, const float r30, const float r31, const float r32, const float r33)
	: Row0(r0), Row1(r1), Row2(r2), Row3(r30, r31, r32, r33)
{
}

Matrix4x4::Matrix4x4(const Vector4& r0, const Vector4& r1, const float r20, const float r21, const float r22, const float r23, const Vector4& r3)
	: Row0(r0), Row1(r1), Row2(r20, r21, r22, r23), Row3(r3)
{
}

Matrix4x4::Matrix4x4(const float r00, const float r01, const float r02, const float r03, const Vector4& r1, const Vector4& r2, const float r30, const float r31, const float r32, const float r33)
	: Row0(r00, r01, r02, r03), Row1(r1), Row2(r2), Row3(r30, r31, r32, r33)
{
}

Matrix4x4::Matrix4x4(const float r00, const float r01, const float r02, const float r03, const Vector4& r1, const float r20, const float r21, const float r22, const float r23, const Vector4& r3)
	: Row0(r00, r01, r02, r03), Row1(r1), Row2(r20, r21, r22, r23), Row3(r3)
{
}

Matrix4x4::Matrix4x4(const float r00, const float r01, const float r02, const float r03, const float r10, const float r11, const float r12, const float r13, const Vector4& r2, const Vector4& r3)
	: Row0(r00, r01, r02, r03), Row1(r10, r11, r12, r13), Row2(r2), Row3(r3)
{
}

Matrix4x4::Matrix4x4(const Vector4& r0, const Vector4& r1, const Vector4& r2, const Vector4& r3)
	: Row0(r0), Row1(r1), Row2(r2), Row3(r3)
{
}

Matrix4x4::Matrix4x4(const Matrix2x2& mat)
	: Row0(mat[0][0], mat[0][1], 0, 0), Row1(mat[1][0], mat[1][1], 0, 0), Row2(0), Row3(0)
{
}

Matrix4x4::Matrix4x4(const Matrix2x2& mat0, const Matrix2x2& mat1, const Matrix2x2& mat2, const Matrix2x2& mat3)
	: Row0(mat0[0][0], mat0[0][1], mat1[0][0], mat1[0][1]), Row1(mat0[1][0], mat0[1][1], mat1[1][0], mat1[1][1]),
	  Row2(mat2[0][0], mat2[0][1], mat3[0][0], mat3[0][1]), Row3(mat2[1][0], mat2[1][1], mat3[1][0], mat3[1][1])
{
}

Matrix4x4::Matrix4x4(const Matrix3x3& mat)
	: Row0(mat[0][0], mat[0][1], mat[0][2], 0), Row1(mat[1][0], mat[1][1], mat[1][2], 0),
	  Row2(mat[2][0], mat[2][1], mat[2][2], 0), Row3(0)
{
}

Matrix4x4::Matrix4x4(const Matrix3x3& mat, const float r03, const float r13, const float r23, const float r30, const float r31, const float r32, const float r33)
	: Row0(mat[0][0], mat[0][1], mat[0][2], r03), Row1(mat[1][0], mat[1][1], mat[1][2], r13),
	  Row2(mat[2][0], mat[2][1], mat[2][2], r23), Row3(r30, r31, r32, r33)
{
}

Matrix4x4::Matrix4x4(const Matrix3x3& mat, const float r03, const float r13, const float r23, const Vector4& r3)
	: Row0(mat[0][0], mat[0][1], mat[0][2], r03), Row1(mat[1][0], mat[1][1], mat[1][2], r13),
	  Row2(mat[2][0], mat[2][1], mat[2][2], r23), Row3(r3)
{
}

Matrix4x4::Matrix4x4(const std::initializer_list<float>& data)
{
	const size_t nbrElem = sizeof(Matrix4x4) / sizeof(float);
	size_t size = data.size();
	assert(size <= nbrElem && "Cannot construct a Matrix 4x4 with more than 16 (float) values");

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

Matrix4x4::Matrix4x4(const std::initializer_list<Vector4>& data)
{
	const size_t nbrElem = sizeof(Matrix4x4) / sizeof(Vector4);
	size_t size = data.size();
	assert(size <= nbrElem && "Cannot construct a Matrix 2x2 with more than 3 (Vector 3) values");

	__assume(size <= nbrElem);

	const Vector4* src = data.begin();

	Row0 = src[0];

	if (size >= 2)
		Row1 = src[1];
	else
		Row1 = Vector4(0);

	if (size >= 3)
		Row2 = src[2];
	else
		Row2 = Vector4(0);

	if (size == 4)
		Row3 = src[3];
	else
		Row3 = Vector4(0);
}

Vector4 Matrix4x4::Diagonal() const
{
	return Vector4(Row0[0], Row1[1], Row2[2], Row3[3]);
}

float Matrix4x4::Trace() const
{
	return Row0[0] + Row1[1] + Row2[2] + Row3[3];
}

float Matrix4x4::Determinant() const
{
	Matrix3x3 subMat;
	float det = 0.f;

	subMat = Matrix3x3(
		Row1.y, Row1.z, Row1.w,
		Row2.y, Row2.z, Row2.w,
		Row3.y, Row3.z, Row3.w
	);
	det += Row0.x * subMat.Determinant();

	subMat.Row0 = Vector3(Row0.y, Row0.z, Row0.w);
	det -= Row1.x * subMat.Determinant();

	subMat = Matrix3x3(
		Row0.y, Row0.z, Row0.w,
		Row1.y, Row1.z, Row1.w,
		Row3.y, Row3.z, Row3.w
	);
	det += Row2.x * subMat.Determinant();

	subMat.Row2 = Vector3(Row2.y, Row2.z, Row2.w);
	det -= Row3.x * subMat.Determinant();
	
	return det;
}


void Matrix4x4::Augment(const MatrixM& in, MatrixM& out) const
{
	assert(in.GetNbrRows() == 4 && "Can't augment 2 matrices that have a different amount of rows");

	__assume(in.GetNbrRows() == 4);

	out = MatrixM(4 + in.GetNbrColumns(), 4, 0);


	for (uint32_t i = 0; i < 4; i++)
	{
		VectorM& vec = out.GetRow(i);
		const VectorM& srcRight = in.GetRow(i);

		uint32_t j;
		for (j = 0; j < 4; j++)
			vec[j] = (&Row0)[i][j];

		for (uint32_t k = 0; k < in.GetNbrColumns(); k++)
			vec[j++] = srcRight[k];
	}
}


Matrix4x4& Matrix4x4::Negate()
{
	Row0 = -Row0;
	Row1 = -Row1;
	Row2 = -Row2;
	Row3 = -Row3;

	return *this;
}

Matrix4x4& Matrix4x4::Transpose()
{
	std::swap(Row0[1], Row1[0]);
	std::swap(Row0[2], Row2[0]);
	std::swap(Row0[3], Row3[0]);

	std::swap(Row1[2], Row2[1]);
	std::swap(Row1[3], Row3[1]);

	std::swap(Row2[3], Row3[2]);

	return *this;
}

Matrix4x4& Matrix4x4::Add(const float scalar)
{
	Row0 += scalar;
	Row1 += scalar;
	Row2 += scalar;
	Row3 += scalar;

	return *this;
}

Matrix4x4& Matrix4x4::Add(const Matrix4x4& mat)
{
	Row0 += mat.Row0;
	Row1 += mat.Row1;
	Row2 += mat.Row2;
	Row3 += mat.Row3;

	return *this;
}

Matrix4x4& Matrix4x4::Multiply(const float scalar)
{
	Row0 *= scalar;
	Row1 *= scalar;
	Row2 *= scalar;
	Row3 *= scalar;

	return *this;
}

Vector4 Matrix4x4::Multiply(const Vector4& vec)
{
	const float x = vec.x * Row0.x + vec.y * Row0.y + vec.z * Row0.z + vec.w * Row0.w;
	const float y = vec.x * Row1.x + vec.y * Row1.y + vec.z * Row1.z + vec.w * Row1.w;
	const float z = vec.x * Row2.x + vec.y * Row2.y + vec.z * Row2.z + vec.w * Row2.w;
	const float w = vec.x * Row3.x + vec.y * Row3.y + vec.z * Row3.z + vec.w * Row3.w;

	return Vector4(x, y, z, w);
}

Matrix4x4& Matrix4x4::Multiply(const Matrix4x4& mat)
{
	Row0 = Vector4(
		Row0[0] * mat.Row0[0] + Row0[1] * mat.Row1[0] + Row0[2] * mat.Row2[0] + Row0[3] * mat.Row3[0],
		Row0[0] * mat.Row0[1] + Row0[1] * mat.Row1[1] + Row0[2] * mat.Row2[1] + Row0[3] * mat.Row3[1],
		Row0[0] * mat.Row0[2] + Row0[1] * mat.Row1[2] + Row0[2] * mat.Row2[2] + Row0[3] * mat.Row3[2],
		Row0[0] * mat.Row0[3] + Row0[1] * mat.Row1[3] + Row0[2] * mat.Row2[3] + Row0[3] * mat.Row3[3]
	);
	Row1 = Vector4(
		Row1[0] * mat.Row0[0] + Row1[1] * mat.Row1[0] + Row1[2] * mat.Row2[0] + Row1[3] * mat.Row3[0],
		Row1[0] * mat.Row0[1] + Row1[1] * mat.Row1[1] + Row1[2] * mat.Row2[1] + Row1[3] * mat.Row3[1],
		Row1[0] * mat.Row0[2] + Row1[1] * mat.Row1[2] + Row1[2] * mat.Row2[2] + Row1[3] * mat.Row3[2],
		Row1[0] * mat.Row0[3] + Row1[1] * mat.Row1[3] + Row1[2] * mat.Row2[3] + Row1[3] * mat.Row3[3]
	);
	Row2 = Vector4(
		Row2[0] * mat.Row0[0] + Row2[1] * mat.Row1[0] + Row2[2] * mat.Row2[0] + Row2[3] * mat.Row3[0],
		Row2[0] * mat.Row0[1] + Row2[1] * mat.Row1[1] + Row2[2] * mat.Row2[1] + Row2[3] * mat.Row3[1],
		Row2[0] * mat.Row0[2] + Row2[1] * mat.Row1[2] + Row2[2] * mat.Row2[2] + Row2[3] * mat.Row3[2],
		Row2[0] * mat.Row0[3] + Row2[1] * mat.Row1[3] + Row2[2] * mat.Row2[3] + Row2[3] * mat.Row3[3]
	);
	Row3 = Vector4(
		Row3[0] * mat.Row0[0] + Row3[1] * mat.Row1[0] + Row3[2] * mat.Row2[0] + Row3[3] * mat.Row3[0],
		Row3[0] * mat.Row0[1] + Row3[1] * mat.Row1[1] + Row3[2] * mat.Row2[1] + Row3[3] * mat.Row3[1],
		Row3[0] * mat.Row0[2] + Row3[1] * mat.Row1[2] + Row3[2] * mat.Row2[2] + Row3[3] * mat.Row3[2],
		Row3[0] * mat.Row0[3] + Row3[1] * mat.Row1[3] + Row3[2] * mat.Row2[3] + Row3[3] * mat.Row3[3]
	);

	return *this;
}

void Matrix4x4::Multiply(const Matrix4x4& left, const Matrix4x4& right, Matrix4x4& dst)
{
	dst.Row0 = Vector4(
		left.Row0[0] * right.Row0[0] + left.Row0[1] * right.Row1[0] + left.Row0[2] * right.Row2[0] + left.Row0[3] * right.Row3[0],
		left.Row0[0] * right.Row0[1] + left.Row0[1] * right.Row1[1] + left.Row0[2] * right.Row2[1] + left.Row0[3] * right.Row3[1],
		left.Row0[0] * right.Row0[2] + left.Row0[1] * right.Row1[2] + left.Row0[2] * right.Row2[2] + left.Row0[3] * right.Row3[2],
		left.Row0[0] * right.Row0[3] + left.Row0[1] * right.Row1[3] + left.Row0[2] * right.Row2[3] + left.Row0[3] * right.Row3[3]
	);
	dst.Row1 = Vector4(
		left.Row1[0] * right.Row0[0] + left.Row1[1] * right.Row1[0] + left.Row1[2] * right.Row2[0] + left.Row1[3] * right.Row3[0],
		left.Row1[0] * right.Row0[1] + left.Row1[1] * right.Row1[1] + left.Row1[2] * right.Row2[1] + left.Row1[3] * right.Row3[1],
		left.Row1[0] * right.Row0[2] + left.Row1[1] * right.Row1[2] + left.Row1[2] * right.Row2[2] + left.Row1[3] * right.Row3[2],
		left.Row1[0] * right.Row0[3] + left.Row1[1] * right.Row1[3] + left.Row1[2] * right.Row2[3] + left.Row1[3] * right.Row3[3]
	);
	dst.Row2 = Vector4(
		left.Row2[0] * right.Row0[0] + left.Row2[1] * right.Row1[0] + left.Row2[2] * right.Row2[0] + left.Row2[3] * right.Row3[0],
		left.Row2[0] * right.Row0[1] + left.Row2[1] * right.Row1[1] + left.Row2[2] * right.Row2[1] + left.Row2[3] * right.Row3[1],
		left.Row2[0] * right.Row0[2] + left.Row2[1] * right.Row1[2] + left.Row2[2] * right.Row2[2] + left.Row2[3] * right.Row3[2],
		left.Row2[0] * right.Row0[3] + left.Row2[1] * right.Row1[3] + left.Row2[2] * right.Row2[3] + left.Row2[3] * right.Row3[3]
	);
	dst.Row3 = Vector4(
		left.Row3[0] * right.Row0[0] + left.Row3[1] * right.Row1[0] + left.Row3[2] * right.Row2[0] + left.Row3[3] * right.Row3[0],
		left.Row3[0] * right.Row0[1] + left.Row3[1] * right.Row1[1] + left.Row3[2] * right.Row2[1] + left.Row3[3] * right.Row3[1],
		left.Row3[0] * right.Row0[2] + left.Row3[1] * right.Row1[2] + left.Row3[2] * right.Row2[2] + left.Row3[3] * right.Row3[2],
		left.Row3[0] * right.Row0[3] + left.Row3[1] * right.Row1[3] + left.Row3[2] * right.Row2[3] + left.Row3[3] * right.Row3[3]
	);
}


void Matrix4x4::Translation(const Vector3& translation, Matrix4x4& dst)
{
	dst = Identity;

	dst.Row0[3] = translation.x;
	dst.Row1[3] = translation.y;
	dst.Row2[3] = translation.z;
}

void Matrix4x4::Rotation(const Vector3& rotation, Matrix4x4& dst)
{
	Matrix3x3 rotX;
	Matrix3x3 rotY;
	Matrix3x3 rotZ;

	Matrix3x3::RotationX(rotation.x, rotX);
	Matrix3x3::RotationY(rotation.y, rotY);
	Matrix3x3::RotationZ(rotation.z, rotZ);

	rotZ.Multiply(rotY).Multiply(rotX);

	dst = Matrix4x4(rotZ, 0, 0, 0, 0, 0, 0, 1);
}

void Matrix4x4::Rotation(const float angle, const Vector3& axis, Matrix4x4& dst)
{
	// Based on https://en.wikipedia.org/wiki/Transformation_matrix#Rotation_2

	const float c = std::cos(angle);
	const float s = std::sin(angle);
	const float c2 = 1 - c;

	const float r00 = axis.x * axis.x * c2 + c;
	const float r01 = axis.y * axis.x * c2 - axis.z * s;
	const float r02 = axis.z * axis.x * c2 + axis.y * s;

	const float r10 = axis.x * axis.y * c2 + axis.z * s;
	const float r11 = axis.y * axis.y * c2 + c;
	const float r12 = axis.z * axis.y * c2 - axis.x * s;

	const float r20 = axis.x * axis.z * c2 - axis.y * s;
	const float r21 = axis.y * axis.z * c2 + axis.x * s;
	const float r22 = axis.z * axis.z * c2 + c;

	dst = Matrix4x4(
		r00, r01, r02, 0,
		r10, r11, r12, 0,
		r20, r21, r22, 0,
		0, 0, 0, 1
	);
}

void Matrix4x4::Scaling(const Vector3& scaling, Matrix4x4& dst)
{
	dst = Identity;

	dst.Row0[0] = scaling.x;
	dst.Row1[1] = scaling.y;
	dst.Row2[2] = scaling.z;
}


void Matrix4x4::TRS(const Vector3& translation, const float angle, const Vector3& axis, const Vector3& scaling, Matrix4x4& dst)
{
	Matrix4x4 scalingMat(
		scaling.x, 0, 0, 0,
		0, scaling.y, 0, 0,
		0, 0, scaling.z, 0,
		0, 0, 0, 1
	);

	Matrix4x4::Rotation(angle, axis, dst);
	dst.Row3[3] = 1;
	dst.Multiply(scalingMat);

	dst.Row0[3] = translation.x;
	dst.Row1[3] = translation.y;
	dst.Row2[3] = translation.z;
}

void Matrix4x4::TRS(const Vector3& translation, const Vector3& rotation, const Vector3& scaling, Matrix4x4& dst)
{
	Matrix4x4 scalingMat(
		scaling.x, 0, 0, 0,
		0, scaling.y, 0, 0,
		0, 0, scaling.z, 0,
		0, 0, 0, 1
	);

	Matrix4x4::Rotation(rotation, dst);
	dst.Row3[3] = 1;
	dst.Multiply(scalingMat);

	dst.Row0[3] = translation.x;
	dst.Row1[3] = translation.y;
	dst.Row2[3] = translation.z;
}

void Matrix4x4::TRS(const Vector3& translation, const Matrix3x3& rotation, const Vector3& scaling, Matrix4x4& dst)
{
	Matrix4x4 scalingMat(
		scaling.x, 0, 0, 0,
		0, scaling.y, 0, 0,
		0, 0, scaling.z, 0,
		0, 0, 0, 1
	);

	dst = Matrix4x4(
		rotation
	);
	dst.Row3[3] = 1;
	dst.Multiply(scalingMat);

	dst.Row0[3] = translation.x;
	dst.Row1[3] = translation.y;
	dst.Row2[3] = translation.z;
}

void Matrix4x4::View(const Vector3& eye, const Vector3& center, const Vector3& up, Matrix4x4& dst)
{
	const Vector3 _up = up.NormalizeSafe();

	const Vector3 z = (eye - center).NormalizeSafe();
	const Vector3 x = Vector3::CrossProduct(_up, z).NormalizeSafe();
	const Vector3 y = Vector3::CrossProduct(z, x).NormalizeSafe();

	const float r03 = -Vector3::DotProduct(x, eye);
	const float r13 = -Vector3::DotProduct(y, eye);
	const float r23 = -Vector3::DotProduct(z, eye);

	dst.Row0 = Vector4(x.x,  x.y,  x.z,  r03);
	dst.Row1 = Vector4(y.x,  y.y,  y.z,  r13);
	dst.Row2 = Vector4(z.x,  z.y,  z.z,  r23);
	dst.Row3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

void Matrix4x4::Projection(const float fovY, const float aspectRatio, const float zNear, const float zFar, Matrix4x4& dst)
{
	assert(zFar > zNear && "Z depth far must be greather that Z depth near");
	__assume(zFar > zNear);

	// cot(fovY / 2.0f)
	const float f = 1.0f / std::tan(fovY / 2.0f);
	const float zDiff = zFar - zNear;

	const float r00 = f / aspectRatio;
	const float r22 = -(zFar + zNear) / zDiff;
	const float r23 = -(2 * zFar * zNear) / zDiff;

	dst.Row0 = Vector4(r00,   0.0f,  0.0f,  0.0f);
	dst.Row1 = Vector4(0.0f,  f,     0.0f,  0.0f);
	dst.Row2 = Vector4(0.0f,  0.0f,  r22,   r23);
	dst.Row3 = Vector4(0.0f,  0.0f, -1.0f,  0.0f);
}

void Matrix4x4::Projection(const float left, const float right, const float bottom, const float top,
	const float zNear, const float zFar, Matrix4x4& dst)
{
	assert(zFar > zNear && "Z depth far must be greather that Z depth near");
	__assume(zFar > zNear);

	const float hSub = right - left;
	const float hAdd = right + left;
	const float vSub = top - bottom;
	const float vAdd = top + bottom;
	const float zAdd = zFar + zNear;
	const float zSub = zFar - zNear;

	const float r00 = (2 * zNear) / hSub;
	const float r02 = hAdd / hSub;
	const float r11 = (2 * zNear) / vSub;
	const float r12 = vAdd / vSub;
	const float r22 = -(zAdd / zSub);
	const float r23 = -((2 * zFar * zNear) / zSub);

	dst.Row0 = Vector4(r00,   0.0f,  r02,   0.0f);
	dst.Row1 = Vector4(0.0f,  r11,   r12,   0.0f);
	dst.Row2 = Vector4(0.0f,  0.0f,  r22,   r23);
	dst.Row3 = Vector4(0.0f,  0.0f, -1.0f,  0.0f);
}

void Matrix4x4::ProjectionOrtho(const float left, const float right, const float bottom,
	const float top, const float zNear, const float zFar, Matrix4x4& dst)
{
	// cot(fovY / 2.0f)
	const float hSub = right - left;
	const float hAdd = right + left;
	const float vSub = top - bottom;
	const float vAdd = top + bottom;
	const float zAdd = zFar + zNear;
	const float zSub = zFar - zNear;

	const float r00 = 2.0f / hSub;
	const float r03 = -(hAdd / hSub);
	const float r11 = 2 / vSub;
	const float r13 = -(vAdd / vSub);
	const float r22 = -2.0f / zSub;
	const float r23 = -(zAdd / zSub);

	dst.Row0 = Vector4(r00,   0.0f,  0.0f,  r03);
	dst.Row1 = Vector4(0.0f,  r11,   0.0f,  r13);
	dst.Row2 = Vector4(0.0f,  0.0f,  r22,   r23);
	dst.Row3 = Vector4(0.0f,  0.0f,  0.0f,  1.0f);
}


Vector4 Matrix4x4::operator[](int i) const
{
	assert(i >= 0 && i < 4 && "Matrix 4x4 subscript out of range");
	__assume(i >= 0 && i < 4);

	return (&Row0)[i];
}

Vector4& Matrix4x4::operator[](int i)
{
	assert(i >= 0 && i < 4 && "Matrix 4x4 subscript out of range");
	__assume(i >= 0 && i < 4);

	return (&Row0)[i];
}

void Matrix4x4::Log() const
{
	std::cout << "[ " << Row0.x << ", " << Row0.y << ", " << Row0.z << ", " << Row0.w << " ]" << std::endl;
	std::cout << "[ " << Row1.x << ", " << Row1.y << ", " << Row1.z << ", " << Row1.w << " ]" << std::endl;
	std::cout << "[ " << Row2.x << ", " << Row2.y << ", " << Row2.z << ", " << Row2.w << " ]" << std::endl;
	std::cout << "[ " << Row3.x << ", " << Row3.y << ", " << Row3.z << ", " << Row3.w << " ]" << std::endl;
}
