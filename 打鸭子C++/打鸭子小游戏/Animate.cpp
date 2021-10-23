#include "Animate.h"

unordered_map<string, vector<string>> co;
unordered_map<string, vector<string>> op;
unordered_set<string> legalName{ "MallardDuck", "RedHeadDuck", "RubberDuck", "DecoyDuck", "AirForceOne", "AirBus", \
"Boeing", "Apache", "FlyWithWings", "Swim", "Quack", "Stun", "Squick", "FlyWithPropulsion", "FlyWithPropeller" };

string preDeal(string s)
{
    // 删除s中的非数字、下划线、大小写字母、英文逗号字符
    size_t i = 0;
    while (i < s.length())
    {
        if (!(s[i] >= '0' && s[i] <= '9' || s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z' || s[i] == ',' || s[i] == '_'))
        {
            s.erase(i, 1);
        }
        else i++;
    }

    // 删除s中连续多个逗号或连续多个下划线情况下的多余逗号
    i = 0;
    while (i < s.length() - 1)
    {
        if (s[i] == ',' && s[i + 1] == ',' || s[i] == '_' && s[i + 1] == '_')
        {
            s.erase(i + 1, 1);
        }
        else i++;
    }

    return s;
}

vector<string> split(string s)
{
    vector<string> v;
    size_t left = 0;
    s += ",";
    for (size_t i = 1; i < s.length(); i++)
    {
        if (s[i] == ',')
        {
            v.push_back(s.substr(left, i - left));
            left = i + 1;
        }
    }

    return v;
}

void push(string s)
{
    s = preDeal(s);
    vector<string> v = split(s);
    string cla = v[0].substr(0, v[0].find("_")), objName = v[0].erase(v[0].find('_'), 1);
    if (legalName.count(cla) == 0)
    {
        cerr << "Input objName error: " << cla << endl;
        return;
    }
    if (co.find(cla) == co.end()) co[cla] = vector<string>();
    co[cla].push_back(objName);
    if (op.find(objName) == op.end()) op[objName] = vector<string>();
    for (size_t i = 1; i < v.size(); i++)
    {
        if (legalName.count(v[i]) == 0)
        {
            cerr << "Input behavior error: " << v[i] << endl;
            return;
        }
        if (v[i] == "Quack" || v[i] == "Squick") op[objName].insert(op[objName].begin(), v[i]);
        else op[objName].push_back(v[i]);
    }
}

void animate(string path)
{
    GenJsonFromObj* g = new GenJsonFromObj();
    vector<KeyFrame> keyFrames = g->GenKeyFrames(op);
    g->WriteKeyFrames(path, keyFrames);
}