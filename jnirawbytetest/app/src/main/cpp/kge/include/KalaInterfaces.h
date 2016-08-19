/************************************************************************/
/* kala ok audio base module interface.                                 */
/* deined and written by bosong and ethanzhao, 5.16,2014				*/
/* last modified by ethanzhao, 4-30, 2015, add section singing. kala v2.5*/
/************************************************************************/

#ifndef KALA_AUDIO_BASE_H
#define KALA_AUDIO_BASE_H

#include "math.h"
#include <vector>
#include "SectionInfo.h"

using namespace std;

#define KALA_AUDIO_BASE_VERSION_NUMBER    3600    // add section sing, kala 3.6.0

typedef struct _tagNOTEVET {
    int time_bgn;        // time begin
    int time_dur;        // time duration
    int note_high;        // note hight
} noteVector;

/* song score interface */
class IKalaScore {
public:

    // Configuration
    virtual int SetChannels(int channels) = 0; // // default is 1 (Mono)
    virtual int SetSamplerate(int samplerate) = 0; // default is 44100

    // for ordinary singing
    virtual int Init(char *noteFile,
                     vector<int> sentences) = 0;        //  use note file here and sentence vector input.
    virtual int Init(char *noteMem, int memSize,
                     vector<int> sentence) = 0;// use note memory here and sentence vector input.

    // for section singing, add section memory & memory size & singer string additional. just for ios.
    virtual int Init(char *noteMem, int memSize, vector<int> sentences, char *section_memory,
                     int section_mem_size, char *role_string) = 0;

    // for section singing, add sentence to sing, just for android.
    virtual int Init(char *noteMem, int memSize, vector<int> sentences,
                     vector<int> sentence_to_sing) = 0;

    virtual void Uninit() = 0;                                            // uninit
    virtual int Process(char *inBuffer, int inSize,
                        int timeStamp) = 0;    // input mono PCM data and time position in ms.

    virtual void GetScoreRange(int *maxScore,
                               int *minScore) = 0;            // get the max and min score supported.
    virtual int GetNoteSing(int *iNote,
                            int *bIsHunt) = 0;            // get the singer's note now, and tell if hunt. 1 for yes, 0 for no.
    virtual int GetLastScore() = 0;    // call this function to get a new sentence score, if no new data, return -1.
    virtual int GetTotalScore() = 0;    // get total score

    virtual int GetNoteRange(int *maxVal, int *minVal) = 0;    // get note range to show.
    virtual int GetAllScores(vector<int> *scores) = 0;    // get all scores array.
    virtual int GetNotePlay(vector<noteVector> *notes) = 0;    // get note to show.

    virtual int OpenOrigSing(
            int bOpen) = 0;                // if sing with original music accompaniment,1 for open,0 for close. set 1 will decrease scores.
    virtual int Reseek(
            int time_ms) = 0;                // reset time position by specified time, in ms;
    virtual int SetKeyShift(
            int key_shift_value) = 0;        // when pitch shift by user, send the value for score.

};

/* song de-noise interface v1.0*/
class IKalaClean {
public:
    virtual int Init(int inSampleRate, int inChannel) = 0;    // set sample rate and channel;
    virtual void Uninit() = 0;    // uninit

    //virtual void Process(char* inBuffer, int inSize,
    //					 char* outBuffer, int outSize)		= 0;	// process
    virtual int Process(char *inBuffer, int inSize) = 0;    // process
};

/* song de-noise interface v2.0*/
class IKalaClean2 {
public:
    virtual int Init(int inSampleRate,
                     int inChannel) = 0;    // set sample rate and channel and buffer size to process;
    virtual void Uninit() = 0;    // uninit

    //virtual void Process(char* inBuffer, int inSize,
    //					 char* outBuffer, int outSize)		= 0;	// process
    virtual int Process(char *inBuffer, int inSize) = 0;    // process
};



