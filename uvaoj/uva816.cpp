#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct Ans {
	int x, y;
};
struct Dir {
	char a, b;
};

struct Maze {
	int e, w, s, n;
	vector<Dir> dir;
};

struct Point {
	int x, y, ds;
	char dir;
};

Maze m[11][11];
int x1, y1, x2, y2;

void bfs(Point& point) {
	queue<Point> q;
	q.push(point);
	while (!q.empty()) {
		int x, y, ds; char dir;
		x = q.front().x; y = q.front().y; ds = q.front().ds; dir = q.front().dir; q.pop();
		if (dir == 'E') m[x][y].e = ds + 1;
		else if (dir == 'S') m[x][y].s = ds + 1;
		else if (dir == 'W') m[x][y].w = ds + 1;
		else if (dir == 'N') m[x][y].n = ds + 1;
		for (int i = 0; i < m[x][y].dir.size(); i++) {
			if (m[x][y].dir[i].a == dir) {
				Point t;
			if (m[x][y].dir[i].b == 'E') {t.x=x;t.y=y+1;t.dir='E';t.ds=ds+1;
				if (m[t.x][t.y].e != -1) continue;
				q.push(t);continue;}
			if (m[x][y].dir[i].b == 'S') {t.x=x+1;t.y=y;t.dir='S';t.ds=ds+1;
				if (m[t.x][t.y].s != -1) continue;
				q.push(t);continue;}
			if (m[x][y].dir[i].b == 'W') {t.x=x;t.y=y-1;t.dir='W';t.ds=ds+1;
				if (m[t.x][t.y].w != -1) continue;
				q.push(t);continue;}
			if (m[x][y].dir[i].b == 'N') {t.x=x-1;t.y=y;t.dir='N';t.ds=ds+1;
				if (m[t.x][t.y].n != -1) continue;
				q.push(t);continue;}
			}
		}
	}
}

void solve(vector<Ans>& ans, char dir, int dist) {
	Ans na;
	na.x = x2; na.y = y2;
	ans.push_back(na);
	Point p; p.x = x2; p.y = y2; p.dir = dir;
	if (dir == 'E') p.y--;
	else if (dir == 'S') p.x--;
	else if (dir == 'W') p.y++;
	else if (dir == 'N') p.x++;
	queue<Point> q; q.push(p);
	while (!q.empty()) {
		int x, y; char dr; --dist;
		x = q.front().x; y = q.front().y; dr = q.front().dir; q.pop();
		Ans an;	an.x = x; an.y = y;
		ans.push_back(an);
		Point pt;
		if (m[x][y].e == dist) {pt.x=x;pt.y=y-1;q.push(pt);continue;}
		else if (m[x][y].s == dist) {pt.x=x-1;pt.y=y;q.push(pt);continue;}
		else if (m[x][y].w == dist) {pt.x=x;pt.y=y+1;q.push(pt);continue;}
		else if (m[x][y].n == dist) {pt.x=x+1;pt.y=y;q.push(pt);continue;}
	}
}

int main() {
	string name;
	while (getline(cin,name) && name != "END") {
		char dir; string str;
		getline(cin, str);
		stringstream ss1(str);
		ss1 >> x1 >> y1 >> dir >> x2 >> y2;
		for (int i = 1; i <= 9; i++)
			for (int j = 1; j <= 9; j++) {
				m[i][j].dir.clear();
				m[i][j].e = m[i][j].s = m[i][j].w = m[i][j].n = -1;
		}
		while (getline(cin, str) && str[0] != '0') {
			stringstream ss(str);
			int x, y; string op; ss >> x >> y;
			while (ss >> op && op[0] != '*') {
				Dir dch; char ch = dch.a = op[0];
				for (int i = 1; i < op.size(); i++) {
					if (ch == 'E' && op[i] == 'L') dch.b = 'N';
					else if (ch == 'E' && op[i] == 'R') dch.b = 'S';
					else if (ch == 'E' && op[i] == 'F') dch.b = 'E';
					else if (ch == 'S' && op[i] == 'L') dch.b = 'E';
					else if (ch == 'S' && op[i] == 'R') dch.b = 'W';
					else if (ch == 'S' && op[i] == 'F') dch.b = 'S';
					else if (ch == 'W' && op[i] == 'L') dch.b = 'S';
					else if (ch == 'W' && op[i] == 'R') dch.b = 'N';
					else if (ch == 'W' && op[i] == 'F') dch.b = 'W';
					else if (ch == 'N' && op[i] == 'L') dch.b = 'W';
					else if (ch == 'N' && op[i] == 'R') dch.b = 'E';
					else if (ch == 'N' && op[i] == 'F') dch.b = 'N';
					m[x][y].dir.push_back(dch);
				}
			}
		}
//		m[x1][y1].e = -1;m[x1][y1].s = -1;m[x1][y1].w = -1;m[x1][y1].n = -1;
//		m[x2][y2].e = -1;m[x2][y2].s = -1;m[x2][y2].w = -1;m[x2][y2].n = -1;
		Point p; p.x = x1; p.y = y1; p.dir = dir; p.ds = 0;
		if (dir == 'E') p.y++;
		else if (dir == 'S') p.x++;
		else if (dir == 'W') p.y--;
		else if (dir == 'N') p.x--;
		bfs(p);
		int dist = -1;
		int mindist = 1000000;
		char back;
		if (m[x2][y2].e != -1) {
			if (m[x2][y2].e < mindist) {
				dist = m[x2][y2].e;
				back = 'E';
				mindist = dist;
			}
		}
		if (m[x2][y2].s != -1) {
			if (m[x2][y2].s < mindist) {
				dist = m[x2][y2].s;
				back = 'S';
				mindist = dist;
			}
		}
		if (m[x2][y2].w != -1) {
			if (m[x2][y2].w < mindist) {
				dist = m[x2][y2].w;
				back = 'W';
				mindist = dist;
			}
		}
		if (m[x2][y2].n != -1) {
			if (m[x2][y2].n < mindist) {
				dist = m[x2][y2].n;
				back = 'N';
				mindist = dist;
			}
		}
		cout << name << endl;
		if (dist == -1) {
			cout << "  No Solution Possible\n";
			continue;
		}
		vector<Ans> ans;	
		ans.clear();
		solve(ans, back, dist);
		int cnt = 0;
		for (int i = ans.size()-1; i >=0; i--) {
			if (cnt%10 == 0) printf(" ");
			printf(" (%d,%d)", ans[i].x, ans[i].y);
			if (++cnt%10 == 0)
				printf("\n");
		}
		if (ans.size() % 10 != 0) printf("\n");
	}
	return 0;
}
