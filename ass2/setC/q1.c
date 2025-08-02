#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct input
{
	char pname[10];
	int bt, at, tbt, ft, p;
} tab[10];

struct gantt
{
	int start, end;
	char pname[10];
} g[50], g1[20];

int n, i, k = 0, ct = 0, prev = 0;

int gethighpriority(int ct)
{
	int min = -1, processpos;

	for ( i = 0; i < n; i++)
	{
		if (tab[i].at <= ct && tab[i].tbt != 0 && tab[i].p > min)
		{
			min = tab[i].p;
			processpos = i;
		}
	}
	return processpos;
}

void getinput()
{
	printf("\nEnter No. of Processes: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		printf("\nProcess Name: ");
		scanf("%s", tab[i].pname);

		printf("Arrival Time: ");
		scanf("%d", &tab[i].at);

		printf("Burst Time: ");
		scanf("%d", &tab[i].bt);

		printf("Priority: ");
		scanf("%d", &tab[i].p);

		tab[i].tbt = tab[i].bt;
	}
}

void printinput()
{
	printf("\nPname\tAT\tBT");
	for (i = 0; i < n; i++)
	{
		printf("\n%s\t%d\t%d", tab[i].pname, tab[i].at, tab[i].bt);
	}
}

void sort()
{
	int j;
	struct input temp;

	for (i = 1; i < n; i++)
	{
		for (j = 0; j < n - 1; j++)
		{
			if (tab[j].at > tab[j + 1].at)
			{
				temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
			}
		}
	}
}

int arrived(int ct)
{
	for (i = 0; i < n; i++)
	{
		if (tab[i].at <= ct && tab[i].tbt != 0)
		{
			return 1;
		}
	}
	return 0;
}

void processoutput()
{
	int finish = 0;
	int current = -1;

	while (finish != n)
	{
		if (arrived(ct))
		{
			i = gethighpriority(ct);

			if (current != i)
			{
				g[k].start = ct;
				strcpy(g[k++].pname, tab[i].pname);
				current = i;
			}

			tab[i].tbt--;
			ct++;

			if (tab[i].tbt == 0)
			{
				tab[i].ft = ct;
				finish++;
			}

			g[k - 1].end = ct;
		}
		else
		{
			ct++;
			g[k].start = prev;
			g[k].end = ct;
			strcpy(g[k++].pname, "idle");
			prev = ct;
			current = -1;
		}
	}
}

void printoutput()
{
	int TTAT = 0, TWT = 0;
	float ATAT, AWT;

	printf("\n\n******Final Table******");
	printf("\nPname\tAT\tBT\tFT\tTAT\tWT");

	for (i = 0; i < n; i++)
	{
		int TAT = tab[i].ft - tab[i].at;
		int WT = TAT - tab[i].bt;
		printf("\n%s\t%d\t%d\t%d\t%d\t%d", tab[i].pname, tab[i].at, tab[i].bt, tab[i].ft, TAT, WT);
		TTAT += TAT;
		TWT += WT;
	}

	ATAT = (float)TTAT / n;
	AWT = (float)TWT / n;

	printf("\nTotal TAT = %d\nTotal WT = %d\nAverage TAT = %.2f\nAverage WT = %.2f", TTAT, TWT, ATAT, AWT);
}

void printganttchart()
{
	int j = 0;
	g1[0] = g[0];

	for (i = 1; i < k; i++)
	{
		if (strcmp(g1[j].pname, g[i].pname) == 0)
		{
			g1[j].end = g[i].end;
		}
		else
		{
			j++;
			g1[j] = g[i];
		}
	}

	printf("\n\n******Each Unit Gantt Chart******");
	for (i = 0; i < k; i++)
	{
		printf("\n%d\t%s\t%d", g[i].start, g[i].pname, g[i].end);
	}

	printf("\n\n******Final Gantt Chart******");
	for (i = 0; i <= j; i++)
	{
		printf("\n%d\t%s\t%d", g1[i].start, g1[i].pname, g1[i].end);
	}
}

int main()
{
	srand(time(0));
	getinput();

	printf("\n\nEntered data is:");
	printinput();

	sort();

	printf("\n\nData after sorting:");
	printinput();

	processoutput();
	printoutput();
	printganttchart();

	printf("\n\nRandomized Inputs:\n\n");

	for ( i = 0; i < n; i++)
	{	
		tab[i].tbt = tab[i].bt = rand() % 10+1; 
		tab[i].at = tab[i].ft+2;
	}

	processoutput();
	printoutput();
	printganttchart();

	return 0;
}
