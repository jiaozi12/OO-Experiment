package com.company;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import java.io.*;
import java.util.HashMap;
import java.util.Random;
import java.util.Vector;

import static java.lang.Math.min;

/* 定义打鸭子小游戏生成Json文件类 */
public class GenJsonFromObj {

    // 从本科生输入的对象中解析信息，生成对应的Json文件

    // 返回obj[0..首次出现数字的位置)
    private String getClass(String obj) {
        int idx = 0;
        while (idx < obj.length()) {
            if(obj.charAt(idx) >= '0' && obj.charAt(idx) <= '9') break;
            idx++;
        }
        return obj.substring(0, idx);
    }

    // 生成一条随机移动路径
    private Vector<PathNode> GenPath(Vector<Double> startPos, Vector<Double> timestamp, Vector<Vector<Double>> limit, Integer mode) {
        // startPos为起始坐标
        // timestamp存储若干个时间戳，生成对应时间戳的startPos和endPos
        // limit为限制区间，分别限制了生成的坐标点x,y,z的取值范围
        // mode为0时，生成的路径包含开始节点（角色出现时刻）；mode为1时，生成路径不包含开始节点

        Vector<PathNode> path = new Vector<PathNode>();
        Vector<Double> last = new Vector<Double>(startPos);
        if(mode.equals(0)) path.add(new PathNode(0,0.0, new Vector<Double>(last), new Vector<Double>(last),0.0));  // 开始节点
        timestamp.add(timestamp.get(timestamp.size()-1) * 2 -  timestamp.get(timestamp.size()-2));
        Random seed = new Random();
        for(int i=0;i<timestamp.size()-1;i++) {
            Vector<Double> r = new Vector<Double>();
            for(int j=0;j<limit.size();j++) {
                r.add(limit.get(j).get(0) + ((limit.get(j).get(1) - limit.get(j).get(0)) * seed.nextDouble()));
            }
            path.add(new PathNode(2, timestamp.get(i), new Vector<Double>(last), r, timestamp.get(i+1)-timestamp.get(i)));
            last.clear();
            last.addAll(r);
        }

        return path;
    }

    // 从本科生输入的一项基本素材动作信息中构造一个keyFrame序列
    public Vector<KeyFrame> GenKeyFrames(HashMap<String, Vector<String>> op) {
        // op存储角色和其具有的behavior，如op["RedHeadDuck"] = ["FlyWithWings"]表示RedHeadDuck具有FlyWithWings的表现
        // 返回一个KeyFrame，是为该id对象生成的从0时刻到结束时刻的KeyFrame，用于生成json文件给unity解析显示
        Integer type = 3;
        Double totalTime = 30.0;
        Vector<KeyFrame> keyFrames = new Vector<KeyFrame>();

        // 为所有角色生成移动路径
        for(String it : op.keySet()) {
            int cnt = 0;
            for(String jt : op.get(it)) {
                if(!jt.toLowerCase().equals("quack") && !jt.toLowerCase().equals("squick")) cnt++;
            }
            Double time = 0.0, dur = totalTime / cnt, startTime = 0.0, endTime = 0.0;
            Vector<Double> startPos = new Vector<Double>();
            for(int i=0;i<3;i++) startPos.add(0.0);

            // 检查是否有"stun"；如果有，则先删除"stun"后的所有动作，然后在"stun"后添加"death"动作
            int idx = -1;
            for(int i=0;i<op.get(it).size();i++) {
                if(op.get(it).get(i).toLowerCase().equals("stun")) {
                    idx = i + 1;
                    break;
                }
            }
            if(idx != -1) {
                for(int i=op.get(it).size()-1;i>=idx;i--) {
                    op.get(it).remove(op.get(it).size()-1);
                }
                op.get(it).add("Death");
            }

            for(String jt : op.get(it)) {
                String be = jt.toLowerCase();
                Vector<PathNode> path = new Vector<PathNode>();

                // 每一个if对应一种动画/声音表现
                if(be.equals("flywithwings") || be.equals("flywithpropulsion") || be.equals("flywithpropeller")) {
                    Vector<Double> timestamp = new Vector<Double>();
                    startTime = endTime;
                    endTime += dur;
                    for(Double t = startTime; t < endTime; t += dur/4) timestamp.add(t);
                    Integer mode = 1;
                    if(op.get(it).get(0).equals(jt)) mode = 0;
                    Vector<Vector<Double>> limit = new Vector<Vector<Double>>();
                    for(int i=0;i<3;i++) {
                        Vector<Double> tmp = new Vector<Double>();
                        tmp.add(0.0);
                        tmp.add(1.0);
                        limit.add(tmp);
                    }
                    path = GenPath(startPos, timestamp, limit, mode);
                    startPos.clear();
                    startPos.addAll(path.lastElement().endpos);
                }
                else if(be.equals("flynoway") || be.equals("mutequack")) continue;
                else if(be.equals("swim")) {
                    Vector<Double> timestamp = new Vector<Double>();
                    startTime = endTime;
                    endTime += dur;
                    for(Double t = startTime; t < endTime; t += dur/4) timestamp.add(t);
                    Integer mode = 1;
                    if(op.get(it).get(0).equals(jt)) mode = 0;
                    Vector<Vector<Double>> limit = new Vector<Vector<Double>>();
                    Vector<Double> tmp = new Vector<Double>();
                    tmp.add(0.0); tmp.add(0.5); limit.add(new Vector<Double>(tmp)); tmp.clear();
                    tmp.add(0.0); tmp.add(0.0); limit.add(new Vector<Double>(tmp)); tmp.clear();
                    tmp.add(0.0); tmp.add(1.0); limit.add(new Vector<Double>(tmp));
                    path = GenPath(startPos, timestamp, limit, mode);
                    startPos.clear();
                    startPos.addAll(path.lastElement().endpos);
                }
                else if(be.equals("quack") || be.equals("squick")) {
                    Double st = 0.0, et = 0.0;
                    Vector<Double> zero = new Vector<Double>() {{add(0.0); add(0.0); add(0.0);}};
                    for(String kt : op.get(it)) {
                        String be2 = kt.toLowerCase();
                        if(be2.equals("stun")) et += 2;
                        else if(be2.equals("death")) break;
                        else et += dur;
                    }
                    KeyFrame kf1 = new KeyFrame(0, type, getClass(it), it, st, zero, zero, 0.0, "");
                    KeyFrame kf2 = new KeyFrame(3, type, jt, it, st, zero, zero, min(et, totalTime), "");
                    keyFrames.add(kf1);
                    keyFrames.add(kf2);
                }
                else if(be.equals("stun")) {
                    // stun动画只播放2s
                    startTime = endTime;
                    endTime += 2;
                    KeyFrame kf = new KeyFrame(2, type, getClass(it), it, startTime, startPos, startPos, 2.0, "Stun");
                    keyFrames.add(kf);
                }
                else if(be.equals("death")) {
                    // 一旦播放death，就一直播放，直到整个动画结束
                    startTime = endTime;
                    endTime = totalTime;
                    KeyFrame kf = new KeyFrame(2, type, getClass(it), it, startTime, startPos, startPos, endTime-startTime, "Death");
                    keyFrames.add(kf);
                    break;
                }

                for(PathNode p : path) {
                    String content = "";
                    if(p.action.equals(0)) content = "";
                    else if(p.action.equals(2)) content = jt;
                    KeyFrame kf = new KeyFrame(p.action, type, getClass(it), it, p.timestamp, p.startpos, p.endpos, p.duration, content);
                    keyFrames.add(kf);
                }
            }
        }
        return keyFrames;
    }

