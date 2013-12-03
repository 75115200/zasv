#ifndef _TRAVEL_H_
#define _TRAVEL_H_

#include "btree.h"

void preOrder_r(BTNode *b);
void inOrder_r(BTNode *b);
void postOrder_r(BTNode *b);

void preOrder(BTNode *b);
void inOrder(BTNode *b);
void postOrder_1(BTNode *b);
void postOrder_2(BTNode *b);
void postOrder_3(BTNode *b);

void levelOrder(BTNode *b);

#endif