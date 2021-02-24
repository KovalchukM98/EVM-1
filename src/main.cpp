#include "header/sc.h"
#include "header/myTerm.h"
#include "header/myBigChars.h"
//#include <ncurses.h>

int main()
{
    // int *arr = sc_memoryInit();
    // int *command = new int;
    // int *sc_command = new int;
    // int *operand = new int;
    // sc_memorySet(101, 1);
    // sc_memorySet(10, 1);
    // int mem_value = 0;
    // sc_memoryGet(10, &mem_value);
    // std::cout << mem_value << "\n\n";
    // sc_memoryGet(101, &mem_value);
    // const char *filename = "file.txt";
    // sc_memorySave(filename);
    // sc_memoryLoad(filename);
    // sc_memoryGet(10, arr);
    // sc_commandEncode(51, 89, sc_command);
    // std::cout << "\nsc_command(10)= " << *sc_command << "\n";
    // sc_commandDecode(*sc_command, command, operand);
    // sc_regInit();
    // sc_regSet(1,1);
    // int *reg_value = new int;
    // sc_regGet(1,reg_value);
    // mt_clrscr();
    // escape_commands();
    // mt_setfgcolor(GREEN);
    // mt_setbgcolor(BLUE);
    // std::cout << "Check string.\E[00m\n";
    // int col = 0, row = 0;
    // mt_getscreensize(row, col);
    // mt_gotoXY(10, 10);
    mt_clrscr();
    bc_box(1, 5, 8, 8);
    char* ch = new char[3];
    strcpy(ch, "a");
    bc_printA(ch);
    printf("\n");
    //temp();
    int bigchar[2];
    bigchar[0] = 0x10101010;
    bigchar[1] = 0x101010FF;
    mt_clrscr();
    bc_printbigchar(bigchar, 1, 1, BLACK, BLACK);
    return 0;
}