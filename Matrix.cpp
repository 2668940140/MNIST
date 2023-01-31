#include "Matrix.h"
#include <cstring>
#include <algorithm>
#include <exception>
#include <utility>
#include <cstdlib>
#include <ctime>

using namespace Linear;

int Matrix::lastRand = 0;
Matrix::Matrix(int m_row, int m_col, double num) : numOfRow(m_row), numOfColumn(m_col)
{
	if (m_row < 0 || m_col < 0)
		throw std::exception("row/col size < 0");
	if (m_row == 0 || m_col == 0)
	{
		size = 0;
		m_row = m_col = 0;
		data = nullptr;
	}
	else
	{
		size = numOfRow * numOfColumn;
		data = new double[m_row * m_col];
		std::fill(data, data + size, num);
	}
}

Matrix::Matrix(const Matrix& m) : Matrix(m.numOfRow, m.numOfColumn)
{
	std::copy(m.data, m.data + size, data);
}

Matrix::Matrix(Matrix&& m) : numOfRow(m.numOfRow), numOfColumn(m.numOfColumn), size(m.size)
{
	data = m.data;
	m.data = nullptr;
}

Matrix::Matrix(double m) : Matrix(1, 1)
{
	data[0] = m;
}

Linear::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> m)
{
	numOfRow = int(m.size());
	numOfColumn = int(m.begin()->size());
	if (numOfRow == 0 || numOfColumn == 0)
	{
		size = 0;
		numOfRow = numOfColumn = 0;
		data = nullptr;
	}
	else
	{
		size = numOfRow * numOfColumn;
		data = new double[size];
		int cnt = 0;
		for (auto& p1 : m)
			for (auto& p2 : p1)
			{
				if (p1.size() != numOfColumn)
					throw std::exception("Column sizes are not the same.");
				data[cnt++] = p2;
			}
	}
	
}

Matrix::Matrix(double m, int n) : Matrix(n, n)
{
	for (int i = 0; i < n; ++i)
	{
		*this[i][i] = m;
	}
}

void Linear::Matrix::assign(int m_row, int m_col, double num)
{
	if (m_row < 0 || m_col < 0)
		throw std::exception("row/col size < 0");
	if (m_row == 0 || m_col == 0)
	{
		delete[] data;
		size = 0;
		numOfColumn = numOfRow = 0;
		data = nullptr;
	}
	else
	{
		delete[] data;
<<<<<<< HEAD
		numOfRow = m_row;
		numOfColumn = m_col;
=======
>>>>>>> c305fc995ca677e435cde7d565c241f85421e3fd
		size = numOfRow * numOfColumn;
		data = new double[size];
		std::fill(data, data + size, num);
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

Matrix Matrix::operator+(const Matrix& m) const
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

Matrix Matrix::operator-() const
{
	Matrix out(*this);
	for (int i = 0; i < size; ++i)
	{
		out.data[i] = -out.data[i];
	}
	return out;
}

Matrix Matrix::operator-(const Matrix& m) const
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

void Linear::Matrix::random(double min, double max)
{
	for (int i = 0; i < size; i++)
	{
		srand(int(time(0))+lastRand);
		lastRand = rand();
		data[i] = double(lastRand) / (double(RAND_MAX) / double(max - min)) + min;
	}
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

void Linear::RowVector::assign(int n, double val)
{
	Matrix::assign(1, n, val);
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

void Linear::ColVector::assign(int n, double val)
{
	Matrix::assign(n, 1, val);
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

<<<<<<< HEAD
Matrix Linear::operator+(Matrix&& m1, const Matrix& m2)
{
	if (m1.numOfRow != m2.numOfRow || m1.numOfColumn != m2.numOfColumn)
	{
		throw(std::exception("matrix addition of inconsistent specifications"));
	}
	Matrix out(std::move(m1));
	for (int i = 0; i < out.size; ++i)
	{
		out.data[i] += m2.data[i];
	}
	return out;
}

=======
>>>>>>> c305fc995ca677e435cde7d565c241f85421e3fd
std::ostream& Linear::operator<<(std::ostream& os, const Matrix& m)
{
	for (int i = 0; i < m.numOfRow; ++i)
		for (int j = 0; j < m.numOfColumn; ++j)
		{
			if (j == 0)
				os << '(';
			os << m[i][j];
			if (j == m.numOfColumn - 1)
				os << ')' << std::endl;
			else
				os << '\t';
		
		}
	return os;
}
