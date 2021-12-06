#include "Plane.h"
#include "Animate.h"

void PlaneProduct::setFlyBehavior(FlyBehavior* fb)
{
	flyBehavior = fb;
}
FlyBehavior* PlaneProduct::getFlyBehavior()
{
	return flyBehavior;
}
string PlaneProduct::getName()
{
	return name;
}
void PlaneProduct::setName(string name)
{
	this->name = name;
}
string PlaneProduct::performStun()
{
	return name + "." + "Stun";
}
string PlaneProduct::performFailing()
{
	return name + "." + "Failing";
}
string PlaneProduct::performDeath()
{
	return name + "." + "Death";
}

string AirForceOne::performFly()
{
	return this->getName() + "." +  "FlyWithPropulsion";
}

string AirBus::performFly()
{
	return this->getName() + "." + "FlyWithPropulsion";
}

string Boeing::performFly()
{
	return this->getName() + "." + "FlyWithPropulsion";
}

string Apache::performFly()
{
	return this->getName() + "." + "FlyWithPropeller";
}