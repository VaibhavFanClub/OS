#include<stdio.h>

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

void calcav()
{
    int i, j;
    int TR[10];
    int TA[10];
    
    for(i = 0; i < nor; i++)
        TA[i] = 0;
    
    printf("\nEnter total of each resource:\n");
    for(i = 0; i < nor; i++)
    {
        printf("%c: ", 65 + i);
        scanf("%d", &TR[i]);
    }
    
    for(j = 0; j < nor; j++)
    {
        for(i = 0; i < nop; i++)
        {
            TA[j] += A[i][j];  
        }
    }
    
    for(i = 0; i < nor; i++)
    {
        AV[i] = TR[i] - TA[i];
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

void displaydata()
{
	int i, j;
	
	printf("\n\tAllocation\t\tMAX\t\tNeed\n\t");
	for(i = 0; i < 3; i++)
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
		printf("\t");
		for(j=0; j<nor; j++)
			printf("%4d", N[i][j]);
	}
	printf("\nAvailable");
	for(i=0;i<nor;i++)
		printf("%4d", AV[i]);
}

int checkneed(int pno)
{
	int i;
	for(i = 0; i<nor; i++)
		if(N[pno][i]>AV[i])
			return 0;
	return 1;
}

void banker()
{
	int p=0, j=0, k=0, flag=0, safe[10];
	while(flag<2)
	{
		if(!finish[p])
		{
			printf("\n\nNeed of process P%d(,",p);
			for(j=0;j<nor;j++)
				printf("%d,", N[p][j]);
			if(checkneed(p))
			{
				printf(") <= Available(");
				for(j=0;j<nor;j++)
					printf("%d,",AV[j]);
				printf(")");
				
				printf("\nNeed is Satisfied, So process P%d can be granted required resources.\nAfter P%d finishes, it will release all the resources.", p, p);
				
				for(j=0;j<nor;j++)
					AV[j] = AV[j] + A[p][j];
					
				printf("New Available = ");
				for(j=0;j<nor;j++)
					printf("%d ",AV[j]);
				finish[p] = 1;
				safe[k++] = p;
			}
			else
			{
				printf(") > Available (");
				for(j = 0;j<nor;j++)
					printf("%d,", AV[j]);
				printf(")");
				
				printf("\nNeed is not satisfied, So process P%d cannot be granted required resources.\nProcess P%d has to wait.", p, p);
			}
		}
		if((p+1)%nop == 0)
			flag++;
		p = (p+1)%nop;
	}
	
	if(k == nop)
	{
		printf("\nSystem is in Safe state...");
		printf("\nSafe Sequence: ");
		for(j=0;j<k;j++)
			printf("P%d->", safe[j]);	
	}
	else{
		printf("\nSystem is NOT in Safe state...");
	}
}

int main()
{
	printf("\nEnter No. of Processes: ");
	scanf("%d", &nop);
	
	printf("\nEnter No. of Resources: ");
	scanf("%d", &nor);
	
	printf("\nEnter Allocation Matrix: ");
	acceptdata(A);
	
	printf("\nEnter Max Matrix: ");
	acceptdata(M);
	
	printf("\nEnter Total: ");
	calcav();
	calcneed();
	displaydata();
	banker();
	
	return 0;
}

