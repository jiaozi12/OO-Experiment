/* ʵ��GenerateJson.h�е��෽�� */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <unordered_map>
#include <map>
#include <random>
#include "GenerateJson.h"

using namespace boost::property_tree;
default_random_engine e(time(NULL));

string lower(string s)
{
	// ��s�е����д�д��ĸת��ΪСд
	for (auto& it : s)
	{
		if (it >= 'A' && it <= 'Z') it += 32;
	}
	return s;
}

string getClass(string obj)
{
	// ����obj[0..�״γ������ֵ�λ��)
	int idx = 0;
	while (idx < obj.length())
	{
		if (obj[idx] >= '0' && obj[idx] <= '9') break;
		idx++;
	}

	return obj.substr(0, idx);
}

vector<PathNode> GenJsonFromObj::GenPath(vector<double> startPos, vector<double> timestamp, vector<pair<double, double>> limit, int mode)
{
	// startPosΪ��ʼ����
	// timestamp�洢���ɸ�ʱ��������ɶ�Ӧʱ�����startPos��endPos
	// limitΪ�������䣬�ֱ����������ɵ������x,y,z��ȡֵ��Χ
	// modeΪ0ʱ�����ɵ�·��������ʼ�ڵ㣨��ɫ����ʱ�̣���modeΪ1ʱ������·����������ʼ�ڵ�

	vector<PathNode> path;
	vector<double> last = startPos;
	if(mode == 0) path.push_back(PathNode(0, 0, startPos, startPos, 0)); // ��ʼ�ڵ�
	timestamp.push_back(timestamp.back() + timestamp.back() - timestamp[timestamp.size() - 2]);

	for (size_t i = 0; i < timestamp.size()-1; i++)
	{ 
		uniform_real_distribution<double> x(limit[0].first, limit[0].second), y(limit[1].first, limit[1].second), z(limit[2].first, limit[2].second);
		vector<double> random = { x(e), y(e), z(e) };
		if (timestamp[i] == 0) timestamp[i] = 1;
		path.push_back(PathNode(2, timestamp[i], last, random, timestamp[i+1]-timestamp[i]));
		last = random;
	}

	return path;
}

