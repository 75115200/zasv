/************************************************************************/
/* volume infterface                                                   */
/* written by ethanzhao, 6-4, 2015.                                     */
/* copy right reserved.                                                 */
/************************************************************************/
#ifndef C_KALA_VOLUME_Z_H
#define C_KALA_VOLUME_Z_H

#include "KalaInterfaces.h"

class LIB_KALAAUDIOBASE_API CKalaVolume:public IKalaVolume
{
public:

	/* input pcm samples, just for mono, and output volume value, out value in [0,100] */
	int Process(const char* inBuffer, int inSize, int* outVolume);

private:
	
};



#endif





