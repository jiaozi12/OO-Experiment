#pragma once
#include <string>
#include "Plane.h"
using namespace std;

class PlaneProduct; // 类的前置说明，若没有前置说明，则会编译报错（类PlaneProduct在PlaneFactory后面，但PlaneFactory使用了PlaneProduct）

class SimplePlaneFactory
{
public:
	// 使用简单工厂生成AirForceOne、AirBus两种类型的山寨飞机
	PlaneProduct* produce(string arg, string name);
};

class PlaneFactory
{
public:
	// 使用工厂模式生成Boeing和Apache飞机
	virtual PlaneProduct* produce(string name) = 0;
};

class BoeingFactory : public PlaneFactory
{
public:
	PlaneProduct* produce(string name);
};

class ApacheFactory : public PlaneFactory
{
public:
	PlaneProduct* produce(string name);
};