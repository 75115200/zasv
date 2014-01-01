/*************************************************************************
> File Name:     CardManager.cpp
> Author:        Landerl Young
> Mail:          LanderlYoung@gmail.com
> Created Time:  2013/12/27 22:00:56
************************************************************************/
// to support pch
#include "stdafx.h"

#include "CardManager.h"
#include "Mwic_32.h"

CardManager::CardManager() :
m_icdev(0), m_passwdChecked(false), noPasswdFunc(0), notInitFunc(0)
{
}

CardManager::~CardManager()
{
}

//reserved
bool CardManager::writeBuffer(float balance)
{
	return true;
}

//reserved
float CardManager::getBuffer()
{
	return 0;
}

bool CardManager::writeBalance(float num)
{
	unsigned char *bytes = float2bytes(num);
	short st = swr_4442(m_icdev, BALANCE_ADDR, BALANCE_LEN, bytes);
	delete[] bytes;
	if (!st)
		return false;
	return true;

}

bool CardManager::writeInfo(DATA_T info_type,
							const std::string& data)
{
	int len = data.length();
	unsigned char *info = 0;
	short st = 0;
	switch (info_type) {
	case PUBLISHER:
		if (len > PUBLISHER_LEN)
			len = PUBLISHER_LEN;
		info = new unsigned char[len];
		memcpy(info, data.c_str(), sizeof(unsigned char)*len);
		st = swr_4442(m_icdev, PUBLISHER_ADDR, len, info);
		break;
	case CARD_ID:
		if (len > CARD_ID_LEN)
			len = CARD_ID_LEN;
		info = new unsigned char[len];
		memcpy(info, data.c_str(), sizeof(unsigned char)*len);
		st = swr_4442(m_icdev, CARD_ID_ADDR, len, info);
		break;
	case USER_NAME:
		if (len > USER_NAME_LEN)
			len = USER_NAME_LEN;
		info = new unsigned char[len];
		memcpy(info, data.c_str(), sizeof(unsigned char)*len);
		st = swr_4442(m_icdev, USER_NAME_ADDR, len, info);
		break;
	default:
		return false;
	}
	delete[] info;
	if (!st) {
		return false;
	}
	return true;
}

int CardManager::init(int port, long baud)
{
#ifdef _DEBUG
	m_icdev = (HANDLE)1;
	return 0;
#endif
	m_icdev = ic_init(port, baud);
	if (m_icdev  < 0) {
		return 1;
	}
	short status;
	short st = get_status(m_icdev, &status);
	if (st < 0) {
		m_icdev = 0;
		return 1;
	}
	if (status == 0) {
		m_icdev = 0;
		return 2;
	}
	if (turn_on(m_icdev) < 0) {
		m_icdev = 0;
		return 3;
	}
	return 0;
}

bool CardManager::disConnect()
{
	if (initConfirm()) {
		ic_exit(m_icdev);
		return true;
	} else {
		return false;
	}
}

int CardManager::getInfo(DATA_T data_type, std::string& out)
{
	if (!initConfirm()) {
		return -7;
	}
	unsigned char *info = 0;
	int len = 0;
	short st = 0;

	switch (data_type) {
		case PUBLISHER:
			len = PUBLISHER_LEN;
			info = new unsigned char[PUBLISHER_LEN];
			memset(info, 0, sizeof(unsigned char)*len);
			st = srd_4442(m_icdev, PUBLISHER_ADDR, len, info);
			break;
		case CARD_ID:
			len = CARD_ID_LEN;
			info = new unsigned char[len];
			memset(info, 0, sizeof(unsigned char)*len);
			st = srd_4442(m_icdev, CARD_ID_ADDR, len, info);
			break;
		default: //USER_NAME
			len = USER_NAME_LEN;
			info = new unsigned char[len];
			memset(info, 0, sizeof(unsigned char)*len);
			st = srd_4442(m_icdev, USER_NAME_ADDR, len, info);
			break;
	}
	if (!st)
		return 1;
	char *str = new char[len+1];
	memcpy(str, info, sizeof(char)*len);
	str[len] = 0;
	delete[] info;
	out = std::string(str);
	return 0;
}

bool CardManager::checkPassWd(const unsigned char *key)
{
#ifdef _DEBUG
	m_passwdChecked = true;
	return true;
#endif
	if (!initConfirm()) {
		return false;
	}
	unsigned char *passwd = const_cast<unsigned char*>(key);
	if (!csc_4442(m_icdev, 3, passwd)) {
		m_passwdChecked = true;
		return true;
	} else {
		return false;
	}
}

int CardManager::release(float initialBalance)
{
	if (!initConfirm()) {
		return -1;
	}
	std::string publisher("Young Co.,Ltd");
	std::string card_id("1234567890");
	std::string userName("Sakura Kyoko");
	if (!writeInfo(PUBLISHER, publisher)) {
		return 1;
	}
	if (!writeInfo(CARD_ID, card_id)) {
		return 2;
	}
	if (!writeInfo(USER_NAME, userName)) {
		return 3;
	}
	if (!writeBalance(initialBalance)) {
		return 4;
	}
	return 0;
}

int CardManager::consume(float costs)
{
	if (!initConfirm() || !passWordConfirm()) {
		return -7;
	}
	if (costs < 0)
		return -1;
	float cur_balance = getBalance();
	if (cur_balance < costs) {
		return 1;
	}
	cur_balance -= costs;
	if (!writeBalance(cur_balance)) {
		return 2;
	}
	return 0;
}

float CardManager::getBalance()
{
	if (!initConfirm()) {
		return -7;
	}
	unsigned char balance_c[4];
	short st = srd_4442(m_icdev, BALANCE_ADDR, BALANCE_LEN, balance_c);
	float balance = bytes2float(balance_c);
	return balance;
}

int CardManager::charge(float amount)
{
	if (!initConfirm() || !passWordConfirm()) {
		return -7;
	}
	if (amount <= 0) {
		return -1;
	}
	float cur_balance = getBalance();
	cur_balance += amount;
	if (!writeBalance(amount)) {
		return 1;
	}
	return 0;
}

unsigned char* CardManager::float2bytes(float num)
{
	union {
		float f;
		unsigned char byte[4];
	} r;
	r.f = num;
	unsigned char *bytes = new unsigned char[4];
	for (int i = 0; i < 4; i++) {
		bytes[i] = r.byte[i];
	}
	return bytes;
}

float CardManager::bytes2float(unsigned char* bytes)
{
	union {
		float f;
		unsigned char byte[4];
	} r;
	for (int i = 0; i < 4; i++) {
		r.byte[i] = bytes[i];
	}
	return r.f;
}
