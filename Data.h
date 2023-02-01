#pragma once
#include "NeuralNetwork.h"
#include <string>
#include <utility>
#include <fstream>
#include <iostream>
class Data
{
	typedef std::string string;
private:
	string imageFileName;
	string labelFileName;
	std::ifstream imageIn, labelIn;
	int m_size = -1;
	int numOfRow = -1;
	int numOfColumn = -1;
	int picSize = -1;
public:
	Data(const string& imf, const string& lbf);
	inline bool open(const string& imf, const string& lbf);
	bool good() const;
	inline int size() const;
	std::pair <Linear::RowVector, Linear::RowVector> operator[](int index);
	int row_n() const { return numOfRow; }
	int column_n() const { return numOfColumn; }
};

namespace Visualize
{
	void show(const Linear::RowVector&,int,int);
}