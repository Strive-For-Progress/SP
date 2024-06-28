#include <stdio.h>
#include "apue.h"

void accumulation(int d_sum);

int main()
{
	FILE* sum;
	int total_sum=0;
	pid_t pid[5];
	int year=5, week=52, day=7;
	TELL_WAIT();
	
	sum = fopen("sum.txt", "w");
	fprintf(sum, "%d\n", 0);
	fclose(sum);

	/**********************************************************/
	int i;
	
	for ( i=0 ; i<5 ; i++)  {
		if ((pid[i] = fork()) < 0) err_sys("fork error");
		else if (pid[i]==0) break;
	}

	if (pid[i] == 0) {
		int value=0, cnt = 0, d_sum =0;
			char filename[10];
			for (int j =0 ; j < week ;j++) {		
				sprintf(filename, "%d-%02d.txt", i+1, j+1);
				FILE* fp = fopen(filename, "r");
				while (fscanf(fp, "%d", &value) != EOF){
					d_sum += value;
					cnt++;
					if (cnt == 96) { //a day
						WAIT_PARENT(); 
						accumulation(d_sum);
						TELL_PARENT(getppid());
						cnt = d_sum = 0;
					}
				} 
			}
			exit(0);
	}
	else {
		for (int j=0 ; j<year*week*day ;j++) {
			TELL_CHILD(pid[i]);
			WAIT_CHILD();
		}
	}
	
	/**********************************************************/



	sum = fopen("sum.txt", "r");
	fscanf(sum, "%d", &total_sum);
	printf("Day_Average = %d\n",total_sum/(year*week*day));
	fclose(sum);

	return 0;
}

void accumulation(int d_sum)    //Accumulating the daily sum to "sum.txt".
{
	FILE* sum;
	int tmp=0;

	sum = fopen("sum.txt", "r+");
	fscanf(sum, "%d", &tmp);

	tmp += d_sum;

	rewind(sum);
	fprintf(sum, "%d", tmp);
	fclose(sum);

	return;
}