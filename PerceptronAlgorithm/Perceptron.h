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
	void predict(const vector<double>& input, vector<int>& output);			//测试感知器,对测试数据进行分类

	void setItrNum(int itrNum) { this->itrNum = itrNum; }
	void setLRate(float lRate) { this->lRate = lRate; }
	void setWeights(vector<double>) { this->weights = weights; }

	void showWeights();
	void saveWeights(string filePath);	//将weights写到文件
	void readWeights(string filePath);	//将weights从文件中读出

private:
	vector<double> weights;
	vector<vector<double> > x;

	int itrNum;				//迭代次数 iterations number
	float lRate;				//学习率 learning rate

	void augmentation(vector<vector<double> >& trainData);				//训练数据的增广化
	void symbolNormalization(vector<vector<double> >& trainData, const vector<int>& response);	//符号规范化

	double mult(const vector<double> &left, const vector<double> &right);		//两个水平向量相乘（无需转置），结果为一个数
	void add(vector<double> &left, const vector<double> &right, double lRate);//两个水平向量相加
};