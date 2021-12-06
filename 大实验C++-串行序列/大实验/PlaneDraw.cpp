#include "PlaneDraw.h"
#include "util.h"
#include <random>

PlaneDraw::PlaneDraw(string planeName, vector<double> lastPos)
{
	this->planeName = planeName;
	this->planeClass = getClass(planeName);
	this->lastPos = lastPos;
}

vector<double> PlaneDraw::getLastPos()
{
	return lastPos;
}

vector<KeyFrame> PlaneDraw::planning(map<pair<double, double>, vector<string>> actions)
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
				KeyFrame kf = KeyFrame(0, type, planeClass, planeName, it.first.first, map<string, string>(), zero, zero, it.first.second, content);
				keyFrames.emplace_back(kf);
			}
			else if (jt == "FlyWithPropulsion" || jt == "FlyWithPropeller")
			{
				// ·É»ú·ÉÐÐ¶¯»­
				string content = jt;
				vector<pair<double, double>> limit = { make_pair(0.0,1.0), make_pair(0.0,1.0), make_pair(0.0, 1.0) };
				uniform_real_distribution<double> x(limit[0].first, limit[0].second), y(limit[1].first, limit[1].second), z(limit[2].first, limit[2].second);

				vector<double> random = { x(e), y(e), z(e) };
				KeyFrame kf = KeyFrame(2, type, planeClass, planeName, it.first.first, map<string, string>(), lastPos, random, it.first.second, content);
				lastPos = random;
				keyFrames.emplace_back(kf);
			}
			else;
		}
	}

	return keyFrames;
}