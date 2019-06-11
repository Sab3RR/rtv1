/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:24:00 by vsusol            #+#    #+#             */
/*   Updated: 2019/06/11 17:24:04 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/rtv1.h"

void	str(t_var *var)
{
	char	*c;
	char	*s;
	char	*d;

	c = ft_itoa(OBJ->rot.z);
	s = ft_strjoin(" ", c);
	free(c);
	c = ft_itoa(OBJ->rot.y);
	d = ft_strjoin(c, s);
	free(c);
	free(s);
	s = ft_strjoin(" ", d);
	free(d);
	c = ft_itoa(OBJ->rot.x);
	d = ft_strjoin(c, s);
	free(c);
	free(s);
	s = ft_strjoin("rot: ", d);
	free(d);
	var->rot = s;
}

void	tmp_str(t_var *var)
{
	char	*s;
	char	*c;
	char	*d;

	c = ft_itoa(OBJ->pos.z);
	s = ft_strjoin(" ", c);
	free(c);
	c = ft_itoa(OBJ->pos.y);
	d = ft_strjoin(c, s);
	free(c);
	free(s);
	s = ft_strjoin(" ", d);
	free(d);
	c = ft_itoa(OBJ->pos.x);
	d = ft_strjoin(c, s);
	free(c);
	free(s);
	s = ft_strjoin("pos: ", d);
	free(d);
	var->pos = s;
	if (OBJ->type != 4)
	{
		str(var);
	}
}

void	strput(t_var *var)
{
	char	*s;
	char	*i;

	i = ft_itoa(OBJ->size);
	s = JOINFREE;
	if (OBJ->type == 1 || OBJ->type == 2)
	{
		if (OBJ->type == 1)
			SP(var->mlx_ptr, var->win_ptr, 800, 720, 0x0B2F9B, "object: cone");
		if (OBJ->type == 2)
			SP(var->mlx_ptr, var->win_ptr, 800, 720, 0x0B2F9B, CYLINDER);
		SP(var->mlx_ptr, var->win_ptr, 800, 750, 0x0B2F9B, var->rot);
		SP(var->mlx_ptr, var->win_ptr, 800, 765, 0x0B2F9B, s);
	}
	else if (OBJ->type == 3)
	{
		SP(var->mlx_ptr, var->win_ptr, 800, 720, 0x0B2F9B, "object: plane");
		SP(var->mlx_ptr, var->win_ptr, 800, 750, 0x0B2F9B, var->rot);
	}
	else if (OBJ->type == 4)
	{
		SP(var->mlx_ptr, var->win_ptr, 800, 720, 0x0B2F9B, "object: sphere");
		SP(var->mlx_ptr, var->win_ptr, 800, 765, 0x0B2F9B, s);
	}
	(OBJ->type != 3) ? free(s) : NULL;
}

t_o		*seek(double u, double v, t_vec cam, t_var *var)
{
	t_o		*obj;
	t_thr	*thr;

	if (!(thr = (t_thr *)malloc(sizeof(t_thr))))
		return (NULL);
	obj = var->obj;
	K = ft_vectorsub(&var->cam_rot, &cam);
	ft_vectornorm(&K);
	I = ft_vectorcross(&K, &(t_vec){0.0, 1.0, 0.0});
	ft_vectornorm(&I);
	J = ft_vectorcross(&I, &K);
	var->ray_dir = (t_vec){u * I.x + v * J.x + FOV * K.x, u * I.y + v * J.y
						+ FOV * K.y, u * I.z + v * J.z + FOV * K.z};
	ft_vectornorm(&var->ray_dir);
	obj = nearest_obj(thr, obj, var->ray_dir, cam);
	free(thr);
	return (obj);
}

int		mouse(int button, int x, int y, t_var *var)
{
	double	u;
	double	v;

	u = (D_WIDTH - (double)x * 2.0) / D_HEIGHT;
	v = (D_HEIGHT - (double)y * 2.0) / D_WIDTH;
	if (button == 1 && (x >= 0 && x <= D_WIDTH) && (y >= 0 && y <= D_HEIGHT))
	{
		mlx_clear_window(var->mlx_ptr, var->win_ptr);
		mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, var->img_ptr, 0, 0);
		hud(var);
		if ((var->tmp = seek(u, v, (t_vec){var->cam_pos.x + u,
								SOMEMACRO}, var)) == NULL)
		{
			SP(var->mlx_ptr, var->win_ptr, 800, 720, 0x0B2F9B, NOSELECT);
			var->selection = 0;
			return (0);
		}
		strput(var);
		SP(var->mlx_ptr, var->win_ptr, 800, 735, 0x0B2F9B, var->pos);
		free(var->pos);
		(var->tmp->type != 4) ? free(var->rot) : NULL;
		var->selection = 1;
	}
	return (0);
}
