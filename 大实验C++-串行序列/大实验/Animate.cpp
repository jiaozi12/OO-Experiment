#include "Animate.h"
#include "Controller.h"

void produceAnimate(string path, map<string, queue<string>> description)
{
    Controller* c = new Controller(description);
    c->planning(path);
    delete c;
}