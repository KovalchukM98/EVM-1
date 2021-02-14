#include "header/sc.h"
#include "header/myTerm.h"

int main()
{
    int *arr = sc_memoryInit();
    int *command = new int;
    int *sc_command = new int;
    int *operand = new int;
    sc_memorySet(101, 1);
    sc_memorySet(10, 1);
    int mem_value = 0;
    sc_memoryGet(10, &mem_value);
    std::cout << mem_value << "\n\n";
    sc_memoryGet(101, &mem_value);
    const char *filename = "file.txt";
    sc_memorySave(filename);
    sc_memoryLoad(filename);
    sc_memoryGet(10, arr);
    sc_commandEncode(51, 89, sc_command);
    std::cout << "\nsc_command(10)= " << *sc_command << "\n";
    sc_commandDecode(*sc_command, command, operand);
    sc_regInit();
    sc_regSet(1,1);
    int *reg_value = new int;
    sc_regGet(1,reg_value);
    mt_clrscr();
    escape_commands();
    mt_setfgcolor(GREEN);
    mt_setbgcolor(BLUE);
    std::cout << "Check string.\E[00m\n";
    
    return 0;
}
