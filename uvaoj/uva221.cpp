#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iterator>
using namespace std;

struct Bd {
	int bid;
	double x1, x2, y1, y2, z;
};

void bdin(vector<Bd>& vbd, set<double>& sx, set<double>& sz, int n);
int cmp(Bd a, Bd b);
int cmp2(Bd a, Bd b);

const int MAXX = 400;
const int MAXZ = 400;

int a[MAXX][MAXZ];

int main() {
	int n, kase = 1;
	while (cin >> n && n != 0) {
		vector<Bd> vbd;
		set<double> sx, sz;
		bdin(vbd, sx, sz, n);
		sort(vbd.begin(), vbd.end(), cmp);
		memset(a, 0, sizeof(a));
//		for (set<double>::iterator it = sx.begin(); it != sx.end(); ++it)
//			cout << *it << endl;
//		cout << "*********\n";
//		for (set<double>::iterator it = sz.begin(); it != sz.end(); ++it)
//			cout << *it << endl;
		for (int i = 0; i < vbd.size(); i++) {
			int x1, x2, z;
			x1 = distance(sx.begin(), sx.find(vbd[i].x1));
			x2 = distance(sx.begin(), sx.find(vbd[i].x2));
			z = distance(sz.begin(), sz.find(vbd[i].z));
			for (int j = 0; j <= z; j++) {
				for (int k = x1; k < x2; k++) {
					a[j][k] = vbd[i].bid;
				}
			}
		}
		set<int> sb;
		vector<Bd> vb;
		Bd bvd;
		for (int j = 0; j < sx.size(); j++) {
			for (int i = 0; i < sz.size(); i++) {
//				cout << a[i][j] << " ";
				if ((a[i][j] != 0) && (!sb.count(a[i][j]))) {
					sb.insert(a[i][j]);
					bvd.bid = a[i][j];
					for (int k = 0; k < vbd.size(); k++) {
						if (vbd[k].bid == bvd.bid) {
							bvd.x1 = vbd[k].x1;
							bvd.y1 = vbd[k].y1;
							break;
						}
					}
					vb.push_back(bvd);
				}
			}
//			cout << endl;
		}
		sort(vb.begin(), vb.end(), cmp2);
		if (kase > 1) cout << endl;
		cout << "For map #" << kase++ << ", the visible buildings are numbered as follows:\n";
		for (int i = 0; i < vb.size(); i++) {
			if (i > 0) cout << " ";
			cout << vb[i].bid;
		}
		cout << endl;

		vbd.resize(0);
		sx.clear();
		sz.clear();
		sb.clear();
		vb.resize(0);
	}
	return 0;
}

int cmp(Bd a, Bd b) {
	if (a.y1 == b.y1)
		return a.x1 < b.x1;
	else
		return a.y1 > b.y1;
}

int cmp2(Bd a, Bd b) {
	if (a.x1 == b.x1)
		return a.y1 < b.y1;
	else
		return a.x1 < b.x1;
}

void bdin(vector<Bd>& vbd, set<double>& sx, set<double>& sz, int n) {
	Bd bd;
	int bid = 0;
	while (n--) {
		cin >> bd.x1 >> bd.y1 >> bd.x2 >> bd.y2 >> bd.z;
		bid++;
		bd.bid = bid;
		bd.x2 += bd.x1;
		bd.y2 += bd.y1;
		if (!sx.count(bd.x1)) sx.insert(bd.x1);
		if (!sx.count(bd.x2)) sx.insert(bd.x2);
		if (!sz.count(bd.z)) sz.insert(bd.z);
		vbd.push_back(bd);
	}
}
