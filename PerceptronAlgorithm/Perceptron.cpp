#include "Perceptron.h"



Perceptron::Perceptron()
{
}


Perceptron::~Perceptron()
{
}

void Perceptron::train(const vector<vector<double> >& trainData, const vector<int>& response)
{
	if (weights.empty())		//当weights没有被初始化时
	{
		weights = vector<double>(trainData[0].size() + 1, 1);		//将其所有权值初始化为1
	}
	x = trainData;
	augmentation(x);
	symbolNormalization(x, response);

	//用到的成员变量和函数
	//x为已增广化和符号规范化的训练数据,weights为权矢量，itrNum为迭代次数，lRate为学习率，mult()为两水平向量相乘函数
	//开始训练
	int k = itrNum-1;
	vector<double> after = weights;
	vector<double> samk;
	double d = 0;
	int count = 0;
	while (true)
	{
		after = weights;
		samk = x[k % 4];
		d = mult(after, samk);
		cout << k << endl;
		cout << d << endl;
		system("pause");
		if (d > 0)
		{
			count++;
		}
		else
		{
			add(after, samk, lRate);
			weights = after;
			count = 0;
		}

		k++;
		if (count >= 3)
		{
			break;
		}
	}

}
//显示权矢量
void Perceptron::showWeights()
{
	cout << endl<<"权矢量为：";
	vector<double>::const_iterator weightsItr = weights.begin();
	cout << *weightsItr++;
	for (; weightsItr < weights.end(); weightsItr++)
	{
		cout <<","<<*weightsItr;
	}
	cout << endl << "区分界面为：";
	weightsItr = weights.begin();
	cout << *weightsItr++ << "x" << 1 ;
	for (int i = 2; i < weights.size(); i++)
	{
		cout << "+"<< *weightsItr++<<"x"<<i;
	}
	cout << "+" << *weightsItr <<"=0"<< endl;
}
//训练数据的增广化
void Perceptron::augmentation(vector<vector<double> >& trainData)
{
	vector<vector<double> >::iterator itr;
	for (itr = trainData.begin(); itr != trainData.end(); itr++)
	{
		itr->push_back(1);
	}
}
//符号规范化
void Perceptron::symbolNormalization(vector<vector<double>>& trainData, const vector<int>& response)
{
	vector<vector<double> >::iterator dataItr;
	vector<int>::const_iterator respItr;
	for (dataItr = trainData.begin(), respItr = response.begin(); dataItr != trainData.end() || respItr != response.end(); dataItr++, respItr++)
	{
		if (*respItr == 1)		//当属于第二类时，将其符号乘以-1
		{
			vector<double>::iterator dataInnerItr;
			for (dataInnerItr = dataItr->begin(); dataInnerItr < dataItr->end(); dataInnerItr++)
			{
				*dataInnerItr = 0 - *dataInnerItr;
			}
		}
	}
}
//两个水平向量相乘（无需转置），结果为一个数
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

//两个水平向量相加
void Perceptron:: add(vector<double> &left, const vector<double> &right,double lRate)
{
	for (int i = 0; i < left.size(); i++)
	{
		left[i] += right[i]*lRate;
	}
}