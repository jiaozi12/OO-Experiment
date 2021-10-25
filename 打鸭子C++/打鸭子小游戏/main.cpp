// 打鸭子小游戏.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <unordered_map>
#include "Animate.h"
#include "GenerateJson.h"

int main()
{
    vector<string> v = { 
        "MallardDuck_0, FlyWithWings,, Swim", 
        "RedHeadDuck_0, FlyWithWings",
        "RedHeadDuck_1,Swim,Stun,Quack", 
        "RubberDuck_0,Float,Squick", 
        "DecoyDuck_0,Quack",
        "AirForceOne_0,FlyWithPropulsion", 
        "AirBus_0,FlyWithPropulsion" , 
        "Boeing_0,FlyWithPropulsion",
        "Apache_0,FlyWithPropeller" 
    };

    for (auto it : v)
    {
        push(it);
    }
    animate("DuckHunting.json");
}
