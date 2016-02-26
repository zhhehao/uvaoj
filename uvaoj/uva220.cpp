#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXN 12

char board[MAXN][MAXN];
int boardmove[MAXN][MAXN];

char rechar(void);
int list(char player);
void check(int x, int y, char player);
int dcheck(int x, int y, char player, int direction);
char move(int x, int y, char player);
void dmove(int x, int y, char player, int direction);

int main()
{
	int rev, n;
	rev = scanf("%d", &n);
	while (n--)
	{
		memset(board, '\0', sizeof(board));
		for (int i = 1; i <= 8; i++)
			rev = scanf("%s", board[i]+1);
		char player = rechar();
		char c;
		while ((c=rechar()) != 'Q')
		{
			if (c == 'L'){
//				printf("player is %c\n", player);
				int nolegal1 = list(player);
				int kase = 1;
				if (nolegal1)
					printf("No legal move.");
				else{
					for (int i = 1; i <= 8; i++)
						for (int j = 1; j <= 8; j++)
							if (boardmove[i][j] == 1){
								if (kase++ > 1) printf(" ");
								printf("(%d,%d)", i, j);
							}
				}
				printf("\n");
			}
			if (c == 'M'){
//				printf("player is %c\n", player);
				int x = rechar() - '0';
				int y = rechar() - '0';
				char vsplayer = (player == 'W') ? 'B' : 'W';
				int nolegal2 = list(player);
//				if (boardmove[x][y] != 1)
//					nolegal2 = 1;
				if (nolegal2)
					player = move(x, y, vsplayer);
//					{board[x][y] = player; player = vsplayer;}
				else
					player = move(x, y, player);
				int bc, wc;
				bc = wc = 0;
				for (int i = 1; i <= 8; i++)
					for (int j = 1; j <= 8 ; j++)
						if (board[i][j] == 'W')
							wc++;
						else if (board[i][j] == 'B')
							bc++;
				printf("Black - %2d White - %2d\n", bc, wc);
			}
		}
		for (int i = 1; i <= 8; i++)
			printf("%s\n", board[i]+1);
		if (n)
			printf("\n");
	}
	return 0;
}

void dmove(int x, int y, char player, int direction)
{
//	printf("dmove!\n");
	char vsplayer = (player == 'W') ? 'B' : 'W';
	int x1, y1;
	x1 = x; y1 = y;
	switch (direction){
		case 1:
			x1--;
			y1--;
			break;
		case 2:
			x1--;
			break;
		case 3:
			x1--;
			y1++;
			break;
		case 4:
			y1--;
			break;
		case 5:
			y1++;
			break;
		case 6:
			x1++;
			y1--;
			break;
		case 7:
			x1++;
			break;
		case 8:
			x1++;
			y1++;
			break;
	}
	if ((x1>0)&&(y1>0)&&(x1<9)&&(y1<9)){
		if (board[x1][y1] == vsplayer)
			dmove(x1, y1, player, direction);
		if (board[x1][y1] == player)
			board[x][y] = player;
	}
}

char move(int x, int y, char player)
{
	char vsplayer = (player == 'W') ? 'B' : 'W';
	board[x][y] = player;
	if (board[x-1][y-1]==vsplayer) dmove(x-1, y-1, player, 1);
	if (board[x-1][y]==vsplayer) dmove(x-1, y, player, 2);
	if (board[x-1][y+1]==vsplayer) dmove(x-1, y+1, player, 3);
	if (board[x][y-1]==vsplayer) dmove(x, y-1, player, 4);
	if (board[x][y+1]==vsplayer) dmove(x, y+1, player, 5);
	if (board[x+1][y-1]==vsplayer) dmove(x+1, y-1, player, 6);
	if (board[x+1][y]==vsplayer) dmove(x+1, y, player, 7);
	if (board[x+1][y+1]==vsplayer) dmove(x+1, y+1, player, 8);
	return vsplayer;
}

int list(char player)
{
	memset(boardmove, 0, sizeof(boardmove));	
//	printf("list\n");
//	int kase = 1;
	char vsplayer = (player == 'W') ? 'B' : 'W';
//	printf("vsplayer is %c\n", vsplayer);
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
			if (board[i][j] == vsplayer)
				check(i, j, player);
	int nolegal = 1;
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
			if (boardmove[i][j] == 1){
//				if (kase++ > 1) printf(" ");
//				printf("(%d,%d)", i, j);
				nolegal = 0;
			}
//	if (nolegal)
//		printf("No legal move.");
//	printf("\n");
	return nolegal;
}

void check(int x, int y, char player)
{
	int check;
//	printf("check\n");
	if ((x-1>0)&&(y-1>0)&&(board[x-1][y-1]=='-'))
		if (check=dcheck(x, y, player, 1))
			boardmove[x-1][y-1] = 1;
	if ((x-1>0)&&(board[x-1][y]=='-'))
		if (check=dcheck(x, y, player , 2))
			boardmove[x-1][y] = 1;
	if ((x-1>0)&&(y+1<9)&&(board[x-1][y+1]=='-'))
		if (check=dcheck(x, y, player, 3))
			boardmove[x-1][y+1] = 1;
	if ((y-1>0)&&(board[x][y-1]=='-'))
		if (check=dcheck(x, y, player, 4))
			boardmove[x][y-1] = 1;
	if ((y+1<9)&&(board[x][y+1]=='-'))
		if (check=dcheck(x,y, player, 5))
			boardmove[x][y+1] = 1;
	if ((x+1<9)&&(y-1>0)&&(board[x+1][y-1]=='-'))
		if (check=dcheck(x, y, player, 6))
			boardmove[x+1][y-1] = 1;
	if ((x+1<9)&&(board[x+1][y]=='-'))
		if (check=dcheck(x, y, player, 7))
			boardmove[x+1][y] = 1;
	if ((x+1<9)&&(y+1<9)&&(board[x+1][y+1]=='-'))
		if (check=dcheck(x, y, player, 8))
			boardmove[x+1][y+1] = 1;
}

int dcheck(int x, int y, char player, int direction)
{
	int move;
	char vsplayer = (player == 'W') ? 'B' : 'W';
//	printf("dcheck!\n");
	switch (direction){
		case 1:
			x++;
			y++;
			break;
		case 2:
			x++;
			break;
		case 3:
			x++;
			y--;
			break;
		case 4:
			y++;
			break;
		case 5:
			y--;
			break;
		case 6:
			x--;
			y++;
			break;
		case 7:
			x--;
			break;
		case 8:
			x--;
			y--;
			break;
	}
	if ((board[x][y]=='-')||(x<1)||(y<1)||(x>8)||(y>8))
		{move = 0; goto end;}
	if (board[x][y] == player)
		{move = 1; goto end;}
	if (board[x][y] == vsplayer)
		move = dcheck(x, y, player, direction);

	end:
	return move;
}

char rechar(void)
{
	char c;
	while (!isalnum(c=getchar()))
		;
	return c;
}
