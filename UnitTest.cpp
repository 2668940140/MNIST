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
		cout << nt.judge(input);
	}
	catch (const std::exception& e)
	{
		cout << e.what();
		return 0;
	}
	return 0;
}