#include<stdio.h>
#include "fn.h"


int main ()
{
	int read_array[11][3]    ={0};
	int allocated_array[5][3]={0};//{{0,0,1},{1,0,0},{1,3,5},{0,6,3},{0,0,1}};
	int max_array[5][3]      ={0};//{{9,0,1},{1,7,5},{2,3,5},{0,6,5},{0,6,5}};
	int available_array[3]   ={0};//{1,5,2};
	int need_array[row][col] ={0};
	int finish_array[row]    ={0};
	int process_sequence[row]={0}; 
	int i = 0,g=0,safe_state= 1;
	int counter_finished_processes = 0,counter_finished_processes_previous = 1;
	
	//read file
	int start=0,k=0;
	char filename[20];
	FILE *cfptr; // pointer to locate the address in the read file.
				// at initiate the pointer point to first address in the read file.
	do{
	printf("Enter file name + its extention:\n");
	scanf("%[^\n]s",&filename);
	for (k=0;k<=20;k++)
	{
		if(filename[k]== '.') {start =1;}
	}
	}while(start!=1);

	if((cfptr = fopen(filename,"r"))==NULL)
	{
			printf("file can't be opened");
	}
	else
	{
		printf("succeffuly opened tha file :D\n");
		while(!feof(cfptr)&&(fscanf(cfptr,"%d%d%d",&read_array[i][0],&read_array[i][1],&read_array[i][2])==3))
		{
		i++;
		}
	}
	//***** put split data from read array
	for (i=0;i<11;i++)
	{
		if(i<5) // allocated_array
		{
			for (g=0;g<col;g++)
			{
				allocated_array[i][g]=read_array[i][g];
			}
		}
		else if ((i >= 5)&&(i < 10))
		{
			for (g=0;g<col;g++)
			{
				max_array[i-5][g]=read_array[i][g];	
			}	
		}
		else {
			for (g=0;g<col;g++)
			{
				available_array[g]=read_array[i][g];	
			}
		}		
	}
	
	//********************
	//print allocated_array
	printf("Allocated array\n");
	for (i=0;i<row;i++)
	{
		for (g=0;g<col;g++)
		{
			printf("%d ",allocated_array[i][g]);
		}
		printf("\n");
	}
	//print max_array
	printf("max array\n");
	for (i=0;i<row;i++)
	{
		for (g=0;g<col;g++)
		{
			printf("%d ",max_array[i][g]);
		}
		printf("\n");
	}
	//print available_array
	printf("available array\n");
	
		for (g=0;g<col;g++)
		{
			printf("%d ",available_array[g]);
		}
		printf("\n");
	// calculate need array
	printf("need array\n");
	for (i=0;i<row;i++)
	{
		for (g=0;g<col;g++)
		{
			need_array[i][g]=max_array[i][g] - allocated_array[i][g];
			printf("%d ",need_array[i][g]);
			if(need_array[i][g] < 0) safe_state=0;
		}
		printf("\n");
	}
	//****************
	if(safe_state==1){
		while ((check_finish_processes(finish_array) != 1)&& (counter_finished_processes!=counter_finished_processes_previous))
		{ 
			counter_finished_processes_previous = counter_finished_processes;
				for (i = 0;i<row;i++)
				{
				
				if (finish_array[i] != 1)
					{
						if ((need_array[i][0]<=available_array[0])&&(need_array[i][1]<=available_array[1])&&(need_array[i][2]<=available_array[2]))
						{
							finish_array[i]=1;
							process_sequence[counter_finished_processes]=i;
							printf("finished:%d\n",i);
							//printf("counter_finished_processes_previous:%d\n",counter_finished_processes_previous);
							for (g=0 ; g<col ;g++)
							{
								available_array[g]+=allocated_array[i][g];
						
							}
							counter_finished_processes++;
						}
					}
				}		
		}
	}
	if (counter_finished_processes == 5)
	{
		for(i=0 ;i<row;i++)
		{
		printf("%d ",process_sequence[i]);
		}
	}
	else
		printf("unsafe condition :(");
}