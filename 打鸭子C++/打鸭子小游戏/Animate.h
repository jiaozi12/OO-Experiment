#pragma once
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "GenerateJson.h"
using namespace std;

extern unordered_map<string, vector<string>> co;  // �洢�༰����Ķ���������co["RedHeadDuck"] = ["RedHeadDuck1", "RedHeadDuck2"]��ʾ������RedHeadDuck��Ķ���
extern unordered_map<string, vector<string>> op;  // �洢����Ľ�ɫ���������Ӧ��behavior������op["RedHeadDuck1"] = ["FlyWithWings"]��ʾRedHeadDuck1����FlyWithWings��behavior
extern unordered_set<string> legalName;  // �洢���кϷ��Ľ�ɫ��������behavior�������ڼ���û������Ƿ�����Ƿ��������ͷǷ�behavior��

// Ԥ�����û��ṩ���ַ���s
string preDeal(string s);

// �Զ���Ϊ�ָ��������ַ���s�ָ�
vector<string> split(string s);

// ��������Ľ�ɫ����Ͷ�Ӧ��behavior�����浽ȫ�ֱ���op��
void push(string s);

// �˺���ÿ�α����ã�������ݵ�ǰop�е���������һ��JSON�ļ�
void animate(string path);