#include <cstdio>
#include <set>
using namespace std;
set<int> chk;

int main() {
	int n, kase = 1;
	while (scanf("%d", &n) == 1 && n) {
		int num1, num2 = 0;
		int d1, d2, cnt1, cnt2;
		bool isans = true;
		if (kase++ > 1) printf("\n");
		for (int i = 1234; i <= 98765; i++) {
			chk.clear();
			num1 = d1 = i;
			cnt1 = cnt2 = 0;
			do {
				if (!chk.count(d1%10)) chk.insert(d1%10);
				else 
					goto end;
				d1 /= 10;
				cnt1++;
			} while (d1 > 0);
			num2 = d2 = num1 * n;
			do {
				if (!chk.count(d2%10)) chk.insert(d2%10);
				else goto end;
				d2 /= 10;
				cnt2++;
			} while (d2 > 0);
			if (cnt1+cnt2 > 10) break;
			if (chk.size() < 9) goto end;
			if (chk.count(0) && num1 < 10000) goto end;
			printf("%d / ", num2);
			if (num1 < 10000) printf("0");
			printf("%d = %d\n", num1, n);
			isans = false;
		end:
			continue;
		}
		if (isans) {
			printf("There are no solutions for %d.\n", n);
			continue;
		}
	}
	return 0;
}
