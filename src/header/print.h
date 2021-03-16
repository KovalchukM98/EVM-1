#pragma once

#include "myTerm.h"
#include "myBigChars.h"
#include <stdio.h>

int row, column , ind;

// static int bcint0 [2] = {1717992960, 8283750};
// static int bcint1 [2] = {471341056, 3938328};
// static int bcint2 [2] = {538983424, 3935292};
// static int bcint3 [2] = {2120252928, 8282238};
// static int bcint4 [2] = {2120640000, 6316158};
// static int bcint5 [2] = {2114092544, 8273984};
// static int bcint6 [2] = {33701376, 4071998};
// static int bcint7 [2] = {811630080, 396312};
// static int bcint8 [2] = {2120646144, 8283750};
// static int bcint9 [2] = {2087074816, 3956832};
// static int bcintA [2] = {2118269952, 4342338};
// static int bcintB [2] = {1044528640, 4080194};
// static int bcintC [2] = {37895168, 3949058};
// static int bcintD [2] = {1111637504, 4080194};
// static int bcintE [2] = {2114092544, 8258050};
// static int bcintF [2] = {33717760, 131646};
// static int bcintplus [2] = {2115508224, 1579134};
// static int bcintm [2] = {2113929216, 126};

int printBoxMemory()
{
	bc_box(1, 1, 12, 61);
	mt_gotoXY(1, 28);
	printf(" Memory ");
	mt_gotoXY(13, 1);
	return 0;
}

int printBoxAccumulator()
{
	bc_box(1, 61 + 1, 3, 22);
	mt_gotoXY(1, 67);
	printf(" accumulator ");
	mt_gotoXY(13, 1);
	return 0;
}

int printBoxInstructionCounter()
{
	bc_box(4, 61 + 1, 3, 22);
	mt_gotoXY(4, 63);
	printf(" instructionCounter ");
	mt_gotoXY(5, 70);
	printf("+%.4d", instruction_counter);
	mt_gotoXY(13, 1);
	return 0;
}

int printBoxOperation()
{
	bc_box(7, 61 + 1, 3, 22);
	mt_gotoXY(7, 68);
	printf(" Operation ");
	mt_gotoXY(13, 1);
	return 0;
}

int printBoxFlags()
{
	bc_box(10, 61 + 1, 3, 22);
	mt_gotoXY(10, 69);
	printf(" Flags ");
	mt_gotoXY(13, 1);
	return 0;
}

int printBoxCase()
{
	bc_box(13, 1, 10, 46);
	mt_gotoXY(18, 1);
	return 0;
}

int pa_printKeys()
{
	bc_box(13, 47, 10, 37);
	mt_gotoXY(13, 48);
	printf(" Keys: ");
	mt_gotoXY(14, 48);
	printf("l   - load");
	mt_gotoXY(15, 48);
	printf("s   - save");
	mt_gotoXY(16, 48);
	printf("r   - run");
	mt_gotoXY(17, 48);
	printf("t   - step");
	mt_gotoXY(18, 48);
	printf("i   - reset");
	mt_gotoXY(19, 48);
	printf("F5  - accumulator");
	mt_gotoXY(20, 48);
	printf("F6  - instructionCounter");
	mt_gotoXY(21, 48);
	printf("q   - exit");
	return 0;
}

int pa_printMemory()
{
	for (int i = 0; i < 10; i++) {
		mt_gotoXY(2 + i, 2);
		for (int j = 0; j < 10; j++) {
			if (j != 0)
				printf(" ");
			if (arr[i * 10 + j] < 0) {
				printf("-%.4d", -arr[i * 10 + j]);
			} else {
				printf("+%.4d", arr[i * 10 + j]);
			}
		}
	}
	mt_setbgcolor(CYAN);
	mt_gotoXY(2 + row, 2 + column*6);
		if (arr[row * 10 + column] < 0) {
			printf("-%.4d", -arr[row * 10 + column]);
		} else {
			printf("+%.4d", arr[row * 10 + column]);
		}
	printf("\E[0m");
	return 0;
}

int printAllBox()
{
	mt_clrscr();

	printBoxMemory();
	pa_printMemory();
	printBoxAccumulator();
	printBoxInstructionCounter();
	printBoxOperation();
	printBoxFlags();
	printBoxCase();
	pa_printKeys();
	
	mt_gotoXY(24, 1);
	return 0;
}
int pa_resetTerm()
{
	mt_clrscr();
	printBoxMemory();
	printf("\E[00m\n");
	pa_printMemory();
	printBoxAccumulator();
	printBoxInstructionCounter();
	printBoxOperation();
	printBoxFlags();
	printBoxCase();
	pa_printKeys();
	mt_gotoXY(24, 1);
	printf("Input\\Output: ");
	mt_gotoXY(24, 14);

	mt_gotoXY(25, 1);
	for (int i = 0; i < 4; i++) {
		for (int i = 0; i < 83; i++) {
			printf(" ");
		}
		printf("\n");
	}

	mt_gotoXY(33, 1);
	fflush(stdout);
	
	return 0;
}

void pa_moveUp()
{
	if(row > 0) row--;
	pa_resetTerm();
}

void pa_moveDown()
{
	if(row < 10) row++;
	pa_resetTerm();
}

void pa_moveLeft()
{
	if(column > 0) column--;
	pa_resetTerm();
}

void pa_moveRight()
{
	if(column < 10) column++;
	pa_resetTerm();
}

void pa_memset()
{
	int setter = 0;
	if(row == 0) setter = column;
	else setter = column + (10 * row);
	sc_memorySet(setter, 1);
	pa_resetTerm();
}