package com.company;

import java.util.Vector;

public class PathNode {

    // 存储为角色生成的移动路径中的一个节点
    public Integer action;
    public Double timestamp;
    public Vector<Double> startpos;
    public Vector<Double> endpos;
    public Double duration;

    public PathNode(Integer actionIn, Double timestampIn, Vector<Double> startposIn, Vector<Double> endposIn, Double durationIn) {
        action = actionIn;
        timestamp = timestampIn;
        startpos = startposIn;
        endpos = endposIn;
        duration = durationIn;
    }
}
