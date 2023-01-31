#include "NeuralNetwork.h"
#include <iostream>
using namespace std;
using namespace Linear;

int main()
{
	Matrix op = { {1,2},{3,4} };
	RowVector n = {-1,2};
	cout << n * op;
	return 0;
}