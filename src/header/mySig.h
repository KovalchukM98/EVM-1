#pragma once

#include "myTerm.h"
#include <stdio.h>
#include "sc.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <fstream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

/*struct itimerval {
	struct timeval it_interval; //следующее значение
	struct timeval it_value; // текущее значение
};

struct timeval {
	long tv_sec; // секунды 
	long tv_usec; // микросекунды
};*/

void reset_sig_handler(int signo){
	printf("типо сделали сброс настроек\n");
}

void sig_handler(int signo){
	int flag;
	sc_regGet(timer_ignore_flag, &flag);
	if(flag == 0) {
		printf("таймер отключен\n"); //ничего не должно происходить
		return;
	}
	printf("таймер работает\n");  // значение регистра instructionCounter увеличивалось на 1
}

unsigned int set_my_alarm(unsigned int sec){
	struct itimerval nval, oval;
	signal (SIGALRM, sig_handler);

	nval.it_interval.tv_sec = sec;
	nval.it_interval.tv_usec = 0;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;

	/* Запускаем таймер */
	setitimer (ITIMER_REAL, &nval, &oval);
	pause();
}

void set_reset_sig(){
	signal (SIGUSR1, reset_sig_handler);
}

//int setitimer(int which, const struct itimerval *value, struct itimerval *ovalue);

