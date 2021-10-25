/* 实现GenerateJson.h中的类方法 */

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
	// 把s中的所有大写字母转化为小写
	for (auto& it : s)
	{
		if (it >= 'A' && it <= 'Z') it += 32;
	}
	return s;
}

string getClass(string obj)
{
	// 返回obj[0..首次出现数字的位置)
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
	// startPos为起始坐标
	// timestamp存储若干个时间戳，生成对应时间戳的startPos和endPos
	// limit为限制区间，分别限制了生成的坐标点x,y,z的取值范围
	// mode为0时，生成的路径包含开始节点（角色出现时刻）；mode为1时，生成路径不包含开始节点

	vector<PathNode> path;
	vector<double> last = startPos;
	if(mode == 0) path.push_back(PathNode(0, 0, startPos, startPos, 0)); // 开始节点
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
	// op存储角色和其具有的behavior，如op["RedHeadDuck"] = ["FlyWithWings"]表示RedHeadDuck具有FlyWithWings的表现
	// 返回一个KeyFrame，是为该id对象生成的从0时刻到结束时刻的KeyFrame，用于生成json文件给unity解析显示
	const int type = 3;
	const double totalTime = 30;
	vector<KeyFrame> keyFrames;

	// 为所有角色生成移动路径
	for (auto& it : op)
	{
		int cnt = 0;
		for (auto& jt : it.second)
		{
			if (lower(jt) != "quack" && lower(jt) != "squick") cnt++;
		}
		double time = 0, dur = totalTime / cnt, startTime = 0, endTime = 0;
		vector<double> startPos = { 0,0,0 };
		
		// 检查是否有"stun"；如果有，则先删除"stun"后的所有动作，然后在"stun"后添加"death"动作
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
			// 每一个if对应一种动画/声音表现

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
				// stun动画只播放2s
				startTime = endTime;
				endTime += 2;
				KeyFrame kf(2, type, getClass(it.first), it.first, startTime, startPos, startPos, 2, "Stun");
				keyFrames.push_back(kf);
			}
			else if (be == "death")
			{
				// 一旦播放death，就一直播放，直到整个动画结束
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
	ptree root;  // 根节点
	ptree arrv;  // 数组一级节点
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