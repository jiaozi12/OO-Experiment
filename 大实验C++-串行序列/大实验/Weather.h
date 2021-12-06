#pragma once
#include <string>
#include <vector>
using namespace std;

class Observer
{
	// 订阅者抽象类，需要使用观察者模式订阅消息的Role与Duck继承此类
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