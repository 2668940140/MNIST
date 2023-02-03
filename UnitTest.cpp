#include "NeuralNetwork.h"
#include "Data.h"
#include <iostream>
using namespace std;
using namespace Linear;

int main()
{
	/*
	try {
		NeuralNetwork nt = { 2,3,4,5,4};
		//nt.randomInitialize();
		RowVector input = { 1,1 };
		RowVector output = { 0.2,0.4,0.6,0.0};
		nt.optAlpha = 0.01;
		for (int i = 0; i < 10000; ++i)
		{
			cout << nt.train(input, output) << endl;
		}
		cout << nt.judge(input);
		//wstring path(LR"(D:\doucument\快速访问\桌面\save)");
		//cout << nt.save(path.c_str());
	}
	*/

	try {

		//nt.randomInitialize();
		RowVector input = { 1,1 };
		wstring path(LR"(D:\doucument\快速访问\桌面\save)");
		NeuralNetwork nt(path.c_str());
		cout << nt.judge(input);
	}


	/*
	try
	{
		Data test(R"(D:\doucument\Code\projects\easyDeepLearning\Resources\train-images.idx3-ubyte)",
			R"(D:\doucument\Code\projects\easyDeepLearning\Resources\train-labels.idx1-ubyte)");
		cout << test.good() << endl;
		int index;
		while (cin >> index) 
		{
			cout << test[index].second << endl;
			Visualize::show(test[index].first, 28, 28);
		}
	}
	*/

	catch (const std::exception& e)
	{
		cout << e.what();
		return 0;
	}
	return 0;
}