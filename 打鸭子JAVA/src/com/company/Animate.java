package com.company;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Vector;

public class Animate {
    public static HashMap<String, Vector<String>> co = new HashMap<String, Vector<String>>();
    public static HashMap<String, Vector<String>> op = new HashMap<String, Vector<String>>();
    public HashSet<String> legalName = new HashSet<String>() {{add("MallardDuck"); add("RedHeadDuck"); add("RubberDuck");
    add("DecoyDuck"); add("AirForceOne"); add("AirBus"); add("Boeing"); add("Apache"); add("FlyWithWings"); add("Swim");
    add("Quack"); add("Stun"); add("Squick"); add("FlyWithPropulsion"); add("FlyWithPropeller");}};

    private String preDeal(String s) {
        // 删除s中的非数字、下划线、大小写字母、英文逗号字符
        int i = 0;
        while(i < s.length()) {
            if(!(s.charAt(i) >= '0' && s.charAt(i) <= '9' || s.charAt(i) >= 'a' && s.charAt(i) <= 'z' ||
                    s.charAt(i) >= 'A' && s.charAt(i) <= 'Z' || s.charAt(i) == ',' || s.charAt(i) == '_')) {
                s = s.substring(0, i) + s.substring(i+1);
            }
            else i++;
        }

        // 删除s中连续多个逗号或连续多个下划线情况下的多余逗号
        i = 0;
        while (i < s.length() - 1) {
            if(s.charAt(i) == ',' && s.charAt(i+1) == ',' || s.charAt(i) == '_' && s.charAt(i+1) == '_') {
                s = s.substring(0, i+1) + s.substring(i+2);
            }
            else i++;
        }

        return s;
    }

    public void push(String s) {
        s = preDeal(s);
        String[] v = s.split(",");
        String cla = v[0].substring(0, v[0].indexOf("_")), objName = v[0].substring(0, v[0].indexOf("_")) + v[0].substring(v[0].indexOf("_")+1);
        if(!legalName.contains(cla)) {
            System.out.println("Input objName error: " + cla);
            return;
        }
        if(!co.containsKey(cla)) co.put(cla, new Vector<String>());
        co.get(cla).add(objName);
        if(!op.containsKey(objName)) op.put(objName, new Vector<String>());
        for(int i=1;i<v.length;i++) {
            if(!legalName.contains(v[i])) {
                System.out.println( "Input behavior error: " + v[i]);
                return;
            }
            if(v[i].equals("Quack") || v[i].equals("Squick")) op.get(objName).add(0, v[i]);
            else op.get(objName).add(v[i]);
        }
    }

    void animate(String path) throws IOException {
        GenJsonFromObj g = new GenJsonFromObj();
        Vector<KeyFrame> keyFrames = g.GenKeyFrames(op);
        System.out.println("keyFrames" + keyFrames.toString());
        g.WriteKeyFrames(path, keyFrames);
    }
}
