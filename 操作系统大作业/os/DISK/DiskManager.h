/*************************************************************************
  > File Name:     DiskManager.h
  > Author:        Landerl Young
  > Mail:          LanderlYoung@gmail.com 
  > Created Time:  2013年05月15日 星期三 10时24分01秒
 ************************************************************************/
#ifndef __DISK_MANAGER_H__
#define __DISK_MANAGER_H__

#include <iostream>
#include <stdio.h>
#include <vector>
#include "Sector.h"
using namespace std;

class DiskManager {
	public:
		const int blocksPerGroup;
		DiskManager(int size, int blocksPerGroup = 8);
		~DiskManager();
		vector<Block*> *request(int size);
		bool free(int blockNum);
		bool free(vector<int> *blockNums);
		void showStatus();
	private:
		vector<Sector*> *sects;
		void show(vector<Block*> *p);
};

DiskManager::DiskManager(int size, int blocksPerGroup):
	sects(new vector<Sector*>()), blocksPerGroup(blocksPerGroup)
{
	int groups = size / blocksPerGroup;
	int left = size % blocksPerGroup;
	for(int i = 0; i < groups; i++) {
		sects->push_back(
				new Sector(i*blocksPerGroup, (i+1)*blocksPerGroup - 1));
	}
	if (left != 0) {
		sects->push_back(
				new Sector(groups*blocksPerGroup - 1, size -1));
	}
}

DiskManager::~DiskManager() {
	vector<Sector*>::iterator it = sects->begin();
	for(;it != sects->end(); it++)
		delete *it;
	delete sects;
}

vector<Block*> *DiskManager::request(int size) {
	vector<Sector*>::iterator it = sects->begin();
	vector<Block*> *tmp, *res = new vector<Block*>();
	while(size != 0 || it != sects->end()) {
		tmp = (*it)->requestBlock(size);
		size -= tmp->size();
		res->insert(res->end(), tmp->begin(), tmp->end());

		if((*it)->getAvaliableSize() == 0)
			sects->erase(it);
		else 
			it++;
	}

	return res;
}

bool DiskManager::free(int blockNum) {
	vector<Sector*>::iterator it = sects->begin();
	while((*it)->getAvaliableSize() == (*it)->groupSize) {
		it++;
		if(it == sects->end()) {
			Sector * s = new Sector(blocksPerGroup);
			sects->push_back(s);
		}
	}
	(*it)->freeBlock(blockNum);
	return true;
}

/*
 * Old version old free method
 * bad performance
 *
 
bool DiskManager::free(vector<int> *blockNums) {
	vector<int>::iterator it = blockNums->begin();
	for(;it !=blockNums->end(); it++) {
		if(!free(*it))
			return false;
	}
	return true;
}
*/

bool DiskManager::free(vector<int> *blockNums) {
	int count = blockNums->size();
	int tmp;
	vector<Sector*>::iterator it = sects->begin();
	while(count > 0) {
		while((*it)->getAvaliableSize() == (*it)->groupSize) {
			it++;
			if(it == sects->end()) {
				Sector * s = new Sector(blocksPerGroup);
				sects->push_back(s);
			}
		}

		tmp = (*it)->freeBlocks(blockNums);
		count -= tmp;
		if (count != 0) {
			blockNums->erase(blockNums->begin(), blockNums->begin() + tmp);
		}
	}
	return true;
}

void DiskManager::showStatus() {
	int sector = 0;
	cout << "----------Disk Status-----------\n";
	vector<Sector*>::iterator it = sects->begin();
	for(;it != sects->end(); it++) {
		cout << "sector[" << sector++ << "]" ;
		show((*it)->getBlocks());
	}
	cout << "--------------------------------\n";
}

void DiskManager::show(vector<Block*> *p) {
	if(p->size() == 0){
		cout << "null\n";
		return;
	}
	vector<Block*>::iterator it = p->begin();
	for(; it !=p->end(); it++)
		cout << (*it)->getBlockNum() << " ";
	cout << endl;
}
#endif
