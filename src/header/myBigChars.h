#pragma once

#include <iostream>
#include <stdio.h>
#include <sys/ioctl.h>

int bc_printA (char * str){
	if(printf("\E(0 \E[0%s \E(B", str) < 0) {
        return -1;
    }
	return 0;
}

int bc_box(int x1, int y1, int x2, int y2){
	printf("\E[0%d;%dH", x1, y1);
	for(int i = y1; i < y2; ++i){
		printf("%c",'=' );
	}
	for(int i = x1+1; i <= x2; ++i){
		printf("\E[0%d;%dH", i, y1);
		printf("%c", '=');
		printf("\E[0%d;%dH", i, y2);
		printf("%c", '=');
	}
	printf("\E[0%d;%dH", x2, y1);
	for(int i = y1; i < y2; ++i){
		printf("%c",'=' );
	}
	return 0;
}

int bc_printbigchar (int [2], int x, int y, enum color, enum color) {
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

/*
    enter_alt_charset_mode=^N
    exit_alt_charset_mode=^O
    acs_chars=++\054\054--..00__``aaffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz{{||}c~~
*/