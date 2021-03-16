#pragma once

#include "myTerm.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <fstream>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>

//#define KEY_F5 "\E[15~"
//#define KEY_F6 "\E[17~" 
struct termios terminal_settings;
struct termios savetty;
struct termios tty;

int number_of_mem_cell;

enum keys{
	F5 = 0,
	F6,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	QUIT,
	LOAD,
	SAVE,
	KEY_i
};

int rk_mytermsave(void) // запись в termios структуру
{
	if (tcgetattr(0, &terminal_settings)) {
		return 1;
	}
	
	return 0;
}

int rk_mytermrestore(void)
{
	if (tcsetattr(0, TCSANOW, &terminal_settings)){
		return 1;
	}

	return 0;
}

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint){
	struct termios new_settings;
	rk_mytermsave();
	new_settings = savetty;

	if (regime == 1) {
		new_settings.c_lflag &= (~ICANON);

		if (sigint == 1) {
			new_settings.c_lflag &= (~ISIG);
		} else if (sigint == 0) {
			new_settings.c_lflag |= ISIG;
		}

		if (echo == 1) { 
			new_settings.c_lflag &= (~ECHO);
		} else if (echo == 0) {
			new_settings.c_lflag |= ECHO;
		}

		new_settings.c_cc[VMIN] = vmin;		
		new_settings.c_cc[VTIME] = vtime;
	} else if (regime == 0) {
		new_settings.c_lflag |= ICANON;
	}

	tcsetattr(0, TCSANOW, &new_settings);
	return 0;
}


int rk_readkey (enum keys *key){
	rk_mytermregime(1, 0, 1, 1, 1);
	char *c = (char*)calloc(8,sizeof(char));
	read(0, c, 8);
	if(strcmp(c, "\E[15~") == 0){
		*key = F5;
		
	} else if(strcmp(c, "\E[17~") == 0){
		*key = F6;
		
	} else if(strcmp(c, "\E[A") == 0){
		*key = KEY_UP;
		
	} else if(strcmp(c, "\E[B") == 0){
		*key = KEY_DOWN;
		
	} else if(strcmp(c, "\E[C") == 0){
		
		*key = KEY_RIGHT;
		
	} else if(strcmp(c, "\E[D") == 0){
		*key = KEY_LEFT;
		
	} else if(c[0] == 'q'){
		
		*key = QUIT;
	} else if(c[0] == 's'){
		*key = SAVE;
		
		rk_mytermsave();
	} else if(c[0] == 'l'){
		*key = LOAD;
		
		rk_mytermrestore();
	} else if(c[0] == 'i'){
		*key = KEY_i;
		
	}
	rk_mytermregime(0, 0, 1, 1, 1);
	free(c);
	return 0;
}


