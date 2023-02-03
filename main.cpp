#include "NeuralNetwork.h"
#include "Data.h"
#include <string>
#include <vector>
#include <ctime>
#include <list>
int dataSetSize;

int main()
{
	try {
		std::wcout << R"(输入：1 -创建新的网络
2 -从输入的文件路径读取
)";
		int inputOption = -1;
		std::cin >> inputOption;
		std::cin.get();
		NeuralNetwork nt;
		if (inputOption == 1)
		{
			std::vector<int> extents;
			std::wcout << "输入各个层的长度  用空格分割\n";
			int inputNum = -1;
			while (std::cin>>inputNum && std::cin.good())
			{
				extents.emplace_back(inputNum);
			}
			if (std::cin.eof())
				std::cin.clear();
			else
				throw std::exception("Invalid Input");
			nt.reset(extents.begin(), extents.end());
		}
		else if (inputOption == 0)
		{
			std::wcout << "输入文件路径(不含中文)\n";
			std::string path;
			std::getline(std::cin,path);
			nt.reset(path.c_str());
		}
		else
		{
			throw std::exception("Invalid Input");
		}
		std::wcout << R"(按顺序输入(不含中文)：1.图片集路径
			2.标签集路径
)";
		std::string imaPath, lblPath;
		std::getline(std::cin, imaPath);
		std::getline(std::cin, lblPath);
		Data dataSet(imaPath, lblPath);
		if (!dataSet.good())
			throw std::exception("Dataset failing in opening.");
		dataSetSize = dataSet.size();
		std::wcout << R"(输入：1 -训练模式
2 -单个测试模式
3 -数据集全部测试
)";
		std::cin >> inputOption;
		if (inputOption == 1) //训练模式
		{
			std::wcout << R"(按顺序输入：1.迭代次数（单个数据）
2.n次单迭代的目标偏差(n为0则不采用)
3.n(也为显示的偏差,0则不显示)
4.时间/秒
5.偏差修正常数
6.训练后网络保存路径无中文()
)";
			int maxIter = 0, timeBound = 0, stabFactor = 1;
			double aimedDevia = 1.0, optA = 0.01;
			std::string outPath;
			std::cin >> maxIter >> aimedDevia >> stabFactor >> timeBound >> optA;
			std::cin.get();
			std::getline(std::cin, outPath);
			int cnt = 0;
			double devia = 1.0 * stabFactor; //sum of n times deviation
			int beginTime = int(time(nullptr));
			nt.optAlpha = optA;
			std::list<double> deviaList(stabFactor, 1.0);
			while (cnt < maxIter || (time(nullptr)-beginTime)<=timeBound)
			{
				double thisDevia = nt.train(dataSet[cnt % dataSetSize].first, dataSet[cnt % dataSetSize].second);
				if (stabFactor)
				{
					devia -= deviaList.front();
					deviaList.pop_front();
					devia += thisDevia;
					deviaList.emplace_back(thisDevia);
					double aveDevia = devia / stabFactor;
					std::wcout << "偏差:" << aveDevia << std::endl;
					if (aveDevia <= aimedDevia)
						break;
				}
				++cnt;
			}
			if (nt.save(outPath.c_str()))
			{
				std::wcout << "保存成功\n";
			}
			else
				throw std::exception("Save Failed");

		}
		else if (inputOption == 0) //手工单个测试
		{
			std::wcout << "数据集共" << dataSetSize << "组数据" << '\n'
				<< "输入序号获取结果(1-" << dataSetSize << ")" << std::endl
				<< "输入其他以结束\n";
			int index = -1;
			while (std::cin >> index)
			{
				std::wcout << "图片:\n";
				Visualize::show(dataSet[index - 1].first, 28, 28);
				std::wcout << "目标:\n";
				std::cout << nt.judge(dataSet[index - 1].first) << std::endl;
				std::wcout << "MSE偏差:\n";
				std::cout << nt.judge(dataSet[index - 1].first, dataSet[index - 1].second) << std::endl;
			}
		}
		else if (inputOption == 2) //全部测试
		{
			double sumDeiva = 0;
			int rightCnt = 0;
			for (int i = 0; i < dataSetSize; i++)
			{
				Linear::RowVector out(nt.judge(dataSet[i].first));
				Linear::RowVector aim(dataSet[i].second);
				for (int j = 0; j < 10; j++)
				{
					if (aim[j] > 0.5)
					{
						int tmpCnt = 0; //right cnt
						for (int k = 0; k < 10; ++k)
						{
							if (out[j] >= out[k])
								++tmpCnt;
						}
						if (tmpCnt == 10)
							++rightCnt;

						break;
					}
				}
				sumDeiva += AuxFuncs::mse(out, aim);
				std::cout << i + 1 << '/' << dataSetSize << std::endl;
			}
			std::wcout << "正确率:" << rightCnt << '/' << dataSetSize << " = " << double(rightCnt) / double(dataSetSize)
				<< std::endl;
			std::wcout << "平均MSE偏差: " << sumDeiva / dataSetSize << std::endl;
		}
		else
		{
			throw std::exception("Invalid Input");
		}


	}

	catch (const std::exception& e)
	{
		std::cout << e.what();
		system("pause");
		return 1;
	}

	return 0;
}