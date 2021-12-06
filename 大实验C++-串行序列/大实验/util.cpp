#include <vector>
#include <random>
#include "GenerateJson.h"
#include "util.h"

default_random_engine e(time(nullptr));

string getClass(string obj)
{
	// ����obj[0..�״γ������ֵ�λ��)
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
	// ��s�е����д�д��ĸת��ΪСд
	for (auto& it : s)
	{
		if (it >= 'A' && it <= 'Z') it += 32;
	}
	return s;
}