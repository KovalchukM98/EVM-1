#pragma once

#include <stdio.h>
#include <stdlib.h>

#define P_FLAG 0	// переполнение при выполнение операции
#define O_FLAG 1	// ошибка деления на 0
#define M_FLAG 2    // ошибка выхода за границы памяти
#define T_FLAG 3	// игнорирование тактовых импульсов
#define E_FLAG 4    // указана неверная команда

const char *filename = "file.txt";

static const int memSize = 100;
static int arr[memSize];
static int registr = 0;
static int instruction_counter = 0;
static int accumulator = 0;

bool isCommand(int command) {
    if(command != (0x10 || 0x11 || 0x20 || 0x21 || 0x30 || 0x31 || 0x32 || 0x33 || 0x40 || 0x41 || 0x42 || 0x43 ||
        0x51 || 0x52 || 0x53 || 0x54 || 0x55 || 0x56 || 0x57 || 0x58 || 0x59 || 0x60 || 0x61 || 0x62 || 0x63 || 
        0x64 || 0x65 || 0x66 || 0x67 || 0x68 || 0x69 || 0x70 || 0x71 || 0x72 || 0x73 || 0x74 || 0x75 || 0x76)){
            return false;
        }
    return true;
}

int sc_regInit(void)
{
    registr = 0; 
    return 0;
}

int sc_regSet(int flag_num, int value)
{
    // std::cout << "\nRegistr before set:";
    // for(int i = 32; i >= 0; --i){
    //     std::cout << ((registr >> i) & 1) << " ";
    // }
    if(value > 1 || value < 0) return 1;
    registr |= value << flag_num;
    // std::cout << "\nRegistr under set:";
    // for(int i = 32; i > 0; --i){
    //     std::cout << ((registr >> i) & 1) << " ";
    // }
    return 0;
}

int sc_regGet(int flag_num, int* value){
    if(flag_num > 4 || flag_num < 0) return 1;
    int flag;
    flag = (registr >> flag_num) & 0x1;
    //std::cout << "\nFlag:" << *flag;
    *value = flag;
    //std::cout << "\nValue:" << *value;
    return 0;
}

int *sc_memoryInit()
{   
    for(int i = 0; i < memSize; ++i){
        arr[i] = 0;
    }
    instruction_counter = 0;
    return arr;
}

int sc_memorySet(int address, int value)
{
    if(address >= memSize){
        int error_flag = M_FLAG;
        sc_regSet(error_flag,1);
        //std::cout << "memory size error(set)\n\n";
        return 1;
    }
    arr[address] = value;
    return 0;
}

int sc_memoryGet(int address, int* value)
{
    if(address >= memSize){
        int error_flag = M_FLAG;
        sc_regSet(error_flag,1);
        //std::cout << "memory size error(get)\n\n";
        return 1;
    }
    *value = (arr[address]);
    //std::cout << "Value: " << *value << "\n";
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
	if ((operand > 127 || operand < 0) && isCommand(command) &&(command > 127 || command < 0 )) {
        int error_flag = E_FLAG;
        sc_regSet(error_flag,1);
        return 1;
	}
    
	*value = (command << 7) | operand;
    // std::cout << "encode:\nval(10)= " << *value << "\nval(2)= ";
    // for(int i = 14; i >= 0; --i){
    //     std::cout << ((*value >> i) & 1) << " ";
    // }
	return 0;
}

int sc_commandDecode (int value, int * command, int * operand)
{
    
	if((value >> 14) != 0) {
		int error_flag = E_FLAG;
        sc_regSet(error_flag,1);
        //std::cout << ((value >> 14) & 1) << " - Не является началом команды\n";
        return 1;
	}
    *command = value >> 7;
	*operand = value & 127;
    // std::cout << "sc_flag= " << ((value >> 14) & 1);
    // std::cout << "\nCommand(2)= ";
    // for(int i = 6; i >= 0; --i){
    //     std::cout << ((*command >> i) & 1) << " ";
    // }
    // std::cout << "\nOperand(2)= ";
    // for(int i = 6; i >= 0; --i){
    //     std::cout << ((*operand >> i) & 1) << " ";
    // }
	return 0;
}
