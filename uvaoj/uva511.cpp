#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <map>
using namespace std;

const double EPS = 1e-6;

struct Point {
	double x, y;
};

struct Map {
	string name;
	Point point[4];
	double area;
	Point center;
	double ratio;
	double xmin;
	Point lright;
	Point locate;
	double cc;
	double dislr;
	int level;
};

struct Location {
	string name;
	Point pos;
	vector<Map> mlevel;
	int maxlevel;
};

void getmap(vector<Map>& v);
void gtpoint(Map& m, double& x1, double& y1, double& x2, double& y2);
void getlocate(vector<Location>& v, vector<Map>& m);
bool cmp(const Map& a, const Map& b);
double getcc(Point& a, Point& b);

int main() {
	string str;
	getline(cin, str);
	vector<Map> vmap;
	if (str == "MAPS")
		getmap(vmap);
	vector<Location> vlocate;
	getlocate(vlocate, vmap);

	for (;;) {
		getline(cin, str);
		stringstream ss(str);
		string location;
		int level;
		ss >> location;
		if (location == "END") break;
		ss >> level;
		bool nolocate = true;
		for (int i = 0; i < vlocate.size(); i++) {
			if (vlocate[i].name == location) {
				nolocate = false;
				if (vlocate[i].mlevel.size() == 0) {
					cout << location << " at detail level " << level
						 << " no map contains that location\n";
					break;
				}
				if (level > vlocate[i].maxlevel) {
					cout << location << " at detail level " << level
						 << " no map at that detail level; using "
						 << vlocate[i].mlevel[vlocate[i].mlevel.size()-1].name
						 << endl;
					break;
				}
				string levelname;
				for (int j = vlocate[i].mlevel.size() - 1; j >= 0; j--) {
					if (vlocate[i].mlevel[j].level == level) {
						levelname = vlocate[i].mlevel[j].name;
						break;
					}
				}
				cout << location << " at detail level " << level
					 << " using " << levelname  << endl;
				break;
			}
		}
		if (nolocate)
			cout << location << " at detail level " << level << " unknown location\n";
	}

	return 0;
}

void getlocate(vector<Location>& v, vector<Map>& m) {
	Location lo;
	string str;
	Point p;
	for (;;) {
		getline(cin, str);
		stringstream ss(str);
		ss >> lo.name;
		if (lo.name == "REQUESTS") break;
		ss >> p.x >> p.y;
		lo.pos.x = p.x;
		lo.pos.y = p.y;
		for (int i = 0; i < m.size(); i++) {
			int x1, y1, x2, y2;
			x1 = m[i].point[0].x;
			x2 = m[i].point[1].x;
			y1 = m[i].point[2].y;
			y2 = m[i].point[0].y;
			if ((p.x>=x1)&&(p.x<=x2)&&(p.y>=y1)&&(p.y<=y2)) {
				m[i].locate.x = p.x;
				m[i].locate.y = p.y;
				m[i].cc = getcc(m[i].center, lo.pos);
				m[i].dislr = getcc(lo.pos, m[i].lright);
				lo.mlevel.push_back(m[i]);
			}
		}
		sort(lo.mlevel.begin(), lo.mlevel.end(), cmp);
		map<double, int> marea;
		int lev = 1;
		for (int i = 0; i < lo.mlevel.size(); i++) {
			if (!marea.count(lo.mlevel[i].area))
				marea[lo.mlevel[i].area] = lev++;
		}
		for (int i = 0; i < lo.mlevel.size(); i++) {
			lo.mlevel[i].level = marea[lo.mlevel[i].area];
		}
		lo.maxlevel = marea.size();
		v.push_back(lo);
		lo.mlevel.resize(0);
		marea.clear();
	}
}

void getmap(vector<Map>& v) {
	Map m;
	Point p1, p2;
	string str;
	for (;;) {
		getline(cin, str);
		stringstream ss(str);		
		ss >> m.name;
		if (m.name == "LOCATIONS") break;
		ss >> p1.x >> p1.y >> p2.x >> p2.y;
		gtpoint(m, p1.x, p1.y, p2.x, p2.y);
		m.locate.x = 0.0;
		m.locate.y = 0.0;
		m.cc = 0.0;
		m.dislr = 0.0;
		m.level = 0;
		v.push_back(m);
	}
}

void gtpoint(Map& m, double& x1, double& y1, double& x2, double& y2) {
	if (((x1>x2)&&(y1>y2)) || ((x1<x2)&&(y1<y2))) {
		if (x1 > x2) {swap(x1, x2);swap(y1, y2);}
		m.point[0].x = x1;
		m.point[0].y = y2;
		m.point[1].x = x2;
		m.point[1].y = y2;
		m.point[2].x = x1;
		m.point[2].y = y1;
		m.point[3].x = x2;
		m.point[3].y = y1;
		m.lright.x = x2;
		m.lright.y = y1;
		m.area = (x2-x1) * (y2-y1) + EPS;
		m.xmin = x1;
		m.ratio = fabs((y2-y1) / (x2-x1) - 0.75) + EPS;
		m.center.x = (x2+x1) / 2 + EPS;
		m.center.y = (y2+y1) / 2 + EPS;
	}
	else {
		if (x1 > x2) {swap(x1, x2); swap(y1, y2);}
		m.point[0].x = x1;
		m.point[0].y = y1;
		m.point[1].x = x2;
		m.point[1].y = y1;
		m.point[2].x = x1;
		m.point[2].y = y2;
		m.point[3].x = x2;
		m.point[3].y = y2;
		m.lright.x = x2;
		m.lright.y = y2;
		m.area = (x2-x1) * (y1-y2) + EPS;
		m.xmin = x1;
		m.ratio = fabs((y1-y2) / (x2-x1) - 0.75) + EPS;
		m.center.x = (x2+x1) / 2 + EPS;
		m.center.y = (y1+y2) / 2 + EPS;
	}
}

bool cmp(const Map& a, const Map& b) {
	if (a.area == b.area) {
		if (a.cc == b.cc) {
			if (a.ratio == b.ratio) {
				if (a.dislr == b.dislr) {
					return a.xmin > b.xmin;
				}
				else
					return a.dislr < b.dislr;
			}
			else
				return a.ratio > b.ratio;
		}
		else
			return a.cc > b.cc;
	}
	else
		return a.area > b.area;
}

double getcc(Point& a, Point& b) {
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + EPS;
}
