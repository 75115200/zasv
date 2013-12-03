/*************************************************************************
  > File Name:     des.c
  > Author:        Landerl Young
  > Mail:          LanderlYoung@gmail.com 
  > Created Time:  2013/3/24 12:32:37
 ************************************************************************/

#include "des.h"

#ifdef DEBUG
#include <stdio.h>
void p(byte b[],int len);
#endif

static byte K[16][48];
void desKeySetUp(char KEY[]);
void encMsg(byte m[64],byte c[64],int d);
void parse(char msg[],byte ans[]);
void deparse(byte b[],char c[]);
void fFunction(byte r[],byte K[],byte f[]);

#ifdef DEBUG
int main(){

	char key[8] = "87654321";
	char t[9],s[9];
	byte m[64],c[64];
	parse("01234567",m);
	//encryptionByte(m,c,key);
	//decryptionByte(c,m,key);
	encryption("Hellowor",t,key);
	decryption(t,s,key);

	printf("Cypher is:%s\nMessageis:%s\n",t,s);

	return 0;
}
#endif

void encryption(char m[],char c[]){
	byte m_[64],c_[64];
	parse(m,m_);
	encryptionByte(m_,c_);
	deparse(c_,c);
}

void decryption(char c[],char m[]){
	byte m_[64],c_[64];
	parse(c,c_);
	decryptionByte(c_,m_);
	deparse(m_,m);
}

void encryptionByte(byte m[],byte c[]){
	encMsg(m,c,0);
}

void decryptionByte(byte c[],byte m[]){
	encMsg(c,m,1);
}

#ifdef DEBUG
void p(byte b[],int len){
	int i;
	for (i = 0;i < len; ++i){
		if (i % 8 == 0)
			putchar(' ');
		printf("%d",b[i]);
	}
	putchar('\n');
}
#endif

void parse(char msg[],byte ans[]){
	int i,j;
	for(i = 0;i < 8;++i){
		for(j = 0;j < 8;++j)
			ans[i*8 + j] = (msg[i] &  ( 1 << (7 - j))) >> (7 - j );
	}
}

void deparse(byte b[],char c[]){
	int i,j;
	for(i = 0;i < 8;++i){
		c[i] = 0;
		for(j = 0;j < 8;++j)
			c[i] |= b[i*8 + j] << (7 -j);
	}
	//c[8] = 0;
}

void lshift(byte a[],int len,int offset){
	byte tmp[2];
	int i;
	for(i = 0;i < offset; ++i)
		tmp[i] = a[i];

	for(i = 0;i < len - offset;++i)
		a[i] = a[i + offset];

	for(;i < len;++i)
		a[i] = tmp[ i - (len - offset)];
}

void desKeySetUp(char KEY[]){
	int i,j;
	byte c0[28],d0[28];
	byte key[64];

	parse(KEY,key);

#ifdef DEBUG
	printf("Key Set Up!\nkey:\t");
	p(key,64);
#endif

	for(i = 0;i < 28; ++i){
		c0[i] = key[P1[i] -1];
	}
	for(i = 0;i < 28; ++i){
		d0[i] = key[P1[i + 28] -1 ];
	}
#ifdef DEBUG
	printf("C0:\t");
	p(c0,28);
	printf("D0:\t");
	p(d0,28);
	putchar('\n');
#endif
	for(j = 0; j < 16; ++j){
		lshift(c0,28,KTL[j]);
		lshift(d0,28,KTL[j]);

		for(i = 0;i < 48; ++i){
			if(P2[i] > 28)
				K[j][i] = d0[P2[i] - 29];
			else
				K[j][i] = c0[P2[i] - 1];
		}
#ifdef DEBUG
		printf("C%02d:\t",j +1);
		p(c0,28);
		printf("D%02d:\t",j+1);
		p(d0,28);
		printf("K[%02d]:\t", j+1);
		p(K[j],48);
		putchar('\n');
#endif
	}
}

void fFunction(byte r[],byte K[],byte f[]){
	byte e[48],tmp[32];
	//r[] turn to e[] after Selection E
	//tmp[] turn to f[] after Permulation P
	int i,j;
	int row,column;
	byte s;

#ifdef DEBUG
	printf("32 :\t");
	p(r,32);
#endif

	//Select E
	for(i = 0;i < 48;++i)
		e[i] = r[E[i] - 1];

#ifdef DEBUG
	printf("s:\t");
	p(e,48);
	printf("K:\t");
	p(K,48);
#endif

	for(i = 0;i < 48;++i)
		e[i] ^= K[i];
#ifdef DEBUG
	printf("e^:\t");
	p(e,48);
#endif

	//S-Box
	for(i = 0; i < 8;++i){
		//8 S-Box in total
		row = e[i*6] * 2 + e[i*6 + 5];
		column = e[i*6 + 1] * 8 + e[i*6 + 2] * 4 +
			e[i*6 + 3] * 2 + e[i*6 +4];
		s = S[i][row][column];

		tmp[i*4] = (s >> 3) & 0x01;
		tmp[i*4 + 1] = (s >> 2) & 0x01;
		tmp[i*4 + 2] = (s >> 1) & 0x01;
		tmp[i*4 + 3] = s & 0x01;
	}
#ifdef DEBUG
	printf("SB:\t");
	p(tmp,32);
#endif

	//Premulation P
	for(i = 0;i < 32;++i)
		f[i] = tmp[P[i] - 1];
#ifdef DEBUG
	printf("P:\t");
	p(f,32);
#endif
}

void encMsg(byte m[64],byte c[64],int d){
	//d = 0 for encryption
	//otherwise for decryption
	byte l0[32],r0[32],tmp[32];//zhazha
	byte f[32];
	int i,j;
	int ds[2][16]={
		{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
		{15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0}
	};

	d = (d == 0) ? 0:1;

	for (i = 0;i < 32; ++i)
		l0[i] = m[IP[i] - 1];

	for (i = 0;i < 32; ++i)
		r0[i] = m[IP[i + 32] - 1];

#ifdef DEBUG
	if(d == 0)
		printf("Encryption!\nMessage:");
	else
		printf("Decryption\nCypher:\t");
	p(m,64);
	printf("L0:\t");
	p(l0,32);
	printf("R0:\t");
	p(r0,32);
	putchar('\n');
#endif
	for(j = 0;j < 15; ++j){

		fFunction(r0,K[ds[d][j]],f);

		for(i = 0;i < 32; ++i)
			tmp[i] = r0[i];

		for(i = 0;i < 32; ++i)
			r0[i] = l0[i] ^ f[i];

		for(i = 0;i < 32; ++i)
			l0[i] = tmp[i];

#ifdef DEBUG
		printf("L%2d:\t",j + 1);
		p(l0,32);
		printf("R%2d:\t",j + 1);
		p(r0,32);
		putchar('\n');
#endif
	}

	fFunction(r0,K[ds[d][15]],f);
	for(i = 0;i < 32; ++i)
		l0[i] = l0[i] ^ f[i];
#ifdef DEBUG
	printf("L%2d:\t",j + 1);
	p(l0,32);
	printf("R%2d:\t",j + 1);
	p(r0,32);
	putchar('\n');
#endif
	for(i = 0;i < 64; ++i){
		if( IP_1[i] > 32)
			c[i] = r0[IP_1[i] - 33];
		else
			c[i] = l0[IP_1[i] -1];
	}
#ifdef DEBUG
	if(d == 0)
		printf("Cypher:\t");
	else
		printf("Message:");
	p(c,64);
#endif
}
