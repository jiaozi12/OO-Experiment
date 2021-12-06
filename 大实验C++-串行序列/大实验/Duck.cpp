#include "Duck.h"
#include "Animate.h"

/* 实现鸭子基类及其派生类的方法 */

/* Duck类 */

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
		// 天气寒冷，鸭子更改状态（这里未设定，故先空着）
	}
	else if (w == "Hot")
	{
		// 天气炎热，鸭子更改状态（这里未设定，故先空着）
	}
	Observer* sub = this;
	return sub;
}

/* MallardDuck类 */
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

/* RedHeadDuck类 */
string RedHeadDuck::performFly() { return getName() + "." + "FlyWithWings"; }
string RedHeadDuck::performQuack() { return getName() + "." + "Quack"; }
string RedHeadDuck::performSwim() { return getName() + "." + "Swim"; }
string RedHeadDuck::performStun() { return getName() + "." + "Stun"; }
string RedHeadDuck::performFailing() { return getName() + "." + "Failing"; }
string RedHeadDuck::performDeath() { return getName() + "." + "Death"; }

/* RubberDuck类 */
string RubberDuck::performFly() { return getName() + "." + "FlyNoWay"; }
string RubberDuck::performQuack() { return getName() + "." + "Squick"; }
string RubberDuck::performSwim() { return getName() + "." + "Float"; }
string RubberDuck::performStun() { return getName() + "." + "Stun"; }
string RubberDuck::performFailing() { return ""; }
string RubberDuck::performDeath() { return getName() + "." + "Death"; }

/* DecoyDuck类 */
string DecoyDuck::performFly() { return getName() + "." + "FlyNoWay"; }
string DecoyDuck::performQuack() { return getName() + "." + "Quack"; }
string DecoyDuck::performSwim() { return ""; }
string DecoyDuck::performStun() { return getName() + "." + "Stun"; }
string DecoyDuck::performFailing() { return ""; }
string DecoyDuck::performDeath() { return getName() + "." + "Death"; }