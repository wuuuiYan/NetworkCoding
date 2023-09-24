#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//用途：父进程监控子进程的状态

//run model: ./a.out 10 5 15  (three child process, after 10, 5, 15 seconds, they are over)
int main(int argc, char *argv[])
{
	pid_t child_pid;
	int numDead; //记录结束的子进程的个数
	int i;

	for(i = 1; i < argc; i ++) //三次循环，创建三个子进程
	{
		switch(fork())
		{
			case -1: //调用失败
				perror("fork()");
				exit(0);
			case 0: //子进程执行
				printf("Child %d started with PID = %d, sleeping %s seconds\n", i, getpid(), argv[i]);
				sleep(atoi(argv[i])); //传入的参数本质是字符串，需要转化为数字
				exit(0); //创建完一个子进程之后必须退出，不再循环
			default: //父进程执行
				break;
		}
	}

	numDead = 0;

	while(1)
	{
		child_pid = wait(NULL); //wait()函数将返回结束(NULL)的子进程的id号

		if(child_pid == -1) //所有的子进程全部结束
		{
			printf("No more children, Bye bye!\n");
			exit(0);
		}

		numDead++;
		printf("wait() returned child PID : %d(numDead = %d)\n", child_pid, numDead);
	}
}
