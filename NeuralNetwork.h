#pragma once
#include "Matrix.h"
#include <initializer_list>

namespace AuxFuncs
{
	inline Linear::Matrix sigmoid(Linear::Matrix&& m);
	inline double mse(const Linear::RowVector&, const Linear::RowVector&);
}

class NeuralNetwork
{
public:
	enum ActFunc { Sigmoid};
	enum LossFunc { MSE };

private:
	int depth = 0;
	int* extents = nullptr; //lenth equals to depth
	Linear::Matrix* connections = nullptr; //lenth equals to depth-1,specifications accord with extents
	Linear::RowVector* biases = nullptr; //lenth equals to depth - 1, specifications accord with extents
	Linear::RowVector* layers = nullptr; //lenth equals to depth,specifications accord with extents
	Linear::RowVector* errDeviation = nullptr; //lenth equals to depth, specifications accord with extents

public:
	ActFunc actFunc = Sigmoid;
	LossFunc lossFunc = MSE;
	double optAlpha = 0.01;

private: //deleted
	NeuralNetwork(const NeuralNetwork&) = delete;
	NeuralNetwork& operator=(const NeuralNetwork&) = delete;

public:

	template<class Init, class Last>
	NeuralNetwork(Init, Last); //all weights are set to 1 as default

	NeuralNetwork(std::initializer_list<int>); //all weights are set to 1 as default, b equals to 0
	NeuralNetwork(int inputLayerExtent, int hideLayerNum, int hideLayerExtent, int outPutLayerExtent); //all weights are set to 1 as default
	NeuralNetwork(const wchar_t*); //read from file
	void randomInitialize(); //set all weights and b to a random value

	bool save(const wchar_t*) const;
	~NeuralNetwork();

	ActFunc showActFunc() const { return actFunc; }
	LossFunc showLossFunc() const { return lossFunc; }
	double showOptAlpha() const { return optAlpha; }

	inline void setOptAlpha(double);

	const Linear::RowVector& judge(const Linear::RowVector& input);
	double judge(const Linear::RowVector& input, const Linear::RowVector& expectedOutput);
	double train(const Linear::RowVector& input, const Linear::RowVector& expectedOutput); //return the cost, use back-propagation
};
