#pragma once
#include <string>
#include <vector>
#include "FlyBehavior.h"
#include "PlaneFactory.h"
using namespace std;

/* 声明飞机基类及其派生类 */
class PlaneProduct
{
private:
	FlyBehavior* flyBehavior = NULL;
	string name;

public:
	virtual string performFly() = 0;
	string performStun();
	string performFailing();
	string performDeath();
	void setFlyBehavior(FlyBehavior* fb);
	FlyBehavior* getFlyBehavior();
	string getName();
	void setName(string name);
};

class AirForceOne : public PlaneProduct
{
public:
	AirForceOne(string name)
	{
		setFlyBehavior(new FlyWithPropulsion());
		this->setName(name);
	}
	virtual string performFly();
};

class AirBus : public PlaneProduct
{
public:
	AirBus(string name)
	{
		setFlyBehavior(new FlyWithPropulsion());
		this->setName(name);
	}
	virtual string performFly();
};

class Boeing : public PlaneProduct
{
public:
	Boeing(string name)
	{
		setFlyBehavior(new FlyWithPropulsion());
		this->setName(name);
	}
	virtual string performFly();
};

class Apache : public PlaneProduct
{
public:
	Apache(string name)
	{
		setFlyBehavior(new FlyWithPropeller());
		this->setName(name);
	}
	virtual string performFly();
};