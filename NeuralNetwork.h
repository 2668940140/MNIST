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
	enum ActFunc { Sigmoid };
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

protected:
	inline void deleteData();

private: //deleted
	NeuralNetwork(const NeuralNetwork&) = delete;
	NeuralNetwork& operator=(const NeuralNetwork&) = delete;

public:

	template<class Iter>
	NeuralNetwork(Iter begin, Iter end); //all weights are set to 1 as default


	NeuralNetwork(std::initializer_list<int>); //all weights are set to 1 as default, b equals to 0
	NeuralNetwork(int inputLayerExtent = 1, int hideLayerNum = 0, int hideLayerExtent = 1, int outPutLayerExtent = 1); //all weights are set to 1 as default
	NeuralNetwork(const char*); //read from file

	template<class Iter>
	void reset(Iter, Iter);
	void reset(std::initializer_list<int>); //all weights are set to 1 as default, b equals to 0
	void reset(int inputLayerExtent, int hideLayerNum, int hideLayerExtent, int outPutLayerExtent); //all weights are set to 1 as default
	void reset(const char*); //read from file

	void randomInitialize(); //set all weights and b to a random value

	bool save(const char*) const;
	~NeuralNetwork();

	ActFunc showActFunc() const { return actFunc; }
	LossFunc showLossFunc() const { return lossFunc; }
	double showOptAlpha() const { return optAlpha; }

	inline void setOptAlpha(double);

	const Linear::RowVector& judge(const Linear::RowVector& input);
	double judge(const Linear::RowVector& input, const Linear::RowVector& expectedOutput);
	double train(const Linear::RowVector& input, const Linear::RowVector& expectedOutput); //return the cost, use back-propagation
};


template<class Iter>
NeuralNetwork::NeuralNetwork(Iter begin, Iter end) : depth(int(std::distance(begin, end)))
{
	extents = new int[depth];
	if (depth < 2)
		throw std::exception("Sum of layers < 2");

	{
		Iter p1 = begin; int* p2 = extents;
		for (; p1 != end; ++p1, ++p2)
		{
			if (*p1 <= 0)
				throw std::exception("Extent of one layer is not a positive.");
			*p2 = *p1;
		}
	}

	layers = new Linear::RowVector[depth];
	biases = new Linear::RowVector[depth - 1];
	errDeviation = new Linear::RowVector[depth];
	for (int i = 0; i < depth - 1; ++i)
	{
		layers[i].assign(extents[i], 0.0);
		biases[i].assign(extents[i + 1], 0.0);
		errDeviation[i].assign(extents[i + 1], 0.0);
	}
	layers[depth - 1].assign(extents[depth - 1], 0.0);
	errDeviation[depth - 1].assign(extents[depth - 1], 0.0);

	connections = new Linear::Matrix[depth - 1];
	for (int i = 0; i < depth - 1; ++i)
	{
		connections[i].assign(extents[i], extents[i + 1], 0.0);
	}
}

template<class Iter>
void NeuralNetwork::reset(Iter begin, Iter end)
{
	deleteData();
	depth = int(std::distance(begin, end));
	extents = new int[depth];
	if (depth < 2)
		throw std::exception("Sum of layers < 2");

	{
		Iter p1 = begin; int* p2 = extents;
		for (; p1 != end; ++p1, ++p2)
		{
			if (*p1 <= 0)
				throw std::exception("Extent of one layer is not a positive.");
			*p2 = *p1;
		}
	}

	layers = new Linear::RowVector[depth];
	biases = new Linear::RowVector[depth - 1];
	errDeviation = new Linear::RowVector[depth];
	for (int i = 0; i < depth - 1; ++i)
	{
		layers[i].assign(extents[i], 0.0);
		biases[i].assign(extents[i + 1], 0.0);
		errDeviation[i].assign(extents[i + 1], 0.0);
	}
	layers[depth - 1].assign(extents[depth - 1], 0.0);
	errDeviation[depth - 1].assign(extents[depth - 1], 0.0);

	connections = new Linear::Matrix[depth - 1];
	for (int i = 0; i < depth - 1; ++i)
	{
		connections[i].assign(extents[i], extents[i + 1], 0.0);
	}
}