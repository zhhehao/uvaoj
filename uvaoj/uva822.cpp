#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

struct Topic {
	int tid, tnum, twork, twait;
	int start;
};

struct Staff {
	int inid;
	int sid;
	vector<int> vprefer;
	int isidle;
	int count;
	int lastjob;
};

bool cmp(Staff& a, Staff& b);

int main() {
	int t, s;
	int kase = 1;
	for (;;) {
		// 输入所有的topic
		cin >> t;
		if (t == 0) break;
		vector<Topic> vtopic; // 存储所有topic
		Topic topic;
		while (t--) {
			cin >> topic.tid >> topic.tnum >> topic.start >> topic.twork >> topic.twait;
			vtopic.push_back(topic);
		}
		// 输入所有的staff
		cin >> s;
		vector<Staff> vstaff; // 存储所有的staff
		Staff staff;
		int spec, stid;
		int inid = 1;
		while (s--) {
			cin >> staff.sid >> spec;
			while (spec--) {
				cin >> stid;
				for (int i = 0; i < vtopic.size(); i++) {
					if (vtopic[i].tid == stid) {
						staff.vprefer.push_back(i);
						break;
					}
				}
			}
			staff.inid = inid++;
			staff.isidle = 1;
			staff.count = 0;
			staff.lastjob = 0;
			vstaff.push_back(staff);
			staff.vprefer.resize(0);
		}
		// 程序处理部分
		int minu;
		bool allin = false; // 是否所有的topic都进入了队列
		bool alldone = false;
		int vt[22];
		memset(vt, 0, sizeof(vt));
		for (minu = 1;; minu++) { // 计时开始
			for (int i = 0; i < vstaff.size(); i++) { // 处理staff状态
				if (vstaff[i].isidle == 0) 
					vstaff[i].count--;
				if (vstaff[i].count == 0 && vstaff[i].isidle == 0) {
					vstaff[i].isidle = 1;
				}
			}
			if (vstaff.size() > 1)
				sort(vstaff.begin(), vstaff.end(), cmp);
			if (!allin) { // 处理所有的topic加入队列
				bool notopic = true;
				for (int i = 0; i < vtopic.size(); i++) {
					if (vtopic[i].tnum > 0) {
						if (minu == vtopic[i].start+1) {
							vt[i]++;
							vtopic[i].tnum--;
							vtopic[i].start += vtopic[i].twait;
						}
						if (vtopic[i].tnum > 0)
							notopic = false;
					}
				}
				if (notopic) {
					allin = true;
				}
			}
			if (allin && !alldone) {
				bool done = true;
				for (int i = 0; i < vtopic.size(); i++) {
					if (vt[i] > 0) {
						done = false;
						break;
					}
				}
				if (done)
					alldone = true;
			}
			if (alldone) {
				if (vstaff[vstaff.size()-1].isidle == 1)
					goto output;
			}
			if (vstaff[0].isidle == 0)
				continue;
			// 开始领任务
			for (int i = 0; i < vstaff.size(); i++) {
				if (vstaff[i].isidle == 0) break;
				for (int j = 0; j < vstaff[i].vprefer.size(); j++){
					if (vt[vstaff[i].vprefer[j]] > 0) {
						vt[vstaff[i].vprefer[j]]--;
						vstaff[i].isidle = 0;
						vstaff[i].count = vtopic[vstaff[i].vprefer[j]].twork;
						vstaff[i].lastjob = minu;
						break;
					}
				}
			}
		}
		// 输出最后结果
		output:
		printf("Scenario %d: All requests are serviced within %d minutes.\n",kase++,minu-1);		
		// 清空所有容器
		vtopic.resize(0);
		vstaff.resize(0); 
	}
	return 0;
}

bool cmp(Staff& a, Staff& b) {
	if (a.isidle == b.isidle) {
		if (a.lastjob == b.lastjob)
			return a.inid < b.inid;
		else 
			return a.lastjob < b.lastjob;
	}
	else
		return a.isidle > b.isidle;
}
