#pragma once
#include <string>
#include <vector>
#include <queue>
#include <set>
#include "GenerateJson.h"
using namespace std;

class ObjState
{
private:
	vector<double> pos;
	string action;
	map<string, string> clothes;

public:
	ObjState();
	ObjState(vector<double> pos, string action);
	void setPos(vector<double> pos);
	void setAction(string action);
	void setClothes(map<string, string> clothes);
	vector<double> getPos();
	string getAction();
	map<string, string> getClothes();
};

class Controller
{
private:
	map<string, queue<string>> description;  // 存储用户输入的动画描述信息
	map<string, double> exeTime;  // 存储每个动作执行时间
	vector<set<string>> conflictSet;  // 存储互相冲突的状态集。若一个对象不能同时做a和b，则a、b会在同一个集合中
	map<string, ObjState> objs;  // 存储每个对象的状态
	set<string> canExtendAction;  // 存储可以延长执行时间的动作
	vector<KeyFrame> produceKeyFrame(vector<pair<string, double>> seq, double totalTime, string background);  // 根据输入信息生成一个KeyFrame

public:
	Controller(map<string, queue<string>> description);
	void planning(string fileName);
	void writeJson(string fileName, vector<KeyFrame> keyFrames);
};