#include "RoleDraw.h"
#include "util.h"

RoleDraw::RoleDraw(string roleName, vector<double> lastPos)
{
	clothesSupport["Hat"] = vector<string>{ "PeakedCap", "MagicHat" };
	clothesSupport["Jacket"] = vector<string>{ "Shirt", "DownJacket" };
	clothesSupport["Pants"] = vector<string>{ "Trousers", "Shorts" };
	clothesSupport["Shoes"] = vector<string>{ "Sneaker", "Boots" };
	this->roleName = roleName;
	this->roleClass = getClass(roleName);
	this->lastPos = lastPos;
}

string RoleDraw::getClothClass(string cloth)
{
	for (auto& it : clothesSupport)
	{
		if (find(it.second.begin(), it.second.end(), cloth) != it.second.end()) return it.first;
	}

	return "";
}

vector<double> RoleDraw::getLastPos()
{
	return lastPos;
}

vector<KeyFrame> RoleDraw::planning(vector<string> clothes, map<pair<double, double>, vector<string>> actions)
{
	vector<KeyFrame> keyFrames;
	const int type = 3;
	for (int i = clothes.size() - 1; i >= 0; i--)
	{
		string clothClass = getClothClass(clothes[i]);
		if (clothClass != "")
		{
			this->clothes[clothClass] = clothes[i];
		}
	}
	//KeyFrame(int actionIn, int typeIn, string nameIn, string gonameIn, double timestampIn, 
	//map<string, string> clothesIn, vector<double> startposIn, vector<double> endposIn, double durationIn, string contentIn)
	
	for (auto& it : actions)
	{
		for (auto& jt : it.second)
		{
			if (jt == "Appear")
			{
				vector<double> zero = { 0.0,0.0,0.0 };
				lastPos = zero;
				string content = "";
				KeyFrame kf = KeyFrame(0, type, roleClass, roleName, it.first.first, map<string, string>(), zero, zero, it.first.second, content);
				keyFrames.emplace_back(kf);
			}
			else if (jt == "HuntDuck")
			{
				// 播放一段开枪的声音
				string content = "";
				KeyFrame kf = KeyFrame(3, type, "Shoot", roleName, it.first.first, map<string, string>(), lastPos, lastPos, it.first.second, content);
				keyFrames.emplace_back(kf);
			}
			else if (jt == "Walk")
			{
				// 人物角色走路
				string content = jt;
				vector<pair<double, double>> limit = { make_pair(0.6,1.0), make_pair(0.0,0.0), make_pair(0.0, 1.0) };
				uniform_real_distribution<double> x(limit[0].first, limit[0].second), y(limit[1].first, limit[1].second), z(limit[2].first, limit[2].second);

				vector<double> random = { x(e), y(e), z(e) };
				KeyFrame kf = KeyFrame(2, type, roleClass, roleName, it.first.first, map<string, string>(), lastPos, random, it.first.second, content);
				lastPos = random;
				keyFrames.emplace_back(kf);
			}
			else if (jt == "Clothes")
			{
				// 人物穿衣服
				string content = "";
				KeyFrame kf = KeyFrame(7, type, roleClass, roleName, it.first.first, this->clothes, lastPos, lastPos, it.first.second, content);
				keyFrames.emplace_back(kf);
			}
			else;
		}
	}

	return keyFrames;
}