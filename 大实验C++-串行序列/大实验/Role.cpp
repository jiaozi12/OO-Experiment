/*  µœ÷Role.h */
#include <iostream>
#include "Role.h"
#include "RoleDecorator.h"
using namespace std;

vector<string> Role::getDescription()
{
	return vector<string>();
}

string Role::performShoot()
{
	return description + "." + "Shoot";
}

string Role::performWalk()
{
	return description + "." +  "Walk";
}

Observer* Role::update(string w)
{
	Role* newRole = NULL;
	if (w == "Cold")
	{
		size_t idx = 0;
		while (idx < description.length() && !(description[idx] >= '0' && description[idx] <= '9')) idx++;
		string roleType = this->description.substr(0, idx);
		if (roleType == "Hunter") newRole = new Hunter(this->description);
		else if (roleType == "Girl") newRole = new Girl(this->description);
		else if (roleType == "Boy") newRole = new Boy(this->description);
		else;
		if (roleType == "Hunter")
		{
			newRole = new CasualSuit(newRole);
		}
		else if (roleType == "Boy" || roleType == "Girl")
		{
			newRole = new DownJacket(newRole);
			newRole = new Jeans(newRole);
			newRole = new LongHair(newRole);
			newRole = new Boots(newRole);
		}
	}
	else if (w == "Hot")
	{
		size_t idx = 0;
		while (idx < description.length() && !(description[idx] >= '0' && description[idx] <= '9')) idx++;
		string roleType = this->description.substr(0, idx);
		if (roleType == "Hunter") newRole = new Hunter(this->description);
		else if (roleType == "Girl") newRole = new Girl(this->description);
		else if (roleType == "Boy") newRole = new Boy(this->description);
		else;
		if (roleType == "Hunter")
		{
			newRole = new HuntingSuit(newRole);
		}
		else if (roleType == "Boy" || roleType == "Girl")
		{
			newRole = new Shirt(newRole);
			newRole = new CasualPants(newRole);
			newRole = new ShortHair(newRole);
			newRole = new Sneaker(newRole);
		}
	}
	else
	{
		newRole = new Shirt(newRole);
		newRole = new CasualPants(newRole);
		newRole = new ShortHair(newRole);
		newRole = new Sneaker(newRole);
	}
	Observer* sub = newRole;
	return sub;
}