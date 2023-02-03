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
		std::wcout << R"(���룺1 -�����µ�����
2 -��������ļ�·����ȡ
)";
		int inputOption = -1;
		std::cin >> inputOption;
		std::cin.get();
		NeuralNetwork nt;
		if (inputOption == 1)
		{
			std::vector<int> extents;
			std::wcout << "���������ĳ���  �ÿո�ָ�\n";
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
			std::wcout << "�����ļ�·��(��������)\n";
			std::string path;
			std::getline(std::cin,path);
			nt.reset(path.c_str());
		}
		else
		{
			throw std::exception("Invalid Input");
		}
		std::wcout << R"(��˳������(��������)��1.ͼƬ��·��
			2.��ǩ��·��
)";
		std::string imaPath, lblPath;
		std::getline(std::cin, imaPath);
		std::getline(std::cin, lblPath);
		Data dataSet(imaPath, lblPath);
		if (!dataSet.good())
			throw std::exception("Dataset failing in opening.");
		dataSetSize = dataSet.size();
		std::wcout << R"(���룺1 -ѵ��ģʽ
2 -��������ģʽ
3 -���ݼ�ȫ������
)";
		std::cin >> inputOption;
		if (inputOption == 1) //ѵ��ģʽ
		{
			std::wcout << R"(��˳�����룺1.�����������������ݣ�
2.n�ε�������Ŀ��ƫ��(nΪ0�򲻲���)
3.n(ҲΪ��ʾ��ƫ��,0����ʾ)
4.ʱ��/��
5.ƫ����������
6.ѵ�������籣��·��������()
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
					std::wcout << "ƫ��:" << aveDevia << std::endl;
					if (aveDevia <= aimedDevia)
						break;
				}
				++cnt;
			}
			if (nt.save(outPath.c_str()))
			{
				std::wcout << "����ɹ�\n";
			}
			else
				throw std::exception("Save Failed");

		}
		else if (inputOption == 0) //�ֹ���������
		{
			std::wcout << "���ݼ���" << dataSetSize << "������" << '\n'
				<< "������Ż�ȡ���(1-" << dataSetSize << ")" << std::endl
				<< "���������Խ���\n";
			int index = -1;
			while (std::cin >> index)
			{
				std::wcout << "ͼƬ:\n";
				Visualize::show(dataSet[index - 1].first, 28, 28);
				std::wcout << "Ŀ��:\n";
				std::cout << nt.judge(dataSet[index - 1].first) << std::endl;
				std::wcout << "MSEƫ��:\n";
				std::cout << nt.judge(dataSet[index - 1].first, dataSet[index - 1].second) << std::endl;
			}
		}
		else if (inputOption == 2) //ȫ������
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
			std::wcout << "��ȷ��:" << rightCnt << '/' << dataSetSize << " = " << double(rightCnt) / double(dataSetSize)
				<< std::endl;
			std::wcout << "ƽ��MSEƫ��: " << sumDeiva / dataSetSize << std::endl;
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