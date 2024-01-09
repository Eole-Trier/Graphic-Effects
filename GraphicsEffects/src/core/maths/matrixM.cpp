#include "core/maths/matrixM.h"
#include "core/maths/vector2.h"
#include <assert.h>
#include <iostream>
#include <string>
#include <algorithm>

MatrixM::MatrixM()
	: mRows(0), mColumns(0)
{
	mValues = std::make_shared<VectorM[]>(mRows);
}

MatrixM::MatrixM(const uint32_t _size, const float defaultValue)
	: mRows(_size), mColumns(_size)
{
	mIsSquare = true;
	mValues = std::make_shared<VectorM[]>(mRows);

	VectorM* vec = mValues.get();

	for (uint32_t i = 0; i < mRows; i++)
		vec[i] = VectorM(mColumns, defaultValue);
}

MatrixM::MatrixM(const uint32_t _columns, const uint32_t _rows, const float defaultValue)
	: mColumns(_columns), mRows(_rows)
{
	mIsSquare = _columns == _rows;
	mValues = std::make_shared<VectorM[]>(mRows);

	VectorM* vec = mValues.get();

	for (uint32_t i = 0; i < mRows; i++)
		vec[i] = VectorM(mColumns, defaultValue);
}

MatrixM::MatrixM(const uint32_t _columns, const uint32_t _rows, const std::initializer_list<float>& data)
	: mColumns(_columns), mRows(_rows)
{
	size_t size = data.size();
	assert(size == mRows * mColumns && "Can only constructs a Matrix M with Rows * Columns values");

	__assume(size == mRows * mColumns);

	mIsSquare = _columns == _rows;
	mValues = std::make_shared<VectorM[]>(mRows);
	VectorM* vec = mValues.get();
	const float* src = data.begin();

	for (uint32_t i = 0; i < mRows; i++)
	{
		vec[i] = VectorM(mColumns);
		for (uint32_t j = 0; j < mColumns; j++)
			vec[i][j] = src[i * mColumns + j];
	}
}

VectorM MatrixM::Diagonal() const
{
	uint32_t size = std::min(mRows, mColumns);
	VectorM diag(size);
	VectorM* vec = mValues.get();

	for (uint32_t i = 0; i < size; i++)
		diag[i] = vec[i][i];

	return diag;
}

float MatrixM::Trace() const
{
	uint32_t size = std::min(mRows, mColumns);
	VectorM* vec = mValues.get();
	float trace = 0.f;

	for (uint32_t i = 0; i < size; i++)
		trace += vec[i][i];

	return trace;
}

VectorM& MatrixM::GetRow(uint32_t row)
{
	assert(row >= 0 && row < mRows && "Matrix M subscript out of range");

	__assume(row >= 0 && row < mRows);

	return mValues.get()[row];
}

const VectorM& MatrixM::GetRow(uint32_t row) const
{
	assert(row >= 0 && row < mRows && "Matrix M subscript out of range");

	__assume(row >= 0 && row < mRows);

	return mValues.get()[row];
}

uint32_t MatrixM::GetNbrColumns() const
{
	return mColumns;
}

uint32_t MatrixM::GetNbrRows() const
{
	return mRows;
}

const bool MatrixM::IsSquare() const
{
	return mIsSquare;
}

const bool MatrixM::IsDiagonal() const
{
	VectorM* data = mValues.get();

	for (uint32_t i = 0; i < mRows; i++)
	{
		for (uint32_t j = 0; j < mRows; j++)
		{
			if (i == j)
				continue;

			if (data[i][j] != 0)
				return false;
		}
	}

	return true;
}

