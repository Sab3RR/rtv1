#include "inc/rtv1.h"

double	nearest_cone(t_thr *thr, t_o *obj, t_vec ray, t_vec pos)
{
	double	disc;
	double	angl;

	angl = 1 / obj->size;
	thr->dist = ft_vectorsub(&pos, &obj->pos);
	ft_vectornorm(&obj->rot);
	thr->a = ft_vectordot(&ray, &ray) - (1 + pow(angl, 2)) *
			pow(ft_vectordot(&ray, &obj->rot), 2);
	thr->b = 2 * (ft_vectordot(&ray, &thr->dist) - (1 + pow(angl, 2))
			* ft_vectordot(&ray, &obj->rot) * ft_vectordot(&thr->dist, &obj->rot));
	thr->c = ft_vectordot(&thr->dist, &thr->dist) - (1 +
			pow(angl, 2)) * pow(ft_vectordot(&thr->dist, &obj->rot), 2);
	disc = thr->b * thr->b - 4 * thr->a * thr->c;
	if (disc < 0)
		return (-1);
	thr->t0 = (-thr->b + sqrtf(disc)) / (2 * thr->a);
	thr->t1 = (-thr->b - sqrtf(disc)) / (2 * thr->a);
	if (thr->t0 > thr->t1)
		thr->t0 = thr->t1;
	return (finit_cone(thr, obj, ray));
//	return (thr->t0);
}

double	nearest_cylinder(t_thr *thr, t_o *obj, t_vec ray, t_vec pos)
{
	double disc;

	thr->dist = ft_vectorsub(&pos, &obj->pos);
	ft_vectornorm(&obj->rot);
	thr->a = ft_vectordot(&ray, &ray) - pow(ft_vectordot(&ray, &obj->rot), 2);
	thr->b = 2 * (ft_vectordot(&ray, &thr->dist) -
				  (ft_vectordot(&ray, &obj->rot) * ft_vectordot(&thr->dist, &obj->rot)));
	thr->c = ft_vectordot(&thr->dist, &thr->dist) -
			 pow(ft_vectordot(&thr->dist, &obj->rot), 2) - pow(obj->size, 2);
	disc = thr->b * thr->b - 4 * thr->a * thr->c;
	if (disc < 0)
		return (-1);
	thr->t0 = (-thr->b + sqrtf(disc)) / (2 * thr->a);
	thr->t1 = (-thr->b - sqrtf(disc)) / (2 * thr->a);
	if (thr->t0 > thr->t1)
		thr->t0 = thr->t1;
	return (thr->t0);
}

double	nearest_sphere(t_thr *thr, t_o *obj, t_vec ray, t_vec pos)
{
	double disc;

	thr->dist = ft_vectorsub(&pos, &obj->pos);
	thr->a = ft_vectordot(&ray, &ray);
	thr->b = 2 * ft_vectordot(&ray, &thr->dist);
	thr->c = ft_vectordot(&thr->dist, &thr->dist) - (obj->size * obj->size);
	disc = thr->b * thr->b - 4 * thr->a * thr->c;
	if (disc < 0)
		return (-1);
	thr->t0 = (-thr->b + sqrtf(disc)) / (2 * thr->a);
	thr->t1 = (-thr->b - sqrtf(disc)) / (2 * thr->a);
	if (thr->t0 > thr->t1)
		thr->t0 = thr->t1;
	return (thr->t0);
}

double	nearest_plane(t_thr *thr, t_o *obj, t_vec ray, t_vec pos)
{
	thr->t0 = ((ft_vectordot(&obj->rot, &obj->pos) -
				ft_vectordot(&obj->rot, &pos)) / ft_vectordot(&obj->rot, &ray));
	if (thr->t0 < 0.0001)
		return (-1);
	return (thr->t0);
}

t_o		*nearest_obj(t_thr *thr, t_o *obj, t_vec ray, t_vec pos)
{
	t_o		*tmp;
	double	dist;

	tmp = NULL;
	thr->t = 80000.0;
	while (obj != NULL)
	{
		if (obj->type == 1)
			dist = nearest_cone(thr, obj, ray, pos);
		else if (obj->type == 2)
			dist = nearest_cylinder(thr, obj, ray, pos);
		else if (obj->type == 3)
			dist = nearest_plane(thr, obj, ray, pos);
		else if (obj->type == 4)
			dist = nearest_sphere(thr, obj, ray, pos);
		if (dist > 0.0001 && dist < thr->t)
		{
			tmp = obj;
			thr->t = dist;
		}
		obj = obj->next;
	}
	return (tmp);
}
