#include <stdio.h>
#include <string.h>

char sleep[15], first[15], awake[15];
int stu[15][3], second[15];

bool awakeche(void);
bool firstche(int n);
bool sleepche(int n);

int main(void)
{
	for (int rev, n, kase = 1; ; kase++){
		rev = scanf("%d", &n);
		if (n == 0) break;
		memset(sleep, '\0', sizeof(sleep));
		memset(first, '\0', sizeof(first));
		memset(awake, '\0', sizeof(awake));
		memset(stu, 0, sizeof(stu));
		memset(second, 0, sizeof(second));
		for (int i = 0; i < n; i++){
			rev = scanf("%d%d%d", &stu[i][0], &stu[i][1], &stu[i][2]);
			second[i] = stu[i][2];
//			stu[i][2] = (stu[i][2] + 1)%(stu[i][0]+stu[i][1]);
//			printf("%d %d\n", second[i], stu[i][2]);
		}
		for (int i = 0; i < n; i++){
			awake[i] = 'A';
			if (stu[i][2] <= stu[i][0])
				sleep[i] = 'A';
			else
				sleep[i] = 'S';
			first[i] = sleep[i];
		}
		bool sle;
		for (unsigned int minu = 1; ; minu++){
			if (awakeche()){printf("Case %d: %d\n",kase ,minu); goto end;}
			if ((minu > 1) && firstche(n)){printf("Case %d: -1\n", kase); goto end;}
			sle = sleepche(n);
//			printf("%d\n", sle);
			for (int i = 0; i < n; i++){
				if (stu[i][2] == stu[i][0]){
					if (sle){
						sleep[i] = 'S';
						stu[i][2] = ((stu[i][2])%(stu[i][0]+stu[i][1])) + 1;
					}else{
						sleep[i] = 'A';
						stu[i][2] -= (stu[i][0]-1);
					}
//					printf("i = %d, %d\n",i,stu[i][2]);
					continue;
				}
				if (stu[i][2] == stu[i][0] + stu[i][1])
					sleep[i] = 'A';
				stu[i][2] = ((stu[i][2])%(stu[i][0]+stu[i][1])) + 1;
//				printf("i = %d, %d\n",i,stu[i][2]);
//				printf("%s\n", sleep);
			}
		}
		end:
		continue;
	}
	return 0;
}

bool sleepche(int n)
{
	int s = 0;
	for (int i = 0; i < n; i++)
		if (sleep[i] == 'S')
			s++;
	return (s > (n-s)) ? true : false;
}

bool awakeche(void)
{
	return (strcmp(awake, sleep)) ? false : true;
}

bool firstche(int n)
{
	bool check = true;
	for (int i = 0; i < n; i++)
		if (stu[i][2] != second[i])
			check = false;
	
	if ((strcmp(first, sleep) == 0) && check)
		return true;
	else
		return false;
}
