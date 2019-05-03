#include "inc/rtv1.h"

void	fzero(float *s, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		s[i] = 0.0f;
		i++;
	}
}

float	equalizer(float value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}

t_vec	norm(t_thr *thr, t_o *obj, t_vec pos)
{
	t_vec	norm;
	t_vec	temp;
	t_vec	temp2;

	if (obj->type == 1 || obj->type == 2)
	{
		temp = ft_vectorscale(&obj->rot,
							  (ft_vectordot(&thr->ray_dir, &obj->rot) * thr->t0
							   + ft_vectordot(&thr->dist, &obj->rot)));
		if (obj->type == 1)
			temp = ft_vectorscale(&temp, (1 + pow(tan(obj->size), 2)));
		temp2 = ft_vectorsub(&pos, &obj->pos);
		norm = ft_vectorsub(&temp2, &temp);
	}
	else if (obj->type == 3)
		norm = obj->rot;
	if (obj->type == 4)
		norm = ft_vectorsub(&pos, &obj->pos);
	ft_vectornorm(&norm);
	return (norm);
}

float		*addlight(t_o *obj, t_o *light, float *tab, float d)
{
	tab[3] = equalizer(tab[3] * 4.0 * d, 0.0, 1.0);
	tab[0] += tab[3] * (obj->col.red / 255) * (light->col.red / 255);
	tab[1] += tab[3] * (obj->col.green / 255) * (light->col.green / 255);
	tab[2] += tab[3] * (obj->col.blue / 255) * (light->col.blue / 255);
	return (tab);
}

float	sp(t_thr *thr, t_vec dist, float d, float lambert)
{
	float	tmp;
	float	spec;
	t_vec	ref;

	spec = 0.0;
	ref = ft_vectorscale(&thr->norm, (2.0 * ft_vectordot(&thr->norm, &dist)));
	ref = ft_vectorsub(&dist, &ref);
	if ((tmp = ft_vectordot(&ref, &thr->ray_dir)) > 0.0 && lambert > 0.15)
	{
		spec = pow(tmp, 20.0) * 4 * d;
		spec = equalizer(spec, 0.0, 1.0);
	}
	return (spec);
}