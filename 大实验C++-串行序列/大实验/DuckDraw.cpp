#include <random>
#include "DuckDraw.h"
#include "util.h"

DuckDraw::DuckDraw(string duckName, vector<double> lastPos)
{
	this->duckName = duckName;
	this->duckClass = getClass(duckName);
	this->lastPos = lastPos;
}

vector<double> DuckDraw::getLastPos()
{
	return lastPos;
}

vector<KeyFrame> DuckDraw::planning(map<pair<double, double>, vector<string>> actions)
{
	vector<KeyFrame> keyFrames;
	const int type = 3;

	for (auto& it : actions)
	{
		for (auto& jt : it.second)
		{
			if (jt == "Appear")
			{
				vector<double> zero = { 0.0,0.0,0.0 };
				lastPos = zero;
				string content = "";
				KeyFrame kf = KeyFrame(0, type, duckClass, duckName, it.first.first, map<string, string>(), zero, zero, it.first.second, content);
				keyFrames.emplace_back(kf);
			}
			else if (jt == "FlyWithWings")
			{
				// Ѽ�ӷ��ж���
				string content = jt;
				vector<pair<double, double>> limit = { make_pair(0.0,1.0), make_pair(0.0,1.0), make_pair(0.0, 1.0) };
				uniform_real_distribution<double> x(limit[0].first, limit[0].second), y(limit[1].first, limit[1].second), z(limit[2].first, limit[2].second);

				vector<double> random = { x(e), y(e), z(e) };
				KeyFrame kf = KeyFrame(2, type, duckClass, duckName, it.first.first, map<string, string>(), lastPos, random, it.first.second, content);
				lastPos = random;
				keyFrames.emplace_back(kf);
			}
			else if (jt == "Swim" || jt == "Float")
			{
				// Ѽ����Ӿ����
				string content = jt;
				vector<pair<double, double>> limit = { make_pair(0.0,0.4), make_pair(0.0,0.0), make_pair(0.0, 1.0) };
				uniform_real_distribution<double> x(limit[0].first, limit[0].second), y(limit[1].first, limit[1].second), z(limit[2].first, limit[2].second);

				vector<double> random = { x(e), y(e), z(e) };
				KeyFrame kf = KeyFrame(2, type, duckClass, duckName, it.first.first, map<string, string>(), lastPos, random, it.first.second, content);
				lastPos = random;
				keyFrames.emplace_back(kf);
			}
			else if (jt == "Walk")
			{
				// Ѽ����½�����ߵĶ���
				string content = jt;
				vector<pair<double, double>> limit = { make_pair(0.6,1.0), make_pair(0.0,0.0), make_pair(0.0, 1.0) };
				uniform_real_distribution<double> x(limit[0].first, limit[0].second), y(limit[1].first, limit[1].second), z(limit[2].first, limit[2].second);

				vector<double> random = { x(e), y(e), z(e) };
				KeyFrame kf = KeyFrame(2, type, duckClass, duckName, it.first.first, map<string, string>(), lastPos, random, it.first.second, content);
				lastPos = random;
				keyFrames.emplace_back(kf);
			}
			else if (jt == "Failing")
			{
				// Ѽ���ڿ��б����к���䶯��
				string content = jt;
				vector<double> failPos = { lastPos[0], 0.0, lastPos[2] };
				KeyFrame kf = KeyFrame(2, type, duckClass, duckName, it.first.first, map<string, string>(), lastPos, failPos, it.first.second, content);
				lastPos = failPos;
				keyFrames.emplace_back(kf);
			}
			else if (jt == "Stun" || jt == "Death")
			{
				// Ѽ�ӱ����л�����
				string content = jt;
				KeyFrame kf = KeyFrame(2, type, duckClass, duckName, it.first.first, map<string, string>(), lastPos, lastPos, it.first.second, content);
				keyFrames.emplace_back(kf);
			}
			else if (jt == "Quack" || jt == "Squick")
			{
				string content = "";
				vector<double> zero = { 0.0,0.0,0.0 };
				KeyFrame kf = KeyFrame(3, type, jt, duckName, it.first.first, map<string, string>(), zero, zero, it.first.second, content);
				keyFrames.emplace_back(kf);
			}
			else;
		}
	}

	return keyFrames;
}