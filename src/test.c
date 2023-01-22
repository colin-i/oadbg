
//#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>

void main(){
//int e=execl("which","which","bash",(char *)NULL);
//If exec succeeds it will NEVER return. Succeeding means be able to find and launch the command. If it doesn't succeed it will return -1.

	//int e=system("which oadbg");
	//why this is 0?
	//return e;

	//int a=0; will crash chrome
	char a[]={2,0,0,0,'\"','\"'};
	write(fileno(stdout),&a,6);
	//fwrite(&a,4,1,stdout);
}
