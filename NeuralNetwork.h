#pragma once
#include "Matrix.h"
#include <initializer_list>
class NeuralNetwork
{
private:
	const int depth;
	const int* extents; //lenth equals to depth
	Linear::Matrix connections; //lenth equals to depth-1,specifications accord with extents
	Linear::ColVector layers; //lenth equals to depth,specifications accord with extents

private: //deleted
	NeuralNetwork(const NeuralNetwork&) = delete;
	NeuralNetwork& operator=(const NeuralNetwork&) = delete;

public:
	template<class Init, class Last>
	NeuralNetwork(Init, Last);
	NeuralNetwork(std::initializer_list<int>);
};