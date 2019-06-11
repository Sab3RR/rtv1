/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:47:24 by vsusol            #+#    #+#             */
/*   Updated: 2019/06/11 17:47:28 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/rtv1.h"

void	cam_rot(int key, t_var *var, float tmp_pos)
{
	if (key == 123 && (tmp_pos = var->cam_pos.x) < 20000)
	{
		CAMX = var->cam_pos.x * cosf(0.05) + var->cam_pos.z * sinf(0.05);
		CAMZ = tmp_pos * (-sinf(0.05)) + var->cam_pos.z * cosf(0.05);
	}
	else if (key == 124 && (tmp_pos = var->cam_pos.x) > -20000)
	{
		CAMX = var->cam_pos.x * cosf(-0.05) + var->cam_pos.z * sinf(-0.05);
		CAMZ = tmp_pos * (-sinf(-0.05)) + var->cam_pos.z * cosf(-0.05);
	}
	else if (key == 125 && (tmp_pos = var->cam_pos.y) > -20000)
	{
		CAMY = var->cam_pos.y * cosf(-0.05) + var->cam_pos.z * (-sinf(-0.05));
		CAMZ = tmp_pos * sinf(-0.05) + var->cam_pos.z * cosf(-0.05);
	}
	else if (key == 126 && (tmp_pos = var->cam_pos.y) < 20000)
	{
		CAMY = var->cam_pos.y * cosf(0.05) + var->cam_pos.z * (-sinf(0.05));
		CAMZ = tmp_pos * sinf(0.05) + var->cam_pos.z * cosf(0.05);
	}
}

int		rot_hook(int key, t_var *var)
{
	float	tmp_rot;

	if (key == 121 && var->tmp->type != 4 &&
	(tmp_rot = var->tmp->rot.x) < 6000.0)
	{
		var->tmp->rot.x = var->tmp->rot.x
				* cosf(0.5) + var->tmp->rot.y * (-sinf(0.5));
		var->tmp->rot.y = tmp_rot * sinf(0.5) + var->tmp->rot.y * cosf(0.5);
	}
	if (key == 116 && var->tmp->type != 4 &&
	(tmp_rot = var->tmp->rot.x) > -6000.0)
	{
		var->tmp->rot.x = var->tmp->rot.x
				* cosf(-0.5) + var->tmp->rot.y * (-sinf(-0.5));
		var->tmp->rot.y = tmp_rot * sinf(-0.5) + var->tmp->rot.y * cosf(-0.5);
	}
	return (0);
}

int		cam_f_key(int keys, t_var *var)
{
	if (keys == 69)
	{
		var->cam_rot = (t_vec){var->cam_rot.x + 10.0 * var->k.x,
							var->cam_rot.y + 10.0 * var->k.y,
							var->cam_rot.z + 10.0 * var->k.z};
		var->cam_pos = (t_vec){var->cam_pos.x + 10.0 * var->k.x,
							var->cam_pos.y + 10.0 * var->k.y,
							var->cam_pos.z + 10.0 * var->k.z};
	}
	(keys == 15 && var->maxref < 15) ? var->maxref++ : var->maxref;
	(keys == 3 && var->maxref > 0) ? var->maxref-- : var->maxref;
	if (keys == 14)
		var->pref = (var->pref == 0) ? 1 : 0;
	if (keys == 7)
	{
		if (var->aa == 1 || var->aa == 2 || var->aa == 4 || var->aa == 8)
			var->aa *= 2;
	}
	if (keys == 6)
	{
		if (var->aa == 2 || var->aa == 4 || var->aa == 8 || var->aa == 16)
			var->aa /= 2;
	}
	return (0);
}

int		cam_f_add(int keys, t_var *var)
{
	if (keys == 1)
	{
		var->cam_rot = (t_vec){var->cam_rot.x - 10.0 * var->j.x,
							var->cam_rot.y - 10.0 * var->j.y,
							var->cam_rot.z - 10.0 * var->j.z};
		var->cam_pos = (t_vec){var->cam_pos.x - 10.0 * var->j.x,
							var->cam_pos.y - 10.0 * var->j.y,
							var->cam_pos.z - 10.0 * var->j.z};
	}
	else if (keys == 13)
	{
		var->cam_rot = (t_vec){var->cam_rot.x + 10.0 * var->j.x,
							var->cam_rot.y + 10.0 * var->j.y,
							var->cam_rot.z + 10.0 * var->j.z};
		var->cam_pos = (t_vec){var->cam_pos.x + 10.0 * var->j.x,
							var->cam_pos.y + 10.0 * var->j.y,
							var->cam_pos.z - 10.0 * var->j.z};
	}
	cam_f_key(keys, var);
	return (render(var));
}

int		cam_f(int keys, t_var *var)
{
	(keys == 53) ? ft_close(var) : 0;
	if (keys == 0)
	{
		var->cam_rot = (t_vec){var->cam_rot.x + 10.0 * var->i.x,
						var->cam_rot.y + 10.0 * var->i.y,
						var->cam_rot.z + 10.0 * var->i.z};
		var->cam_pos = (t_vec){var->cam_pos.x + 10.0 * var->i.x,
						var->cam_pos.y + 10.0 * var->i.y,
						var->cam_pos.z + 10.0 * var->i.z};
	}
	else if (keys == 2)
	{
		var->cam_rot = (t_vec){var->cam_rot.x - 10.0 * var->i.x,
						var->cam_rot.y - 10.0 * var->i.y,
						var->cam_rot.z - 10.0 * var->i.z};
		var->cam_pos = (t_vec){var->cam_pos.x - 10.0 * var->i.x,
						var->cam_pos.y - 10.0 * var->i.y,
						var->cam_pos.z - 10.0 * var->i.z};
	}
	else if (keys == 5)
		var->spec = (var->spec == 0) ? 1 : 0;
	else if (keys == 48)
		var->hud = (var->hud == 0) ? 1 : 0;
	return (cam_f_add(keys, var));
}
