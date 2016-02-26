#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
using namespace std;
const int maxn = 100 + 5;
int  space[maxn][maxn][maxn], box[55][6];
int volume, area;
int xend, yend, zend, xmax, ymax, zmax;
vector<int> vx, vy, vz;

struct Point {
	int x, y, z;
};

void ff(int a, int b, int c) {
	stack<Point> sta; Point p; p.x = a; p.z = c; p.y = b; sta.push(p);
	while (!sta.empty()) {
		int x, y, z;
		x = sta.top().x; y = sta.top().y; z = sta.top().z; sta.pop();
		Point pf, pc; pf.x = x; pf.y = y; pf.z = z; 
		space[x][y][z] = 2;
		int xsize, ysize, zsize;
		if (x == 0 || x == xend)
			xsize = 1;
		else
			xsize = vx[x-1];
		if (y == 0 || y == yend)
			ysize = 1;
		else
			ysize = vy[y-1];
		if (z == 0 || z == zend)
			zsize = 1;
		else
			zsize = vz[z-1];
		if (y+1 <= yend) {
			if (space[x][y+1][z] == 0) {
				sta.push(pf); pc.x = x; pc.y = y+1; pc.z = z;
				sta.push(pc);continue;
			}
		}
		if (y-1 >= 0) {
			if (space[x][y-1][z] == 0) {
				sta.push(pf); pc.x = x; pc.y = y-1; pc.z = z;
				sta.push(pc); continue;
			}
		}
		if (x+1 <= xend) {
			if (space[x+1][y][z] == 0) {
				sta.push(pf); pc.x = x+1; pc.y = y; pc.z = z;
				sta.push(pc);continue;
			}
		}
		if (x-1 >= 0) {
			if (space[x-1][y][z] == 0) {
				sta.push(pf); pc.x = x-1; pc.y = y; pc.z = z;
				sta.push(pc);continue;
			}
		}
		if (z+1 <= zend) {
			if (space[x][y][z+1] == 0) {
				sta.push(pf); pc.x = x; pc.y = y; pc.z = z+1;
				sta.push(pc);continue;
			}
		}
		if (z-1 >= 0) {
			if (space[x][y][z-1] == 0) {
				sta.push(pf); pc.x = x; pc.y = y; pc.z = z-1;
				sta.push(pc);continue;
			}
		}
		volume += xsize * ysize * zsize;
		if (y+1 <= yend && space[x][y+1][z]==1) area += xsize*zsize;
		if (y-1 >= 0 && space[x][y-1][z]==1) area += xsize*zsize;
		if (x+1 <= xend && space[x+1][y][z]==1) area += ysize*zsize;
		if (x-1 >= 0 && space[x-1][y][z]==1) area += ysize*zsize;
		if (z+1 <= zend && space[x][y][z+1]==1) area += xsize*ysize;
		if (z-1 >= 0 && space[x][y][z-1]==1) area += xsize*ysize;
	}

}

int main() {
	int t; cin >> t;
	while (t--) {
//		memset(box, 0, sizeof(0));
//		memset(space, 0, sizeof(0));
		volume = 0; area = 0; xend = 0; yend = 0; zend = 0;
		xmax = 0; ymax = 0; zmax = 0;
		vx.clear(); vy.clear(); vz.clear();
//		printf("%d %d %d\n", vx.size(), vy.size(), vz.size());
		int n; cin >> n;
		memset(box, 0, sizeof(0));
		for (int i = 0; i < n; i++) {
			int x0, y0, z0, x, y, z;
			cin >> x0 >> y0 >> z0 >> x >> y >> z;
			vx.push_back(x0); vx.push_back(x0+x);
			vy.push_back(y0); vy.push_back(y0+y);
			vz.push_back(z0); vz.push_back(z0+z);
			box[i][0] = x0; box[i][1] = y0; box[i][2] = z0;
			box[i][3] = x+x0; box[i][4] = y+y0; box[i][5] = z+z0;
		}
//		printf("%d %d %d\n", vx.size(), vy.size(), vz.size());
		sort(vx.begin(), vx.end()); xmax = vx[vx.size()-1] - vx[0] + 2;
		xend = unique(vx.begin(), vx.end()) - vx.begin();
		sort(vy.begin(), vy.end()); ymax = vy[vy.size()-1] - vy[0] + 2;
		yend = unique(vy.begin(), vy.end()) - vy.begin();
		sort(vz.begin(), vz.end()); zmax = vz[vz.size()-1] - vz[0] + 2;
		zend = unique(vz.begin(), vz.end()) - vz.begin();	
		memset(space, 0, sizeof(space));
		for (int p = 0; p < n; p++) {
			int xs, xe, ys, ye, zs, ze;
			for (int q = 0; q < xend; q++) {
				if (vx[q] == box[p][0]) xs = q;
				if (vx[q] == box[p][3]) xe = q;
			}
			for (int q = 0; q < yend; q++) {
				if (vy[q] == box[p][1]) ys = q;
				if (vy[q] == box[p][4]) ye = q;
				}
			for (int q = 0; q < zend; q++) {
				if (vz[q] == box[p][2]) zs = q;
				if (vz[q] == box[p][5]) ze = q;
				}
			for (int i = xs + 1; i < xe + 1; i++)
				for (int j = ys + 1; j < ye + 1; j++)
					for (int k = zs + 1; k < ze + 1; k++) 
						space[i][j][k] = 1;
		}

		for (int i = 0; i < xend; i++) vx[i] = vx[i+1] - vx[i];
		for (int i = 0; i < yend; i++) vy[i] = vy[i+1] - vy[i];
		for (int i = 0; i < zend; i++) vz[i] = vz[i+1] - vz[i];
//		printf("%d %d %d\n", xend, yend, zend);
//		printf("%d\n", space[xend][yend][zend]);
		for (int i = 0; i <= xend; i++)
			for (int j = 0; j <= yend ; j++) {
				if (space[i][j][0] == 0) ff(i, j, 0);
				if (space[i][j][zend] == 0) ff(i, j, zend); 
			}
		for (int i = 0; i <= xend; i++)
			for (int k = 0; k <= zend; k++) {
				if (space[i][0][k] == 0) ff(i, 0, k);
				if (space[i][yend][k] == 0) ff(i, yend, k);
			}
		for (int j = 0; j <= yend; j++)
			for (int k = 0; k <= zend; k++) {
				if (space[0][j][k] == 0) ff(0, j, k);
				if (space[xend][j][k] == 0) ff(xend, j, k);
			}
		printf("%d %d\n", area, xmax*ymax*zmax-volume);
	}
	return 0;
}
