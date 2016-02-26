#include <stdio.h>
#include <string.h>

#define MAXN 30

int board[MAXN][MAXN];

int fq(int x, int y, int n);

int main()
{
	int n, rev;
	int kase = 1;

	while (rev=scanf("%d", &n) != EOF)
	{
		memset(board, 0, sizeof(board));
		int len = n;
		int dot = 2 * n - 1;
		for (int i = 1; i <= dot; i += 2)
			for (int j = 1; j <= dot; j += 2)
				board[i][j] = 1;

		int m;
		rev = scanf("%d", &m);
		char hv;
		int x, y;
		for (int i = 0; i < m; i++){
			rev = scanf("%s%d%d", &hv, &x, &y);
			if (hv == 'H')
				board[2*x-1][2*y] = 1;
			if (hv == 'V')
				board[2*y][2*x-1] = 1;
		}
		if (kase > 1)
			printf("\n**********************************\n\n");
		printf("Problem #%d\n\n", kase++);
		int found = 1;
		for (int i = 1; i < len; i++){
			int count = 0;
			for (int j = 1; j <= len-i; j++)
				for (int k = 1; k <= len-i; k++)
					if (fq(j, k, i))
						count++;
			if (count){
				printf("%d square (s) of size %d\n", count, i);
				found = 0;
			}
		}
		if (found)
			printf("No completed squares can be found.\n");

//		for (int i = 1; i <= dot; i++){
//			for (int j = 1; j <= dot; j++)
//				printf("%d ", board[i][j]);
//			printf("\n");
//		}
	}
	return 0;
}

int fq(int x, int y, int n)
{
	int found = 1;
//	printf("x=%d y=%d n=%d\n", x, y, n);
	x = 2 * x - 1;
	y = 2 * y - 1;
	n = 2 * n + 1;

	for (int i = y; i < n + y; i++)
		if (board[x][i]==0 || board[x+n-1][i]==0)
			{found = 0; goto end;}
	for (int i = x; i < n + x; i++)
		if (board[i][y]==0 || board[i][y+n-1]==0)
			{found = 0; goto end;}
//	printf("found=%d\n", found);
	end:
	return found ? 1 : 0;
}
