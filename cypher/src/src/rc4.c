/*************************************************************************
  > File Name:     rc4.c
  > Author:        Landerl Young
  > Mail:          LanderlYoung@gmail.com 
  > Created Time:  2013/6/16 15:05:37
 ************************************************************************/
//#define DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif

#include "rc4.h"

static byte SBOX[256];
static byte R[256];

static int GenKeyi= 0, GenKeyj = 0;
/*
 * public 
 */
void rc4KeySetUp(byte *key, int len);

/*
 * private
 */
void init_SBOX(byte *key, int len);
void fill_R(byte *key, int len);

void fill_R(byte *key, int len) {
	int i = 0;
	for(;i < 256; i++) {
		R[i] = key[i % len];
	}
}

void init_SBOX(byte *key, int len) {
	int i = 0;
	int j = 0;
	byte tmp;

	for(;i < 256; i++)
		SBOX[i] = i;

	for(i = 0; i < 256; i++) {
		j = ((j + SBOX[i] + R[i])) % 256;
		//swap SBOX[i] SBOX[j]
		tmp = SBOX[i];
		SBOX[i] = SBOX[j];
		SBOX[j] = tmp;
	}
}

void rc4KeySetUp(byte *key, int len) {
	GenKeyi = GenKeyj = 0;
	fill_R(key, len);
	init_SBOX(key, len);
}


byte rc4GenKey(void) {
	byte h, k;
	byte tmp;
	GenKeyi = (GenKeyi + 1) % 256;
	GenKeyj = (GenKeyj + SBOX[GenKeyi]) % 256;
	
	//swap SBOX[i] SBOX[j]
	tmp = SBOX[GenKeyi];
	SBOX[GenKeyi] = SBOX[GenKeyj];
	SBOX[GenKeyj] = SBOX[GenKeyi];

	h = (SBOX[GenKeyi] + SBOX[GenKeyj]) % 256;
	k = SBOX[h];
	return k;
}

#ifdef DEBUG
int main(void) {
	rc4KeySetUp("1234567890", 10);
	int i;
	for(i = 0; i < 100; i++)
		printf("%d ", rc4GenKey());

	return 0;
}
#endif
