#include "Duck.h"
#include "Animate.h"

/* ʵ��Ѽ�ӻ��༰��������ķ��� */

/* Duck�� */

void Duck::setFlyBehavior(FlyBehavior* fb) { flyBehavior = fb; }
void Duck::setQuackBehavior(QuackBehavior* qb) { quackBehavior = qb; }
void Duck::setSwimBehavior(SwimBehavior* sb) { swimBehavior = sb; }
void Duck::setStunBehavior(StunBehavior* sb) { stunBehavior = sb; }
void Duck::setName(string name) { this->name = name; }
string Duck::getName() { return name; }
bool Duck::getCanSwim() { return canSwim; }

Observer* Duck::update(string w)
{
	Duck* newRole = NULL;
	if (w == "Cold")
	{
		// �������䣬Ѽ�Ӹ���״̬������δ�趨�����ȿ��ţ�
	}
	else if (w == "Hot")
	{
		// �������ȣ�Ѽ�Ӹ���״̬������δ�趨�����ȿ��ţ�
	}
	Observer* sub = this;
	return sub;
}

/* MallardDuck�� */
string MallardDuck::performFly() { return getName() + "." + "FlyWithWings"; }
string MallardDuck::performQuack() { return getName() + "." + "Quack"; }
string MallardDuck::performSwim() 
{ 
	if (getCanSwim()) return getName() + "." + "Swim";
	else return getName() + "." + "Walk";
}
string MallardDuck::performStun() { return getName() + "." + "Stun"; }
string MallardDuck::performFailing() { return getName() + "." + "Failing"; }
string MallardDuck::performDeath() { return getName() + "." + "Death"; }

/* RedHeadDuck�� */
string RedHeadDuck::performFly() { return getName() + "." + "FlyWithWings"; }
string RedHeadDuck::performQuack() { return getName() + "." + "Quack"; }
string RedHeadDuck::performSwim() { return getName() + "." + "Swim"; }
string RedHeadDuck::performStun() { return getName() + "." + "Stun"; }
string RedHeadDuck::performFailing() { return getName() + "." + "Failing"; }
string RedHeadDuck::performDeath() { return getName() + "." + "Death"; }

/* RubberDuck�� */
string RubberDuck::performFly() { return getName() + "." + "FlyNoWay"; }
string RubberDuck::performQuack() { return getName() + "." + "Squick"; }
string RubberDuck::performSwim() { return getName() + "." + "Float"; }
string RubberDuck::performStun() { return getName() + "." + "Stun"; }
string RubberDuck::performFailing() { return ""; }
string RubberDuck::performDeath() { return getName() + "." + "Death"; }

/* DecoyDuck�� */
string DecoyDuck::performFly() { return getName() + "." + "FlyNoWay"; }
string DecoyDuck::performQuack() { return getName() + "." + "Quack"; }
string DecoyDuck::performSwim() { return ""; }
string DecoyDuck::performStun() { return getName() + "." + "Stun"; }
string DecoyDuck::performFailing() { return ""; }
string DecoyDuck::performDeath() { return getName() + "." + "Death"; }