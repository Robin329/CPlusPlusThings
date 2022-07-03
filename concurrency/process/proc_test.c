#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t fpid; //fpid表示fork函数返回的值
	int count = 0;

	fpid = fork();

	if (fpid < 0)
		printf("Create FAILED!\n");
	else if (fpid == 0) {
		printf("I'm child.\n");
		count++;
	} else {
		printf("I'M Parent.\n");
		count++;
	}
	printf("total result: %d\n", count);
	return 0;
}
