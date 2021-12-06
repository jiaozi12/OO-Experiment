#include <vector>
#include <random>
#include "GenerateJson.h"
#include "util.h"

default_random_engine e(time(nullptr));

string getClass(string obj)
{
	// 返回obj[0..首次出现数字的位置)
	int idx = 0;
	while (idx < obj.length())
	{
		if ((obj[idx] >= '0' && obj[idx] <= '9') || obj[idx] == '_') break;
		idx++;
	}

	return obj.substr(0, idx);
}

string lower(string s)
{
	// 把s中的所有大写字母转化为小写
	for (auto& it : s)
	{
		if (it >= 'A' && it <= 'Z') it += 32;
	}
	return s;
}