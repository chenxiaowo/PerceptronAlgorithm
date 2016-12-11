#include <iostream>
#include <fstream>
#include "Perceptron.h"

using namespace std;

void readDataFromFile(string filePath, vector<vector<double> >& vecs, vector<int>& response);

int main()
{
	vector<vector<double> > trainData;
	vector<int> response;

	readDataFromFile("data.txt", trainData, response);
	Perceptron perceptron = Perceptron();
	perceptron.setItrNum(1);
	perceptron.setLRate(1);
	perceptron.train(trainData,response);
	system("pause");
	return 0;
}

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
