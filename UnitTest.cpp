#include "NeuralNetwork.h"
#include <iostream>
using namespace std;
using namespace Linear;

int main()
{
<<<<<<< HEAD
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
=======
	Matrix op = { {1,2},{3,4} };
	RowVector n = {-1,2};
	cout << n * op;
>>>>>>> c305fc995ca677e435cde7d565c241f85421e3fd
	return 0;
}