#include "core/maths/vectorM.h"
#include <assert.h>
#include <cmath>
#include <iostream>

#include "core/maths/vector2.h"
#include "core/maths/vector3.h"
#include "core/maths/vector4.h"

VectorM::VectorM()
	: mSize(0)
{
	mValues.resize(0);
}

VectorM::VectorM(const uint32_t _size)
	: mSize(_size)
{
	mValues.resize(mSize);
}

VectorM::VectorM(const uint32_t _size, const float defaultValue)
	: mSize(_size)
{
	mValues.resize(mSize);

	for (uint32_t i = 0; i < _size; i++)
		mValues[i] = defaultValue;
}

VectorM::VectorM(const std::initializer_list<float>& data)
	: mSize(data.size())
{
	mValues.resize(mSize);

	const float* it = data.begin();
	for (uint32_t i = 0; i < mSize; i++)
		mValues[i] = *it++;
}

VectorM::VectorM(const VectorM& vec)
{
	vec.DeepCopy(*this);
}

VectorM::~VectorM()
{
}

uint32_t VectorM::Size() const
{
	return mSize;
}

float VectorM::Norm() const
{
	float result = 0.f;

	for (uint32_t i = 0; i < mSize; i++)
	{
		float val = mValues[i];
		result += val * val;
	}

	return std::sqrt(result);
}


float VectorM::NormSquared() const
{
	float result = 0.f;

	for (uint32_t i = 0; i < mSize; i++)
	{
		float val = mValues[i];
		result += val * val;
	}

	return result;
}

VectorM& VectorM::Normalize()
{
	const float norm = Norm();
	for (uint32_t i = 0; i < mSize; i++)
		mValues[i] /= norm;

	return *this;
}

VectorM& VectorM::NormalizeSafe()
{
	const float norm = Norm();
	if (norm == 0)
		return *this;

	for (uint32_t i = 0; i < mSize; i++)
		mValues[i] /= norm;

	return *this;
}


VectorM& VectorM::Negate()
{
	for (uint32_t i = 0; i < mSize; i++)
		mValues[i] = -mValues[i];

	return *this;
}

VectorM& VectorM::Add(const float scalar)
{
	for (uint32_t i = 0; i < mSize; i++)
		mValues[i] += scalar;

	return *this;
}

VectorM& VectorM::Add(const VectorM& vec)
{
	for (uint32_t i = 0; i < mSize; i++)
		mValues[i] += vec.mValues[i];

	return *this;
}

VectorM& VectorM::Multiply(const float scalar)
{
	for (uint32_t i = 0; i < mSize; i++)
		mValues[i] *= scalar;

	return *this;
}

VectorM& VectorM::Multiply(const VectorM& vec)
{
	for (uint32_t i = 0; i < mSize; i++)
		mValues[i] *= vec.mValues[i];

	return *this;
}

VectorM& VectorM::Divide(const float scalar)
{
	assert(scalar != 0 && "Cannot divide by 0");

	__assume(scalar != 0);

	for (uint32_t i = 0; i < mSize; i++)
		mValues[i] /= scalar;

	return *this;
}

VectorM& VectorM::Divide(const VectorM& vec)
{
	for (uint32_t i = 0; i < mSize; i++)
		mValues[i] /= vec.mValues[i];

	return *this;
}

float VectorM::DotProduct(const VectorM& a, const VectorM& b)
{
	assert(a.mSize == b.mSize && "Dot product can only be calculated between vectors of the same length");

	__assume(a.mSize == b.mSize);

	float result = 0.f;

	for (uint32_t i = 0; i < a.mSize; i++)
		result += a.mValues[i] * b.mValues[i];

	return result;
}


float VectorM::Distance(const VectorM& a, const VectorM& b)
{
	assert(a.mSize == b.mSize && "Distance can only be calculated between vectors of the same length");
	
	__assume(a.mSize == b.mSize);

	float dist = 0.f;

	for (uint32_t i = 0; i < a.mSize; i++)
	{
		float component = a.mValues[i] - b.mValues[i];
		dist += component * component;
	}

	return std::sqrt(dist);
}

void VectorM::ShallowCopy(VectorM& out)
{
	out.mValues = mValues;
	out.mSize = mSize;
}

void VectorM::DeepCopy(VectorM& out) const
{
	out.mValues = std::vector<float>(mSize);
	out.mSize = mSize;

	for (uint32_t i = 0; i < mSize; i++)
		out.mValues[i] = mValues[i];
}

void VectorM::Log() const
{
	std::cout << "[ ";
	for (uint32_t i = 0; i < mSize; i++)
	{
		std::cout << mValues[i];
		if (i != mSize - 1)
			std::cout << ", ";
	}
	std::cout << " ]" << std::endl;
}

VectorM& VectorM::operator=(const VectorM& vec)
{
	vec.DeepCopy(*this);
	return *this;
}

float& VectorM::operator[](int i)
{
	int32_t size = mSize;

	assert(i < size && i >= -size && "Vector M subscript out of range");

	__assume(i < size && i >= -size);

	// Allows the vector to be indexed via negative numbers, going from the end
	// v[-1] would yield the last element, v[-2] the second to last...
	if (i < 0)
		i = size + i;

	return mValues[i];
}

float VectorM::operator[](int i) const
{
	int32_t size = mSize;

	assert(i < size && i >= -size && "Vector M subscript out of range");

	__assume(i < size && i >= -size);

	if (i < 0)
		i = size + i;

	return mValues[i];
}

VectorM::operator Vector2() const
{
	assert(mSize >= 2 && "Cannot convert to a Vector 2, the vector was too small");

	__assume(mSize >= 2);

	return Vector2(mValues[0], mValues[1]);
}

VectorM::operator Vector3() const
{
	assert(mSize >= 3 && "Cannot convert to a Vector 3, the vector was too small");

	__assume(mSize >= 3);

	return Vector3(mValues[0], mValues[1], mValues[2]);
}

VectorM::operator Vector4() const
{
	assert(mSize >= 4 && "Cannot convert to a Vector 4, the vector was too small");

	__assume(mSize >= 4);

	return Vector4(mValues[0], mValues[1], mValues[2], mValues[3]);
}
