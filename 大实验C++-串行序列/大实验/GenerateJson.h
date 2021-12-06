#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;

string lower(string s);
string getClass(string obj);

struct KeyFrame
{
	// 对应生成的JSON文件中keyFrames数组的一个元素（一个keyFrame）
	int action;
	int type;
	string name;
	string goname;
	double timestamp;
	string background;
	map<string, string> clothes;
	vector<double> startpos;
	vector<double> endpos;
	vector<double> startrotation;
	vector<double> endrotation;
	vector<double> startscale;
	vector<double> endscale;
	double duration;
	string content;
	int loop;

	KeyFrame(int actionIn, string nameIn, string gonameIn, double timestampIn, string backgroundIn, map<string, string> clothesIn, vector<double> startposIn, vector<double> endposIn, double durationIn, string contentIn)
	{
		action = actionIn;
		type = 3;
		name = nameIn;
		goname = gonameIn;
		timestamp = timestampIn;
		background = backgroundIn;
		clothes = clothesIn;
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