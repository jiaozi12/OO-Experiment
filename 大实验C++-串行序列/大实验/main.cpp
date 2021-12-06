// 大实验.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Role.h"
#include "Duck.h"
#include "RoleDecorator.h"
#include "Animate.h"
#include "Plane.h"
#include "PlaneFactory.h"

void test0();
void test1();

int main()
{
    // 定义场景1所需要的对象
    Role* Hunter0 = new Hunter("Hunter0");  // 猎人
    Duck* MallardDuck0 = new MallardDuck("MallardDuck0");
    Duck* RedHeadDuck0 = new RedHeadDuck("RedHeadDuck0");
    Duck* RubberDuck0 = new RubberDuck("RubberDuck0");

    // 定义场景2所需要的对象
    Role* Boy0 = new Boy("Boy0");
    Role* Girl0 = new Girl("Girl0");
    PlaneFactory* bf = new BoeingFactory, * af = new ApacheFactory;  // 定义一个工厂，生产一架Boeing正版飞机，生产一架Apache正版飞机
    PlaneProduct* Boeing0 = bf->produce("Boeing0");
    PlaneProduct* Apache0 = af->produce("Apache0");

    // 定义场景3所需要的对象
    Duck* MallardDuck1 = new MallardDuck("MallardDuck1");
    PlaneProduct* Apache1 = af->produce("Apache1");
    SimplePlaneFactory* spf = new SimplePlaneFactory;  // 定义一个简单工厂，生产一架AirForceOne，一架AirBus
    PlaneProduct* AirForceOne0 = spf->produce("AirForceOne", "AirForceOne0");
    Role* Hunter1 = new Hunter("Hunter1");  // 猎人

    // 定义一个天气对象，并将所有鸭子和人物角色对象加入到天气的订阅列表中
    Weather* weather = new Weather;
    weather->subscribe((Observer**)&Hunter0);
    weather->subscribe((Observer**)&Boy0);
    weather->subscribe((Observer**)&Girl0);
    weather->subscribe((Observer**)&Hunter1);

    map<string, queue<string>> description;
    queue<string> scene1, scene2, scene3;

    // Scene1
    string curWeather = weather->turnHot();
    vector<string> v = Hunter0->getDescription();
    for (auto it : v) scene1.push(it);
    scene1.push(Hunter0->performWalk());
    scene1.push(MallardDuck0->performSwim());
    scene1.push(RedHeadDuck0->performSwim());
    scene1.push(RubberDuck0->performSwim());
    scene1.push(MallardDuck0->performFly());
    scene1.push(Hunter0->performShoot());
    scene1.push(MallardDuck0->performStun());
    scene1.push(MallardDuck0->performFailing());
    scene1.push(MallardDuck0->performDeath());
    description["Scene1:" + curWeather] = scene1;

    // Scene2
    curWeather = weather->turnCold();
    v = Boy0->getDescription();
    for (auto it : v) scene2.push(it);
    scene2.push(Boy0->performWalk());
    v = Girl0->getDescription();
    for (auto it : v) scene2.push(it);
    scene2.push(Girl0->performWalk());
    scene2.push(Boeing0->performFly());
    scene2.push(Apache0->performFly());
    description["Scene2:" + curWeather] = scene2;

    // Scene3
    curWeather = weather->turnCold();
    scene3.push(MallardDuck1->performSwim());
    scene3.push(MallardDuck1->performFly());
    scene3.push(Apache1->performFly());
    scene3.push(AirForceOne0->performFly());
    v = Hunter1->getDescription();
    for (auto it : v) scene3.push(it);
    scene3.push(Hunter1->performShoot());
    scene3.push(Apache1->performStun());
    scene3.push(Apache1->performFailing());
    scene3.push(Apache1->performDeath());
    description["Scene3:" + curWeather] = scene3;

    for (auto it : description)
    {
        cout << it.first << endl;
        queue<string> q = it.second;
        while (!q.empty())
        {
            cout << q.front() << endl;
            q.pop();
        }
    }
    produceAnimate("Experiment.json", description);
    //test0();
    //test1();
}

void test0()
{
    map<string, queue<string>> description;
    queue<string> scene1;

    Duck* MallardDuck0 = new MallardDuck("MallardDuck0");
    scene1.push("MallardDuck0.Appear");
    scene1.push(MallardDuck0->performQuack()); // Quack
    scene1.push(MallardDuck0->performFly());   // FlyWithWings
    scene1.push(MallardDuck0->performSwim());  // Swim

    Duck* RubberDuck0 = new RubberDuck("RubberDuck0");
    scene1.push("RubberDuck0.Appear");
    scene1.push(RubberDuck0->performQuack());  // Squick
    scene1.push(RubberDuck0->performSwim());   // Float
    scene1.push(RubberDuck0->performFly());    // FlyNoWay

    description["Scene1:Hot"] = scene1;
    produceAnimate("DuckHunting0.json", description);
}

void test1()
{
    map<string, queue<string>> description;
    queue<string> scene1;

    Duck* MallardDuck0 = new MallardDuck("MallardDuck0");
    scene1.push("MallardDuck0.Appear");
    scene1.push(MallardDuck0->performFly());    // FlyWithWings
    scene1.push(MallardDuck0->performSwim());   // Swim

    PlaneProduct* Boeing0 = new Boeing("Boeing0");
    scene1.push("Boeing0.Appear");
    scene1.push(Boeing0->performFly());         // FlyWithPropulsion

    PlaneProduct* Apache0 = new Apache("Apache0");
    scene1.push("Apache0.Appear");
    scene1.push(Apache0->performFly());         // FlyWithPropeller

    description["Scene1:Hot"] = scene1;
    produceAnimate("DuckHunting1.json", description);
}