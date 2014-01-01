/*************************************************************************
> File Name:     CardManager.cpp
> Author:        Landerl Young
> Mail:          LanderlYoung@gmail.com
> Created Time:  2013/12/27 22:00:37
************************************************************************/
#pragma once
#include <iostream>
#include <Windows.h>

class CardManager {
public:
	enum DATA_T {
		PUBLISHER,
		CARD_ID,
		USER_NAME,
	};

private:
	const short PUBLISHER_ADDR = 0x40;
	const short PUBLISHER_LEN = 0x10;
	const short CARD_ID_ADDR =
		PUBLISHER_ADDR + PUBLISHER_LEN;
	const short CARD_ID_LEN = 0x10;
	const short USER_NAME_ADDR =
		CARD_ID_ADDR + CARD_ID_LEN;
	const short USER_NAME_LEN = 0x10;
	const short BALANCE_ADDR =
		USER_NAME_ADDR + USER_NAME_LEN;
	const short BALANCE_LEN = 0x04; //sizeof(float)
	const short BALANCE_BUF_ADDR =
		BALANCE_ADDR + BALANCE_LEN;
	const short BALANCE_BUF_LEN = BALANCE_LEN;

	HANDLE m_icdev;
	bool m_passwdChecked;
	void(*noPasswdFunc)(void);
	void(*notInitFunc)(void);

	inline bool passWordConfirm()
	{
		if (noPasswdFunc && !m_passwdChecked) {
			noPasswdFunc();
		}
		return m_passwdChecked;
	}
	inline bool initConfirm()
	{
		if (notInitFunc && !m_icdev) {
			notInitFunc();
		}
		return m_icdev != 0;
	}
	bool writeBalance(float num);
	bool writeInfo(DATA_T info_type,
				   const std::string& data);
	float getBuffer();
	bool writeBuffer(float balance);

	static unsigned char *float2bytes(float num);
	static float bytes2float(unsigned char* bytes);
public:
	CardManager();
	virtual ~CardManager();

	inline bool isInited()
	{
		return m_icdev != 0;
	}

	inline void setNoPasswdCallBack(void(*callBack)(void))
	{
		noPasswdFunc = callBack;
	}
	inline void setNotInitCallBack(void(*callback)(void))
	{
		notInitFunc = callback;
	}

	/*
	return 0 for ok
	1 for init device error
	2 for no card
	*/
	int init(int port, long baud);
	bool disConnect();
	int getInfo(DATA_T data_type, std::string& out);
	bool checkPassWd(const unsigned char* key);
	/*
	return 0 for ok
	*/
	int release(float initialBalance);
	/*
	return 0 for ok
	*/
	int consume(float costs);
	float getBalance();
	int charge(float amount);
};