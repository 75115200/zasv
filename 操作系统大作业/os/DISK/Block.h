/*************************************************************************
    > File Name:     Block.h
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  2013年05月15日 星期三 10时23分24秒
 ************************************************************************/
#ifndef __BLOCK_H__
#define __BLOCK_H__
class Block {
	public:
		Block(int blockNum);
		~Block();
		int getBlockNum();
	private:
		const int _blockNum;
};

Block::Block(int blockNum) :
	_blockNum(blockNum) {
	}

Block::~Block() {

}

int Block::getBlockNum() {
	return _blockNum;
}
#endif
