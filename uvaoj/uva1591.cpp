#include <stdio.h>

int main(void)
{
	int rev; 
	long long n, sp, sq, ma, mb, mn, m;
	while ((rev=scanf("%lld%lld%lld", &n, &sp, &sq) != EOF)){
		long long mn = n*sq<<10;;
		for (int a = 0; a < 32; a++)
			for (int b = 0; b < 32; b++){
					m = (((n-1)*sp +(((n-1)*sp)<<a))>>b) + sq; 
				if ((m >= n*sq) && (m < mn)){
					mn = m;
					ma = a; 
					mb = b;
				}
			}
		printf("%lld %lld %lld\n", mn, ma, mb);
	}
	return 0;
}
