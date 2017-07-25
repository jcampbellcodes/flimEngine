#include "sndmathtools.h"

#define TWEEN_EPSILON 0.001f

bool nearEqual(float a, float b)
{

	float cmp = (a - b);
	cmp = (cmp < 0) ? -cmp : cmp;

	return (cmp) <= TWEEN_EPSILON;

}