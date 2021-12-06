#include "PlaneFactory.h"

/*  µœ÷PlaneFactory.h */

PlaneProduct* SimplePlaneFactory::produce(string arg, string name)
{
	PlaneProduct* plane = NULL;
	if (arg == "AirForceOne") plane = new AirForceOne(name);
	else if (arg == "AirBus") plane = new AirBus(name);
	else;
	
	return plane;
}

PlaneProduct* BoeingFactory::produce(string name)
{
	return new Boeing(name);
}

PlaneProduct* ApacheFactory::produce(string name)
{
	return new Apache(name);
}