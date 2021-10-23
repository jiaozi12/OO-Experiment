#pragma once
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "GenerateJson.h"
using namespace std;

extern unordered_map<string, vector<string>> co;  // 存储类及该类的对象名，如co["RedHeadDuck"] = ["RedHeadDuck1", "RedHeadDuck2"]表示有两个RedHeadDuck类的对象
extern unordered_map<string, vector<string>> op;  // 存储输入的角色对象与其对应的behavior，例如op["RedHeadDuck1"] = ["FlyWithWings"]表示RedHeadDuck1具有FlyWithWings的behavior
extern unordered_set<string> legalName;  // 存储所有合法的角色对象名与behavior名，用于检查用户输入是否包含非法对象名和非法behavior名

// 预处理用户提供的字符串s
string preDeal(string s);

// 以逗号为分隔符，将字符串s分隔
vector<string> split(string s);

// 接收输入的角色对象和对应的behavior，保存到全局变量op中
void push(string s);

// 此函数每次被调用，都会根据当前op中的数据生成一个JSON文件
void animate(string path);