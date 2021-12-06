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
	map<string, queue<string>> description;  // �洢�û�����Ķ���������Ϣ
	map<string, double> exeTime;  // �洢ÿ������ִ��ʱ��
	vector<set<string>> conflictSet;  // �洢�����ͻ��״̬������һ��������ͬʱ��a��b����a��b����ͬһ��������
	map<string, ObjState> objs;  // �洢ÿ�������״̬
	set<string> canExtendAction;  // �洢�����ӳ�ִ��ʱ��Ķ���
	vector<KeyFrame> produceKeyFrame(vector<pair<string, double>> seq, double totalTime, string background);  // ����������Ϣ����һ��KeyFrame

public:
	Controller(map<string, queue<string>> description);
	void planning(string fileName);
	void writeJson(string fileName, vector<KeyFrame> keyFrames);
};