#pragma once

#include <initializer_list>
#include <vector>
#include <stdint.h>

class Vector2;
class Vector3;
class Vector4;

class VectorM
{
private:
	std::vector<float> mValues;
	uint32_t mSize;
public:
	/// <summary>
	/// Creates a fully empty Vector M object, ONLY USE THIS CONSTRUCTOR IF YOU'RE DOING A COPY AFTER
	/// </summary>
	VectorM();

	/// <summary>
	/// Creates a Vector M object with a specified size, VALUES ARE UN-INITIALIZED
	/// </summary>
	/// <param name="_size"></param>
	VectorM(const uint32_t _size);

	/// <summary>
	/// Creates a Vector M object with a default value
	/// </summary>
	/// <param name="_size">Size</param>
	/// <param name="defaultValue">Default value</param>
	VectorM(const uint32_t _size, const float defaultValue);

	/// <summary>
	/// Creates a Vector M object via an initializer list
	/// </summary>
	/// <param name="data">Data</param>
	VectorM(const std::initializer_list<float>& data);

	VectorM(const VectorM& vec);

	~VectorM();

	/// <summary>
	/// Returns the size of the Vector M (M value)
	/// </summary>
	/// <returns></returns>
	_NODISCARD uint32_t Size() const;

	/// <summary>
	/// Gets the norm of the Vector M
	/// </summary>
	/// <returns>Result</returns>
	_NODISCARD float Norm() const;

	/// <summary>
	/// Gets the squared norm of the Vector M
	/// </summary>
	/// <returns>Result</returns>
	_NODISCARD float NormSquared() const;

	/// <summary>
	/// Normalizes the Vectorm M
	/// </summary>
	/// <returns>Ref to this</returns>
	VectorM& Normalize();

	/// <summary>
	/// Normalizes the Vectorm M (checks for 0)
	/// </summary>
	/// <returns>Ref to this</returns>
	VectorM& NormalizeSafe();

	/// <summary>
	/// Negates the Vector M
	/// </summary>
	/// <returns>Ref to this</returns>
	VectorM& Negate();

	/// <summary>
	/// Adds a scalar value to the Vector M
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Ref to this</returns>
	VectorM& Add(const float scalar);

	/// <summary>
	/// Adds a Vector M to the Vector M
	/// </summary>
	/// <param name="vec">Vector to add</param>
	/// <returns>Ref to this</returns>
	VectorM& Add(const VectorM& vec);

	/// <summary>
	/// Mulitplies the Vector M by a scalar value
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Ref to this</returns>
	VectorM& Multiply(const float scalar);

	/// <summary>
	/// Mulitplies the Vector M by another Vector M
	/// </summary>
	/// <param name="vec">Vector to multiply by</param>
	/// <returns>Ref to this</returns>
	VectorM& Multiply(const VectorM& vec);

	/// <summary>
	/// Divides the Vector M by a scalar value
	/// </summary>
	/// <param name="scalar">Scalar</param>
	/// <returns>Ref to this</returns>
	VectorM& Divide(const float scalar);

	/// <summary>
	/// Divides the Vector M by another Vector M
	/// </summary>
	/// <param name="vec">Vector to divide by</param>
	/// <returns>Ref to this</returns>
	VectorM& Divide(const VectorM& vec);

	/// <summary>
	/// Calculates the dot product between two Vector M of the same length
	/// </summary>
	/// <param name="a">First vector</param>
	/// <param name="b">Second vector</param>
	/// <returns>Result</returns>
	_NODISCARD static float DotProduct(const VectorM& a, const VectorM& b);

	/// <summary>
	/// Calculates the distance between two Vector M of the same length
	/// </summary>
	/// <param name="a">First vector</param>
	/// <param name="b">Second vector</param>
	/// <returns>Result</returns>
	_NODISCARD static float Distance(const VectorM& a, const VectorM& b);

	/// <summary>
	/// Creates a shallow copy of the current vector, and puts into the "out" parameter
	/// The shallow copy shares the pointer to the data of the vector, it does not duplicate the values
	/// </summary>
	/// <param name="out">Destination vector</param>
	void ShallowCopy(VectorM& out);

	/// <summary>
	/// Creates a deep copy of the current vector, and puts into the "out" parameter
	/// The deep copy does not sharedthe pointer to the data of the vector, it fully duplicates all the data
	/// </summary>
	/// <param name="out">Destination vector</param>
	void DeepCopy(VectorM& out) const;

	/// <summary>
	/// Logs the Vector M to the console
	/// </summary>
	void Log() const;

	VectorM& operator=(const VectorM& vec);

	/// <summary>
	/// Setter for the vector M via array indexing
	/// </summary>
	/// <param name="i">Index [-Size;Size[ range</param>
	/// <returns>Reference to the value</returns>
	_NODISCARD float& operator[](int i);

	/// <summary>
	/// Getter for the vector via array indexing
	/// </summary>
	/// <param name="i">Index [-Size;Size[ range</param>
	/// <returns>Value</returns>
	_NODISCARD float  operator[](int i) const;

	_NODISCARD operator Vector2() const;
	_NODISCARD operator Vector3() const;
	_NODISCARD operator Vector4() const;
};
