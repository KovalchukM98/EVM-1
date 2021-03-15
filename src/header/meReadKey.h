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
struct termios terminal_settings;
struct termios savetty;
struct termios tty;

enum keys{
	F5 = 0,
	F6,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	QUIT,
	LOAD,
	SAVE
};

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint){
	if(regime != 0){
		tcgetattr (0, &tty);
		savetty = tty;
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
		// TCSANOW.  Немедленное  выполнение  изменений
		// TCSADRAIN.Выполняет ту же функцию, что и TCSANOW, 
		//  но пе-ред установкой новых параметров ждѐт опустошения очереди вывода
		// TCSAFLUSH.Аналогично TCSADRAIN ждѐт, пока очередь выво-да не опустеет,
		//  а затем также очищает и очередь ввода перед уста-новкой для параметров дисциплины линии связи значений, 
		//  задан-ных в структуре tnew

	} else{
		tcsetattr (0, TCSAFLUSH, &savetty);
	}
	return 0;
}

int rk_readkey (enum keys *key){
	rk_mytermregime(1, 0, 1, 1, 1);
	char *c = (char*)calloc(8,sizeof(char));
	read(0, c, 8);
	if(strcmp(c, "\E[15~") == 0){
		*key = F5;
		printf("f5");
	} else if(strcmp(c, "\E[17~") == 0){
		*key = F6;
		printf("f6");
	} else if(strcmp(c, "\E[A") == 0){
		*key = KEY_UP;
		printf("up");
	} else if(strcmp(c, "\E[B") == 0){
		*key = KEY_DOWN;
		printf("down");
	} else if(strcmp(c, "\E[C") == 0){
		*key = KEY_RIGHT;
		printf("right");
	} else if(strcmp(c, "\E[D") == 0){
		*key = KEY_LEFT;
		printf("left");
	} else if(c[0] == 'q'){
		*key = QUIT;
		printf("quit");
	} else if(c[0] == 's'){
		*key = SAVE;
		printf("save");
		rk_mytermsave();
	} else if(c[0] == 'l'){
		*key = LOAD;
		printf("load");
		rk_mytermrestore();
	} 
	rk_mytermregime(0, 0, 1, 1, 1);
	free(c);
	return 0;
}

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

