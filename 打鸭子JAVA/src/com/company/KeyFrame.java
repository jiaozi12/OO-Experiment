package com.company;

import java.util.Vector;

public class KeyFrame {

    // 对应生成的JSON文件中keyFrames数组的一个元素（一个keyFrame）
    public Integer action;
    public Integer type;
    public String name;
    public String goname;
    public Double timestamp;
    public Vector<Double> startpos;
    public Vector<Double> endpos;
    public Vector<Double> startrotation;
    public Vector<Double> endrotation;
    public Vector<Double> startscale;
    public Vector<Double> endscale;
    public Double duration;
    public String content;
    public Integer loop;

    public KeyFrame(Integer actionIn, Integer typeIn, String nameIn, String goNameIn, Double timestampIn, Vector<Double> startPosIn, Vector<Double> endPosIn, Double durationIn, String contentIn) {
        action = actionIn;
        type = typeIn;
        name = nameIn;
        goname = goNameIn;
        timestamp = timestampIn;
        startpos = startPosIn;
        endpos = endPosIn;
        startrotation = new Vector<Double>() {{add(0.0);add(0.0);add(0.0);}};
        endrotation = new Vector<Double>() {{add(0.0);add(0.0);add(0.0);}};
        startscale = new Vector<Double>() {{add(1.0);add(1.0);add(1.0);}};
        endscale = new Vector<Double>() {{add(1.0);add(1.0);add(1.0);}};
        duration = durationIn;
        content = contentIn;
        loop = 0;
    }
}
