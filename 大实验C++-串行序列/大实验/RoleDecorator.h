#pragma once
#include "Role.h"

/* �����ɫװ���༰�����ࣨ�����·��ࣩ */

// ��ɫװ���߳�����
class RoleDecorato : public Role
{

};

// ����
class Shirt : public RoleDecorato
{
private:
	// ��һ��ʵ����¼��ɫ��Ҳ���Ǳ�װ����
	Role* role;

public:
	Shirt(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// ���޷�
class DownJacket : public RoleDecorato
{
public:
	Role* role;

public:
	DownJacket(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// ţ�п�
class Jeans : public RoleDecorato
{
public:
	Role* role;

public:
	Jeans(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// ���п�
class CasualPants : public RoleDecorato
{
public:
	Role* role;

public:
	CasualPants(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// �̷�
class ShortHair : public RoleDecorato
{
public:
	Role* role;

public:
	ShortHair(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// ����
class LongHair : public RoleDecorato
{
public:
	Role* role;

public:
	LongHair(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// �˶�Ь
class Sneaker : public RoleDecorato
{
public:
	Role* role;

public:
	Sneaker(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// ѥ��
class Boots : public RoleDecorato
{
public:
	Role* role;

public:
	Boots(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// ����װ
class HuntingSuit : public RoleDecorato
{
public:
	Role* role;

public:
	HuntingSuit(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};

// ����װ
class CasualSuit : public RoleDecorato
{
public:
	Role* role;

public:
	CasualSuit(Role* role) { this->role = role; this->description = role->description; }
	vector<string> getDescription();
};