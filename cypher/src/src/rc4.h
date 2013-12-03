/*************************************************************************
    > File Name:     rc4.h
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  2013/6/16 16:02:02
 ************************************************************************/
#ifndef _RC4_H_
#define _RC4_H_
typedef unsigned char byte;

void rc4KeySetUp(byte *key, int len);
byte rc4GenKey(void);

#endif
