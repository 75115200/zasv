
//+ ----------------------------------------------------
//+ SuperSound的对外接口定义
//+ ----------------------------------------------------

#ifndef __SUPERSOUND_API_H__
#define __SUPERSOUND_API_H__


#include <stdint.h>
#include "supersound_types.h"

#if defined(_MSC_VER)
#if !defined(__SUPERSOUND_API)
#define __SUPERSOUND_API __stdcall
#endif
#else
#if !defined(__SUPERSOUND_API)
#define __SUPERSOUND_API  __attribute__ ((visibility("default")))
#endif
#endif

//+ ----------------------------------------------------
//+ 全局初始化函数，整个过程只调用一次
//+ 返回值为errCode
//+ ----------------------------------------------------
int32_t __SUPERSOUND_API supersound_init();

//+ ----------------------------------------------------
//+ 设置数据模型路径，内部通过fopen来打开，需要相关权限设置，只调用一次，因为内部在需要的时候才加载，所以外部保证可用性
//+ pPathLL：左声道对左声道影响模型
//+ pPathLR：左声道对右声道影响模型
//+ pPathRL：右声道对左声道影响模型
//+ pPathRR：右声道对右声道影响模型
//+ 返回值为errCode
//+ ----------------------------------------------------
int32_t __SUPERSOUND_API supersound_set_datamodel(const char * pPathLL, const char * pPathLR, const char * pPathRL, const char * pPathRR);

//+ ----------------------------------------------------
//+ 创建音效实例，线程安全
//+ pInst：标识实例指针
//+ nSamplerate：输入音频的采样率
//+ nChannles：输入音频的声道数
//+ 返回值为errCode
//+ ----------------------------------------------------
int32_t __SUPERSOUND_API supersound_create_inst(SUPERSOUND_INST * pInst, int32_t nSamplerate, int32_t nChannels);

//+ ----------------------------------------------------
//+ 设置音效以及效果强度，设置了这个之后，效果生效，线程安全
//+ inst：标识实例指针
//+ eType：需要改变强度的音效类型
//+ fInstensity：目标强度
//+ 返回值为errCode
//+ ----------------------------------------------------
int32_t __SUPERSOUND_API supersound_set_intensity(SUPERSOUND_INST inst, SUPERSOUND_EFFECT_TYPE eType, float fInstensity);

//+ ----------------------------------------------------
//+ 获取需要延迟补偿的点数，如果外围不支持，可以不调用，只是最后会少一点数据，一个实例只需调用一次，线程安全
//+ inst：标识实例指针
//+ 返回值为需要延迟补偿的采样点的数量，在最后使用相同数量的0来补充
//+ ----------------------------------------------------
int32_t __SUPERSOUND_API supersound_get_lookahead(SUPERSOUND_INST inst);

//+ ----------------------------------------------------
//+ 对浮点数据音频进行处理，同一个实例必须顺序执行
//+ inst：标识实例指针
//+ pdata：音频流数据
//+ nSamples：输入的音频长度（采样点），同时也是输出音频长度（需要考虑延迟补偿）
//+ mSamples = len(PCM data) / len(PCM)
//+ 返回值为errCode
//+ ----------------------------------------------------
int32_t __SUPERSOUND_API supersound_processf(SUPERSOUND_INST inst, float * pdata, int32_t nSamples);

//+ ----------------------------------------------------
//+ 对整型数据音频进行处理，内部转换成浮点数据处理，同一个实例必须顺序执行
//+ inst：标识实例指针
//+ pdata：音频流数据
//+ nSamples：输入的音频长度（采样点），同时也是输出音频长度（需要考虑延迟补偿）
//+ 返回值为errCode
//+ ----------------------------------------------------
int32_t __SUPERSOUND_API supersound_process(SUPERSOUND_INST inst, short * pdata, int32_t nSamples);

//+ ----------------------------------------------------
//+ 销毁音效实例，线程安全
//+ pInst：待销毁的音效实例
//+ ----------------------------------------------------
void __SUPERSOUND_API supersound_destory_inst(SUPERSOUND_INST * pInst);

//+ ----------------------------------------------------
//+ 全局逆初始化函数，整个过程只调用一次
//+ ----------------------------------------------------
void __SUPERSOUND_API supersound_uninit();


#endif /* __SUPERSOUND_API_H__ */