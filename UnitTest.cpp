/*
#include "NeuralNetwork.h"
#include "Data.h"
#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;
using namespace Linear;

int main()
{
	try
	{
		Data test(R"(D:\doucument\Code\projects\easyDeepLearning\Resources\train-images.idx3-ubyte)",
			R"(D:\doucument\Code\projects\easyDeepLearning\Resources\train-labels.idx1-ubyte)");
		vector<int> spec{ 784, 30, 10 };
		NeuralNetwork nt(spec.begin(), spec.end());
		Linear::RowVector ea1 = { 0.1,0.2,0.4,0.2,0.9,0.5,0.9,0.2,0.4,0.9 };
		Linear::RowVector ea2 = { 0.2,0.4,0.9,0.8,0.1,0.2,0.4,0.2,0.6,0.6 };
		nt.optAlpha = 0.01;
		//nt.randomInitialize();
		Visualize::show(test[0].first, 28, 28);
		//cout.setf(ios::fixed);
		//cout.precision(18);
		cout << test[0].second << endl;
		for (int i = 0; i < 1000; i++)
		{
			cout << nt.train(test[0].first, test[0].second) << endl;
		}
		cout << nt.judge(test[0].first) << endl;
		nt.save(R"(D:\projectTmp\testSave)");
		nt.reset(R"(D:\projectTmp\testSave)");
		cout << nt.judge(test[0].first) << endl;
	}


	catch (const std::exception& e)
	{
		cout << e.what();
		return 0;
	}
	return 0;
}
*/