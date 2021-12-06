#pragma once
#include <vector>
#include <string>
#include "Weather.h"
using namespace std;

/* ����װ��ģʽ�к������ɫ��ص���*/

// Role�൱��װ��ģʽģ���е�Component��

class Observer;

class Role : public Observer
{
public:
	string description;

public:
	virtual vector<string> getDescription();
	string performWalk();
	string performShoot();
	Observer* update(string w);
};

class Hunter : public Role
{
public:
	Hunter(string description) { this->description = description; }
};

class Boy : public Role
{
public:
	Boy(string description) { this->description = description; }
};

class Girl : public Role
{
public:
	Girl(string description) { this->description = description; }
};