void MatrixM::GaussJordanPivot()
{
	uint32_t lastPivotIndex = 0;
	uint8_t i = 0;

	if (_ITERATOR_DEBUG_LEVEL)
	{
		std::cout << "Start matrix :" << std::endl;
		Log();
	}

	for (uint32_t j = 0; j < mRows; j++)
	{
		// Try find pivot of current column
		float_t pivotValue = GetRow(j)[lastPivotIndex];
		uint8_t currPivotLine = lastPivotIndex;

		for (uint8_t _y = lastPivotIndex; _y < mRows; _y++)
		{
			float_t value = GetRow(_y)[j];
			if (fabsf(value) > pivotValue)
			{
				pivotValue = value;
				currPivotLine = _y;
			}
		}

		if (pivotValue == 0)
			continue;

		if (_ITERATOR_DEBUG_LEVEL)
			std::cout << "Found pivot (" << pivotValue << ") on row " << (int)currPivotLine << std::endl;

		// Normalize pivot row
		GetRow(currPivotLine).Divide(pivotValue);

		if (_ITERATOR_DEBUG_LEVEL)
		{
			std::cout << "Normalizing row " << (int)currPivotLine << std::endl;
			Log();
		}
		
		// Permute rows to have the pivot line at the current row
		if (lastPivotIndex != currPivotLine)
		{
			VectorM& pivotRow = GetRow(currPivotLine);
			VectorM& lastPivotRow = GetRow(lastPivotIndex);

			for (uint8_t _x = 0; _x < mColumns; _x++)
				std::swap(lastPivotRow[_x], pivotRow[_x]);

			if (_ITERATOR_DEBUG_LEVEL)
			{
				std::cout << "Swapping rows " << (int)currPivotLine << " and " << lastPivotIndex << std::endl;
				Log();
			}
		}

		for (uint8_t _y = 0; _y < mRows; _y++)
		{
			if (_y == lastPivotIndex)
				continue;

			VectorM& row = GetRow(_y);

			float_t alpha = row[j];
			for (uint8_t _x = 0; _x < mColumns; _x++)
			{
				float_t iValue = row[_x];
				float_t rValue = GetRow(lastPivotIndex)[_x];
				row[_x] = iValue - rValue * alpha;

				if (fabsf(row[_x]) < 1e-6)
					row[_x] = 0;
			}

			if (_ITERATOR_DEBUG_LEVEL)
			{
				std::cout << "Zero-ing row " << (int)_y << std::endl;
				Log();
			}
		}

		lastPivotIndex++;
	}
}

bool MatrixM::Inverse(MatrixM& dst) const
{
	if (!mIsSquare)
		return false;

	__assume(mRows == mColumns);

	MatrixM identity;
	MatrixM augmented;
	GetIdentity(mRows, identity);
	Augment(identity, augmented);
	augmented.GaussJordanPivot();

	augmented.Log();

	if (!augmented.IsDiagonal())
		return false;

	for (uint32_t i = 0; i < mRows; i++)
	{
		if (augmented[i][i] != 1)
			return false;
	}

	dst = MatrixM(mColumns, mRows, 0);

	for (uint32_t i = 0; i < mRows; i++)
	{
		VectorM& rowDst = dst.GetRow(i);
		VectorM& rowSrc = augmented.GetRow(i);
		for (uint32_t j = 0; j < mColumns; j++)
			rowDst[j] = rowSrc[mColumns + j];
	}

	return true;
}

void MatrixM::Augment(const MatrixM& in, MatrixM& out) const
{
	assert(in.mRows == mRows && "Can't augment 2 matrixs that have a different amount of rows");

	__assume(in.mRows == mRows);

	out = MatrixM(mColumns + in.mColumns, mRows, 0);

	VectorM* data = out.mValues.get();
	VectorM* srcLeft = mValues.get();
	VectorM* srcRight = in.mValues.get();

	for (uint32_t i = 0; i < mRows; i++)
	{
		VectorM& vec = data[i];

		uint32_t j;
		for (j = 0; j < mColumns; j++)
			vec[j] = srcLeft[i][j];
	
		for (uint32_t k = 0; k < in.mColumns; k++)
			vec[j++] = srcRight[i][k];
	}
}

void MatrixM::Transpose(MatrixM& out) const
{
	out = MatrixM(mRows, mColumns, 0);

	VectorM* vec = mValues.get();

	for (uint32_t i = 0; i < mRows; i++)
	{
		for (uint32_t j = 0; j < mColumns; j++)
			out[j][i] = vec[i][j];
	}
}

MatrixM& MatrixM::Negate()
{
	VectorM* vec = mValues.get();

	for (uint32_t i = 0; i < mRows; i++)
		vec->Negate();

	return *this;
}

MatrixM& MatrixM::Add(const float scalar)
{
	VectorM* vec = mValues.get();

	for (uint32_t i = 0; i < mRows; i++)
		vec->Add(scalar);

	return *this;
}

MatrixM& MatrixM::Add(const MatrixM& mat)
{
	assert(mat.mColumns == mColumns && mat.mRows == mRows && "Can't add matrices of different sizes");

	__assume(mat.mColumns == mColumns && mat.mRows == mRows);

	VectorM* vec = mValues.get();

	for (uint32_t i = 0; i < mRows; i++)
		vec[i].Add(mat[i]);

	return *this;
}

