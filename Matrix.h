#pragma once
#include <utility>
#include <algorithm>
#include <iostream>
namespace Linear {
	class Matrix
	{
	protected:
		static int lastRand;
		int numOfRow = 0;
		int numOfColumn = 0;
		int size = 0;
		double* data = nullptr;
	public:
		Matrix(int m_row = 0, int m_col = 0, double num = 0.0); //给出行数和列数创建
		int row_n() const { return numOfRow; }
		int column_n() const { return numOfColumn; }
		int capacity() const { return size; }

		Matrix(const Matrix&);
		Matrix(Matrix&&);
		Matrix(std::initializer_list<std::initializer_list<double>>);
		explicit Matrix(double);
		Matrix(double, int);

		virtual void assign(int, int, double num = 0.0);

		double* operator[](int);
		const double* operator[](int) const;

		Matrix& operator=(const Matrix&);
		Matrix& operator=(Matrix&&);

		Matrix operator+(const Matrix&)const;
		friend Matrix operator+(Matrix&&, const Matrix&);
		Matrix& operator+=(const Matrix&);

		Matrix operator-()const;
		Matrix operator-(const Matrix&)const;
		Matrix& operator-=(const Matrix&);
		friend Matrix operator-(Matrix&&, const Matrix&);

		Matrix operator*(const Matrix&)const;
		Matrix& operator*=(const Matrix&);
		
		friend Matrix operator*(double, const Matrix& m);
		friend Matrix operator*(double, Matrix&&);

		Matrix transpose() const;

		friend Matrix dot2(const Matrix& m1, const Matrix& m2);
		friend Matrix dot2(Matrix&& m1, const Matrix& m2);

		template<class... Args>
		friend Matrix dot(const Matrix& m, Args... args)
		{
			return dot2(m, dot(args...));
		}
		template<class... Args>
		friend Matrix dot(const Matrix&& m, Args... args)
		{
			return dot2(std::move(m), dot(args...));
		}
		friend Matrix dot(const Matrix& m)
		{
			return m;
		}

		void random(double min=0.0, double max=1.0);
		~Matrix();

		friend std::ostream& operator<<(std::ostream&, const Matrix&);
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
		int row_n() const = delete;

		template<class Init, class Last>
		RowVector(Init, Last);

		RowVector(std::initializer_list<double> l) : RowVector(l.begin(), l.end()) {}
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
		int column_n() const = delete;

		template<class Init, class Last>
		ColVector(Init, Last);

		ColVector(std::initializer_list<double> l) : ColVector(l.begin(), l.end()) {}
		double& operator[](int index) { return data[index]; }
		const double& operator[](int index) const { return data[index]; }
		RowVector transpose() const; //O(n)
		virtual void assign(int n = 0, double val = 0.0);
		double* begin() const { return data; }
		double* end() const { return data + size; }
		using Matrix::operator=;
	};

	template<class Init, class Last>
	inline RowVector::RowVector(Init m_1, Last m_2) : Matrix(1, int(std::distance(m_1, m_2)))
	{
		std::copy(m_1, m_2, data);
	}

	template<class Init, class Last>
	inline ColVector::ColVector(Init m_1, Last m_2) : Matrix(int(std::distance(m_1, m_2)), 1)
	{
		std::copy(m_1, m_2, data);
	}

	
}

