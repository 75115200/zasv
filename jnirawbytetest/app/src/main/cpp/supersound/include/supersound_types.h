
//+ ----------------------------------------------------
//+ SuperSound相关类型定义
//+ ----------------------------------------------------

#ifndef __SUPERSOUND_TYPES_H__
#define __SUPERSOUND_TYPES_H__


//+ ----------------------------------------------------
//+ SuperSound实例定义
//+ ----------------------------------------------------
typedef void* SUPERSOUND_INST;

//+ ----------------------------------------------------
//+ 音效类型定义
//+ ----------------------------------------------------
enum SUPERSOUND_EFFECT_TYPE
{
	SUPERSOUND_NONE_TYPE,			//无音效
	SUPERSOUND_SURROUND_TYPE,		//全景环绕
	SUPERSOUND_BASS_TYPE,			//超重低音
	SUPERSOUND_VOCAL_TYPE,			//清澈人声
	SUPERSOUND_STUDIO_TYPE,			//现场律动

	SUPERSOUND_MAX_TYPE,			//类型最大值，限制输入
};

//+ ----------------------------------------------------
//+ 音效强度范围定义
//+ ----------------------------------------------------
//全景环绕部分
#define SUPERSOUND_SURROUND_PARAM_MIN		(0.0f)
#define SUPERSOUND_SURROUND_PARAM_DEFAUT	(1.3f)
#define SUPERSOUND_SURROUND_PARAM_MAX		(3.0f)
//超重低音部分
#define SUPERSOUND_BASS_PARAM_MIN			(0.0f)
#define SUPERSOUND_BASS_PARAM_DEFAUT		(1.5f)
#define SUPERSOUND_BASS_PARAM_MAX			(3.0f)
//清澈人声部分
#define SUPERSOUND_VOCAL_PARAM_MIN			(0.0f)
#define SUPERSOUND_VOCAL_PARAM_DEFAUT		(0.1f)
#define SUPERSOUND_VOCAL_PARAM_MAX			(1.5f)
//现场律动部分
#define SUPERSOUND_STUDIO_PARAM_MIN			(1.0f)
#define SUPERSOUND_STUDIO_PARAM_DEFAUT		(1.5f)
#define SUPERSOUND_STUDIO_PARAM_MAX			(2.0f)


#endif /* __SUPERSOUND_TYPES_H__ */