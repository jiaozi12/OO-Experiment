#pragma once
#include <vector>
#include <string>
#include "Weather.h"
using namespace std;

/* 定义装饰模式中和人物角色相关的类*/

// Role相当于装饰模式模板中的Component类

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