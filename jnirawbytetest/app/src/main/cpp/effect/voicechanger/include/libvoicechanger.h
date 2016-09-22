#ifndef LIBVOICECHANGER_H
#define LIBVOICECHANGER_H

int libVoiceChangerCreate_API(void **p);// 0: OK, -1: Failed
int libVoiceChangerFree_API(void *p);// 0: OK, -1: Failed

void libVoiceChangerReset_API(void *mVC);// called only one time after calling libVoiceChangerCreate_API

// samplerate: 8000/16000/48000
// channel: 1
// voicekind and environment:voicekind can change the pitch and the rate,enviroment give other effect such as reverb,vibrato,EQ,echo,etc.the two settings are independent
// voicekind:-1:Bypass;1:cat;2:man;8:slowly;7:fast; Don't set it with other value,or @dustinwang for support.   (If the voicechanger is used in communication, rate must not be changed)
// environment:-1:Bypass;3:vibrato;2:echo;Don't set it with other value,or @dustinwang for support.
// PTT example:Set (voicekind,environment) (1,-1) is "luoli"; (2,-1) is "uncle";(8,3) is "ghost"...(Because voicekind 8 will change the rate of sound, it must not be used in communication)

void libVoiceChangerCalcu_API(void *mVC,int samplerate,int channel,int voicekind,int environment);

//use libVoiceChangerCalcu_API2 to set tempodelta and pitchdelta:
//if setkind == 2 tempodelta, pitchdelta, adaptive, environment are used. we advice tempodelta(-80.0~200.0) pitchdelta(-10.0~10.0),adaptive set 0,environment set -1(if you only want to change rate or pitch) 
//if setkind == 0 voicekind,environment are used(then it's the same as libVoiceChangerCalcu_API)
void libVoiceChangerCalcu_API2(void *mVC,int samplerate,int channel,float tempodelta,float pitchdelta,int adaptive,int voicekind,int environment,int setkind);

//I : inLen: MUST be samplerate * 0.02
//I : input: the input PCM
//O: output: the output PCM
//O: outlen:when the rate is changed the length of output is not the same with inLen,otherwise "outlen = inLen"
void libVoiceChangerRun_API(void *mVC, short *input, int inLen, short *output,int *outlen);
void libVoiceChangerGetMEMpitch(void *mVC,float *pitch,int n);//get the pVC->mPitchControl."mempitchdeltan"
void libVoiceChangerSetMEMpitch(void *mVC,float pitch,int n);//set the pVC->mPitchControl."mempitchdeltan"

#endif