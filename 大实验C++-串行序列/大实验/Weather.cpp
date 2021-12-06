#include <iostream>
#include "Weather.h"
using namespace std;

void Weather::subscribe(Observer**sub)
{
	this->subs.push_back(sub);
}
void Weather::unSubscribe(Observer** sub)
{
	for (int i = 0; i < this->subs.size(); i++)
	{
		if (this->subs[i] == sub)
		{
			this->subs.erase(this->subs.begin() + i);
			i--;
		}
	}
}
void Weather::notify()
{
	for (int i=0;i<this->subs.size();i++)
	{
		*(this->subs[i]) = (*(this->subs[i]))->update(this->curWea);
	}
}
string Weather::turnCold()
{
	this->curWea = "Cold";
	this->notify();
	
	return "Cold";
}
string Weather::turnHot()
{
	this->curWea = "Hot";
	this->notify();

	return "Hot";
}