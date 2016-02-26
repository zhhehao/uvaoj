#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <queue>
#include <string>
using namespace std;

const double EPS = 1e-6;

struct Patient {
	string name;
	int sn, room, bed;
	int ts, tr, tb;
	int tin;
	bool isout;
};

struct Patb {
	int room, sn;
	bool operator < (const Patb& a) const {
		return room > a.room;
	}
};

struct Room {
	int sn, tu, tin;
};

struct Bed {
	int sn, tu, tin;
};

int geth(int th, int tm);
int getm(int tm);

int main() {
	// 输入初始数据
	int rn, bn, tst, tpp, trp, tbp, pn;
	while(cin >> rn >> bn >> tst >> tpp >> trp >> tbp >> pn) {
	// 初始化room
	vector<Room> vr;
	for (int i = 1; i <= rn; i++) {
		Room room;
		room.sn = i;
		room.tu = 0;
		room.tin = 0;
		vr.push_back(room);
	}
	// 初始化bed
	vector<Bed> vb;
	for (int i = 1 ; i <= bn; i++) {
		Bed bed;
		bed.sn = i;
		bed.tu = 0;
		bed.tin = 0;
		vb.push_back(bed);
	}
	// 初始化 patient
	vector<Patient> vp;
	queue<int> qp;
	for (int i = 1; i <= pn; i++) {
		Patient pat;
		cin >> pat.name >> pat.tr >> pat.tb;
		pat.sn = i;
		pat.room = 0;
		pat.bed = 0;
		pat.isout = false;
		vp.push_back(pat);
		qp.push(pat.sn);
	}
	// 初始化队列
	priority_queue<Patb> pqp;
	priority_queue<int, vector<int>, greater<int> > pqr;
	priority_queue<int, vector<int>, greater<int> > pqb;
	// 开始模拟
	int tend; // 最后的模拟结束时间
	int lastp = pn;
	for (int t = 0; ; t++) {
		// room
		for (int i = 0; i < vr.size(); i++) {
			if (vr[i].tin == t)
				pqr.push(i);
		}
		// bed
		for (int i = 0; i < vb.size(); i++) {
			if (vb[i].tin == t)
				pqb.push(i);
		}
		// patient
		for (int i = 0; i < vp.size(); i++) {
			if (vp[i].isout) {
				continue;
			}
			if (vp[i].room == 0) {
				if (!pqr.empty()) {
					vp[i].room = vr[pqr.top()].sn;
					vp[i].ts = t;
					vp[i].tin = t + vp[i].tr;
					vr[pqr.top()].tu += vp[i].tr; 
					vr[pqr.top()].tin = t + vp[i].tr + trp;
					pqr.pop();
				}
				else
					continue;
			} else if (vp[i].room > 0) {
				if (t == vp[i].tin) {
					Patb patb;
					patb.sn = i;
					patb.room = vp[i].room;
					pqp.push(patb);
				}
			}
		}
		while (!pqp.empty()) {
			int sn = pqp.top().sn;	
			vp[sn].bed = vb[pqb.top()].sn;
			vp[sn].isout = true;
			lastp--;
			vb[pqb.top()].tu += vp[sn].tb;
			vb[pqb.top()].tin = t + vp[sn].tb + tbp + tpp;
			pqp.pop();
			pqb.pop();
		}
		if (lastp == 0) {
			int tmax = t;
			for (int i = 0; i < vb.size(); i++) {
				if (vb[i].tin > tmax)
					tmax = vb[i].tin;
			}
			if (tmax == 0)
				tend = 0;
			else
				tend = tmax - tbp;
			break;
		}
	}
	printf(" Patient          Operating Room          Recovery Room\n");
	printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n ");
	for (int i = 0; i < 54; i++)
		printf("-");
	printf("\n");
	for (int i = 0; i < vp.size(); i++) {
		printf("%2d  ", vp[i].sn);
		cout << left << setw(10) << vp[i].name;
		printf("%2d%5d:%02d", vp[i].room, geth(tst, vp[i].ts), getm(vp[i].ts));
		printf("%5d:%02d", geth(tst, vp[i].ts+vp[i].tr), getm(vp[i].ts+vp[i].tr));
		printf("%7d%5d", vp[i].bed, geth(tst, vp[i].ts+vp[i].tr+tpp));
		printf(":%02d", getm(vp[i].ts+vp[i].tr+tpp));
		printf("%5d", geth(tst, vp[i].ts+vp[i].tr+tpp+vp[i].tb));
		printf(":%02d\n", getm(vp[i].ts+vp[i].tr+tpp+vp[i].tb));
	}
	printf("\nFacility Utilization\nType  # Minutes  %% Used\n");
	for (int i = 0; i < 25; i++)
		printf("-");
	printf("\n");
	for (int i = 0; i < vr.size(); i++) {
		double uti;
		if (tend == 0)
			uti = 0;
		else
			uti = vr[i].tu * 1.0 / tend * 100 + EPS;
		printf("Room%3d%8d%8.2f\n", vr[i].sn, vr[i].tu, uti);
	}
	for (int i = 0; i < vb.size(); i++) {
		double uti;
		if (tend == 0)
			uti = 0;
		else
			uti = vb[i].tu * 1.0 / tend * 100 + EPS;
		printf("Bed%4d%8d%8.2f\n", vb[i].sn, vb[i].tu, uti);
	}
	printf("\n");
	
	vr.resize(0);
	vb.resize(0);
	vp.resize(0);
	}
	return 0;
}

int geth(int th, int tm) {
	return th + tm / 60;
}

int getm(int tm) {
	return tm % 60;
}