    // 将生成的一个keyFrame序列写入JSON文件
    void WriteKeyFrames(String fileName, Vector<KeyFrame> keyFrames) throws IOException {
        OutputStreamWriter osw = new OutputStreamWriter(new FileOutputStream(fileName),"UTF-8");
        JSONObject root = new JSONObject(true);
        JSONArray arr = new JSONArray();
        for(KeyFrame kf : keyFrames) {
            JSONObject keyFrame = new JSONObject(true);
            keyFrame.put("action", kf.action.toString());
            keyFrame.put("type", kf.type.toString());
            keyFrame.put("name", kf.name);
            keyFrame.put("goname", kf.goname);
            keyFrame.put("timestamp", kf.timestamp.toString());
            JSONArray jsonArray = new JSONArray();
            for(Double it : kf.startpos) {
                jsonArray.add(it.toString());
            }
            keyFrame.put("startpos", jsonArray);
            jsonArray = new JSONArray();
            for(Double it : kf.endpos) {
                jsonArray.add(it.toString());
            }
            keyFrame.put("endpos", jsonArray);
            jsonArray = new JSONArray();
            for(Double it : kf.startrotation) {
                jsonArray.add(it.toString());
            }
            keyFrame.put("startrotation", jsonArray);
            jsonArray = new JSONArray();
            for(Double it : kf.endrotation) {
                jsonArray.add(it.toString());
            }
            keyFrame.put("endrotation", jsonArray);
            jsonArray = new JSONArray();
            for(Double it : kf.startscale) {
                jsonArray.add(it.toString());
            }
            keyFrame.put("startscale", jsonArray);
            jsonArray = new JSONArray();
            for(Double it : kf.endscale) {
                jsonArray.add(it.toString());
            }
            keyFrame.put("endscale", jsonArray);
            jsonArray = new JSONArray();
            keyFrame.put("duration", kf.duration.toString());
            keyFrame.put("content", kf.content);
            keyFrame.put("loop", kf.loop.toString());

            arr.add(keyFrame);
        }
        root.put("keyFrames", arr);
        osw.write(root.toString());
        osw.flush();//清空缓冲区，强制输出数据
        osw.close();//关闭输出流
    }
}
