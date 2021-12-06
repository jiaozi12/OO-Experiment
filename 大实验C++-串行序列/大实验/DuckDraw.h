#pragma once
#include <map>
#include <vector>
#include <string>
#include "GenerateJson.h"
using namespace std;

/* ����Duck�Ķ���JSON����������� */

class DuckDraw
{
private:
	string duckName;
	string duckClass;
	vector<double> lastPos;

public:
	DuckDraw(string duckName, vector<double> lastPos);
	vector<double> getLastPos();
	vector<KeyFrame> planning(map<pair<double, double>, vector<string>> actions);  // actions�洢ÿ��ʱ���Ӧ��ִ�еĶ���
};