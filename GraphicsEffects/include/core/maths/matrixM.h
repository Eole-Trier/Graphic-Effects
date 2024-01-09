#pragma once

#include <memory>
#include "core/maths/vectorM.h"

class MatrixM
{
private:
	std::shared_ptr<VectorM[]> mValues;
	uint32_t mColumns;
	uint32_t mRows;
	bool mIsSquare;

public:
	// <summary>
	/// Creates a fully empty Matrix M object, ONLY USE THIS CONSTRUCTOR IF YOU'RE DOING A COPY AFTER
	/// </summary>
	MatrixM();

	/// <summary>
	/// Creates a Matrix M object with a default value
	/// </summary>
	/// <param name="_size">Size</param>
	/// <param name="defaultValue">Default value</param>
	MatrixM(const uint32_t _size, const float defaultValue);

	/// <summary>
	/// Creates a Matrix M object with the specified number of columns/rows
	/// </summary>
	/// <param name="_columns">Number of columns</param>
	/// <param name="_rows">Number of rows</param>
	/// <param name="defaultValue">Default value</param>
	MatrixM(const uint32_t _columns, const uint32_t _rows, const float defaultValue);

	
	MatrixM(const uint32_t _columns, const uint32_t _rows, const std::initializer_list<float>& data);

	// Prohibit copy constructor because of the smart pointer, the shallow/deep copy methods shall be used instead
	MatrixM(const MatrixM&) = delete;

	_NODISCARD VectorM Diagonal() const;
	_NODISCARD float Trace() const;

	_NODISCARD VectorM& GetRow(uint32_t row);
	_NODISCARD const VectorM& GetRow(uint32_t row) const;

	_NODISCARD uint32_t GetNbrColumns() const;
	_NODISCARD uint32_t GetNbrRows() const;

	_NODISCARD const bool IsSquare() const;
	_NODISCARD const bool IsDiagonal() const;

	void GaussJordanPivot();
	_NODISCARD bool Inverse(MatrixM& dst) const;

	void Augment(const MatrixM& in, MatrixM& out) const;
	void Transpose(MatrixM& out) const;
	
	MatrixM& Negate();
	MatrixM& Add(const float scalar);
	MatrixM& Add(const MatrixM& mat);
	MatrixM& Multiply(const float scalar);
	MatrixM& Multiply(const MatrixM& mat);

	_NODISCARD float Determinant() const;
	void SubMatrix(const uint32_t x, const uint32_t y, const uint32_t sizeX, const uint32_t sizeY,
		const bool wrapAround, MatrixM& dst) const;

	/// <summary>
	/// Creates a shallow copy of the current matrix, and puts into the "out" parameter
	/// The shallow copy shares the pointer to the data of the matrix, it does not duplicate the values
	/// </summary>
	/// <param name="out">Destination matrix</param>
	void ShallowCopy(MatrixM& out);

	/// <summary>
	/// Creates a deep copy of the current matrix, and puts into the "out" parameter
	/// The deep copy does not share the pointer to the data of the matrix, it fully duplicates all the data
	/// </summary>
	/// <param name="out">Destination matrix</param>
	void DeepCopy(MatrixM& out) const;

	_NODISCARD VectorM& operator[](uint32_t i);
	_NODISCARD const VectorM& operator[](uint32_t i) const;

	MatrixM& operator=(const MatrixM& mat);

	static void GetIdentity(uint32_t size, MatrixM& out);

	void Log();
};
