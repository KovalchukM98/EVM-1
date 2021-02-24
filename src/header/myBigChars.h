#pragma once

#include "myTerm.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

/*
    enter_alt_charset_mode=^N
    exit_alt_charset_mode=^O
    acs_chars=++\054\054--..00__``aaffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz{{||}c~~
*/

#define LINE_HORIZONTAL "q"
#define LINE_VERTICAL "x"

#define CORNER_LEFT_TOP "l"
#define CORNER_RIGHT_TOP "k"
#define CORNER_RIGHT_BOTTOM "j"
#define CORNER_LEFT_BOTTOM "m"

#define SMACS "\E(0"
#define RMACS "\E(B"

#define BLACK_CHAR "a"

int bc_printA (const char * str){
	printf(SMACS);
    if(printf("%s", str) < 0) {
        return -1;
    }
    printf(RMACS);
	return 0;
}

// void temp()
// {
//     printf("\E(0%c\E(B", BLACK_CHAR);
//     for(char ch = 'a'; ch < 'z'; ch++) printf("\E(0%c\E(B", ch);
//     printf("\n");
//     for(char ch = 'A'; ch < 'Z'; ch++) printf("\E(0%c\E(B", ch);
//     printf("\n");
// }

int bc_box(int x1, int y1, int x2, int y2){
	printf(SMACS);
	mt_gotoXY(x1, y1);
    printf(CORNER_LEFT_TOP);
	for(int i = y1 + 1; i < y2 + y1; ++i){
		printf(LINE_HORIZONTAL);
	}
    printf(CORNER_RIGHT_TOP);
	for(int i = x1 + 1; i <= x2; ++i){
		mt_gotoXY(i, y1);
		printf(LINE_VERTICAL);
		mt_gotoXY(i, y2 + y1);
		printf(LINE_VERTICAL);
	}
	mt_gotoXY(x2, y1);
    printf(CORNER_LEFT_BOTTOM);
	for(int i = y1 + 1; i < y2 + y1; ++i){
		printf(LINE_HORIZONTAL);
	}
    printf(CORNER_RIGHT_BOTTOM);
    printf(RMACS);
    printf("\n");
	return 0;
}

int bc_printbigchar (int [2], int x, int y, enum colors, enum colors) {
	int value;
	for (int j = 0; j < 8; ++j) {
        mt_gotoXY(x, (y + j));
        for (int i = 0; i < 8; ++i) {
            bc_printA((value == 1) ? (BLACK_CHAR) : (" "));
        }
    }
	return 0;
}

int bc_setbigcharpos (int * big, int x, int y, int value) {
	return 0;
}

int bc_getbigcharpos(int * big, int x, int y, int *value){
	return 0;
}

int bc_bigcharwrite (int fd, int * big, int count){
	return 0;
}

int bc_bigcharread (int fd, int * big, int need_count, int * count){
	return 0;
}

