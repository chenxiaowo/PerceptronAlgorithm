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
	void predict(const vector<vector<double> >& input, vector<int>& output);			//测试感知器,对测试数据进行分类

	void setItrNum(int itrNum) { this->itrNum = itrNum; }//设置迭代次数
	void setLRate(float lRate) { this->lRate = lRate; }//设置学习率
	void setWeights(vector<double>) { this->weights = weights; }//设置权值向量

	void showWeights();//显示权值向量
	void saveWeights(string filePath);	//将weights写到文件
	void readWeights(string filePath);	//将weights从文件中读出

private:
	vector<double> weights;//权值向量
	vector<vector<double> > x;//样本集合

	int itrNum;				//迭代次数 iterations number
	float lRate;				//学习率 learning rate

	void augmentation(vector<vector<double> >& trainData);				//训练数据的增广化
	void symbolNormalization(vector<vector<double> >& trainData, const vector<int>& response);	//符号规范化

	double mult(const vector<double> &left, const vector<double> &right);		//两个水平向量相乘（无需转置），结果为一个数
	void add(vector<double> &left, const vector<double> &right, double lRate);//两个水平向量相加
};