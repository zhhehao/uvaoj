#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;
const int maxn = 128 +5;
char buf[maxn];
int main() {
	int n; scanf("%d", &n) == 1;
	fgets(buf, maxn, stdin);
	while (n--) {
		memset(buf, '\0', sizeof(buf));
		stack<char> s; while (!s.empty()) s.pop();
		fgets(buf, maxn, stdin);
//		printf("%s\n", buf);
		bool no = false;
		for (int i = 0; buf[i] != '\0'; i++) {
			if (buf[i] == '(' || buf[i] == '[')
				s.push(buf[i]);
			else if (buf[i] == ')' || buf[i] == ']') {
				if (s.empty()) {no = true; break;}
				if (buf[i] == ')' && s.top() == '(') {
					s.pop(); continue;
				} else if (buf[i] == ']' && s.top() == '[' ) {
					s.pop(); continue;
				} else {no = true; break;}
			}
		}
		if (!s.empty()) no = true;
		if (no) {printf("No\n"); continue;}
		printf("Yes\n");
	}
	return 0;
}
