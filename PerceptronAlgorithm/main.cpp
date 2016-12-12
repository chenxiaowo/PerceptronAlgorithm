#include <iostream>
#include <fstream>
#include<string>
#include "Perceptron.h"

using namespace std;

void readDataFromFile(string filePath, vector<vector<double> >& vecs, vector<int>& response);
void readDataFromKeyboard(vector<vector<double> >& vecs, vector<int>& response,string filepath);	//从键盘获得训练数据或测试数据 vecs存放的是数据，response是每条数据对应的类别，在二分类里，0为第一类，1为第二类
float getAccuracy(const vector<int>& result, const vector<int>& response);		//计算测试数据被正确分类的正确率

int main()
{
	int select=0;
	vector<vector<double> > trainData, testData;
	vector<int> trainResponse, testResponse, testResult;
	cout << "请选择数据来源 ：    1-文件    2-输入：" << endl;
	//cin >> select;
	//getchar();
	//if (select == 1)
	//{
	//	
	//}
	//else
	//{
	//	readDataFromKeyboard(trainData, trainResponse, "data.txt");
	//}
	readDataFromFile("data.txt", trainData, trainResponse);
	readDataFromFile("test.txt", testData, testResponse);
	Perceptron perceptron = Perceptron();
	perceptron.setItrNum(1);	//设置迭代次数
	perceptron.setLRate(1);		//设置学习率
	perceptron.train(trainData, trainResponse);	//使用训练样本对感知器进行训练
	perceptron.showWeights();	//输出权向量及其函数
	system("pause");
	perceptron.predict(testData, testResult);	//用训练好的感知器进行分类
	cout << endl << "测试样本的正确率为：" << getAccuracy(testResult, testResponse);	//显示测试结果
	
	return 0;
}
//从文件中读取测试数据或者训练数据
void readDataFromFile(string filePath, vector<vector<double> >& vecs, vector<int>& response)
{
	ifstream in;
	in.open(filePath);

	if (!in)
	{
		cerr << "file open failed!" << endl;
		exit(-1);
	}
	int i = 0;
	response.clear();
	while (in.peek() != '\n' && !in.eof())
	{
		vector<double> vec;
		double data;
		while (in.peek() != '\n' && in.peek() != ',' && !in.eof())
		{
			in >> data;
			vec.push_back(data);
		}
		response.push_back(i);
		vecs.push_back(vec);
		if (in.get() == '\n')	//if read \n
		{
			i++;
		}
	}
}

float getAccuracy(const vector<int>& result, const vector<int>& response)
{
	vector<int>::const_iterator rstItr, respItr;
	int sum = 0, hit = 0;
	for (rstItr = result.begin(), respItr = response.begin(); rstItr < result.end() && respItr < response.end(); rstItr++, respItr++)
	{
		sum++;
		if (*rstItr == *respItr)
		{
			hit++;
		}
	}
	return (float)hit / sum;
}




void readDataFromKeyboard(vector<vector<double> >& vecs, vector<int>& response ,string filepath)
{
	cout << "请在第一行输入第一类样本，第二行输入第二类样本：" << endl;

	ofstream output;
	output.open(filepath);
	string strtmp;
	getline(cin, strtmp);
	int line = 0;
	while (!strtmp.empty())
	{
		if (line == 0)
		{
			output << strtmp;
		}
		else
		{
			output << "\n" << strtmp;
		}

		line++;

		getline(cin, strtmp);
		if (strtmp == "#")
		{
			break;
		}

	}
	output.flush();
	output.close();
}