#include <stdio.h>
#include <string.h>
#define MAXN 15

char s[MAXN];
char t[MAXN]; 

bool ro1(void);
bool ro2(void);
bool ro3(void);

int main(void)
{
	int rev;
	memset(s, '\0', sizeof(s));
	memset(t, '\0', sizeof(t));
	while ((rev=scanf("%s", s) != EOF))
	{
		for (int i = 6; i < 12; i++){
			t[i-6] = s[i];
			s[i] = '\0';
		}
		
		bool same = false;
		if (!strncmp(s, t, 6)){
			same = true;
			goto end;
		}
		for (int i = 0; i < 4; i++){
			if (same = ro1())
				goto end;
			for (int j = 0; j < 4; j++){
				if (same = ro2())
					goto end;
				for (int k = 0; k < 4; k++)
					if (same = ro3())
						goto end;
			}
		}
//		for (int i = 0; i < 4; i++)
//			if (same = ro2())
//				goto end;
//		for (int i = 0; i < 4; i++)
//			if (same = ro3())
//				goto end;

		end:
		same ? printf("TRUE\n") : printf("FALSE\n");
	}
	return 0;
}

bool ro1(void)
{
	char tmp;
	bool same = false;
	tmp = t[2];
	t[2] = t[4];
	t[4] = t[3];
	t[3] = t[1];
	t[1] = tmp;
	if (!strncmp(s, t, 6))
		same = true;
//	printf("%s\n", t);
	return same;
}

bool ro2(void)
{
	char tmp;
	bool same = false;
	tmp = t[0];
	t[0] = t[1];
	t[1] = t[5];
	t[5] = t[4];
	t[4] = tmp;
	if (!strncmp(s, t, 6))
		same = true;
//	printf("%s\n", t);
	return same;
}

bool ro3(void)
{
	char tmp;
	bool same = false;
	tmp = t[0];
	t[0] = t[3];
	t[3] = t[5];
	t[5] = t[2];
	t[2] = tmp;
	if (!strncmp(s, t, 6))
		same = true;
//	printf("%s\n", t);
	return same;
}

