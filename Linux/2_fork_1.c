#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t pid1, pid2;

	//父进程返回子进程的id号(非零值)，子进程返回0
	pid1 = fork(); 
	//这一行语句执行的结果：通过拷贝调用进程(即父进程A)创建大儿子进程B，A、B进程都会执行下面的所有代码
	
	pid2 = fork();
	//这一行语句执行的结果：通过拷贝调用进程(即父进程A)创建小儿子进程C，A、C进程都会执行下面的所有代码
	//					  通过拷贝调用进程(即大儿子进程B)创建孙子进程D，B、D进程都会执行下面的所有代码

	//进程id号每次运行都会不一样
	printf("pid1 = %d, pid2 = %d\n", pid1, pid2);
	//最终会输出四行，这说明该程序最终创建了四个进程
	//从输出值中可以得到大儿子进程、小儿子进程和孙子进程的id号
	//要得到父进程的id号，需要调用getppid()函数

	return 0;
}
