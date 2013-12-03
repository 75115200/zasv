/*************************************************************************
  > File Name:     Sector.h
  > Author:        Landerl Young
  > Mail:          LanderlYoung@gmail.com 
  > Created Time:  2013年05月15日 星期三 10时25分34秒
 ************************************************************************/
#ifndef __SECTOR_H__
#define __SECTOR_H__

#include <vector>
#include "Block.h"
using namespace std;

class Sector {
	public:
		const int groupSize;
		int freeBlocks(vector<int> *p) const;
		bool freeBlock(int blockNum) const;
		Sector(int groupSize);
		Sector(int blockNumFrom, int blockNumEnd);
		~Sector();
		int getAvaliableSize() const;
		vector<Block*> *requestBlock(int number) const;
		vector<Block*> *getBlocks() const;
	private:
		vector<Block*> * const group;
		bool contains(int blockNum) const;
};
Sector::Sector(int groupSize):
	group(new vector<Block*>()), groupSize(groupSize) {
	}

Sector::Sector(int blockNumFrom, int blockNumEnd):
	group(new vector<Block*>()), groupSize(blockNumEnd - blockNumFrom + 1) {
		int i = blockNumFrom;
		for(; i <= blockNumEnd; i++) 
			group->push_back(new Block(i));
	}

Sector::~Sector() {
	vector<Block*>::iterator it = group->begin();
	for(; it !=group->end(); it++)
		delete *it;
	delete group;
}

int Sector::getAvaliableSize() const{
	return group->size();
}

vector<Block*>* Sector::requestBlock(int number) const {
	vector<Block*> *res = new vector<Block*>;
	number = number > group->size() ? group->size() : number;
	for (int i = 0; i < number; i++) {
		if(group->size() == 1) {
			res->push_back(group->front());
			group->erase(group->begin());
		} else {
			res->push_back(group->at(1));
			group->erase(++group->begin());
		}
	}
	return res;
}

int Sector::freeBlocks(vector<int> *p) const {
	int res;
	int avaliableSize = groupSize - group->size();
	if(avaliableSize < p->size())
		res = avaliableSize;
	else
		res = p->size();

	vector<int>::iterator it = p->begin();

	for(int i = 0; i < res; i++) {
		group->push_back(new Block(*it));
		it++;
	}
	return res;
}

bool Sector::freeBlock(int blockNum) const {
	if(getAvaliableSize() == groupSize)
		return false;
	group->push_back(new Block(blockNum));
	return true;
}

bool Sector::contains(int blockNum) const{
	vector<Block*>::iterator it;
	for( it = group->begin(); it != group->end(); it++) {
		if ((*it)->getBlockNum() == blockNum)
			return true;
	}
	return false;
}

vector<Block*> *Sector::getBlocks() const{
	return group;
}
#endif
