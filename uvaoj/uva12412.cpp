#include <stdio.h>
#include <string.h>
#define EPS 1e-5

typedef struct 
{
	char sid[12];
	int cid;
	char name[12];
	int yw, sx, yy, bc;
} student;

char a_sid[1000][12];
char a_name[1000][12];
int a_score[1000][6];

void add(void);
void query(int n);
void rank();
void stat();

int add_i;

int main()
{

	int rev, choice;
	add_i = 0;
	memset(a_sid, '\0', sizeof(a_sid));
	memset(a_name, '\0', sizeof(a_name));
	memset(a_score, 0, sizeof(a_score));
	while (1)
	{
		printf("Welcome to Student Performance Management System (SPMS).\n\n");
		printf("1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n");
		printf("5 - Show Statistics\n0 - Exit\n\n");
		rev = scanf("%d", &choice);
		if (!choice) break;
		switch (choice)
		{
			case 1:
				add();
				break;
			case 2:
				query(2);
				break;
			case 3:
				query(3);
				break;
			case 4:
				rank();
				break;
			case 5:
				stat();
				break;
		}
	}
	return 0;
}

void add(void)
{
	int rev;
	student a;
	while (1)
	{
		printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
		int dup = 0;
		rev = scanf("%s", a.sid);
		int len = strlen(a.sid);
		if (len != 10) break;
		rev = scanf("%d%s%d%d%d%d",  &a.cid, a.name, &a.yw, &a.sx, &a.yy, &a.bc);
		for (int i = 0; i <= add_i; i++)
			if (!strcmp(a_sid[i], a.sid))
				dup = 1;		
		if (dup) 
			{printf("Duplicated SID.\n"); continue;}
		strcpy(a_sid[add_i], a.sid);
		strcpy(a_name[add_i], a.name);
		a_score[add_i][0] = a.cid;
		a_score[add_i][1] = a.yw;
		a_score[add_i][2] = a.sx;
		a_score[add_i][3] = a.yy;
		a_score[add_i][4] = a.bc;
		a_score[add_i][5] = a.yw + a.sx + a.yy + a.bc;
//		printf("Total Score:%d", a_score[add_i][5]);
		add_i++;
	}
}

void query(int n)
{
	int rev;
	while (1)
	{
		char s[12];
		printf("Please enter SID or name. Enter 0 to finish.\n");
		rev = scanf("%s", s);
		int len = strlen(s);
		if (len == 1 && s[0] == '0') break;
		int num = 0;
//		printf("add_i %d n %d\n", add_i, n);
		for (int i = 0; i < add_i; i++)
		{	
			if ((!strcmp(s, a_name[i])) || (!strcmp(s, a_sid[i])))
				{
					if (n == 2)
					{
						strcpy(a_sid[i], "\0\0\0\0\0\0\0\0\0\0\0\0");
						strcpy(a_name[i], "\0\0\0\0\0\0\0\0\0\0\0\0");

						num++;
					}
					else if (n == 3)
					{
						int rank = 1;
						for (int j = 0; j < add_i; j++)
						{
							if (strlen(a_sid[j]) == 0) continue;
							if (j == i) continue;
							if (a_score[j][5] > a_score[i][5])
								rank++;
						}
						printf("%d %s %d %s %d %d %d %d %d %.2f\n", rank,
						a_sid[i], a_score[i][0], a_name[i], a_score[i][1],
						a_score[i][2], a_score[i][3], a_score[i][4],
						a_score[i][5], a_score[i][5] / 4.0 + EPS);
					}
				}
		}
		if (n == 2)
			printf("%d student(s) removed.\n", num);
	}
}

void rank()
{
	printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
}	

void stat()
{
	int rev;
		printf("Please enter class ID, 0 for the whole statistics.\n");
		int cid;
		rev = scanf("%d", &cid);
		for (int i = 1; i < 5; i++)
		{	
			int num = 0, sum = 0, pass = 0, fail = 0;
			switch (i)
			{
				case 1: 
					printf("Chinese\n");
					break;
				case 2:
					printf("Mathematics\n");
					break;
				case 3:
					printf("English\n");
					break;
				case 4:
					printf("Programming\n");
					break;
			}
			for (int j = 0; j < add_i; j++)
			{
				if (strlen(a_sid[j]) == 0)
					continue;
				if (cid == 0)
				{
					num++;
					sum += a_score[j][i];
					if (a_score[j][i] >=60)
						pass++;
					else
						fail++;
				}
				else if (a_score[j][0] == cid)
				{
					num++;
					sum += a_score[j][i];
					if (a_score[j][i] >= 60)
						pass++;
					else
						fail++;
				}
			}
			printf("Average Score: %.2f\n", num == 0 ? 0 :(double)sum / (double)num + EPS);
			printf("Number of passed students: %d\n", pass);
			printf("Number of failed students: %d\n\n", fail);

		}
		int a4 = 0, a3 = 0, a2 = 0, a1 = 0, a0 = 0;
		for (int i = 0; i < add_i; i++)
		{
			int mark = 0;
			if (strlen(a_sid[i]) == 0)
				continue;
			if ((cid != 0) && (a_score[i][0] != cid))
				continue;
			for (int j = 1; j < 5; j++)
			{
				if (a_score[i][j] >=60)
					mark++;
			}
			switch (mark)
			{
				case 0:
					a0++;
					break;
				case 1:
					a1++;
					break;
				case 2:
					a2++;
					break;
				case 3:
					a3++;
					break;
				case 4:
					a4++;
					break;
			}
		}
		printf("Overall:\n");
		printf("Number of students who passed all subjects: %d\n", a4);
		printf("Number of students who passed 3 or more subjects: %d\n", a4+a3);
		printf("Number of students who passed 2 or more subjects: %d\n", a4+a3+a2);
		printf("Number of students who passed 1 or more subjects: %d\n", a4+a3+a2+a1);
		printf("Number of students who failed all subjects: %d\n\n", a0);

}
