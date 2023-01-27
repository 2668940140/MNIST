#pragma once
#include <utility>
namespace Linear {
	class Matrix
	{
	protected:
		int numOfRow;
		int numOfColumn;
		int size;
		double* data;
	public:
		Matrix(int, int); //给出行数和列数创建
		int row_n() const { return numOfRow; }
		int column_n() const { return numOfColumn; }

		Matrix(const Matrix&);
		Matrix(Matrix&&);
		explicit Matrix(double);
		Matrix(double, int);

		double* operator[](int);
		const double* operator[](int) const;

		Matrix& operator=(const Matrix&);
		Matrix& operator=(Matrix&&);

		Matrix operator+(const Matrix&)const&;
		Matrix operator+(const Matrix)&&;
		Matrix& operator+=(const Matrix&);

		Matrix operator-()const&;
		Matrix operator-()&&;

		Matrix operator-(const Matrix&)const&;
		Matrix operator-(const Matrix&)&&;
		Matrix& operator-=(const Matrix&);

		Matrix operator*(const Matrix&)const;
		Matrix& operator*=(const Matrix&);

		Matrix transpose() const;
		~Matrix();
	};

	class ColVector;

	class RowVector : public Matrix
	{
	public:
		RowVector(int n) : Matrix(1, n) {}
		explicit RowVector(const Matrix&);
		explicit RowVector(Matrix&&);
		explicit RowVector(double m) : Matrix(m) {}
		RowVector(double*, int);
		template<class Init, class Last>
		RowVector(Init, Last);
		double operator[](int index) { return data[index]; }
		const double operator[](int index) const { return data[index]; }
		ColVector transpose() const; //O(n)
	};

	class ColVector : public Matrix
	{
	public:
		ColVector(int n) : Matrix(n, 1) {}
		explicit ColVector(const Matrix&);
		explicit ColVector(Matrix&&);
		explicit ColVector(double m) : Matrix(m) {}
		ColVector(double*, int);
		template<class Init, class Last>
		ColVector(Init, Last);
		double operator[](int index) { return data[index]; }
		const double operator[](int index) const { return data[index]; }
		RowVector transpose() const; //O(n)
	};

	template<class Init, class Last>
	inline RowVector::RowVector(Init m_1, Last m_2)
	{
		std::copy(m_1, m_2, data);
	}

	template<class Init, class Last>
	inline ColVector::ColVector(Init m_1, Last m_2)
	{
		std::copy(m_1, m_2, data);
	}

}