#pragma once
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>
#include "GenerateJson.h"
using namespace std;

// ������q�е���Ϣ������JSON�ļ�
void produceAnimate(string path, map<string, queue<string>> description);