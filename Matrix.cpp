#include "Matrix.h"
#include <cstring>
#include <algorithm>
#include <exception>
#include <utility>

using namespace Linear;
Matrix::Matrix(int m_row, int m_col) : numOfRow(m_row), numOfColumn(m_col)
{
	if (m_row <= 0 || m_col <= 0)
		throw std::exception("row/col size <= 0");
	size = numOfRow * numOfColumn;
	data = new double[m_row * m_col];
	memset(data, 0, sizeof(data));
}

Matrix::Matrix(const Matrix& m) : Matrix(m.numOfRow, m.numOfColumn)
{}

Matrix::Matrix(Matrix&& m) : numOfRow(m.numOfRow), numOfColumn(m.numOfColumn), size(m.size)
{
	data = m.data;
	m.data = nullptr;
}

Matrix::Matrix(double m) : Matrix(1, 1)
{
	data[0] = m;
}

Matrix::Matrix(double m, int n) : Matrix(n, n)
{
	for (int i = 0; i < n; ++i)
	{
		*this[i][i] = m;
	}
}

inline double* Matrix::operator[](int index)
{
	return data + index * numOfColumn;
}

inline const double* Matrix::operator[](int index) const
{
	return data + index * numOfColumn;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	numOfRow = m.numOfRow;
	numOfColumn = m.numOfColumn;
	size = m.size;
	std::copy(m.data, m.data + m.size, data);
	return *this;
}

Matrix& Matrix::operator=(Matrix&& m)
{
	numOfRow = m.numOfRow;
	numOfColumn = m.numOfColumn;
	size = m.size;
	delete[] data;
	data = m.data;
	m.data = nullptr;
	return *this;
}

Matrix Matrix::operator+(const Matrix& m) const&
{
	if (m.numOfRow != numOfRow || m.numOfColumn != numOfColumn)
	{
		throw(std::exception("matrix addition of inconsistent specifications"));
	}
	Matrix out(*this);
	for (int i = 0; i < size; ++i)
	{
		out.data[i] += m.data[i];
	}
	return out;
}

Matrix Matrix::operator+(const Matrix m)&&
{
	if (m.numOfRow != numOfRow || m.numOfColumn != numOfColumn)
	{
		throw(std::exception("matrix addition of inconsistent specifications"));
	}
	Matrix out(std::move(*this));
	for (int i = 0; i < size; ++i)
	{
		out.data[i] += m.data[i];
	}
	return out;
}

Matrix Matrix::operator-() const&
{
	Matrix out(*this);
	for (int i = 0; i < size; ++i)
	{
		out.data[i] = -out.data[i];
	}
	return out;
}

Matrix Matrix::operator-()&&
{
	Matrix out(std::move(*this));
	for (int i = 0; i < size; ++i)
	{
		out.data[i] = -out.data[i];
	}
	return out;
}

Matrix Matrix::operator-(const Matrix& m) const&
{
	if (m.numOfRow != numOfRow || m.numOfColumn != numOfColumn)
	{
		throw(std::exception("matrix deduction of inconsistent specifications"));
	}
	Matrix out(*this);
	for (int i = 0; i < size; ++i)
	{
		out.data[i] -= m.data[i];
	}
	return out;
}

Matrix Matrix::operator-(const Matrix& m)&&
{
	if (m.numOfRow != numOfRow || m.numOfColumn != numOfColumn)
	{
		throw(std::exception("matrix deduction of inconsistent specifications"));
	}
	Matrix out(std::move(*this));
	for (int i = 0; i < size; ++i)
	{
		out.data[i] -= m.data[i];
	}
	return out;
}

Matrix Matrix::operator*(const Matrix& m)const
{
	if (numOfColumn != m.numOfRow)
	{
		throw(std::exception("matrix multiplication of inconsistent specifications"));
	}
	Matrix out(numOfRow, m.numOfColumn);
	for (int i = 0; i < numOfRow; ++i)
	{
		for (int j = 0; j < m.numOfColumn; ++j)
		{
			for (int k = 0; k < numOfColumn; ++k)
			{
				out[i][j] += (*this)[i][k] * m[k][j];
			}
		}
	}
	return out;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
	if (m.numOfRow != numOfRow || m.numOfColumn != numOfColumn)
	{
		throw(std::exception("matrix additon of inconsistent specifications"));
	}
	for (int i = 0; i < size; ++i)
	{
		data[i] += m.data[i];
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
	if (m.numOfRow != numOfRow || m.numOfColumn != numOfColumn)
	{
		throw(std::exception("matrix deduction of inconsistent specifications"));
	}
	for (int i = 0; i < size; ++i)
	{
		data[i] -= m.data[i];
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
	*this = *this * m;
	return *this;
}

Matrix::~Matrix()
{
	delete[] data;
}

RowVector::RowVector(const Matrix& m) : Matrix(m)
{
	if (numOfRow != 1)
		throw (std::exception("An improper matrix conversion to row-vector."));
}

RowVector::RowVector(Matrix&& m) : Matrix(std::move(m))
{
	if (numOfRow != 1)
		throw (std::exception("An improper matrix conversion to row-vector."));
}

RowVector::RowVector(double* ar, int n) : Matrix(1, n)
{
	std::copy(ar, ar + n, data);
}

ColVector RowVector::transpose() const
{
	return ColVector(data, numOfColumn);
}

ColVector::ColVector(const Matrix& m) : Matrix(m)
{
	if (numOfColumn != 1)
		throw (std::exception("An improper matrix conversion to col-vector."));
}

ColVector::ColVector(Matrix&& m) : Matrix(std::move(m))
{
	if (numOfColumn != 1)
		throw (std::exception("An improper matrix conversion to col-vector."));
}

ColVector::ColVector(double* ar, int n) : Matrix(n, 1)
{
	std::copy(ar, ar + n, data);
}

RowVector ColVector::transpose() const
{
	return RowVector(data, numOfRow);
}

Matrix Matrix::transpose() const
{
	if (numOfColumn == 1 || numOfRow == 1)
	{
		Matrix out(*this);
		std::swap(out.numOfRow, out.numOfColumn);
		return out;
	}
	else
	{
		Matrix out(numOfColumn, numOfRow);
		for (int i = 0; i < numOfRow; ++i)
			for (int j = 0; j < numOfColumn; ++j)
			{
				out[j][i] = *this[i][j];
			}
		return out;
	}

}
