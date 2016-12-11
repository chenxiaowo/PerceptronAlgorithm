#include "Perceptron.h"



Perceptron::Perceptron()
{
}


Perceptron::~Perceptron()
{
}

void Perceptron::train(const vector<vector<double> >& trainData, const vector<vector<int> >& response)
{
	if (weights.empty())
	{
		weights = vector<double>(trainData[0].size, 1);
	}
	x = trainData;
	augmentation(x);
	symbolNormalization(x, response);

	//x为已增广化和符号规范化的训练数据,weights为权矢量

}

void Perceptron::augmentation(vector<vector<double> >& trainData)
{
	vector<vector<double> >::iterator itr;
	for (itr = trainData.begin(); itr != trainData.end(); itr++)
	{
		itr->push_back(1);
	}
}

void Perceptron::symbolNormalization(vector<vector<double>>& trainData, const vector<vector<int>>& response)
{
	vector<vector<double> >::iterator dataItr;
	vector<vector<int> >::const_iterator respItr;
	for (dataItr = trainData.begin(),respItr = response.begin(); dataItr != trainData.end()||respItr !=response.end(); dataItr++,respItr++)
	{
		vector<int>::const_iterator respInnerItr = respItr->begin();
		int i;
		for (i = 0; i < respItr->size()&& *respInnerItr++ != 1; i++)
		{
		}
		if (i==1)		//当属于第二类时，将其符号乘以-1
		{
			vector<double>::iterator dataInnerItr;
			for (dataInnerItr= dataItr->begin(); dataInnerItr < dataItr->end(); dataInnerItr++)
			{
				*dataInnerItr = 0 - *dataInnerItr;
			}
		}
	}
}

double Perceptron::mult(const vector<double> &left, const vector<double> &right)
{
	double result = 0;
	vector<double>::const_iterator itrLeft, itrRight;
	for (itrLeft = left.begin(), itrRight = right.begin(); itrLeft < left.end() && itrRight<right.end(); itrLeft++, itrRight++)
	{
		result += *itrLeft * *itrRight;
	}
	return result;
}