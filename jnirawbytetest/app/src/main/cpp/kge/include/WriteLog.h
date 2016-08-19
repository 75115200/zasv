#ifndef WRITE_LOG_H_H
#define WRITE_LOG_H_H

#include <vector>
using namespace std;

/************************************************************************/
/* write log head file                                                  */
/************************************************************************/
//#ifdef __cplusplus
//extern "C"{
//
//#endif

/*
* Des:
*	write int array data in *.txt file by specified name and length.write at the end
* Input:
*	iMode, 0 for new, and 1 for add. 
*/
int WriteIntsToFile	(char* pFileName, int* pData, int iDataLen, int iMode);

/*
* Des:
*	write float array data in *.txt file by specified name and length.write at the end
* Input:
*	iMode, 0 for new, and 1 for add. 
*/
int WriteFloatsToFile	(char* pFileName, float* pData, int iDataLen, int iMode);

/*
* Des:
*	write string in the txt file, write in the end.
* Input:
*	iMode, 0 for new, and 1 for add. 
* Return:
*	0 for successful, negative for errors.
*/
int WriteStringToFile	(char* pFileName, char* pString, int iMode);
//
//#ifdef __cplusplus
//};
//#endif



/*
* Des:
*	write int array data in *.txt file by specified name and length.write in the end
* Return:
*	0 for successful, negative for errors.
*/
int WriteVectorToFile	(char* pFileName, vector<int> pData, int iMode);

#endif
