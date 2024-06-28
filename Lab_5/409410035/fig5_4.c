#include "apue.h"

int main(void)
{

	int c,cnt=0;
	FILE* target = fopen ("100mb_file","r");
	while( (c = getc(target)) != EOF ) {
		if(putc(c,stdout) == EOF)
			err_sys("output error");
		cnt++;
	}
		
		
	if(ferror(target))
		err_sys("input error");
	printf("Loop Iterations : %d\n",cnt);
	
	exit(0);
}

