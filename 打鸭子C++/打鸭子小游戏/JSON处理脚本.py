# -*- coding: utf-8 -*-
"""
Created on Sun Oct 10 16:22:06 2021

@author: 16053
"""

import json
import codecs

data = []
with codecs.open("DuckHunting.json", "r", "utf-8") as f:
    for line in f:
        
        dic = line
        data.append(dic)
        #print (json.dumps(dic, indent=4, ensure_ascii=False))

s = ''
for d in data:
    s += d
data = json.loads(s)

for it in data['keyFrames']:
    it['action'] = int(it['action'])
    it['type'] = int(it['type'])
    it['timestamp'] = float(it['timestamp'])
    for j in range(len(it['startpos'])):
        it['startpos'][j] = float(it['startpos'][j])
    for j in range(len(it['endpos'])):
        it['endpos'][j] = float(it['endpos'][j])
    for j in range(len(it['startrotation'])):
        it['startrotation'][j] = float(it['startrotation'][j])
    for j in range(len(it['endrotation'])):
        it['endrotation'][j] = float(it['endrotation'][j])
    for j in range(len(it['startscale'])):
        it['startscale'][j] = float(it['startscale'][j])
    for j in range(len(it['endscale'])):
        it['endscale'][j] = float(it['endscale'][j])
    it['duration'] = float(it['duration'])
    it['loop'] = int(it['loop'])

with open("DuckHunting.json", "w", encoding='utf-8') as f:
    # json.dump(dict_var, f)  # 写为一行
    json.dump(data, f,indent=2,sort_keys=False, ensure_ascii=False)  # 写为多行