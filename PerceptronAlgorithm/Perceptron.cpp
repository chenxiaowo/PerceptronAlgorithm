#include "Perceptron.h"



Perceptron::Perceptron()
{
}


Perceptron::~Perceptron()
{
}

void Perceptron::train(const vector<vector<double> >& trainData, const vector<int>& response)
{
	if (weights.empty())		//��weightsû�б���ʼ��ʱ
	{
		weights = vector<double>(trainData[0].size() + 1, 1);		//��������Ȩֵ��ʼ��Ϊ1
	}
	x = trainData;
	augmentation(x);
	symbolNormalization(x, response);

	//�õ��ĳ�Ա�����ͺ���
	//xΪ�����㻯�ͷ��Ź淶����ѵ������,weightsΪȨʸ����itrNumΪ����������lRateΪѧϰ�ʣ�mult()Ϊ��ˮƽ������˺���
	//��ʼѵ��
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
//��ʾȨʸ��
void Perceptron::showWeights()
{
	cout << endl<<"Ȩʸ��Ϊ��";
	vector<double>::const_iterator weightsItr = weights.begin();
	cout << *weightsItr++;
	for (; weightsItr < weights.end(); weightsItr++)
	{
		cout <<","<<*weightsItr;
	}
	cout << endl << "���ֽ���Ϊ��";
	weightsItr = weights.begin();
	cout << *weightsItr++ << "x" << 1 ;
	for (int i = 2; i < weights.size(); i++)
	{
		cout << "+"<< *weightsItr++<<"x"<<i;
	}
	cout << "+" << *weightsItr <<"=0"<< endl;
}
//ѵ�����ݵ����㻯
void Perceptron::augmentation(vector<vector<double> >& trainData)
{
	vector<vector<double> >::iterator itr;
	for (itr = trainData.begin(); itr != trainData.end(); itr++)
	{
		itr->push_back(1);
	}
}
//���Ź淶��
void Perceptron::symbolNormalization(vector<vector<double>>& trainData, const vector<int>& response)
{
	vector<vector<double> >::iterator dataItr;
	vector<int>::const_iterator respItr;
	for (dataItr = trainData.begin(), respItr = response.begin(); dataItr != trainData.end() || respItr != response.end(); dataItr++, respItr++)
	{
		if (*respItr == 1)		//�����ڵڶ���ʱ��������ų���-1
		{
			vector<double>::iterator dataInnerItr;
			for (dataInnerItr = dataItr->begin(); dataInnerItr < dataItr->end(); dataInnerItr++)
			{
				*dataInnerItr = 0 - *dataInnerItr;
			}
		}
	}
}
//����ˮƽ������ˣ�����ת�ã������Ϊһ����
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

//����ˮƽ�������
void Perceptron:: add(vector<double> &left, const vector<double> &right,double lRate)
{
	for (int i = 0; i < left.size(); i++)
	{
		left[i] += right[i]*lRate;
	}
}