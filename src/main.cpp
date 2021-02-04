#include "header/sc.h"

int main()
{
    int *arr = sc_memoryInit();
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
    return 0;
}
