/************************************************************************/
/* statics infterface                                                   */
/* written by ethanzhao, 3.5, 2013. last modified 4.25, 2013            */
/* copy right reserved.                                                 */
/************************************************************************/


#ifndef C_STATICS_FILE_H_H
#define C_STATICS_FILE_H_H

//#ifdef __cplusplus
//extern "C"{
//#endif

/*
* Des:
*	get mean of short array
*/
int stGetMeanShort	(short* pSamples, int iLen, int* iMean);
/*
* Des:
*	get mean of int array
*/
int stGetMeanInt	(int* pData, int iLen, float* fMean);

///*
//* Des:
//*	get number data bigger than mean value
//*/
//int stGetRight		(int* pData, int iLen, int* iCnt);

/*
* Des:
*	get range, max - min
*/
int stGetRange		(int* pData, int iLen, int* iRange);


/*
* Des:
*	get stdanrd variance of short array
*/
int stGetStdvarShort (short* pSample, int iLen, float* fStd);


/*
* Des:
*	get standard variance of int array
*/
int stGetStdvarInt	(int* pData, int iLen, float* fStd);

/*
* Des:
*	get mean of short array
*/
int stZeroCross	(short* pSample, int iLen, int* iNum);

/*
* Des:
*	get power of audio signal, power = energy/ length.
*	if bQuick = 1 for quick method, 0 for standard.
*/
int stGetPower	(short* pSample, int iLen, float* fPower, int bQuick);

/*
* Des:
*	normalize data, normalize the data to [0, iNormVal]. 
*/
int stNormalizeData	(int* pData, int iLen, int iNormVal);

/*
* Des:
*	find and max in array;
*/
int stFindMax	(int* pData, int iLen, int* iMax);

/*
* Des:
*	find and min in array;
*/
int stFindMin	(int* pData, int iLen, int* iMin);


/*
* Des:
*	find and min in array;
*/
int stFindMaxShort	(short* pData, int iLen, int* iMax);

/*
* Des:
*	find and min in array;
*/
int stFindMinShort	(short* pData, int iLen, int* iMin);

//#ifdef __cplusplus
//};
//#endif
//

#endif