MatrixM& MatrixM::Multiply(const float scalar)
{
	VectorM* vec = mValues.get();

	for (uint32_t i = 0; i < mRows; i++)
		vec->Multiply(scalar);

	return *this;
}

MatrixM& MatrixM::Multiply(const MatrixM& mat)
{
	assert(mColumns == mat.mRows && "Can only multiply matrices where the number of column/row differ");

	__assume(mColumns == mat.mRows);

	MatrixM result(mRows, mat.mColumns, 0);

	for (size_t i = 0; i < result.mRows; i++)
	{
		for (size_t j = 0; j < result.mColumns; j++)
		{
			for (size_t k = 0; k < mColumns; k++)
				result[i][j] += mValues[i][k] * mat[k][j];
		}
	}

	result.DeepCopy(*this);

	return *this;
}

float MatrixM::Determinant() const
{
	if (!mIsSquare)
		return 0.f;

	if (mRows == 2)
	{
		return mValues[0][0] * mValues[1][1] - mValues[0][1] * mValues[1][0];
	}

	float det = 0.f;

	MatrixM buffer;
	for (uint32_t i = 0; i < mRows; i++)
	{
		SubMatrix((i + 1) % mRows, 1, mRows - 1, mColumns - 1, false, buffer);
		float subDet = buffer.Determinant();
		subDet *= mValues[i][0];
		if (i & 1)
			det -= subDet;
		else
			det += subDet;
	}

	return det;
}

void MatrixM::SubMatrix(const uint32_t x, const uint32_t y, const uint32_t sizeX, const uint32_t sizeY,
	const bool wrapAround, MatrixM& dst) const
{
	assert(x < mColumns && y < mRows && "Out of range sub-matrix coordinates");
	assert(sizeX <= mColumns && y <= mRows && "Sub-matrix size can't be larger than the source matrix");

	__assume(x < mColumns&& y < mRows);
	__assume(sizeX <= mColumns && y <= mRows);

	dst = MatrixM(sizeX, sizeY, 0);
	uint32_t overflow = x + sizeX - mRows;

	for (uint32_t i = 0; i < sizeX; i++)
	{
		for (uint32_t j = 0; j < sizeY; j++)
		{
			if (i < overflow)
				dst[i][j] = mValues[i][y + j];
			else
				dst[i][j] = mValues[x + i - overflow][y + j];
		}
	}
}

void MatrixM::ShallowCopy(MatrixM& out)
{
	out.mRows = mRows;
	out.mColumns = mColumns;
	out.mIsSquare = mIsSquare;
	out.mValues = mValues;
}

void MatrixM::DeepCopy(MatrixM& out) const
{
	out.mRows = mRows;
	out.mColumns = mColumns;
	out.mIsSquare = mIsSquare;

	out.mValues = std::make_shared<VectorM[]>(mRows);
	VectorM* dst = out.mValues.get();
	VectorM* src = mValues.get();
	
	for (uint32_t i = 0; i < mRows; i++)
		src[i].DeepCopy(dst[i]);
}

VectorM& MatrixM::operator[](uint32_t i)
{
	assert(i >= 0 && i < mRows && "Matrix M subscript out of range");

	__assume(i >= 0 && i < mRows);

	return mValues.get()[i];
}

const VectorM& MatrixM::operator[](uint32_t i) const
{
	assert(i >= 0 && i < mRows && "Matrix M subscript out of range");

	__assume(i >= 0 && i < mRows);

	return mValues.get()[i];
}

MatrixM& MatrixM::operator=(const MatrixM& mat)
{
	mat.DeepCopy(*this);
	return *this;
}

void MatrixM::GetIdentity(uint32_t size, MatrixM& out)
{
	out = MatrixM(size, 0);
	for (uint32_t i = 0; i < size; i++)
		out[i][i] = 1;
}

void MatrixM::Log()
{
	VectorM* vec = mValues.get();

	for (uint32_t i = 0; i < mRows; i++)
	{
		std::cout << "[ ";
		for (uint32_t j = 0; j < mColumns; j++)
		{
			std::cout << std::to_string(vec[i][j]);
			if (j != mColumns - 1)
				std::cout << ", ";
		}
		std::cout << " ]" << std::endl;
	}

	std::cout << std::endl;
}
