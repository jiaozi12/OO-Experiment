package com.company;

import java.io.IOException;
import java.util.Vector;

public class Main {

    public static void main(String[] args) throws IOException {
        String[] v = new String[]{
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

        Animate ani = new Animate();
        for (String it : v) {
            ani.push(it);
        }
        ani.animate("DuckHunting.json");
    }
}
