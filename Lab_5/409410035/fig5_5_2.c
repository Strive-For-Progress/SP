#include "apue.h"
#define	Fully_buffered  1
#define	Line_buffered 2
#define	unbuffered  3

// This is the program for Part2

int main(int argc , char** argv)
{
	char buf[MAXLINE];
	FILE* fp = fopen ("100mb_file","r");
	FILE* fp2 = fopen ("/dev/null","w+");
	int cmd = 0;
	sscanf(argv[1], "%d", &cmd);	
	switch (cmd) {
		case Fully_buffered : setvbuf(fp, buf, _IOFBF, MAXLINE); break;
		case Line_buffered : setvbuf(fp, buf, _IOLBF, MAXLINE); break;
		case unbuffered : setvbuf(fp, buf, _IONBF, MAXLINE) ; break;
	}

	while( (fgets(buf,MAXLINE,fp)) != NULL ) 
		if(fputs(buf,fp2) == EOF)
			err_sys("output error");
		
	if(ferror(fp))
		err_sys("input error");


	fclose(fp);
	exit(0);
}

