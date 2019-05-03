#include "inc/rtv1.h"

t_o	*nearest_ref(t_thr *thr, t_o *node, t_o *obj, t_vec pos)
{
	t_o		*tmp;
	double	dist;

	tmp = NULL;
	while (node != NULL)
	{
		if (node != obj)
		{
			if (node->type == 1)
				dist = nearest_cone(thr, node, thr->ref, pos);
			else if (node->type == 2)
				dist = nearest_cylinder(thr, node, thr->ref, pos);
			else if (node->type == 3)
				dist = nearest_plane(thr, node, thr->ref, pos);
			else if (node->type == 4)
				dist = nearest_sphere(thr, node, thr->ref, pos);
			if (dist > 0.0001 && dist < thr->t)
			{
				tmp = node;
				thr->t = dist;
			}
		}
		node = node->next;
	}
	return (tmp);
}

t_o	*ref_init(t_thr *thr, t_o *obj, t_vec *pos)
{
	t_o	*tmp;

	thr->t = 8000.0;
	thr->ref = ft_vectorscale(&thr->norm,
							  (2 * ft_vectordot(&thr->refpos, &thr->norm)));
	thr->ref = ft_vectorsub(&thr->refpos, &thr->ref);
	ft_vectornorm(&thr->ref);
	tmp = nearest_ref(thr, thr->obj, obj, *pos);
	if (!tmp)
		return (NULL);
	*pos = (t_vec){pos->x + thr->t * thr->ref.x, pos->y +
				thr->t * thr->ref.y, pos->z + thr->t * thr->ref.z};
	thr->refpos = (t_vec){thr->ref.x, thr->ref.y, thr->ref.z};
	thr->norm = norm(thr, tmp, *pos);
	return (tmp);
}

int		shadow(t_thr *mlx, t_o *tmp, t_o *light, t_vec pos)
{
	t_o	*obj;
	t_vec	dist;

	obj = mlx->obj;
	dist = ft_vectorsub(&light->pos, &pos);
	mlx->t = sqrtf(ft_vectordot(&dist, &dist));
	ft_vectornorm(&dist);
	while (obj != NULL)
	{
		if (obj != tmp)
		{
			if (obj->type == 1)
				mlx->a = nearest_cone(mlx, obj, dist, pos);
			else if (obj->type == 2)
				mlx->a = nearest_cylinder(mlx, obj, dist, pos);
			else if (obj->type == 3)
				mlx->a = nearest_plane(mlx, obj, dist, pos);
			else if (obj->type == 4)
				mlx->a = nearest_sphere(mlx, obj, dist, pos);
			if (mlx->a > 0.0001 && mlx->a < mlx->t)
				return (1);
		}
		obj = obj->next;
	}
	return (0);
}

float	*reflect_obj(t_thr *thr, t_o *obj, t_vec *pos, float *tab)
{
	t_o		*tmp;
	t_o		*light;
	t_vec	dist;
	double	d;

	if (thr->cpt >= thr->maxref || (light = thr->light) == NULL)
		return (tab);
	if ((tmp = ref_init(thr, obj, pos)) == NULL || (thr->cpt++) < 0)
		return (tab);
	while (light != NULL)
	{
		tab[3] = 0.14;
		dist = ft_vectorsub(&light->pos, pos);
		d = equalizer(1.0 / sqrtf(sqrtf(ft_vectordot(&dist, &dist))), 0.0, 1.0);
		ft_vectornorm(&dist);
		if (shadow(thr, tmp, light, *pos) == 0)
			tab[3] += equalizer(ft_vectordot(&dist, &thr->norm), 0.0, 1.0);
		tab = addlight(tmp, light, tab, d);
		tab[0] += (COND) ? sp(thr, dist, d, tab[3]) : 0.0;
		tab[1] += (COND) ? sp(thr, dist, d, tab[3]) : 0.0;
		tab[2] += (COND) ? sp(thr, dist, d, tab[3]) : 0.0;
		light = light->next;
	}
	return ((PREF) ? tab : reflect_obj(thr, tmp, pos, tab));
}

float	*light(t_thr *thr, t_o *tmp, t_o *light, float *tab)
{
	t_vec	dist;
	t_vec	pos;
	float	d;

	pos = (t_vec){thr->cam_pos.x + thr->t * thr->ray_dir.x, thr->cam_pos.y +
			   thr->t * thr->ray_dir.y, thr->cam_pos.z + thr->t * thr->ray_dir.z};
	thr->norm = norm(thr, tmp, pos);
	while (light != NULL)
	{
		tab[3] = 0.15;
		dist = ft_vectorsub(&light->pos, &pos);
		d = equalizer((1.0 / sqrtf(sqrtf(ft_vectordot(&dist, &dist)))), 0., 1.);
		ft_vectornorm(&dist);
		if (shadow(thr, tmp, light, pos) == 0)
			tab[3] += equalizer(ft_vectordot(&dist, &thr->norm), 0.0, 1.0);
		tab = addlight(tmp, light, tab, d);
		tab[0] += (COND) ? sp(thr, dist, d, tab[3]) : 0.0;
		tab[1] += (COND) ? sp(thr, dist, d, tab[3]) : 0.0;
		tab[2] += (COND) ? sp(thr, dist, d, tab[3]) : 0.0;
		light = light->next;
	}
	thr->refpos = (t_vec){thr->ray_dir.x, thr->ray_dir.y, thr->ray_dir.z};
	return ((COND) ? tab : reflect_obj(thr, tmp, &pos, tab));
}