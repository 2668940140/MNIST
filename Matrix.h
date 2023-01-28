#pragma once
#include <utility>
#include <algorithm>
namespace Linear {
	class Matrix
	{
	protected:
		int numOfRow = 0;
		int numOfColumn = 0;
		int size = 0;
		double* data = nullptr;
	public:
		Matrix(int m_row = 0, int m_col = 0, double num = 0.0); //给出行数和列数创建
		int row_n() const { return numOfRow; }
		int column_n() const { return numOfColumn; }

		Matrix(const Matrix&);
		Matrix(Matrix&&);
		explicit Matrix(double);
		Matrix(double, int);

		virtual void assign(int, int, double num = 0.0);

		double* operator[](int);
		const double* operator[](int) const;

		Matrix& operator=(const Matrix&);
		Matrix& operator=(Matrix&&);

		Matrix operator+(const Matrix&)const;
		Matrix& operator+=(const Matrix&);

		Matrix operator-()const;
		Matrix operator-(const Matrix&)const;
		Matrix& operator-=(const Matrix&);

		Matrix operator*(const Matrix&)const;
		Matrix& operator*=(const Matrix&);

		Matrix transpose() const;

		void random(double min=0.0, double max=1.0);
		~Matrix();
	};

	class ColVector;

	class RowVector : public Matrix
	{
	public:
		RowVector(int n = 0, double val = 0.0) : Matrix(1, n, val) {}
		RowVector(const Matrix&);
		RowVector(Matrix&&);
		explicit RowVector(double m) : Matrix(m) {}
		RowVector(double*, int);
		template<class Init, class Last>
		RowVector(Init, Last);
		double& operator[](int index) { return data[index]; }
		const double& operator[](int index) const { return data[index]; }
		ColVector transpose() const; //O(n)
		virtual void assign(int n = 0, double val = 0.0);
		double* begin() const { return data; }
		double* end() const { return data + size; }
		using Matrix::operator=;
	};

	class ColVector : public Matrix
	{
	public:
		ColVector(int n = 0, double val = 0.0) : Matrix(n, 1, val) {}
		ColVector(const Matrix&);
		ColVector(Matrix&&);
		explicit ColVector(double m) : Matrix(m) {}
		ColVector(double*, int);
		template<class Init, class Last>
		ColVector(Init, Last);
		double& operator[](int index) { return data[index]; }
		const double& operator[](int index) const { return data[index]; }
		RowVector transpose() const; //O(n)
		virtual void assign(int n = 0, double val = 0.0);
		double* begin() const { return data; }
		double* end() const { return data + size; }
		using Matrix::operator=;
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