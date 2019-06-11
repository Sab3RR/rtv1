/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:57:42 by vsusol            #+#    #+#             */
/*   Updated: 2019/06/11 16:57:48 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/rtv1.h"

float	*ray_set(t_thr *thr, float *tab, double x, double y)
{
	double	u;
	double	v;

	u = (D_WIDTH - x * 2.0) / D_HEIGHT;
	v = (D_HEIGHT - y * 2.0) / D_WIDTH;
	K = ft_vectorsub(&thr->cam_rot, &thr->cam_pos);
	ft_vectornorm(&K);
	I = ft_vectorcross(&K, &(t_vec){0.0, 1.0, 0.0});
	ft_vectornorm(&I);
	J = ft_vectorcross(&I, &K);
	thr->ray_dir = (t_vec){u * I.x + v * J.x + FOV * K.x, u * I.y + v * J.y
						+ FOV * K.y, u * I.z + v * J.z + FOV * K.z};
	ft_vectornorm(&thr->ray_dir);
	fzero(tab, 4);
	thr->cpt = 0;
	return (tab);
}

void	ft_put_pixel(t_thr *thr, int x, int y, int color)
{
	int				i;
	unsigned int	p;

	i = 0;
	p = x * (thr->bpp / 8) + y * (thr->size_line);
	while (i < (thr->bpp / 8))
	{
		thr->img_addr[p + i] = color;
		color >>= 8;
		i++;
	}
}

int		rt(t_thr *thr, t_o *obj, double x, double y)
{
	float	r[3];
	t_o		*tmp;
	double	p;
	float	*tab;

	if (!(tab = (float *)malloc(sizeof(float) * 4)))
		return (-1);
	fzero(r, 3);
	p = 0.0;
	while (y < thr->ty + 1 && (x = thr->tx) > -1)
	{
		while (x < thr->tx + 1 && (p += 1) > 0)
		{
			ray_set(thr, tab, x, y);
			if ((tmp = nearest_obj(thr, obj, thr->ray_dir, thr->cam_pos)))
				tab = light(thr, tmp, thr->light, tab);
			fequlizer(r, tab);
			x = x + (1.0 / thr->aa);
		}
		y = y + (1.0 / thr->aa);
	}
	ft_put_pixel(thr, thr->tx, thr->ty, (((int)(r[0] / p * 255) & 0xff) << 16) +
		(((int)(r[1] / p * 255) & 0xff) << 8) + ((int)(r[2] / p * 255) & 0xff));
	free(tab);
	return (0);
}

void	*p_thread(void *arg)
{
	t_tab_thr	*tab;
	t_thr		*thr;
	t_o			*node;
	double		x;
	double		y;

	tab = (t_tab_thr *)arg;
	node = tab->var->obj;
	thr = (t_thr *)malloc(sizeof(t_thr));
	cp_var(tab->var, thr);
	y = 0.0;
	while (y < D_HEIGHT)
	{
		x = D_WIDTH * tab->i / P_THREADS;
		while (x < D_WIDTH * (tab->i + 1) / P_THREADS)
		{
			thr->tx = (int)x;
			thr->ty = (int)y;
			rt(thr, node, x++, y);
		}
		y++;
	}
	free_lists(thr->light, thr->obj);
	free(thr);
	pthread_exit(0);
}

int		render(t_var *var)
{
	pthread_t	thr[P_THREADS];
	t_tab_thr	tab[P_THREADS];
	void		*ret;
	int			i;

	i = -1;
	mlx_destroy_image(var->mlx_ptr, var->img_ptr);
	mlx_clear_window(var->mlx_ptr, var->win_ptr);
	var->img_ptr = mlx_new_image(var->mlx_ptr, D_WIDTH, D_HEIGHT);
	while (++i < P_THREADS)
	{
		tab[i].i = i;
		tab[i].var = var;
		pthread_create(&thr[i], NULL, p_thread, &tab[i]);
	}
	i = -1;
	while (++i < P_THREADS)
		(void)pthread_join(thr[i], &ret);
	mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, var->img_ptr, 0, 0);
	hud(var);
	return (0);
}
