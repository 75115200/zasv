
//+ ----------------------------------------------------
//+ SuperSound相关错误码
//+ ----------------------------------------------------

#ifndef __SUPERSOUND_ERR_H__
#define __SUPERSOUND_ERR_H__


enum
{
	ERROR_SUPERSOUND_SUCCESS = 0,		//成功
	ERROR_SUPERSOUND_FAILED = -1,		//外围错误

	ERROR_SUPERSOUND_PARAM = 1000,		//参数错误，一般为传入了空指针
	ERROR_SUPERSOUND_NOT_SUPPORT,		//不支持，一般为通道数和采样率
	ERROR_SUPERSOUND_NO_MEMORY,			//内存申请失败
	ERROR_SUPERSOUND_LOAD_MODEL,		//加载数据模型失败
	ERROR_SUPERSOUND_HAS_SET_MODEL,		//已经设置过数据模型
	ERROR_SUPERSOUND_NOT_LOAD_MODEL,	//未加载数据模型
};


#endif /* __SUPERSOUND_ERR_H__ */