/* volume change interface */
//class IKalaVolume
//{
//public:
//	virtual int  Init() = 0;
//	virtual void Uninit() = 0;
//
//	virtual void Process(unsigned char* inChannel, int inSize,
//						 unsigned char* outBuffer, int outSize) = 0;
//
//	virtual void GetVolumeRange(int* maxVolume, int* minVolume) = 0;
//	virtual int  GetDefaultVolume() = 0;
//
//	virtual int  GetVolume() = 0;
//	virtual int  SetVolume() = 0;
//};

/* change voice style */
class IKalaVoiceShift {
public:
    virtual int Init(int sampeRate, int channel, char *noteMem, int noteSize) = 0;

    virtual void Uninit() = 0;

    virtual int GetIdRange(int *maxId, int *minId) = 0;

    virtual int GetIdDefault() = 0;

    virtual int SetTypeId(int typeID) = 0;

    virtual int GetTypeId() = 0;

    virtual char *GetNameById(int typeID) = 0;

    virtual int Process(char *inBuffer, int inSize, char *outBuffer, int outSize) = 0;

    virtual int SetKeyShift(
            int key_shift_value) = 0;        // when pitch shift by user, send the value for score.
    virtual int GetAutoTuneLatency() = 0;
};

/* change tone style */
class IKalaToneShift {
public:
    virtual int Init(int sampeRate, int channel) = 0;

    virtual void Uninit() = 0;

    virtual int GetShiftRange(int *maxVal, int *minVal) = 0;

    virtual int GetShiftDefault() = 0;

    virtual int SetShiftValue(int shiftVal) = 0;

    virtual int GetShiftValue() = 0;

    virtual int Process(char *inBuffer, int inSize, char *outBuffer, int outSize) = 0;
};

/* reverb */
class IKalaReverb {
public:
    virtual int Init(int sampeRate, int channel) = 0;

    virtual void Uninit() = 0;

    virtual void GetIdRange(int *maxVal, int *minVal) = 0;

    virtual int GetIdDefault() = 0;

    virtual int SetTypeId(int typeID) = 0;

    virtual int GetTypeId() = 0;

    virtual char *GetNameById(int typeID) = 0;

    virtual int Process(char *inBuffer, int inSize, char *outBuffer, int outSize) = 0;
};

/* mix sound */
class IKalaMix {
public:
    virtual int Init(int sampeRate, int channel) = 0;

    virtual void Uninit() = 0;

    /* deal with buffer, two mono input, 1 stereo output. make sure the output buffer size >= 2* max(left, right) */
    virtual int Process(char *leftChannel, int leftSize,
                        char *rightChannel, int rightSize,
                        char *outBuffer, int outSize) = 0;

    /*
    music: Music Input (Stereo In)
    original:  Original Track (Stereo In)
    vocal:  Vocal(Stereo In, post-processed vocal)
    mixdown: Output of the mixdown
    size: Bytes to process
    mixvocal: True to mix the vocal to mixdown
    */
    virtual int ProcessSmart(const char *music, const char *original,
                             const char *vocal, char *mixdown, int size, bool mixvocal) = 0;

    ///* deal with buffer, two mono input, 1 mono output. make sure the output buffer size <= min(left, right) */
    //virtual int  ProcessMono	(char* leftChannel, int leftSize,
    //					 char* rightChannel,int rightSize,
    //					 char* outMono, int outSize) = 0;


    /* add */
    virtual int GetVolumeRange(int *maxVolume,
                               int *minVolume) = 0;    // get volume range, the same for left and right channel.
    virtual int GetVolumeDefault(
            int *volumeDefault) = 0;                // get volume value default;
    virtual int GetDelayDefault(int *delayMs) = 0;                // get default delay value in ms.
    virtual int Reset() = 0;                // reset delay and volume to default value.

    /* get interface */
    virtual void GetDelayRange(int *maxDelay, int *minDelay) = 0;    // get delay range in ms
    virtual int GetDelay() = 0;                                    // get delay parameter in ms
    virtual int GetLeftVolume() = 0;                                    // get left volume mix volume rate.
    virtual int GetRightVolume() = 0;                                    // get right volume mix volume rate.

