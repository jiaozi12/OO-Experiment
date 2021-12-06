#include "Controller.h"
#include "util.h"
#include "RoleDraw.h"
#include "PlaneDraw.h"
#include "DuckDraw.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
using namespace boost::property_tree;

ObjState::ObjState()
{
	this->pos = vector<double>{ 0.0, 0.0, 0.0 };
	this->action = "";
	this->clothes = { {"Hat", ""}, {"Jacket", ""}, {"Pants", ""}, {"Shoes", ""} };
}
ObjState::ObjState(vector<double> pos, string action)
{
	this->pos = pos;
	this->action = action;
	this->clothes = { {"Hat", ""}, {"Jacket", ""}, {"Pants", ""}, {"Shoes", ""} };
}
void ObjState::setPos(vector<double> pos)
{
	this->pos = pos;
}
void ObjState::setAction(string action)
{
	this->action = action;
}
void ObjState::setClothes(map<string, string> clothes)
{
	this->clothes = clothes;
}
vector<double> ObjState::getPos()
{
	return this->pos;
}
string ObjState::getAction()
{
	return this->action;
}
map<string, string> ObjState::getClothes()
{
	return this->clothes;
}

Controller::Controller(map<string, queue<string>> description)
{
	this->description = description;
	exeTime = { {"Appear", 0.1}, {"Shirt", 0.1}, {"DownJacket", 0.1}, {"Jeans", 0.1}, {"CasualPants", 0.1}, 
	{"ShortHair", 0.1}, { "LongHair", 0.1 }, { "Boots", 0.1 }, { "Sneaker", 0.1 }, { "HuntingSuit", 0.1 },
	{"CasualSuit", 0.1}, { "FlyWithWings", 3.0 },{"Swim", 3.0}, { "Float", 3.0 }, { "Quack", 1.0 }, 
	{ "Squick", 1.0 }, { "Stun", 1.0 }, {"Failing", 1.0}, {"Death", 3.0}, {"FlyWithPropulsion", 3.0}, 
	{"FlyWithPropeller", 3.0}, {"Walk", 3.0}, {"Shoot", 1.0}, {"FlyNoWay", 3.0}, {"Land", 1.0}};

	conflictSet = { {"Appear"}, {"Shirt", "DownJacket"}, {"Jeans", "CasualPants"}, {"ShortHair", "LongHair"},
		{"Boots", "Sneaker"}, {"HuntingSuit", "CasualSuit"}, {"FlyWithWings", "Swim", "Float", "FlyNoWay", 
		"FlyWithPropulsion", "FlyWithPropeller", "Walk", "Shoot", "Stun", "Failing", "Death", "Land"}};

	canExtendAction = { "FlyWithWings", "Swim", "Float", "Quack", "Squick", "Death", "FlyWithPropulsion", "FlyWithPropeller", "Walk" };
}