vector<KeyFrame> GenJsonFromObj::GenKeyFrames(unordered_map<string, vector<string>> op)
{
	// op�洢��ɫ������е�behavior����op["RedHeadDuck"] = ["FlyWithWings"]��ʾRedHeadDuck����FlyWithWings�ı���
	// ����һ��KeyFrame����Ϊ��id�������ɵĴ�0ʱ�̵�����ʱ�̵�KeyFrame����������json�ļ���unity������ʾ
	const int type = 3;
	const double totalTime = 30;
	vector<KeyFrame> keyFrames;

	// Ϊ���н�ɫ�����ƶ�·��
	for (auto& it : op)
	{
		int cnt = 0;
		for (auto& jt : it.second)
		{
			if (lower(jt) != "quack" && lower(jt) != "squick") cnt++;
		}
		double time = 0, dur = totalTime / cnt, startTime = 0, endTime = 0;
		vector<double> startPos = { 0,0,0 };
		
		// ����Ƿ���"stun"������У�����ɾ��"stun"������ж�����Ȼ����"stun"�����"death"����
		int idx = -1;
		for (int i = 0; i < it.second.size(); i++)
		{
			if (lower(it.second[i]) == "stun")
			{
				idx = i + 1;
				break;
			}
		}
		if (idx != -1)
		{
			for (size_t i = it.second.size() - 1; i >= idx; i--) it.second.erase(it.second.begin() + i);
			it.second.push_back("Death");
		}

		for (auto& jt : it.second)
		{
			string be = lower(jt);
			vector<PathNode> path;
			// ÿһ��if��Ӧһ�ֶ���/��������

			if (be == "flywithwings" || be == "flywithpropulsion" || be == "flywithpropeller")
			{
				vector<double> timestamp;
				startTime = endTime;
				endTime += dur;
				for (double t = startTime; t < endTime; t += dur/4) timestamp.push_back(t);
				int mode = find(it.second.begin(), it.second.end(), jt)==it.second.begin() ? 0 : mode = 1;
				vector<pair<double, double>> limit = { make_pair(0,1), make_pair(0,1), make_pair(0,1) };
				path = GenPath(startPos, timestamp, limit, mode);
				startPos = path.back().endpos;
			}

			else if (be == "flynoway" || be == "mutequack") continue;
			else if (be == "swim" || be == "float")
			{
				vector<double> timestamp;
				startTime = endTime;
				endTime += dur;
				for (double t = startTime; t < endTime; t += dur/4) timestamp.push_back(t);
				int mode = find(it.second.begin(), it.second.end(), jt) == it.second.begin() ? 0 : mode = 1;
				vector<pair<double, double>> limit = { make_pair(0,0.5), make_pair(0,0), make_pair(0,1) };

				path = GenPath(startPos, timestamp, limit, mode);
				startPos = path.back().endpos;
			}
			else if (be == "quack" || be == "squick")
			{
				double st = 0, et = 0;
				vector<double> zero = { 0,0,0 };
				for (auto& kt : it.second)
				{
					string be2 = lower(kt);
					if (be2 == "stun") et += 2;
					else if (be2 == "death") break;
					else et += dur;
				}
				KeyFrame kf1(0, type, getClass(it.first), it.first, st, zero, zero, 0, "");
				KeyFrame kf2(3, type, jt, it.first, st+1, zero, zero, min(et, totalTime)-1, "");
				keyFrames.push_back(kf1);
				keyFrames.push_back(kf2);
			}
			else if (be == "stun")
			{
				// stun����ֻ����2s
				startTime = endTime;
				endTime += 2;
				KeyFrame kf(2, type, getClass(it.first), it.first, startTime, startPos, startPos, 2, "Stun");
				keyFrames.push_back(kf);
			}
			else if (be == "death")
			{
				// һ������death����һֱ���ţ�ֱ��������������
				startTime = endTime;
				endTime = totalTime;
				KeyFrame kf(2, type, getClass(it.first), it.first, startTime, startPos, startPos, endTime-startTime, "Death");
				keyFrames.push_back(kf);
				break;
			}

			for (auto& p : path)
			{
				string content = "";
				if (p.action == 0) content = "";
				else if (p.action == 2) content = jt;
				KeyFrame kf(p.action, type, getClass(it.first), it.first, p.timestamp, p.startpos, p.endpos, p.duration, content);
				keyFrames.push_back(kf);
			}
		}
	}
	
	return keyFrames;
}

void GenJsonFromObj::WriteKeyFrames(string fileName, vector<KeyFrame> keyFrames)
{
	ptree root;  // ���ڵ�
	ptree arrv;  // ����һ���ڵ�
	for (auto& kf : keyFrames)
	{
		ptree children;
		ptree keyFrame;

		keyFrame.put("action", kf.action);
		keyFrame.put("type", kf.type);
		keyFrame.put("name", kf.name);
		keyFrame.put("goname", kf.goname);
		keyFrame.put("timestamp", kf.timestamp);
		for (auto& it : kf.startpos) 
		{
			ptree child;
			child.put("", it);
			children.push_back(make_pair("", child));
		}
		keyFrame.add_child("startpos", children);
		children.clear();
		for (auto& it : kf.endpos)
		{
			ptree child;
			child.put("", it);
			children.push_back(make_pair("", child));
		}
		keyFrame.add_child("endpos", children);
		children.clear();
		for (auto& it : kf.startrotation)
		{
			ptree child;
			child.put("", it);
			children.push_back(make_pair("", child));
		}
		keyFrame.add_child("startrotation", children);
		children.clear();
		for (auto& it : kf.endrotation)
		{
			ptree child;
			child.put("", it);
			children.push_back(make_pair("", child));
		}
		keyFrame.add_child("endrotation", children);
		children.clear();
		for (auto& it : kf.startscale)
		{
			ptree child;
			child.put("", it);
			children.push_back(make_pair("", child));
		}
		keyFrame.add_child("startscale", children);
		children.clear();
		for (auto& it : kf.endscale)
		{
			ptree child;
			child.put("", it);
			children.push_back(make_pair("", child));
		}
		keyFrame.add_child("endscale", children);
		children.clear();
		keyFrame.put("duration", kf.duration);
		keyFrame.put("content", kf.content);
		keyFrame.put("loop", kf.loop);
		
		arrv.push_back(make_pair("", keyFrame));
	}
	root.add_child("keyFrames", arrv);
	write_json(fileName, root);
}