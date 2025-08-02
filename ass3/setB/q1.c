#include<stdio.h>
#include<stdlib.h>

int nop, nor, A[10][10], M[10][10], AV[10], N[10][10], finish[10];

void acceptdata(int x[10][10])
{
	int i, j;
	
	for(i = 0; i< nop; i++)
	{
		printf("\nP%d\n",i);
		
		for(j = 0; j < nor; j++)
		{
			printf("%c: ", 65+j);
			scanf("%d", &x[i][j]);
		}
	}
}

void acceptav()
{
	int i;
	for(i=0; i<nor; i++)
	{
		printf("%c: ", 65+i);
		scanf("%d", &AV[i]);
	}
}

void calcneed()
{
	int i, j;
	
	for(i = 0; i<nop; i++)
	{
		for(j = 0; j < nor; j++)
		{
			N[i][j] = M[i][j] - A[i][j];
		}
	}
}

void displaydata(int allocM, int maxM, int needM, int avalM)
{
	int i, j;
	if(allocM == 1 && maxM == 1){
		printf("\n\tAllocation\t\tMAX\n\t");
		for(i = 0; i < 2; i++)
		{
			for(j=0;j<nor;j++)
			{
				printf("%4c", 65+j);
			}
			
			printf("\t");
		}
		
		for(i=0; i<nop; i++)
		{
			printf("\nP%d\t", i);
			for(j=0; j<nor; j++)
				printf("%4d", A[i][j]);
			printf("\t");
			for(j=0; j<nor; j++)
				printf("%4d", M[i][j]);
		}
	} else if (needM == 1){
		printf("\n\tNeed\n\t");
		for(i = 0; i < 1; i++)
		{
			for(j=0;j<nor;j++)
			{
				printf("%4c", 65+j);
			}
			
			printf("\t");
		}
		
		for(i=0; i<nop; i++)
		{
			printf("\nP%d\t", i);
			for(j=0; j<nor; j++)
				printf("%4d", N[i][j]);
		}
	}else if (avalM == 1){
		printf("\nAvailable");
		for(i=0;i<nor;i++)
			printf("%4d", AV[i]);
		printf("\n");			
	}
}


int main()
{
	int ch;
	
	printf("\nEnter No. of Processes: ");
	scanf("%d", &nop);
	
	printf("\nEnter No. of Resources: ");
	scanf("%d", &nor);
	
	printf("\nEnter Allocation Matrix: ");
	acceptdata(A);
	
	printf("\nEnter Max Matrix: ");
	acceptdata(M);
	
	while(1)
	{
		printf("\n1.Accept Available.\n2.Display Allocation, Max.\n3.Find Need and Display It.\n4.Display Available.\n5.Exit.");
		printf("\nEnter choice:");
		scanf("%d", &ch);
		switch(ch)
		{	
			case 1:
				printf("\nEnter Availability: \n");
				acceptav();
				break;
			case 2:
				displaydata(1, 1, 0, 0);
				break;
			case 3:
				calcneed();
				displaydata(0, 0, 1, 0);
				break;
			case 4:
				displaydata(0, 0, 0, 1);
				break;
			case 5:
				printf("\nExiting...\n");
				exit(0);
			default:
				printf("Invalid choice!\n");
		}
	}
	return 0;
}

