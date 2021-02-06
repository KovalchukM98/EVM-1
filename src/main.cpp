#include "header/sc.h"

int main()
{
    int *arr = sc_memoryInit();
    int *command = new int;
    int *sc_command = new int;
    int *operand = new int;//, *sc_command = 0;
    sc_memorySet(101, 1);
    sc_memorySet(10, 1);
    int value = 0;
    sc_memoryGet(10, &value);
    std::cout << value << "\n\n";
    sc_memoryGet(101, &value);
    const char *filename = "file.txt";
    sc_memorySave(filename);
    sc_memoryLoad(filename);
    sc_memoryGet(10, arr);
    sc_commandEncode(51, 89, sc_command);
    std::cout << "\nsc_command(10)= " << *sc_command << "\n";
    sc_commandDecode(*sc_command, command, operand);
    return 0;
}
