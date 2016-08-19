/************************************************************************/
/* mix sound files														*/
/* create by ethanzhao 5.13, 2014										*/
/* last modified by ethanzhao, 5.14,2014								*/
/************************************************************************/

#ifndef MIX_SOUND_WAV_FILE_H
#define MIX_SOUND_WAV_FILE_H

#define MIX_SOUND_WAV_VERSION "1.0.1"		/* version string */
#define MAX_DELAY_TIME_MS	5000		// max delay in ms
#define MIN_DELAY_TIME_MS	-5000		// min delay in ms

/*
* Des:
*	mix 2 mono pcm files to 1 stereo pcm file, by specified rate,and delays in ms.
* Input:
*	pDstName, output pcm file name, name = path + file name.
*	pBgName, input pcm file name, background music file name,name = path + file name.
*	pVoice, input pcm file name,voice file name, name = path + file name.
*	fBgRate, rate of background music,in [0,2.0];
*	fVRate, rate of voice music, in [0,2];
*	iDelayMs, voice sound delay time in ms.[-5000, 5000].
* Output:
*	NULL;
* Return:
*	0 for success, else for errors.
* Notice:
*	(1) the input file are both pcm mono, but the output file is pcm stereo.
*	(2) the output file may be longer than the both, because the delay time.
*/
//int MixFileMono2Stereo	(char* pDstName, char* pBgName, float fBgRate, char* pVoiceName,
//						 float fVrate, int iDelayMs);



/*
* Des:
*	mix sound as the MixFileMono2Stereo, but in buffer sample rather than file. 
*	the iOutSize here to check the buffer is big enough to store the data output.
* Return:
*	return 0 for success, negative values for errors.
* Notice:
*	(1) the input buffer are both pcm mono, but the output buffer is pcm stereo. to make sure that
*		the output size >= 2* max(inputsize1, inputsize2)
*/
//int MixSampleBufMono2Stereo	(char* pOutStereo, int* iOutSize, char* pBgMono, int iBgSize, float fBgRate, 
//							 char* pVoiceMono,int iVsize,float fVrate, int iDelayMs);



//int MixPcmDataMono	(char* pDst, int iDstsize,float fDstRate, char* pSrc, int iSrcSize, float fSrcRate);
int PcmMono2Stereo	(char* pStereoOut, int iOutSize, char* pMonoInput, int iInSize);

#endif

