#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Perceptron
{
public:
	Perceptron();
	virtual ~Perceptron();

	void train(const vector<vector<double> >& trainData, const vector<int>& response);	//ѵ�������õ�Ȩʸ��
	void predict(const vector<vector<double> >& input, vector<vector<double> > &output);

	void setItrNum(int itrNum) { this->itrNum = itrNum; }
	void setLRate(float lRate) { this->lRate = lRate; }
	void setWeights(vector<double>) { this->weights = weights; }

	void showWeights();
	void saveWeights(string filePath);
	void readWeights(string filePath);

private:
	vector<double> weights;
	vector<vector<double> > x;

	int itrNum;				//�������� iterations number
	float lRate;				//ѧϰ�� learning rate

	void augmentation(vector<vector<double> >& trainData);				//ѵ�����ݵ����㻯
	void symbolNormalization(vector<vector<double> >& trainData, const vector<int>& response);	//���Ź淶��

	double mult(const vector<double> &left, const vector<double> &right);		//����ˮƽ������ˣ�����ת�ã������Ϊһ����

};