    /* set interface */
    virtual int SetDelay(
            int iMs) = 0;                        // set delay in ms. delay means right channel delay. default: 0.
    virtual int SetLeftVolume(
            int iValue) = 0;                        // set left volume ,[0,200],default: 100 mean no volume change.
    virtual int SetRightVolume(
            int iValue) = 0;                        // set right volume,[0,200],default: 100 mean no volume change.
};

/* reverb */
//class IKalaGain
//{
//public:
//	virtual int  Init( int sampeRate, int channel ) = 0;	// init
//	virtual void Uninit()							= 0;	// uninit
//	virtual int  Process(char* inBuffer, int inSize)= 0;	// process input and output
//
//	virtual int  Disable(int bEnable)				= 0;	// set 0 to disable the box. and.
//};

class IKalaGain {
public:

    // support mono and stereo now.
    virtual int Init(int inSampleRate, int inChannel) = 0;    // set sample rate and channel;
    virtual void Uninit() = 0;    // uninit

    // process input buffer and output size.
    virtual int Process(char *inBuffer, int inSize) = 0;
};

/* section singing*/
class IKalaSection {
public:

    /* overload function, input section file name & sentence info, like score. */
    virtual int init(char *section_file_name, vector<int> sentences) = 0;

    /* overload function, input section file memory & sentence info, like score. */
    virtual int init(char *section_memory, int input_len,
                     vector<int> sentences) = 0; // input memory not file.

    /* get section info all. get every sentence's section info. sentence,0,1,2,3...*/
    virtual int GetSectionInfo(vector<SectionSingers> *section_info_all) = 0;

    /* uninit function*/
    virtual void uinit() = 0;

private:

};


class IKalaVolume {
public:

    /* input pcm samples, just for mono, and output volume value, out value in [0,100] */
    virtual int Process(const char *inBuffer, int inSize, int *outVolume) = 0;

private:

};


/* Generic DSP Processor Interface */
class IKalaDspProcessor {
public:

    virtual int Init(int inSampleRate, int inChannel) = 0;    // set sample rate and channel;
    virtual void Uninit() = 0;    // uninit

    // process input buffer and output size.
    virtual int Process(char *inBuffer, int inSize) = 0;
};


/* volume scaler interface, used for v3.5  */
class IKalaVolumeScaler {
public:

    virtual int Init(int inSampleRate, int inChannel) = 0;    // set sample rate and channel;
    virtual void Uninit() = 0;    // uninit

    // process input buffer and output size.
    virtual int Process(char *inBuffer, int inSize) = 0;
};

class ISingLearning {
public:
    enum EScoreResultType {
        SRT_1,                // Corresponding S
        SRT_2,                // Corresponding A
        SRT_3,                // Corresponding B
        SRT_4,                // Corresponding C
        SRT_5,                // Corresponding silence
        SRT_NO_RESULT,        // Corresponding rap,
    };

    enum EWordResultType {
        WRT_NO_ERROR,
        WRT_PITCH_LOW,
        WRT_PITCH_HIGH,
        WRT_WORD_LATE,
        WRT_WORD_EARLY,
    };

public:
    virtual int Init(const char *szConfigFile, int nSampleRate) = 0;

    virtual void Uninit() = 0;

    virtual int SetChannels(int nChannelNum) = 0;

    virtual int CheckResource(const char *szNoteStr, int nNoteSize, const char *szQrcStr,
                              int nQrcSize) = 0;

    virtual int CreateSession(const char *szNoteStr, int nNoteSize, const char *szQrcStr,
                              int nQrcSize) = 0;

    virtual void DestorySession() = 0;

    virtual int StartSession(int nBeginTime_ms, int nEndTime_ms) = 0;

    virtual void StopSession() = 0;

    virtual int PutBuffer(char *pBuffer, int nBufferSize, bool &bLastSent) = 0;

    virtual int PutBuffer(char *pBuffer, int nBufferSize, int nTimeStamp_ms) = 0;

    virtual int GetResult(int &nCurSentIndex, EScoreResultType &nScoreType,
                          std::vector<EWordResultType> &aWordResultType) = 0;

    virtual int GetLastResult(EScoreResultType &nScoreType) = 0;
};

#endif
