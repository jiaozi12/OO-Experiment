#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

string lower(string s);

struct KeyFrame
{
	// ��Ӧ���ɵ�JSON�ļ���keyFrames�����һ��Ԫ�أ�һ��keyFrame��
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
	// �洢Ϊ��ɫ���ɵ��ƶ�·���е�һ���ڵ�
	int action;
	double timestamp;
	vector<double> startpos;
	vector<double> endpos;
	double duration;

	PathNode(int a, double t, vector<double> s, vector<double> e, double d) : action(a), timestamp(t), startpos(s), endpos(e), duration(d) {}
};


/* �����Ѽ��С��Ϸ����Json�ļ��� */

class GenJsonFromObj
{
	// �ӱ���������Ķ����н�����Ϣ�����ɶ�Ӧ��Json�ļ�
public:

	// ����һ������ƶ�·��
	vector<PathNode> GenPath(vector<double> startPos, vector<double> timestamp, vector<pair<double, double>> limit, int mode);

	// �ӱ����������һ������زĶ�����Ϣ�й���һ��keyFrame����
	vector<KeyFrame> GenKeyFrames(unordered_map<string, vector<string>> op);

	// �����ɵ�һ��keyFrame����д��JSON�ļ�
	void WriteKeyFrames(string fileName, vector<KeyFrame> keyFrames);
};