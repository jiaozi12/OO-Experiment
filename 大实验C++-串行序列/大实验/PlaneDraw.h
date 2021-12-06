#pragma once
#include <map>
#include <vector>
#include <string>
#include "GenerateJson.h"
using namespace std;

/* ����Plane�Ķ���JSON����������� */

class PlaneDraw
{
private:
	string planeName;
	string planeClass;
	vector<double> lastPos;

public:
	PlaneDraw(string planeName, vector<double> lastPos);
	vector<double> getLastPos();
	vector<KeyFrame> planning(map<pair<double, double>, vector<string>> actions);  // actions�洢ÿ��ʱ���Ӧ��ִ�еĶ���
};