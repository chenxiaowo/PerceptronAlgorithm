#include <iostream>
#include <fstream>
#include "Perceptron.h"

using namespace std;

void readDataFromFile(string filePath, vector<vector<double> >& vecs, vector<int>& response);
void readDataFromKeyboard(vector<vector<double> >& vecs, vector<int>& response);	//从键盘获得训练数据或测试数据 vecs存放的是数据，response是每条数据对应的类别，在二分类里，0为第一类，1为第二类

int main()
{
	vector<vector<double> > trainData;
	vector<int> response;

	readDataFromFile("data.txt", trainData, response);
	Perceptron perceptron = Perceptron();
	perceptron.setItrNum(1);	//设置迭代次数
	perceptron.setLRate(1);		//设置学习率
	perceptron.train(trainData,response);	//训练
	perceptron.showWeights();
	system("pause");
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
