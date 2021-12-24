#pragma once

#include "defs.h"

void ACFXGenCodeSecert(const char *code, _BYTE *secert);
void ACFXGenCodeSecertBeautify(const char *code, _BYTE *secert);
char ACFXMatchSecert(const char *name, const _BYTE *secert);
char ACFXMatchSecertBeautify(const char *name, const _BYTE *secert);

int ACFXLookup(int a1);
char ACFCharToUpper(char a1);
bool ACFCharIsLower(unsigned __int8 a1);

static _BYTE ACDXMatchedResult[5];

static _BYTE ACDXSecertCode0[32] = {
	0x59,	//'Y'
	0x35,	//'5'
	0x45,	//'E'
	0x37,	//'7'
	0x55,	//'U'
	0x5A,	//'Z'
	0x39,	//'9'
	0x58,	//'X'
	0x50,	//'P'
	0x32,	//'2'
	0x33,	//'3'
	0x51,	//'Q'
	0x57,	//'W'
	0x4B,	//'K'
	0x4D,	//'M'
	0x4E,	//'N'
	0x36,	//'6'
	0x41,	//'A'
	0x2B,	//'+'
	0x54,	//'T'
	0x53,	//'S'
	0x43,	//'C'
	0x21,	//'!'
	0x34,	//'4'
	0x56,	//'V'
	0x46,	//'F'
	0x47,	//'G'
	0x48,	//'H'
	0x4A,	//'J'
	0x52,	//'R'
	0x2D,	//'-'
	0x44	//'D'
};

static _BYTE ACDXSecretCode1[8] = { // 5 elements enough
	0x5D,
	0x22,
	0x4F,
	0x4E,
	0x0FC,
	0,
	0,
	0
};

static _BYTE ACDXSecretCode2[8] = { // 5 elements enough
	2,
	3,
	5,
	8,
	9,
	0,
	0,
	0
};
