#include "NeuralNetwork.h"
#include <iterator>
#include <algorithm>
#include <exception>
#include <cstdlib>

/*
const int depth;
int* extents; //lenth equals to depth
Linear::Matrix* connections; //lenth equals to depth-1,specifications accord with extents
Linear::RowVector* biases; //lenth equals to depth - 1, specifications accord with extents
Linear::RowVector* layers; //lenth equals to depth,specifications accord with extents	
ActFunc actFunc = Sigmoid;
LossFunc lossFunc = MSE;
double optAlpha = 0.01;
*/

template<class Init, class Last>
NeuralNetwork::NeuralNetwork(const Init begin, const Last end) : depth(int(std::distance(begin,end)))
{
	extents = new int[depth];
	if (depth < 2)
		throw std::exception("Sum of layers < 2");

	{
		Init p1 = begin;int* p2 = extents;
		for (; p1 != end; ++p1,++p2)
		{
			if (*p1 <= 0)
				throw std::exception("Extent of one layer is not a positive.");
			*p2 = *p1;
		}
	}
	
	layers = new Linear::RowVector[depth];
	biases = new Linear::RowVector[depth-1];
	for (int i = 0; i < depth - 1; ++i)
	{
		layers[i].assign(extents[i], 0.0);
		biases[i].assign(extents[i+1], 0.0);
	}
	layers[depth-1].assign(extents[depth-1], 0.0);
	
	connections = new Linear::Matrix[depth - 1];
	for (int i = 0; i < depth-1; ++i)
	{
		connections[i].assign(extents[i + 1], extents[i], 1.0);
	}
}

NeuralNetwork::NeuralNetwork(std::initializer_list<int> m) : NeuralNetwork(m.begin(),m.end())
{
}

NeuralNetwork::NeuralNetwork(int inputLayerExtent, int hideLayerNum, int hideLayerExtent, int outPutLayerExtent) : depth(2 + hideLayerNum)
{
	if (inputLayerExtent <= 0 || hideLayerExtent <= 0 || outPutLayerExtent <= 0)
		throw std::exception("Extent of one layer is not a positive.");
	extents = new int[depth];
	extents[0] = inputLayerExtent;
	for (int i = 1; i < depth - 1; ++i)
	{
		extents[i] = hideLayerExtent;
	}
	extents[depth - 1] = outPutLayerExtent;

	layers = new Linear::RowVector[depth];
	biases = new Linear::RowVector[depth - 1];
	for (int i = 0; i < depth - 1; ++i)
	{
		layers[i].assign(extents[i], 0.0);
		biases[i].assign(extents[i + 1], 0.0);
	}
	layers[depth - 1].assign(extents[depth - 1], 0.0);

	connections = new Linear::Matrix[depth - 1];
	for (int i = 0; i < depth - 1; ++i)
	{
		connections[i].assign(extents[i + 1], extents[i], 1.0);
	}
}

NeuralNetwork::NeuralNetwork(const char*)
{
}

void NeuralNetwork::randomInitialize()
{
	for (int i = 0; i < depth-1; ++i)
	{
		connections[i].random();
		biases[i].random();
	}
	return;
}

void NeuralNetwork::readSave(const char*)
{
}

void NeuralNetwork::save(const char*) const
{
}

NeuralNetwork::~NeuralNetwork()
{
	delete[] extents, connections, biases, layers;
}

inline void NeuralNetwork::setOptAlpha(double)
{
}

const Linear::RowVector& NeuralNetwork::judge(const Linear::RowVector& input)
{
	layers[0] = input;
	for (int i = 0; i < depth - 1; ++i)
	{
		layers[i + 1] = (layers[i] * connections[i]).transpose() + biases[i];
	}
	return layers[depth - 1];
}

double NeuralNetwork::judge(const Linear::RowVector& input, const Linear::RowVector& expectedOutput)
{
	return 0.0;
}

double NeuralNetwork::train(const Linear::RowVector& input, const Linear::RowVector& expectedOutput)
{
	return 0.0;
}
