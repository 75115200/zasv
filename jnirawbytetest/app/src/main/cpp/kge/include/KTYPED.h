#ifndef KALA_AUDIO_BASE_TYPE_H
#define KALA_AUDIO_BASE_TYPE_H

#ifdef _MSC_VER
// MSVC build for Windows, and it's (expected to be) able to handle true stereo in real time 
#define PSEUDO_MULTICHANNELS 0
#else
#define PSEUDO_MULTICHANNELS 1
#endif

#ifdef LIBKALAAUDIOBASE_DYNAMIC_EXPORTS
#define LIB_KALAAUDIOBASE_API __declspec(dllexport)
#endif

#ifdef LIBKALAAUDIOBASE_DYNAMIC_IMPORTS
#define LIB_KALAAUDIOBASE_API __declspec(dllimport)
#endif

#ifndef LIB_KALAAUDIOBASE_API
#define LIB_KALAAUDIOBASE_API
#endif

#define SONG_SCORE_FRAME_MS		40
#define SONG_SCORE_CHANNEL_NUM	1
#define SONG_SCORE_FRAME_SIZE    KALA_DEFAULT_SAMPLE_RATE*SONG_SCORE_FRAME_MS/1000*2*SONG_SCORE_CHANNEL_NUM // mono
#define SONG_SCORE_FRAME_SHIF	 SONG_SCORE_FRAME_SIZE
//#define SONG_SCORE_MAX_SCORE	100		// max score value.
//#define SONG_SCORE_MIN_SCORE	0		// min score value.


#ifndef safe_free
#define safe_free(p)      { if(p) { free(p); (p)=NULL; } }
#endif

//typedef struct _tagFLOAT_BUFFER
//{
//	float* buf;	// buffer in float
//	int len;	// float length.
//
//}FltBuf, *PFltBuf;

#endif
