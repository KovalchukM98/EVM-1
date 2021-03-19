#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <fstream>
#include <fcntl.h>
#include <termios.h>

typedef struct tCHS{
	int C;
	int H;
	int S;

	int max_C;
	int max_H;
	int max_S;
} tCHS;

typedef struct tLARGE{
	int C;
	int H;
	int S;

	int max_C;
	int max_H;
	int max_S;
} tLARGE;

typedef struct tIDECHS{
	int C;
	int H;
	int S;

	int max_C;
	int max_H;
	int max_S;
} tIDECHS;

typedef struct tLBA{
	long long address;

	int max_C;
	int max_H;
	int max_S;
} tLBA;

// lba <-> chs
int g_lba2chs (tLBA lba, tCHS *chs){
	chs.max_C = lba.max_C;
	chs.max_H = lba.max_H;
	chs.max_S = lba.max_S;

	chs.S = (lba.address % chs.S) + 1;
	chs.H = ((lba.address - chs.S + 1)/ chs.max_S) % chs.max_H;
	chs.C = (lba.address - chs.S + 1 - chs.H * chs.max_S)/(chs.max_H * chs.max_S);
	return 0;
}

int a_lba2chs (tCHS geometry, tLBA, tCHS *){

}

int g_chs2lba (tCHS chs, tLBA *lba){
	lba.max_C = chs.max_C;
	lba.max_H = chs.max_H;
	lba.max_S = chs.max_S;

	lba.address = (((chs.C * chs.max_H) + chs.H) * chs.max_S) + (chs.S – 1);
	return 0;
}

int a_chs2lba (tCHS geometry, tCHS, tLBA *){

}
//---------------------------------------------------------
// lba <-> large
int g_lba2large (tLBA, tLARGE *){

}

int a_lba2large (tLARGE geometry, tLBA, tLARGE *){

}

int g_large2lba (tLARGE, tLBA *){

}

int a_large2lba (tLARGE geometry, tLARGE, tLBA *){

}
//---------------------------------------------------------
// lba <-> idechs
int g_lba2idechs (tLBA, tIDECHS *){

}

int a_lba2idechs (tIDECHS geometry, tLBA, tIDECHS *){

}

int g_idechs2lba (tIDECHS, tLBA *){

}

int a_idechs2lba (tIDECHS geometry, tIDECHS, tLBA *){

}
//---------------------------------------------------------
// chs <-> large
int g_chs2large (tCHS, tLARGE *){

}

int a_chs2large (tCHS geometry1, tLARGE geometry2, tCHS, tLARGE *){

}

int g_large2chs (tLARGE, tCHS *){

}

int a_large2chs (tLARGE geometry1, tCHS geometry2, tLARGE, tCHS *){

}
//---------------------------------------------------------
// chs <-> idechs
int g_chs2idechs (tIDECHS, tLBA *){

}

int a_chs2idechs (tCHS geometry1, tIDECHS geometry2, tCHS, tIDECHS*){

}

int g_idechs2chs (tIDECHS, tCHS *){

}

int a_idechs2chs (tIDECHS geometry1, tCHS geometry2, tIDECHS, tCHS*){

}
//---------------------------------------------------------
// large <-> idechs
int g_large2idechs (tLARGE, tIDECHS *){

}

int a_large2idechs (tLARGE geometry1, tIDECHS geometry2, tLARGE, tIDECHS *){

}

int g_idechs2lagre (tIDECHS, tLARGE *){

}

int a_idechs2large (tIDECHS geometry1, tLARGE geometry2, tIDECHS, tLARGE *){

}
//---------------------------------------------------------
int main(){
	return 0;
}