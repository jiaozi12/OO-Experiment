#pragma once
#include <map>
#include <vector>
#include <string>
#include "GenerateJson.h"
using namespace std;

/* 处理Duck的动画JSON生成相关事项 */

class DuckDraw
{
private:
	string duckName;
	string duckClass;
	vector<double> lastPos;

public:
	DuckDraw(string duckName, vector<double> lastPos);
	vector<double> getLastPos();
	vector<KeyFrame> planning(map<pair<double, double>, vector<string>> actions);  // actions存储每个时间段应该执行的动作
};