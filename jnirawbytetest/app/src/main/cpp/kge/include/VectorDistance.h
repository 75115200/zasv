#ifndef SONG_VECTOR_DISTANCE_H
#define SONG_VECTOR_DISTANCE_H

/* 
* Des:
*	calculate distance for int data, the vector input be the same length, and output
*	distance, [0,100], 100 means the same, and 0 means no relationship.
*
*/
int	calDistanceInt100	(int* pVec1, int* pVect2, int iNum, int* iDistance);


/* 
* Des:
*	calculate distance for int data, the vector input be the same length, and output
*	distance, [0,100], 100 means the same, and 0 means no relationship.
*
*/
int	calDistanceInt200	(const int* pV, const int* pN, int iLen, int* iDistance);

/* 
* Des:
*	calculate distance for int data, the vector input be the same length, and output
*	distance, [0,100], 100 means the same, and 0 means no relationship.
*
*/
int	calDistanceInt300	(const int* pV, const int* pN, int iLen, int* iDistance);

#endif
