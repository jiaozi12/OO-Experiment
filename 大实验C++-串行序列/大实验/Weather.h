#pragma once
#include <string>
#include <vector>
using namespace std;

class Observer
{
	// �����߳����࣬��Ҫʹ�ù۲���ģʽ������Ϣ��Role��Duck�̳д���
public:
	virtual Observer* update(string w) = 0;
};

class Weather
{
private:
	string curWea;
	vector<Observer**> subs;

public:
	void subscribe(Observer** sub);
	void unSubscribe(Observer** sub);
	void notify();
	string turnCold();
	string turnHot();
};