#pragma once
#include "Role.h"

/* 定义角色装饰类及其子类（各种衣服类） */

// 角色装饰者抽象类
class RoleDecorato : public Role
{

};

// 衬衫
class Shirt : public RoleDecorato
{
private:
	// 用一个实例记录角色，也就是被装饰者
	Role* role;

public:
	Shirt(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// 羽绒服
class DownJacket : public RoleDecorato
{
public:
	Role* role;

public:
	DownJacket(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// 牛仔裤
class Jeans : public RoleDecorato
{
public:
	Role* role;

public:
	Jeans(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// 休闲裤
class CasualPants : public RoleDecorato
{
public:
	Role* role;

public:
	CasualPants(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// 短发
class ShortHair : public RoleDecorato
{
public:
	Role* role;

public:
	ShortHair(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// 长发
class LongHair : public RoleDecorato
{
public:
	Role* role;

public:
	LongHair(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// 运动鞋
class Sneaker : public RoleDecorato
{
public:
	Role* role;

public:
	Sneaker(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// 靴子
class Boots : public RoleDecorato
{
public:
	Role* role;

public:
	Boots(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// 打猎装
class HuntingSuit : public RoleDecorato
{
public:
	Role* role;

public:
	HuntingSuit(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// 休闲装
class CasualSuit : public RoleDecorato
{
public:
	Role* role;

public:
	CasualSuit(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};