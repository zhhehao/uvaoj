#include <stdio.h>

int main()
{
	int rev, can;

	while (1)
	{
		int s[6][2];
		int sc[15];

		for (int i = 0; i < 6; i++)
			if (rev=scanf("%d%d", &s[i][0], &s[i][1]) == EOF)
				goto bye;

		sc[0] = s[0][0];
		int q = 1;
	    for (int i = 0; i < 6; i++)
			for (int j = 0; j < 2; j++)
			{
				int eq = 1;
				for (int k = 0; k < q; k++)
					if (sc[k] == s[i][j]) {eq = 0; break;}
				if (eq) {sc[q] = s[i][j]; q++;}
			}

		if (q == 1) {can = 1; goto out;}
		if (q > 3) {can = 0; goto out;}
		if (q == 2)
		{
			int com = 0;
			for (int i = 0; i < 6; i++)
				if (s[i][0] == s[i][1])
					com++;
			if (com == 2)
				{can = 1; goto out;}
			else
				{can = 0; goto out;}
		}
		if (q == 3)
		{
			int com = 0;
			for (int i = 0; i < 6; i++)
				if ((s[i][0]==sc[0] && s[i][1]==sc[1])||(s[i][0]==sc[1] && s[i][1]==sc[0]))
					com++;	
			if (com != 2) {can = 0; goto out;}

			com = 0;
			for (int i = 0; i < 6; i++)
				if ((s[i][0]==sc[0] && s[i][1]==sc[2])||(s[i][0]==sc[2] && s[i][1]==sc[0]))
					com++;
			if (com != 2) {can = 0; goto out;}

			com = 0;
			for (int i = 0; i < 6; i++)
				if ((s[i][0]==sc[1] && s[i][1]==sc[2])||(s[i][0]==sc[2] && s[i][1]==sc[1]))
					com++;
			if (com != 2) {can = 0; goto out;}
			else {can = 1; goto out;}

		}


		out:
		if (can)
			printf("POSSIBLE\n");
		else
			printf("IMPOSSIBLE\n");
	}	
	bye:
	return 0;
}
