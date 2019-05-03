#include "inc/rtv1.h"

float	*fequlizer(float *r, float *tab)
{
	r[0] += equalizer(tab[0], 0.0, 1.0);
	r[1] += equalizer(tab[1], 0.0, 1.0);
	r[2] += equalizer(tab[2], 0.0, 1.0);
	return (r);
}