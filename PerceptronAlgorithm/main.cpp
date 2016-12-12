#include <iostream>
#include <fstream>
#include<string>
#include "Perceptron.h"

using namespace std;

void readDataFromFile(string filePath, vector<vector<double> >& vecs, vector<int>& response);
void readDataFromKeyboard(vector<vector<double> >& vecs, vector<int>& response,string filepath);	//�Ӽ��̻��ѵ�����ݻ�������� vecs��ŵ������ݣ�response��ÿ�����ݶ�Ӧ������ڶ������0Ϊ��һ�࣬1Ϊ�ڶ���
float getAccuracy(const vector<int>& result, const vector<int>& response);		//����������ݱ���ȷ�������ȷ��

int main()
{
	int select=0;
	vector<vector<double> > trainData, testData;
	vector<int> trainResponse, testResponse, testResult;
	cout << "��ѡ��������Դ ��    1-�ļ�    2-���룺" << endl;
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
	perceptron.setItrNum(1);	//���õ�������
	perceptron.setLRate(1);		//����ѧϰ��
	perceptron.train(trainData, trainResponse);	//ʹ��ѵ�������Ը�֪������ѵ��
	perceptron.showWeights();	//���Ȩ�������亯��
	system("pause");
	perceptron.predict(testData, testResult);	//��ѵ���õĸ�֪�����з���
	cout << endl << "������������ȷ��Ϊ��" << getAccuracy(testResult, testResponse);	//��ʾ���Խ��
	
	return 0;
}
//���ļ��ж�ȡ�������ݻ���ѵ������
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
	cout << "���ڵ�һ�������һ���������ڶ�������ڶ���������" << endl;

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