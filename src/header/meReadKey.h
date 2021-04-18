#pragma once

#include "myTerm.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <fstream>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>

//#define KEY_F5 "\E[15~"
//#define KEY_F6 "\E[17~" 
static struct termios terminal_settings;

int number_of_mem_cell;

enum keys{
	F5 = 0,
	F6,
	KEY_t,
	KEY_r,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	QUIT,
	LOAD,
	SAVE,
	KEY_i,
	KEY_1,
	UNREGISTERED_KEY,
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
	new_settings = terminal_settings;

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
		
	} else if (c[0] == '1') {
		*key = KEY_1;
	} else if(c[0] == 't'){
		*key = KEY_t;
	} else if(c[0] == 'r'){
		*key = KEY_r;
	} else{
		*key = UNREGISTERED_KEY;
	}
	rk_mytermregime(0, 0, 1, 1, 1);
	free(c);
	return 0;
}

int READ(int operand){
    int value;
    mt_gotoXY(25, 1);
    scanf("%d", &value);
    arr[column + 10*row] = value;
    return 0;
}

int WRITE(int operand){
	mt_gotoXY(25, 1);
	printf("%x", arr[column + 10*row]);
	return 0;
}

int LOAD_CMD(int operand){
	accumulator = arr[column + 10*row];
	return 0;
}

int STORE(int operand){
	arr[column + 10*row] = accumulator;
	return 0;
}

int ADD(int operand){
	accumulator += arr[column + 10*row];
	return 0;
}

int SUB(int operand){
	accumulator -= arr[column + 10*row];
	return 0;
}

int DIVIDE(int operand){
	accumulator /= arr[column + 10*row];
	return 0;
}

int MUL(int operand){
	accumulator *= arr[column + 10*row];
	return 0;
}

int JUMP(int operand){
	scanf("%d", &ind);
	column = ind % 10;
	row = ind / 10;
	return 0;
}

int JNEG(int operand){
	if(accumulator < 0){
		JUMP(operand);
	}
	return 0;
}

int JZ(int operand){
	if(accumulator == 0){
		JUMP(operand);
	}
	return 0;
}

int HALT(){
	sc_regSet(T_FLAG, 1);
	return 0;
}

int doComand(){
    // int command;
    // int operand;
    // int value = arr[column + (10 * row)];
    // printf("%s\n", "aaaaaaaaaaaaaa" );
    // if(sc_commandDecode(value, &command, &operand) || !isCommand(command)){
    // 	sc_regSet(E_FLAG, 1);
    //     return 1;
    // }
    // printf("%d\n", command );
    // switch(command){
    //     case 0x10: //read
    //         READ(operand);
    //         break;
    //     case 0x11: //write
    //     	WRITE(operand);
    //     	break;
    //     case 0x20: //load
    //     	LOAD_CMD(operand);
    //     	break;
    //     case 0x21: //store
    //     	STORE(operand);
    //     	break;
    //     case 0x30: //add
    //     	ADD(operand);
    //     	break;
    //     case 0x31: //sub
    //     	SUB(operand);
    //     	break;
    //     case 0x32: //divide
    //     	DIVIDE(operand);
    //     	break;
    //     case 0x33: //mul
    //     	MUL(operand);
    //     	break;
    //     case 0x40: //jump
    //     	JUMP(operand);
    //     	break;
    //     case 0x41: //jneg
    //     	JNEG(operand);
    //     	break;
    //     case 0x42: //jz
    //     	JZ(operand);
    //     	break;
    //     case 0x43: // halt
    //     	HALT(operand);
    //     	break;
    //     default:
    //         break;
    // }
    READ(1);
    return 0;
}

int Make_bin_comand(int adress, int command, int operand){
	//привести в бинарный вид и загрузить в память
	return 0;
}

int Get_comand_code(char *word, int size){
	return 228;
}

int Assembler_parse(char* str){
	int adress = 0;
	//int command = 0;
	int operand = 0;

	//парсим адресс
	char buf[2];
	buf[0] = str[0];
	buf[1] = str[1];
	adress = atoi(buf);
	if(adress > 99 || adress < 0){
		return 1;
	}

	//парсим слово
	int i = 2;
	while(str[i] == ' '){
		++i;
	}
	int j = i;
	while(str[j] != ' '){
		++j;
	}
	char *word = (char*)calloc(j-i, sizeof(char));
	int cnt = 0;
	while(i < j){
		word[cnt] = str[i];
		i++;
		cnt++;
	}
	//command = Get_comand_code(word, cnt); //дописать свич со всеми возможными командами

	//парсим операнд
	char c;
	while(str[i] == ' '){
		++i;
	}
	while(str[i] != ';' && str[i] != ' ' && str[i] != '\t'){
		c = str[i];
		operand = operand*10 + atoi(&c);
		i++;
	}
	printf("%d %s %d\n", adress, word, operand);
	Make_bin_comand(adress, command, operand);
	free(word);
	return 0;
}

int Assembler_read(){
	FILE* input;
	input = fopen("test", "r");
	if(input == NULL){
		return 1;
	}
	char str[50];
	int bufsize = 50;
	int cnt = 0;
	while(true){
		fgets(str, bufsize, input);
		//printf("%s", str);
		if(Assembler_parse(str) != 0){
			break;
		}
		cnt++;
		if(feof(input) || cnt == 100){
			break;
		}
	}
	fclose(input);
	return 0;
}