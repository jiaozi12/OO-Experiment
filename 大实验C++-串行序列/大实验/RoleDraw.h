#pragma once
#include <map>
#include <vector>
#include <string>
#include "GenerateJson.h"
using namespace std;

/* 处理Role人物角色的动画JSON生成相关事项 */

class RoleDraw
{
private:
	string roleName;
	string roleClass;
	vector<double> lastPos;
	map<string, vector<string>> clothesSupport;  // 存储人物角色支持的各个部位的服饰
	map<string, string> clothes;  // 人物需要穿的衣服

	string getClothClass(string cloth);  // 获取cloth衣服对应的部位类别，若不属于任何类别，返回""

public:
	RoleDraw(string roleName, vector<double> lastPos);
	vector<double> getLastPos();
	vector<KeyFrame> planning(vector<string> clothes, map<pair<double, double>, vector<string>> actions);  // actions存储每个时间段应该执行的动作
};