#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define EPS 1e-6

typedef struct {
	double h;
	double s;
	int id;
}square;

int s[1000];
int t[1000];

int main(void)
{
	int rev, m, n, v;
	int kase = 1;
	while (rev=scanf("%d%d", &m, &n) && m){
		int len = m * n;
		memset(s, 0, sizeof(s));
		memset(t, 0, sizeof(t));
		for (int i = 1; i <= len; i++)
			rev = scanf("%d", &s[i]);
		rev = scanf("%d", &v);
		sort(s+1, s+len+1);
		t[0] = s[1];
		for (int i = 1; i < len; i++)
			t[i] = s[i+1] - s[i];
		t[len] = s[len];

		printf("Region %d\n", kase++);

		if (v == 0){
			printf("Water level is %.2f meters.\n", (double)t[0]);
			printf("%.2f percent of the region is under water.\n\n", 0.0);
			continue;
		}
		int vmax = 0;
		for (int i = 1; i < len; i++)
			vmax += t[i] * 100 * i;
		if (v > vmax){
			printf("Water level is %.2f meters.\n", (v-vmax)/(100.0*len) + t[len] + EPS);
			printf("%.2f percent of the region is under water.\n\n", 100.0);
		}
		
		square a;
		a.h = 0;
		a.s = 100;
		a.id = 0;
		int vc1, vc2;
		vc1 = vc2 = 0;
		for (int i = 1; i < len; i++){
			vc1 = vc2;
			a.id = i;
			a.s = 100 * a.id;
			vc2 += t[i] * a.s;
			if (vc2 > v){
				printf("Water level is %.2f meters.\n", (v-vc1)/a.s + a.h + t[0] + EPS);
				printf("%.2f percent of the region is under water.\n\n",
				a.id * 1.0 /len * 100 + EPS);
				break;
			}
			a.h += t[i];
		}
	}

	return 0;
}
