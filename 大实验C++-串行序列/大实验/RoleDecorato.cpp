/*  µœ÷RoleDecorato.h */
#include "RoleDecorator.h"

vector<string> Shirt::getDescription()
{
	vector<string> rd = role->getDescription();
	rd.push_back(description  + "." + "Shirt");
	return rd;
}

vector<string> DownJacket::getDescription()
{
	vector<string> rd = role->getDescription();
	rd.push_back(description + "." +  "DownJacket");
	return rd;
}

vector<string> Jeans::getDescription()
{
	vector<string> rd = role->getDescription();
	rd.push_back(description + "." +  "Jeans");
	return rd;
}

vector<string> CasualPants::getDescription()
{
	vector<string> rd = role->getDescription();
	rd.push_back(description + "." +  "CasualPants");
	return rd;
}

vector<string> ShortHair::getDescription()
{
	vector<string> rd = role->getDescription();
	rd.push_back(description + "." +  "ShortHair");
	return rd;
}

vector<string> LongHair::getDescription()
{
	vector<string> rd = role->getDescription();
	rd.push_back(description + "." +  "LongHair");
	return rd;
}

vector<string> Sneaker::getDescription()
{
	vector<string> rd = role->getDescription();
	rd.push_back(description + "." +  "Sneaker");
	return rd;
}

vector<string> Boots::getDescription()
{
	vector<string> rd = role->getDescription();
	rd.push_back(description + "." +  "Boots");
	return rd;
}

vector<string> HuntingSuit::getDescription()
{
	vector<string> rd = role->getDescription();
	rd.push_back(description + "." + "HuntingSuit");
	return rd;
}

vector<string> CasualSuit::getDescription()
{
	vector<string> rd = role->getDescription();
	rd.push_back(description + "." + "CasualSuit");
	return rd;
}