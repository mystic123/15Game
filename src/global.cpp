/*
 * 15Game
 * 
 * Author: Paweł Kapica
 * 
 */

#include "global.h"

namespace {
	direction operator*(direction dir, int a)
	{
		direction dir2 = { dir.x*a, dir.y*a };
		return dir2;
	}

	direction& operator*=(direction &dir, int a)
	{
		dir.x=dir.x*a;
		dir.y=dir.y*a;
		return dir;
	}

	int sgn(int x)
	{
		if (x>0)
			return 1;
		else if (x<0)
			return -1;
		else
			return 0;
	}
}
