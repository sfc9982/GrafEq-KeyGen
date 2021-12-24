#include "decompiled.h"

#include <cctype>
#include <cstring>

void ACFXGenCodeSecertBeautify(const char *code, _BYTE *secert)
{
	char xcode[18];
	for (int i = 0; i < 16; i++)
		xcode[i] = ACFXLookup(code[i]);
	for (int i = 0; i < 10; i++)
	{
		int c = i * 8 / 5;
		int d = i * 8 % 5;
		secert[i] = (xcode[c] >> d) |
		(xcode[c + 1] << (5 - d)) |
		(xcode[c + 2] << (10 - d));
	}
}

void ACFXGenCodeSecert(const char *code, _BYTE *secert)
{
	int v2; // edi
	unsigned int v3; // esi
	int v4; // ebx
	int v5; // eax
	int v6; // eax
	unsigned int v7; // ebp
	unsigned int v8; // edx
	int v9; // ecx
	int v10; // [esp+10h] [ebp-Ch]
	int secertPtr; // [esp+14h] [ebp-8h]
	signed __int16 v12; // [esp+18h] [ebp-4h]

	v2 = 0;
	v12 = 80;
	v3 = 80;
	secertPtr = 0;
	v10 = 0;
	do
	{
		if ((unsigned __int16)v2 <= 0x1Bu)
		{
			v4 = (unsigned __int16)((unsigned __int16)(27 - v2) / 5u + 1);
			v2 += v4 + 4 * v4;
			do
			{
				v5 = (unsigned __int16)v10;
				LOBYTE(v5) = code[(unsigned __int16)v10++];
				v12 -= 5;
				v3 = ((unsigned __int16)ACFXLookup(v5) << 27) | (v3 >> 5);
				--v4;
			} while (v4);
		}
		if ((unsigned __int16)v2 >= 8u)
		{
			v6 = (unsigned __int16)v2;
			v7 = (unsigned int)(unsigned __int16)v2 >> 3;
			do
			{
				v8 = v3 >> (32 - v6);
				v9 = (unsigned __int16)secertPtr++;
				v2 += 65528;
				v6 -= 8;
				--v7;
				secert[v9] = v8;
			} while (v7);
		}
	} while (v12);
}

char ACFXMatchSecertBeautify(const char *name, const _BYTE *secert)
{
	int nameLen = strlen(name); // bp
	_BYTE vResult[5];
	vResult[0] = secert[0];
	vResult[1] = secert[1];
	vResult[2] = secert[4];
	vResult[3] = secert[6];
	vResult[4] = secert[7];

	int v9 = 0; // eax
	while (1)
	{
		char v16 = ACDXSecretCode1[v9];
		for (int i = 0; i < nameLen; i++)
		{
			v16 += name[i] | (17 * v9 + vResult[(i + v9) % 5]);
		}
		if (secert[ACDXSecretCode2[v9]] != v16)
			break;
		++v9;
		if (v9 >= 5)
		{
			for (int i = 0; i < 5; i++)
				ACDXMatchedResult[i] = vResult[i];
			return 1;
		}
	}
	return 0;
}

char __cdecl ACFXMatchSecert(const char *name, _BYTE *secert)
{
	const char *xname = 0; // ecx
	_BYTE *secert1; // ebx
	char secertAt4; // dl
	const char *xname1; // edi
	char secertAt1; // cl
	char secertAt6; // al
	char secertAt7; // cl
	unsigned __int16 xnameLength0; // bp
	int v9; // eax
	int tmpV9cpy0; // esi
	const char *v11; // ecx
	int v12; // esi
	int v13; // edi
	int v14; // edx
	char v16; // [esp+13h] [ebp-1Dh]
	int v17; // [esp+14h] [ebp-1Ch]
	const char *xname2; // [esp+18h] [ebp-18h]
	int tmpV9cpy1; // [esp+1Ch] [ebp-14h]
	unsigned __int16 xnameLength1; // [esp+20h] [ebp-10h]
	int v21; // [esp+24h] [ebp-Ch]
	char secertAt7_2; // [esp+28h] [ebp-8h]

	secert1 = secert;
	secertAt4 = secert[4];
	xname1 = xname;
	secertAt1 = secert[1];
	LOBYTE(v21) = *secert;
	secertAt6 = secert[6];
	BYTE1(v21) = secertAt1;
	secertAt7 = secert[7];
	xname2 = xname1;
	BYTE2(v21) = secertAt4;
	HIBYTE(v21) = secertAt6;
	secertAt7_2 = secertAt7;
	xnameLength0 = strlen(xname1);
	v9 = 0;
	xnameLength1 = xnameLength0;
	v17 = 0;
	while (1)
	{
		tmpV9cpy0 = (signed __int16)v9;
		tmpV9cpy1 = (signed __int16)v9;
		v16 = ACDXSecretCode1[(signed __int16)v9];
		if (xnameLength0 > 0u)
		{
			v11 = xname1;
			v12 = (signed __int16)v9 - (_DWORD)xname1; //如果此行报错，尝试加上"-fpermissive"参数后进行编译
			v13 = xnameLength0;
			do
			{
				v14 = (signed int)&(v11++)[v12] % 5; //如果此行报错，尝试加上"-fpermissive"参数后进行编译
				v16 += *(v11 - 1) | (17 * v9 + *((_BYTE *)&v21 + v14));
				--v13;
			} while (v13);
			secert1 = secert;
			xname1 = xname2;
			v9 = v17;
			xnameLength0 = xnameLength1;
			tmpV9cpy0 = tmpV9cpy1;
		}
		if (secert1[(unsigned __int8)ACDXSecretCode2[tmpV9cpy0]] != v16)
			break;
		v17 = ++v9;
		if ((signed __int16)v9 >= 5)
		{
			*((unsigned *)ACDXMatchedResult) = v21;
			ACDXMatchedResult[4] = secertAt7_2;
			return 1;
		}
	}
	return 0;
}

int ACFXLookup(int a1)
{
	char v1; // cl
	int result; // eax

	v1 = ACFCharToUpper(a1);
	result = 0;
	while (v1 != ACDXSecertCode0[(unsigned __int16)result])
	{
		if ((unsigned __int16)++result >= 0x20u)
			return 0;
	}
	return result;
}

char ACFCharToUpper(char a1)
{
	if (ACFCharIsLower(a1))
		a1 -= 32;
	return a1;
}

bool ACFCharIsLower(unsigned __int8 a1)
{
	return a1 <= 0x7Fu && islower(a1);
}
