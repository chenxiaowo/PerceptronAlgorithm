#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Perceptron
{
public:
	Perceptron();
	virtual ~Perceptron();

	void train(const vector<vector<double> >& trainData, const vector<int>& response);	//训练样本得到权矢量
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

	int itrNum;				//迭代次数 iterations number
	float lRate;				//学习率 learning rate

	void augmentation(vector<vector<double> >& trainData);				//训练数据的增广化
	void symbolNormalization(vector<vector<double> >& trainData, const vector<int>& response);	//符号规范化

	double mult(const vector<double> &left, const vector<double> &right);		//两个水平向量相乘（无需转置），结果为一个数

};