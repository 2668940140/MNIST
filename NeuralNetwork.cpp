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
	errDeviation = new Linear::RowVector[depth];
	for (int i = 0; i < depth - 1; ++i)
	{
		layers[i].assign(extents[i], 0.0);
		biases[i].assign(extents[i+1], 0.0);
		errDeviation[i].assign(extents[i + 1], 0.0);
	}
	layers[depth-1].assign(extents[depth-1], 0.0);
	errDeviation[depth - 1].assign(extents[depth - 1], 0.0);

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
	delete[] extents, connections, biases, layers, errDeviation;
}

inline void NeuralNetwork::setOptAlpha(double)
{
}

const Linear::RowVector& NeuralNetwork::judge(const Linear::RowVector& input)
{
	switch (actFunc)
	{
	case NeuralNetwork::Sigmoid:
		layers[0] = input;
		for (int i = 0; i < depth - 1; ++i)
		{
			layers[i + 1] = AuxFuncs::sigmoid(layers[i] * connections[i] + biases[i]);
		}
		return layers[depth - 1];
		break;
	default:
		throw std::exception("Unexcepted actFunc");
		break;
	}

}

double NeuralNetwork::judge(const Linear::RowVector& input, const Linear::RowVector& expectedOutput)
{
	judge(input);
	switch (lossFunc)
	{
	case NeuralNetwork::MSE:
		return AuxFuncs::mse(layers[depth - 1], expectedOutput);
		break;
	default:
		throw std::exception("Unexcepted lossFunc");
		break;
	}
}

double NeuralNetwork::train(const Linear::RowVector& input, const Linear::RowVector& expectedOutput)
{
	judge(input);
	
	switch (actFunc)
	{
	case NeuralNetwork::Sigmoid:
		switch (lossFunc)
		{
		case NeuralNetwork::MSE:
			errDeviation[depth - 1] = dot(layers[depth - 1] - expectedOutput , layers[depth - 1] , 
			Linear::RowVector(extents[depth-1],1.0) - layers[depth - 1]);
			for (int i = depth - 2; i >= 0; --i)
			{
				errDeviation[i] = dot(errDeviation[i + 1] * connections[i] , layers[i] , 
					Linear::RowVector(extents[i], 1.0) - layers[i]);
			}
			for (int i = 0; i < depth - 1; ++i)
			{
				biases[i] -= optAlpha * errDeviation[i];
				connections[i] -= optAlpha * layers[i].transpose() * errDeviation[i];
			}
			break;
		default:
			throw std::exception("Unexcepted lossFunc");
			break;
		}
		break;
	default:
		throw std::exception("Unexcepted actFunc");
		break;
	}
	
	switch (lossFunc)
	{
	case NeuralNetwork::MSE:
		return AuxFuncs::mse(layers[depth - 1], expectedOutput);
		break;
	default:
		throw std::exception("Unexcepted lossFunc");
		break;
	}
}

Linear::Matrix AuxFuncs::sigmoid(Linear::Matrix&& m)
{
	for (int i = 0; i < m.row_n(); ++i)
		for (int j = 0; j < m.column_n(); ++j)
			m[i][j] = 1 / (1 + exp(-m[i][j]));
	return m;
}

double AuxFuncs::mse(const Linear::RowVector& m1, const Linear::RowVector& m2)
{
	double out = 0.0;
	if (m1.column_n() != m2.column_n())
		throw std::exception("Vector of invalid sizes called mse");
	for (int i = 0; i < m1.column_n(); ++i)
	{
		out += pow(m1[i] - m2[i], 2);
	}
	out /= m1.column_n() * 2; //for a better-looking derivative
	return out;
}