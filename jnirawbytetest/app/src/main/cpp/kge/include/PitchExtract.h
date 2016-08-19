#ifndef SONG_SCOREPITCH_DETECT_METHOD_H
#define SONG_SCOREPITCH_DETECT_METHOD_H

#define ERR_INPUT_NULL		-1
#define ERR_INVALID_VALUE	-2
#define ERR_MALLOC_NULL		-3
#define ERR_OPEN_WAV		-4
#define ERR_OPEN_TXT		-5
#define ERR_NOT_SUPPORT		-6

#define MAX_PITCH_VALUE 1000
#define MIN_PITCH_VALUE 100


// test function 
//int Pitch_test		();

/*
* Des:
*	pitch detect, for stereo audio, both left and right output, for mono, only output as left channel. 
* Input:
* Output:
* Return:
*	0 for success, else for errors.
*/
int PitchDetectStereo			(short* pSample, int iLen, int iChannel,int iSampleRate, float* fPitchL, float* fPitchR);

/*
* Des:
*	pitch detect, for mono audio. 
* Input:
* Output:
* Return:
*	0 for success, else for errors.
*/
int PitchDetectMono		(short* pSample, int iLen, int iSampleRate, float* fPitch);

/*
* Des:
*	quick version for pitch detect mono audio. 
*/
int PitchDetectMono_Quick	(short* pSample, int iLen, int iSampleRate, float* fPitch);

/*
* Des:
*	filter pitch array, use mid filter 
* Input:
* Output:
* Return:
*	0 for success, else for errors.
*/
int FilterPitchArray	(float* pPitch, int iNum);


/*
* Des:
*	filter pitch array, use mid filter, use step 5. 
* Input:
* Output:
* Return:
*	0 for success, else for errors.
*/
int FilterPitchInt	(int* pPitch, int iNum);

/*
* Des:
*	extract all the pitch array from .wav file, and save them in the txt file.
* Input:
*	pWavName, the wav file name.
*	pTxtLeft, pTxtRight,the txt file name to save the pitches. left to save the left channel,
*		and right to save the right channel.
* Output:
*	iPitchNum, how many pitch data extract.
* Return:
*	0 for success, else for errors.
*/
//int PitchFromWavToTxt	(char* pWavName, char* pTxtLeft, char* pTxtRight, int* iPitchNum);


/*
* Des:
*	extract all the pitch array from .wav file and save as arrays, both left and right, the iNum
*   specify the length of the array, if no enough memory to save, malloc new memory, and return
*	the real length in iNum.
*
*/
//int PitchDetectAllWav	(char* pWavName, float** pfLeft, float** pfRight, int* iNum, int bIsFilter);

/*
* Des:
*	quick method, input the wav file, and write the pitch array in txt. only left channel,
*   only 0.2~0.4 time length used, and down sample rate by 2.
* Input:
*	pWavName, the .wav file name.
*	pTxtName, the .txt file name.
*	bUseFilter, if use filter in pitch array, 1 for using, and 0 for no.
* Output:
*	model.
* Return:
*	0 for success,else for errors.
*/
//int ExtractPitch2Txt_Quick	(char* pWavName, char* pTxtName, int bUseFilter);


/* convert pitch to midi info */
int Pitch2Midi	(float fpitch);

/* convert midi to pitch */
int Midi2Pitch	(int fmidi);

int NormlizeMidi100	(int iMidi);

#endif
