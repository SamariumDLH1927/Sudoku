#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdio>

using namespace std;

int initial[9][9];
int final[9][9];
int state[9][9][9] = {0};
int statenum[9][9];
int numrowstate[9][9] = {0};
int numcolstate[9][9] = {0};
int numblkstate[9][3][3] = {0};
	

void delpossi(int m, int n, int num)
{
	for(int i = 0; i < 9; i++)
	{
		state[m][i][num] = 1;
		state[i][n][num] = 1;
		state[m][n][i] = 1;
		for(int j = (m/3)*3; j < (m/3)*3 +3; j++)
		{
			for(int k = (n/3)*3; k < (n/3)*3 +3; k++)
			{
				state[j][k][num] = 1;
			}
		}
	}
	numrowstate[num][m] = 1;
	numcolstate[num][n] = 1;
	numblkstate[num][m/3][n/3] = 1;
}

void filein()
{
	FILE *fp;
	if((fp = fopen("D:\\sudoku.txt", "r")) == NULL)
	{
		printf("failed to open the file\n");
		exit(0);
	}
	else
	{
		printf("succeeded in opening\n");
		int tempin;
		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				fscanf(fp, "%d", &tempin);
				initial[i][j] = tempin;
				if(tempin)
				{
					final[i][j] = initial[i][j];
					statenum[i][j] = 9;
					delpossi(i, j, final[i][j]-1);
				}
				else
				{
					statenum[i][j] = 0;
				}
			}
		}
	}
}

int scanthenum()
{
	int continuescan = 0;
	for(int n = 0; n < 9; n++)
	{
		for(int i = 0; i < 9; i++)
		{
			if(numrowstate[n][i] == 0)
			{
				int t = 0;
				int tempzero;
				for(int j = 0; j < 9; j++)
				{
					t += state[i][j][n];
					if(state[i][j][n] == 0)
					{
						tempzero = j;
					}
				}
				if(t == 8)
				{
					final[i][tempzero] = n+1;
					delpossi(i, tempzero, n);
					continuescan++;
				}
			}
			if(numcolstate[n][i] == 0)
			{
				int t = 0;
				int tempzero;
				for(int j = 0; j < 9; j++)
				{
					t += state[j][i][n];
					if(state[j][i][n] == 0)
					{
						tempzero = j;
					}
				}
				if(t == 8)
				{
					final[tempzero][i] = n+1;
					delpossi(tempzero, i, n);
					continuescan++;
				}
			}
			if(numblkstate[n][i/3][i%3] == 0)
			{
				int t = 0;
				int tempzero1, tempzero2;
				for(int j = (i/3)*3; j < (i/3)*3 +3; j++)
				{
					for(int k = (i%3)*3; k < (i%3)*3 +3; k++)
					{
						t += state[j][k][n];
						if(state[j][k][n] == 0)
						{
							tempzero1 = j;
							tempzero2 = k;
						}
					}
				}
				if(t == 8)
				{
					final[tempzero1][tempzero2] = n+1;
					delpossi(tempzero1, tempzero2, n);
					continuescan++;
				}
			}
		}
	}
	return continuescan;
}

int scanthesudoku()
{
	int continuescan = 0;
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(statenum[i][j] < 9)
			{
				int tempzero;
				statenum[i][j] = 0;
				for(int k = 0; k < 9; k++)
				{
					statenum[i][j] += state[i][j][k];
					if(state[i][j][k] == 0)
					{
						tempzero = k;
					}
				}
				if(statenum[i][j] == 8)
				{
					final[i][j] = tempzero+1;
					delpossi(i, j, tempzero);
					continuescan++;
				}
			}
		}
	}
	return continuescan;
}

int check()
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(final[i][j] == 0)
			{
				return 1;
			}
		}
	}
	return 0;
}

void fileout()
{
	FILE *fp;
	fp = fopen("D:\\sudoku.txt", "w");
	for(int i = 0; i < 9; i++)
	{
		if(i&&!(i%3))
		{
			fprintf(fp, "\n");
		}
		for(int j = 0; j < 9; j++)
		{
			if(j&&!(j%3))
			{
				fprintf(fp, "  ");
			}
			fprintf(fp, "%d ", initial[i][j]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n\n\n");
	for(int i = 0; i < 9; i++)
	{
		if(i&&!(i%3))
		{
			fprintf(fp, "\n");
		}
		for(int j = 0; j < 9; j++)
		{
			if(j&&!(j%3))
			{
				fprintf(fp, "  ");
			}
			fprintf(fp, "%d ", final[i][j]);
		}
		fprintf(fp, "\n");
	}
}

int main()
{
	filein();
	while(scanthesudoku() + scanthenum())
	{
		;
	}
	fileout();
	return 0;
}