vector<KeyFrame> Controller::produceKeyFrame(vector<pair<string, double>> seq, double totalTime, string background)
{
	vector<KeyFrame> keyFrames;
	for (auto it : seq)
	{
		string obj = it.first.substr(0, it.first.find(".")), action = it.first.substr(it.first.find(".") + 1);
		double timestamp = it.second;
		if (canExtendAction.count(action) == 0)
		{
			// action为事件，时间很短暂
			if (action == "Appear")
			{
				vector<double> zero = { 0.0,0.0,0.0 };
				objs[obj] = ObjState(zero, action);
				string content = "";
				KeyFrame kf = KeyFrame(0, getClass(obj), obj, timestamp, background, map<string, string>(), zero, zero, exeTime[action], content);
				keyFrames.emplace_back(kf);
			}
			else if (action == "Shirt" || action == "DownJacket")
			{
				string content = "";
				map<string, string> clothes = objs[obj].getClothes();
				clothes["Jacket"] = action;
				objs[obj].setClothes(clothes);
				KeyFrame kf = KeyFrame(7, getClass(obj), obj, timestamp, background, clothes, objs[obj].getPos(), objs[obj].getPos(), exeTime[action], content);
				keyFrames.emplace_back(kf);
			}
			else if (action == "Jeans" || action == "CasualPants")
			{
				string content = "";
				map<string, string> clothes = objs[obj].getClothes();
				clothes["Pants"] = action;
				objs[obj].setClothes(clothes);
				KeyFrame kf = KeyFrame(7, getClass(obj), obj, timestamp, background, clothes, objs[obj].getPos(), objs[obj].getPos(), exeTime[action], content);
				keyFrames.emplace_back(kf);
			}
			else if (action == "ShortHair" || action == "LongHair")
			{
				string content = "";
				map<string, string> clothes = objs[obj].getClothes();
				clothes["Hat"] = action;
				objs[obj].setClothes(clothes);
				KeyFrame kf = KeyFrame(7, getClass(obj), obj, timestamp, background, clothes, objs[obj].getPos(), objs[obj].getPos(), exeTime[action], content);
				keyFrames.emplace_back(kf);
			}
			else if (action == "Boots" || action == "Sneaker")
			{
				string content = "";
				map<string, string> clothes = objs[obj].getClothes();
				clothes["Shoes"] = action;
				objs[obj].setClothes(clothes);
				KeyFrame kf = KeyFrame(7, getClass(obj), obj, timestamp, background, clothes, objs[obj].getPos(), objs[obj].getPos(), exeTime[action], content);
				keyFrames.emplace_back(kf);
			}
			else if (action == "HuntingSuit" || action == "CasualSuit")
			{
				string content = "";
				map<string, string> clothes = objs[obj].getClothes();
				clothes["Jacket"] = action;
				clothes["Pants"] = action;
				clothes["Hat"] = action;
				clothes["Shoes"] = action;

				objs[obj].setClothes(clothes);
				KeyFrame kf = KeyFrame(7, getClass(obj), obj, timestamp, background, clothes, objs[obj].getPos(), objs[obj].getPos(), exeTime[action], content);
				keyFrames.emplace_back(kf);
			}
			else if (action == "Shoot")
			{
				string content = "";
				KeyFrame kf = KeyFrame(3, action, obj, timestamp, background, map<string, string>(), objs[obj].getPos(), objs[obj].getPos(), exeTime[action], content);
				keyFrames.emplace_back(kf);
			}
			else if (action == "Stun")
			{
				KeyFrame kf = KeyFrame(2, getClass(obj), obj, timestamp, background, map<string, string>(), objs[obj].getPos(), objs[obj].getPos(), exeTime[action], action);
				keyFrames.emplace_back(kf);
			}
			else if (action == "Failing")
			{
				vector<double> pos = objs[obj].getPos();
				pos[1] = 0.0;
				KeyFrame kf = KeyFrame(2, getClass(obj), obj, timestamp, background, map<string, string>(), objs[obj].getPos(), pos, exeTime[action], action);
				objs[obj].setPos(pos);
				keyFrames.emplace_back(kf);
			}
			else if (action == "Land")
			{
				vector<double> pos = objs[obj].getPos();
				pos[1] = 0.0;
				KeyFrame kf = KeyFrame(2, getClass(obj), obj, timestamp, background, map<string, string>(), objs[obj].getPos(), pos, exeTime[action], "FlyWithWings");
				objs[obj].setPos(pos);
				keyFrames.emplace_back(kf);
			}
		}
		else
		{
			// 当前action为可以延长执行时间的状态
			// 先找到当前action可以执行到的最大时间戳（通过查找其后面有没有互斥动作实现）
			double endTime = totalTime;
			for (auto jt : seq)
			{
				string obj2 = jt.first.substr(0, jt.first.find(".")), action2 = jt.first.substr(jt.first.find(".") + 1);
				double timestamp2 = jt.second;
				bool over = false;
				if (timestamp2 > timestamp && obj == obj2)
				{
					for (auto kt : conflictSet)
					{
						if (kt.count(action) > 0 && kt.count(action2) > 0)
						{
							endTime = timestamp2;
							over = true;
							break;
						}
					}
				}
				if (over) break;
			}
			
			//canExtendAction = { "FlyWithWings", "Swim", "Float", "Quack", "Squick", "Death", "FlyWithPropulsion", "FlyWithPropeller", "Walk" };
			// 为每种动作情况单独生成KeyFrame
			if (action == "FlyWithWings" || action == "Swim" || action == "Float" || action == "Death" ||
				action == "FlyWithPropulsion" || action == "FlyWithPropeller" || action == "Walk")
			{
				vector<pair<double, double>> limit;
				if (action == "Swim" || action == "Float")
				{
					limit = { make_pair(0.0,0.4), make_pair(0.0,0.0), make_pair(0.3, 0.7) };
				}
				else if (action == "FlyWithWings" || action == "FlyWithPropulsion" || action == "FlyWithPropeller")
				{
					limit = { make_pair(0.0,0.4), make_pair(0.0,0.5), make_pair(0.3, 0.7) };
				}
				else if (action == "Walk")
				{
					limit = { make_pair(0.6,1.0), make_pair(0.0,0.0), make_pair(0.3, 0.7) };
				}
				else if (action == "Death")
				{
					vector<double> pos = objs[obj].getPos();
					limit = { make_pair(pos[0], pos[0]), make_pair(pos[1], pos[1]), make_pair(pos[2], pos[2]) };
				}
				else if (action == "FlyNoWay")
				{
					vector<double> pos = objs[obj].getPos();
					limit = { make_pair(pos[0], pos[0]), make_pair(0.0, 0.0), make_pair(pos[2], pos[2]) };
				}
				uniform_real_distribution<double> x(limit[0].first, limit[0].second), y(limit[1].first, limit[1].second), z(limit[2].first, limit[2].second);
				vector<double> random = { x(e), y(e), z(e) };
				KeyFrame kf = KeyFrame(2, getClass(obj), obj, timestamp, background, map<string, string>(), objs[obj].getPos(), random, endTime-timestamp, action);
				objs[obj].setPos(random);
				keyFrames.emplace_back(kf);
			}
			else if (action == "Quack" || action == "Squick")
			{
				string content = "";
				KeyFrame kf = KeyFrame(3, action, obj, timestamp, background, map<string, string>(), objs[obj].getPos(), objs[obj].getPos(), endTime - timestamp, content);
				keyFrames.emplace_back(kf);
			}
		}
	}
	
	return keyFrames;
}
void Controller::planning(string fileName)
{
	vector<KeyFrame> keyFrames;
	double totalTime = 0.0, timestramp = 0.0;

	for (auto scene : description)
	{

		string background = scene.first.substr(scene.first.find(":") + 1);
		queue<string> info = scene.second;

		set<string> objsSet;
		while (!info.empty())
		{
			objsSet.insert(info.front().substr(0, info.front().find(".")));
			info.pop();
		}
		for (auto obj : objsSet)
		{
			vector<string> v;
			info = scene.second;
			while (!info.empty())
			{
				v.emplace_back(info.front());
				info.pop();
			}
			for (size_t i = 0; i < v.size(); i++)
			{
				if (v[i].substr(0, v[i].find(".")) == obj)
				{
					v.insert(v.begin() + i, obj + ".Appear");
					break;
				}
			}
			for (size_t i = 0; i < v.size(); i++)
			{
				if (v[i].substr(0, v[i].find(".")) == obj && v[i].substr(v[i].find(".") + 1) == "FlyWithWings")
				{
					for (size_t j = i + 1; j < v.size(); j++)
					{
						if (v[j].substr(0, v[j].find(".")) == obj && (v[j].substr(v[j].find(".") + 1) == "Swim"))
						{
							v.insert(v.begin() + j, obj + ".Land");
							break;
						}
					}
				}
			}
			while (!scene.second.empty()) scene.second.pop();
			for (auto it : v) scene.second.push(it);
		}

		info = scene.second;
		// 计算当前场景总时长
		while (!info.empty())
		{
			string t = info.front();
			info.pop();
			totalTime += exeTime[t.substr(t.find(".") + 1)];
		}

		info = scene.second;
		vector<pair<string, double>> seq;
		while (!info.empty())
		{
			string t = info.front();
			info.pop();
			string obj = t.substr(0, t.find(".")), action = t.substr(t.find(".") + 1);
			if (exeTime.find(action) == exeTime.end()) continue;
			seq.emplace_back(make_pair(t, timestramp));
			timestramp += exeTime[action];
		}
		vector<KeyFrame> keyFrame = produceKeyFrame(seq, totalTime, background);
		for (auto k : keyFrame)
		{
			keyFrames.emplace_back(k);
		}
	}

	writeJson(fileName, keyFrames);
}

void Controller::writeJson(string fileName, vector<KeyFrame> keyFrames)
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
		keyFrame.put("background", kf.background);
		for (auto& it : kf.clothes)
		{
			children.put(it.first, it.second);
		}
		keyFrame.add_child("clothes", children);
		children.clear();
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