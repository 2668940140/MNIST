#include "NeuralNetwork.h"
#include <iostream>
using namespace std;
using namespace Linear;

int main()
{
	try {
		NeuralNetwork nt = { 2,2,2};
		//nt.randomInitialize();
		RowVector input = { 1,1 };
		double inputA;
		cin >> inputA;
		nt.optAlpha = inputA;
		int limit = 0;
		cin >> limit;
		for (int i = 0; i < limit; ++i)
		{
			cout << nt.train(input, input) << endl;
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
		return 0;
	}
	return 0;
}