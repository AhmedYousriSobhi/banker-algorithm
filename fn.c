#include<stdio.h>
#include "fn.h"

int check_finish_processes(int *processes)
{
	int i = -1;
	int flag = 1;  // all finished
	for (i=0 ; i<5 ;i++)
	{
		if (processes[i]== 0)
			flag = 0;
	}
		
		return flag;
}