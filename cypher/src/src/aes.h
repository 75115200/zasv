/*************************************************************************
    > File Name:     aes.h
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  2013/6/16 14:09:41
 ************************************************************************/
#ifndef _AES_H_
#define _AES_H_
void aesKeySetUp(char key[]);
void aesEncrypt(char msg[], char cyp[]);
void aesDecrypt(char msg[], char cyp[]);
#endif
