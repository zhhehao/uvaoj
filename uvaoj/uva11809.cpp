#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
	int rev;
	char s[100];
	double st[10] = {log(0.5), log(0.75), log(0.875), log(0.9375), log(0.96875), log(0.984375), log(0.9921875), log(0.99609375), log(0.998046875), log(0.9990234375)};

	while (1)
	{
		rev = scanf("%s", s);
		rev = strcmp(s, "0e0");
		if (!rev) break;

		int len = strlen(s);
		int e = 0;
		for (int i = 18; i < len; i++)
			e += (s[i]-'0') * pow(10, len-i-1);


		double m = 0.0;
		m += (s[0] - '0');
		for (int i = 2; i < 18; i++)
			m += (s[i]-'0') * pow(10, -1 * (i-1));

		int ae;
		double aem = log(m) + e*log(10);
		for (int i = 1; i < 31; i++)
			if ((pow(2, i)-1) > aem)
				{ae = i; break;}

		m = log(m) + e*log(10) - (pow(2, ae)-1)*log(2);

		int am;
		for (int i = 0; i < 10; i++)
			if (fabs(m-st[i]) < 0.00001)
				{am = i; break;}

		printf("%d %d\n", am, ae);
		
	}
	return 0;
}
