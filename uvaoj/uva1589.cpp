#include <stdio.h>
#include <string.h>

#define MAXR 15
#define MAXC 15

int board[MAXR][MAXC];
int loca[10][4];
char piece[10];

int judge(int x, int y, int n);
int gen(int x, int y, int i);
int cha(int x, int y, int i);
int can(int x, int y, int i);
int hor(int x, int y, int i);

int main()
{
	int rev, n, x, y;
	while ((rev=scanf("%d%d%d", &n, &x, &y)) && n)
	{
		memset(board, 0, sizeof(board));
		memset(loca, 0, sizeof(loca));
		memset(piece, '\0', sizeof(piece));

		for (int i = 0; i < n; i++) {
			rev = scanf("%s%d%d", &piece[i], &loca[i][0], &loca[i][1]);
			board[loca[i][0]][loca[i][1]] = 1;
		}

		int mate = 1;
		if (x - 1 > 0)
			if ((mate = judge(x-1, y, n)) == 0)
				goto end;
		if (x + 1 < 4)
			if ((mate = judge(x+1, y, n)) == 0)
				goto end;
		if (y - 1 > 3) 
			if ((mate = judge(x, y-1, n)) == 0)
				goto end;
		if (y + 1 < 7) 
			if ((mate = judge(x, y+1, n)) == 0)
				goto end;
		
		end:
		printf("%s\n", mate ? "YES" : "NO");
	}
	return 0;
}

int judge(int x, int y, int n)
{
	int mate = 0;
//	printf("x %d y %d\n", x, y);
	for (int i = 0; i < n; i++) {
		switch (piece[i]) {
			case 'G':
				mate = gen(x, y, i);
//				mate = 0;
				break;
			case 'R':
				mate = cha(x, y, i);
//				mate = 0;
				break;
			case 'H':
				mate = hor(x, y, i);
				break;
			case 'C':
				mate = can(x, y, i);
				break;
		}
		if (mate == 1) break;
	}
//	printf("mate %d\n", mate);
	return mate;
}

int gen(int x, int y, int i)
{
	int block = 1;
	int m = loca[i][0], n = loca[i][1];

	if (n == y) {
		block = 0;
		for (int j = x + 1; j < m; j++)
			if (board[j][y] == 1) {
				block = 1;
				break;
			}
	}
//	printf("G block %d\n", block);
	return block ? 0 : 1;
}

int cha(int x, int y, int i)
{
	int block = 1;
	int start, end;
	int m = loca[i][0], n = loca[i][1];
	
	if (x == m && y == n) goto end;
	if (m == x) {
		block = 0;
		if (n > y) {start = y; end = n;}
		else {start = n; end = y;}
		for (int j = start + 1; j < end; j++) {
			if (board[x][j] == 1) {
				block = 1;
				break;
			}
		}
	} else if (n == y) {
		block = 0;
		if (m > x) {start = x; end = m;}
		else {start = m; end = x;}
		for (int j = start + 1; j < end; j++) {
			if (board[j][y] == 1) {
				block = 1;
				break;
			}
		}
	}
	end:
//	printf("R block %d\n", block);
	return block ? 0 : 1;
}

int can(int x, int y, int i)
{
	int mate = 0;
	int block, start, end;
	int m = loca[i][0], n = loca[i][1];
		
	if (m == x) {
		block = 0;
		if (n > y) {start = y; end = n;}
		else {start = n; end = y;}
		for (int j = start + 1; j < end; j++) {
			if (board[x][j] == 1) {
				block++;
			}
		}	
	} else if (n == y) {
		block = 0;
		if (m > x) {start = x; end = m;}
		else {start = m; end = x;}
		for (int j = start + 1; j < end; j++) {
			if (board[j][y] == 1) {
				block++;
			}
		}
	}
	if (block == 1) mate = 1;
	return mate;
}

int hor(int x, int y, int i)
{
	int mate = 0;
	int	m = loca[i][0],	n = loca[i][1];

	if ((n-2 == y) && (board[m][n-1] == 0))
		if ((m-1 == x) || (m+1 == x)) {
			mate = 1;
			goto end;
		}
	if ((n+2 == y) && (board[m][n+1] == 0))
		if ((m-1 == x) || (m+1 == x)) {
			mate = 1;
			goto end;
		}
	if ((m-2 == x) && (board[m-1][n] == 0))
		if ((n-1 == y) || (n+1 == y)) {
			mate = 1;
			goto end;
		}	
	if ((m+2 == x) && (board[m+1][n] == 0))
		if ((n-1 == y) || (n+1 == y)) {
			mate = 1;
			goto end;
		}
	end:
	return mate;
}
