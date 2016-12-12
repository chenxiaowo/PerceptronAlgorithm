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
	vector<int> err;
	while (true)
	{
		after = weights;
		samk = x[k % 4];
		d = mult(after, samk);
		cout <<"������"<< k+1 << endl;
		cout <<"d>0?    " <<(d>0) << endl;
		system("pause");
		if (d > 0)
		{
			count++;
			err.push_back(k%4);
		}
		else
		{
			cout <<"��ǰ��ֵ�������" << endl;
			for (int i = 0; i < err.size(); i++)
			{
				vector<double> tmp = x[err[i]];
				cout << "(" << tmp[0] << "," << tmp[1] << ")" << endl;
			}
			
			cout << "��ֵ�����"<<count<< endl;
			add(after, samk, lRate);
			weights = after;
			count = 0;
			err.clear();
		}

		k++;
		if (count >= 3)
		{
			break;
		}
		cout <<"��ǰ��Ȩʸ����" << endl;
		vector<double>::const_iterator weightsItr = weights.begin();
		cout << *weightsItr++;
		for (; weightsItr < weights.end(); weightsItr++)
		{
			cout << "," << *weightsItr;
		}
		cout << endl;
		cout << "\t" << endl;
		system("pause");
	}

}
//���Ը�֪��,�Բ������ݽ��з���
void Perceptron::predict(const vector<vector<double> >& input, vector<int>& output)
{
	vector<vector<double> > test = input;
	augmentation(test);
	vector<vector<double> >::const_iterator inputItr;
	
	for (inputItr = test.begin(); inputItr != test.end() ; inputItr++)
	{
		if (mult(*inputItr, weights) > 0)
		{
			output.push_back(0);
		}
		else
		{
			output.push_back(1);
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