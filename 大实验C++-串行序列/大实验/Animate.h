#pragma once
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>
#include "GenerateJson.h"
using namespace std;

// 将队列q中的信息解析成JSON文件
void produceAnimate(string path, map<string, queue<string>> description);