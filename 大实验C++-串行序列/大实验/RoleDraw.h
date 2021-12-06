#pragma once
#include <map>
#include <vector>
#include <string>
#include "GenerateJson.h"
using namespace std;

/* ����Role�����ɫ�Ķ���JSON����������� */

class RoleDraw
{
private:
	string roleName;
	string roleClass;
	vector<double> lastPos;
	map<string, vector<string>> clothesSupport;  // �洢�����ɫ֧�ֵĸ�����λ�ķ���
	map<string, string> clothes;  // ������Ҫ�����·�

	string getClothClass(string cloth);  // ��ȡcloth�·���Ӧ�Ĳ�λ������������κ���𣬷���""

public:
	RoleDraw(string roleName, vector<double> lastPos);
	vector<double> getLastPos();
	vector<KeyFrame> planning(vector<string> clothes, map<pair<double, double>, vector<string>> actions);  // actions�洢ÿ��ʱ���Ӧ��ִ�еĶ���
};