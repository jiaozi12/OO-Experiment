#pragma once
#include <string>
#include "Plane.h"
using namespace std;

class PlaneProduct; // ���ǰ��˵������û��ǰ��˵���������뱨����PlaneProduct��PlaneFactory���棬��PlaneFactoryʹ����PlaneProduct��

class SimplePlaneFactory
{
public:
	// ʹ�ü򵥹�������AirForceOne��AirBus�������͵�ɽկ�ɻ�
	PlaneProduct* produce(string arg, string name);
};

class PlaneFactory
{
public:
	// ʹ�ù���ģʽ����Boeing��Apache�ɻ�
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