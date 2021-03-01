#pragma once

#include "myTerm.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <fstream>

//#define KEY_F5 "\E[15~"
//#define KEY_F6 "\E[17~" 

enum keys{
	F5 = 0,
	F6,
}

int rk_readkey (enum keys *key){
	char c;
	getch(c);
}

int rk_mytermsave (void){
	std::ofstream out("term_setting.txt");
	
	out.close();
}

int rk_mytermrestore (void){
	std::ifstream in("term_setting.txt");
	//чтение и установка всяких цветов текста и фона?
	in.close();
}

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint){

}