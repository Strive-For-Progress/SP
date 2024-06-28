#include "apue.h"

int main(void)
{
	char buf[MAXLINE];
	int cnt = 0 ;	
	FILE* fp = fopen ("100mb_file","r");
	while( (fgets(buf,MAXLINE,fp)) != NULL ) {
		if(fputs(buf,stdout) == EOF)
			err_sys("output error");
		cnt++;
	}
	if(ferror(fp))
		err_sys("input error");
	printf("Loop Iterations : %d\n",cnt);
	exit(0);
}

