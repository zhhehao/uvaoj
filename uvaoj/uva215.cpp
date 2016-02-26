#include <cstdio>
#include <cstring>
#include <vector>
#include <cctype>
#include <queue>
using namespace std;
#define EXP csheet[x][y].value
struct Cell{
	char value[80];
} csheet[22][12];
int row, col;
int out1[22][12];
struct Exp{
	int x, y;
};
vector<Exp> out2;

void input() {
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			scanf("%s", csheet[i][j].value) == 1;
//	printf("%s\n",csheet[1][1].value );
}

struct QE{
	int x, y, value;
	char op;
	bool isop, isva;
};

int getlong(int num) {
	if (num < 10)
		return 1;
	else if (num < 100)
		return 2;
	else if (num < 1000)
		return 3;
	else if (num < 10000)
		return 4;
	else if (num < 100000)
		return 5;
	else if (num < 1000000)
		return 6;
}

void getqe(queue<QE>& q, int x, int y) {
	int len = strlen(EXP);
	QE qe;
	for (int i = 0; i < len;) {
		if (isalpha(EXP[i])) {
			qe.x = EXP[i] - 'A';
			qe.y = EXP[i+1] - '0';
			qe.isop = false;
			qe.isva = false;
			q.push(qe);
			i += 2;
			continue;
		}
		else if (isdigit(EXP[i])) {
			sscanf(EXP+i, "%d", &qe.value);
			qe.isop = false;
			qe.isva = true;
			q.push(qe);
			i += getlong(qe.value);
			continue;
		}
		else if (EXP[i] == '-' || EXP[i] == '+') {
			qe.op = EXP[i];
			qe.isop = true;
			qe.isva = false;
			q.push(qe);
			i++;
			continue;
		}
	}
}

int vis[22][12];

int cycle(int x, int y) {
//	printf("%d %d\n", x, y);
//	if (isdigit(EXP[0]) || EXP[0] == '-') {
//		int num;
//		sscanf(EXP, "%d", &num);
//		return num;
//	}	
	vis[x][y] = -1;
	queue<QE> qe;
	getqe(qe, x, y);
	int sum = 0; int oper = 1; bool iscycle = false;
	while (!qe.empty()) {
		if (!qe.front().isva && !qe.front().isop) {
			if (vis[qe.front().x][qe.front().y] < 0) {iscycle = true; break;}
			else {
				int result = cycle(qe.front().x, qe.front().y);
//				printf("%d %d %d\n", qe.front().x, qe.front().y, result);
				if (result == 99999) {iscycle = true; break;}
				else {
					if (oper == 1) sum += result;
					else if (oper == -1) sum -= result;
				}
			}
		}
		else if (qe.front().isva) {
			if (oper == 1) sum += qe.front().value;
			else if (oper == -1) sum -= qe.front().value;
		}
		else if (qe.front().isop) {
			if (qe.front().op == '+') oper = 1;
			else if (qe.front().op == '-') oper = -1;
		}
		qe.pop();
	}
	if (iscycle)
		return 99999;
	vis[x][y] = 1;
//	printf("%d %d %d\n", x, y, sum);
	return sum;
}

bool getvalue(int x, int y) {
//	if (isdigit(EXP[0]) || EXP[0] == '-') {
//		int num;
//		sscanf(EXP, "%d", &num);
//		out1[x][y] = num;
//		return true;
//	}
//	else {
//		printf("%d %d\n", x, y);
		int result = cycle(x, y);
		if (result != 99999) {
			out1[x][y] = result;
			return true;
		}
		else {
			Exp ex;
			ex.x = x; ex.y = y;
			out2.push_back(ex);
			return false;
		}
//	}
}

void solve() {
	memset(out1, 0, sizeof(out1));
	out2.clear();
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col;j++)
			getvalue(i, j);
}

void output() {
	if (out2.size()) {
		for (int i = 0; i < out2.size(); i++)
			printf("%c%d: %s\n", 'A'+out2[i].x, out2[i].y, csheet[out2[i].x][out2[i].y].value);
		printf("\n");
	}
	else {
		printf(" ");
		for (int i = 0; i < col; i++)
			printf("%6d", i);
		printf("\n");
		for (int i = 0; i < row; i++) {
			printf("%c", 'A'+i);
			for (int j = 0; j < col; j++)
				printf("%6d", out1[i][j]);
			printf("\n");
		}
		printf("\n");
	}
}

int main() {
	while (scanf("%d%d", &row, &col) == 2 && row) {
		input();
		solve();
		output();
	}
	return 0;
}
