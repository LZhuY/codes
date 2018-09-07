#include <stdio.h>
#include <signal.h>

#include <iostream>

void sigHandler(int sig){
	std::cout << "sig=" << sig << std::endl;
}

int main(){
	struct sigaction act,oldact;
	act.sa_handler  = sigHandler;
	act.sa_flags = SA_NODEFER | SA_RESETHAND;
	//sigprocmask(SIG_UNBLOCK, &block, NULL); 屏蔽信号
	sigemptyset(&act.sa_mask); //操作信号集，全部清空
	sigaction(SIGINT, &act, &oldact); //kill -INT pid sigaddset
	sigaction(SIGHUP, &act, &oldact); //kill -HUP pid
	while(1)sleep(5);
	return 0;
}