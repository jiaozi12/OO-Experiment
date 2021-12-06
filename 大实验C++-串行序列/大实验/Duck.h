#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "SwimBehavior.h"
#include "StunBehavior.h"
#include "Weather.h"

using namespace std;
class Observer;

/* 声明鸭子基类及其派生类 */
class Duck : public Observer
{
private:
	FlyBehavior* flyBehavior = NULL;
	QuackBehavior* quackBehavior = NULL;
	SwimBehavior* swimBehavior = NULL;
	StunBehavior* stunBehavior = NULL;
	bool canSwim = true;
	string name;

public:
	virtual string performFly() = 0;
	virtual string performQuack() = 0;
	virtual string performSwim() = 0;
	virtual string performStun() = 0;
	virtual string performFailing() = 0;
	virtual string performDeath() = 0;
	void setFlyBehavior(FlyBehavior* fb);
	void setQuackBehavior(QuackBehavior* qb);
	void setSwimBehavior(SwimBehavior* sb);
	void setStunBehavior(StunBehavior* sb);
	void setName(string name);
	string getName();
	Observer* update(string w);
	bool getCanSwim();
};

class MallardDuck : public Duck
{
public:
	MallardDuck(string name)
	{
		setFlyBehavior(new FlyWithWings());
		setQuackBehavior(new Quack());
		setSwimBehavior(new Swim());
		setStunBehavior(new Stun());
		setName(name);
	}
	virtual string performFly();
	virtual string performQuack();
	virtual string performSwim();
	virtual string performStun();
	virtual string performFailing();
	virtual string performDeath();
};

class RedHeadDuck : public Duck
{
public:
	RedHeadDuck(string name)
	{
		setFlyBehavior(new FlyWithWings());
		setQuackBehavior(new Quack());
		setSwimBehavior(new Swim());
		setStunBehavior(new Stun());
		setName(name);
	}
	virtual string performFly();
	virtual string performQuack();
	virtual string performSwim();
	virtual string performStun();
	virtual string performFailing();
	virtual string performDeath();
};

class RubberDuck : public Duck
{
public:
	RubberDuck(string name)
	{
		setFlyBehavior(new FlyNoWay());
		setQuackBehavior(new Squick());
		setSwimBehavior(new Float());
		setStunBehavior(new Stun());
		setName(name);
	}
	virtual string performFly();
	virtual string performQuack();
	virtual string performSwim();
	virtual string performStun();
	virtual string performFailing();
	virtual string performDeath();
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck(string name)
	{
		setFlyBehavior(new FlyNoWay());
		setQuackBehavior(new Quack());
		setStunBehavior(new Stun());
		setName(name);
	}
	virtual string performFly();
	virtual string performQuack();
	virtual string performSwim();
	virtual string performStun();
	virtual string performFailing();
	virtual string performDeath();
};