#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

LL n, m, no, so, we, ea, ans;

int main() {
	int cas = 0;
	while (scanf("%lld%lld", &n, &m) == 2 && n) {
		scanf("%lld%lld%lld%lld", &no, &so, &we, &ea);
		ans = 0;
		if (no < so) swap(no, so);
		if (we < ea) swap(we, ea);
		LL t1, t2;
		t1 = n+n*(m-1)*2*ea+(m-1)+(m-1)*(n-1)*so*2;
		t2 = m+m*(n-1)*2*so+(n-1)+(m-1)*(n-1)*ea*2;
		if (we > ea) {
			t1 += (m-1)*n;
			t2 += (m-1)*(n-1);
		}
		if (no > so) {
			t1 += (m-1)*(n-1);
			t2 += m*(n-1);
		}
		if (t1 < t2) {
			swap(m, n);
			swap(no, we);
			swap(so, ea);
		}
		bool flag = true;
		if (ea) {
			ans += n+(m-1)*n*ea*2;
			we -= ea;
			ea = 0;
			--m;
			flag = false;
		}
		if (we) {
			ans += m*n;
			--we;
			if (flag) --m;
		}
		we = min(m, we);
		while (we || no) {
			if (so) {
				t1 = m*n+(n-1)*m*2*so;
				t2 = m*n+(m-1)*n+(m-1)*(n-1)*(2*so-1);
	            if(no > so) {
	            	t1 = m*n+(n-1)*m*(2*so+1);
	            	t2 = m*n+(m-1)*n+(m-1)*(n-1)*2*so;
	            }
	            if(t1 > t2 || !we) {
	                ans += m+m*(n-1)*so*2;
	                no -= so;
	                so = 0;
	                --n;
	                if(no) {
	                	ans += m*n;
	                	--no;
	                }
	                no = min(n, no);
	            }
	            else {
	            	ans += m*n;
	            	--m;
	            	--we;
	            }
			}
			else if (!we) {
				ans += m*no*(2*n-no+1)/2;
				no = 0;
			}
			else if (!no) {
				ans += n*we*(2*m-we+1)/2;
				we = 0;
			}
			else {
				ans += m*n;
	            if(m>n) {
	            	--m;
	            	--we;
	            }
	            else {
	            	--n;
	            	--no;
	            }
			}
		}
		printf("Case %d: %lld\n", ++cas, ans);
	}
	return 0;
}
