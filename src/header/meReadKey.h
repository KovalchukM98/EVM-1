#pragma once

#include "myTerm.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <fstream>
#include <fcntl.h>
#include <termios.h>

//#define KEY_F5 "\E[15~"
//#define KEY_F6 "\E[17~" 

struct termios savetty;
struct termios tty;

enum keys{
	F5 = 0,
	F6
};

int rk_readkey (enum keys &key){
	char *c = (char*)malloc(sizeof(char));
	scanf("%c", c);
	if(c == '5'){
		key = F5;
	} else if( c == '6'){
		key = F6;
	}
	free(c);
}

int rk_mytermsave (void){
	FILE *fp = fopen("term_setting.txt", "w");
	fprintf(fp, "%d\n", 1); //а что писать то?
	fclose(fp);
}

int rk_mytermrestore (void){
	FILE *fp = fopen("term_setting.txt", "r");
	fscanf(fp, "%d", 1);
	fclose(fp);
}

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint){
	if(regime != 0){
		tcgetattr (0, &tty);
		//savetty = tty;
		tty.c_lflag &= ~(ICANON);
		tty.c_cc[VMIN] = vmin;
		tty.c_cc[VTIME] = vtime;
		if(echo == 0){
			tty.c_lflag &= ~(ECHO);
		} else{
			tty.c_lflag |= ECHO;
		}
		if(sigint == 0){
			tty.c_lflag &= ~(ISIG);
		} else{
			tty.c_lflag |= ISIG;
		}
		tcsetattr (0, TCSAFLUSH, &tty);

	} else{
		tcsetattr (0, TCSAFLUSH, &savetty);
	}
}