#include "inc/rtv1.h"

t_vec	ft_vectoradd(t_vec vec1, t_vec vec2)
{
	t_vec	vec;

	vec.x = vec1.x + vec2.x;
	vec.y = vec1.y + vec2.y;
	vec.z = vec1.z + vec2.z;
	return (vec);
}

short	lower_than_min(double t, t_thr *thr, t_o *obj, t_vec ray)
{
	t_vec	add;
	t_vec	sub;

	sub = ft_vectoradd(ray, ft_vectorscale(&thr->ray_dir, t));
	add = ft_vectorsub(&sub, &obj->pos);
	if (t > 0)
	{
		if (ft_vectordot(&obj->rot, &add) > 0.0)
			return (0);
	}
	else
		return (1);
	return (0);
}

short	higher_than_max(double t, t_thr *thr, t_o *obj, t_vec ray)
{
	t_vec	sub;
	t_vec	add;
	t_vec	add2;

	add = ft_vectoradd(ray, ft_vectorscale(&thr->ray_dir, t));
	add2 = ft_vectoradd(obj->pos, ft_vectorscale(&obj->rot, obj->size));
	sub = ft_vectorsub(&add, &add2);
	if (t > 0)
	{
		if (ft_vectordot(&obj->rot, &sub) < 0.0)
			return (0);
	}
	else
		return (1);
	return (0);
}


float	finit_cone(t_thr *thr, t_o *obj, t_vec ray)
{
	short	r1_too_low;
	short	r1_too_high;
	short	r2_too_low;
	short	r2_too_high;

	r1_too_low = lower_than_min(thr->t0, thr, obj, ray);
	r1_too_high = higher_than_max(thr->t0, thr, obj, ray);
	r2_too_low = lower_than_min(thr->t1, thr, obj, ray);
	r2_too_high = higher_than_max(thr->t1, thr, obj, ray);

	if (r1_too_low == 1 || r1_too_high == 1)
	{
		if (r2_too_low == 1 || r2_too_high == 1)
			return (-1);
		return (thr->t1);
	}
	else
		return (thr->t0);
}


