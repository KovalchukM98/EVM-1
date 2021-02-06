#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define MEMORY_BORDER_ERROR 1;

const int memSize = 100;
static int arr[memSize];
static int registr;
int error_flag = 0;

int sc_regInit(void)
{
    registr = 0; 
    return 0;
}

int sc_regSet(int flag_num, int value)
{
    if(value > 1 || value < 0) return 1;
    registr |= value << (flag_num-1);
    return 0;
}

int sc_regGet(int flag_num, int* value){
    if(flag_num > 1 || flag_num < 0) return 1;
    int flag = (registr >> (flag_num - 1)) & 1;
    value = &flag;
    return 0;
}

int *sc_memoryInit()
{   
    for(int i = 0; i < memSize; ++i){
        arr[i] = 0;
    }
    return arr;
}

int sc_memorySet(int address, int value)
{
    if(address >= memSize){
        registr |= MEMORY_BORDER_ERROR;
        std::cout << "memory size error(set)\n\n";
        return 1;
    }
    arr[address] = value;
    return 0;
}

int sc_memoryGet(int address, int* value)
{
    if(address >= memSize){
        registr |= MEMORY_BORDER_ERROR;
        std::cout << "memory size error(get)\n\n";
        return 1;
    }
    *value = (arr[address]);
    std::cout << "Value: " << *value << "\n";
    return 0;
}

int sc_memorySave(const char* filename)
{
    FILE* pFile = fopen (filename, "wb");
    fwrite (arr , sizeof(int), memSize, pFile);
    fclose (pFile);
    return 0;
}

int sc_memoryLoad(const char* filename)
{
    FILE* pFile = fopen (filename, "rb");
    fread(arr , sizeof(int), memSize, pFile);
    fclose (pFile);
    return 0;
}

int sc_commandEncode(int command, int operand, int *value)
{
	if ((operand > 127 || operand < 0) && (command > 127 || operand < 0 )) {
        return 1;
	}
    
	*value = (command << 7) | operand;

	return 0;
}

int sc_commandDecode (int value, int * command, int * operand)
{
	if ((value >> 14) != 0) {
		error_flag = 1;
        return 1;
	}

	*command = value >> 7;
	*operand = value & 0x7F;
	return 0;
}
