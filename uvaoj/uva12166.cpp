#include <cstdio>
#include <cstring>
#include <cctype>
#include <map>
using namespace std;
const int maxn = 65535 + 10;
long long allw[maxn];
char num[20];
char buf[1000000 + 10];

int main() {
	int t; scanf("%d", &t); fgets(num, 20, stdin);
	while (t--) {
		int lcnt, ncnt, cnt; long long w;
		lcnt = ncnt = cnt = 0;
		memset(allw, 0, sizeof(allw)); memset(buf, '\0', sizeof(buf));
		memset(num, '\0', sizeof(num));
		fgets(buf, 1000010, stdin);
		for (int i = 0; buf[i] != '\0'; i++) {
			if (isdigit(buf[i])) num[cnt++] = buf[i];	
			else if (buf[i] == '[') lcnt++;
			else if (buf[i] == ',' && isdigit(num[0])) {
				num[cnt] = '\0'; sscanf(num, "%lld", &w); allw[ncnt++] = (w << lcnt);cnt = 0;
				num[cnt]='\0';
			}
			else if (buf[i] == ']') {
				if (isdigit(num[0])) {
					num[cnt]='\0';sscanf(num,"%lld",&w);allw[ncnt++]=(w<<lcnt);cnt = 0;
					num[cnt]='\0'; 
				}
				lcnt--;
			}
		}
		if (isdigit(num[0])) {
			num[cnt]='\0'; sscanf(num,"%lld",&w);allw[ncnt++]=(w<<lcnt);
		}
		map<long long, int> ma; ma.clear();
		for (int i = 0; i < ncnt; i++)
			if (!ma.count(allw[i]))	
				ma[allw[i]] = 1;
			else 
				ma[allw[i]]++;
		int maxi = 0; int summ = 0;
		for (map<long long, int>::iterator it = ma.begin(); it != ma.end(); ++it) { 
			summ += it->second;
			if (it->second  > maxi) maxi = it->second;
		}
		printf("%d\n", summ - maxi);
	}
	return 0;
}
