#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

string lower(string s);

struct KeyFrame
{
	// 对应生成的JSON文件中keyFrames数组的一个元素（一个keyFrame）
	int action;
	int type;
	string name;
	string goname;
	double timestamp;
	vector<double> startpos;
	vector<double> endpos;
	vector<double> startrotation;
	vector<double> endrotation;
	vector<double> startscale;
	vector<double> endscale;
	double duration;
	string content;
	int loop;

	KeyFrame(int actionIn, int typeIn, string nameIn, string gonameIn, double timestampIn, vector<double> startposIn, vector<double> endposIn, double durationIn, string contentIn)
	{
		action = actionIn;
		type = typeIn;
		name = nameIn;
		goname = gonameIn;
		timestamp = timestampIn;
		startpos = startposIn;
		endpos = endposIn;
		startrotation = vector<double>{ 0,0,0 };
		endrotation = vector<double>{ 0,0,0 };
		startscale = vector<double>{ 1,1,1 };
		endscale = vector<double>{ 1,1,1 };
		duration = durationIn;
		content = contentIn;
		loop = 0;
	}
};

struct PathNode
{
	// 存储为角色生成的移动路径中的一个节点
	int action;
	double timestamp;
	vector<double> startpos;
	vector<double> endpos;
	double duration;

	PathNode(int a, double t, vector<double> s, vector<double> e, double d) : action(a), timestamp(t), startpos(s), endpos(e), duration(d) {}
};


/* 定义打鸭子小游戏生成Json文件类 */

class GenJsonFromObj
{
	// 从本科生输入的对象中解析信息，生成对应的Json文件
public:

	// 生成一条随机移动路径
	vector<PathNode> GenPath(vector<double> startPos, vector<double> timestamp, vector<pair<double, double>> limit, int mode);

	// 从本科生输入的一项基本素材动作信息中构造一个keyFrame序列
	vector<KeyFrame> GenKeyFrames(unordered_map<string, vector<string>> op);

	// 将生成的一个keyFrame序列写入JSON文件
	void WriteKeyFrames(string fileName, vector<KeyFrame> keyFrames);
};