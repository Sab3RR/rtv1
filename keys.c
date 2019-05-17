#include "inc/rtv1.h"

int			objectsrot(int keys, t_var *var)
{
	float	tmp_rot;

	if (keys == 123 && OBJ->type != 4 && (tmp_rot = OBJ->rot.x) < 6000.0)
	{
		OBJ->rot.x = OBJ->rot.x * cosf(0.5) + OBJ->rot.z * sinf(0.5);
		OBJ->rot.z = tmp_rot * (-sinf(0.5)) + OBJ->rot.z * cosf(0.5);
	}
	if (keys == 124 && OBJ->type != 4 && (tmp_rot = OBJ->rot.x) > -6000.0)
	{
		OBJ->rot.x = OBJ->rot.x * cosf(-0.5) + OBJ->rot.z * sinf(-0.5);
		OBJ->rot.z = tmp_rot * (-sinf(-0.5)) + OBJ->rot.z * cosf(-0.5);
	}
	if (keys == 125 && OBJ->type != 4 && (tmp_rot = OBJ->rot.y) > -6000.0)
	{
		OBJ->rot.y = OBJ->rot.y * cosf(-0.5) + OBJ->rot.z * (-sinf(-0.5));
		OBJ->rot.z = tmp_rot * sinf(-0.5) + OBJ->rot.z * cosf(-0.5);
	}
	if (keys == 126 && OBJ->type != 4 && (tmp_rot = OBJ->rot.y) < 6000.0)
	{
		OBJ->rot.y = OBJ->rot.y * cosf(0.5) + OBJ->rot.z * (-sinf(0.5));
		OBJ->rot.z = tmp_rot * sinf(0.5) + OBJ->rot.z * cosf(0.5);
	}
	return (ft_last_hook(keys, var));
}

int		parameters(int keys, t_var *var)
{
	if (keys == 36 && (var->selection = 0) > -1)
		return (0);
	else if (keys == 24 && OBJ->type != 3)
		OBJ->size = (OBJ->size < 10000) ? OBJ->size + 5 : OBJ->size;
	else if (keys == 27 && OBJ->type != 3)
		OBJ->size = (OBJ->size > 6) ? OBJ->size - 5 : OBJ->size;
	else if (keys == 0)
		OBJ->pos = (t_vec){OBJ->pos.x + 10.0 * var->i.x,
						   OBJ->pos.y + 10.0 * var->i.y, OBJ->pos.z + 10.0 * var->i.z};
	else if (keys == 2)
		OBJ->pos = (t_vec){OBJ->pos.x - 10.0 * var->i.x,
						   OBJ->pos.y - 10.0 * var->i.y, OBJ->pos.z - 10.0 * var->i.z};
	else if (keys == 13)
		OBJ->pos = (t_vec){OBJ->pos.x + 10.0 * var->j.x,
						   OBJ->pos.y + 10.0 * var->j.y, OBJ->pos.z + 10.0 * var->j.z};
	else if (keys == 1)
		OBJ->pos = (t_vec){OBJ->pos.x - 10.0 * var->j.x,
						   OBJ->pos.y - 10.0 * var->j.y, OBJ->pos.z - 10.0 * var->j.z};
	else if (keys == 69)
		OBJ->pos = (t_vec){OBJ->pos.x - 10.0 * var->k.x,
						   OBJ->pos.y - 10.0 * var->k.y, OBJ->pos.z - 10.0 * var->k.z};
	else if (keys == 78)
		OBJ->pos = (t_vec){OBJ->pos.x + 10.0 * var->k.x,
						   OBJ->pos.y + 10.0 * var->k.y, OBJ->pos.z + 10.0 * var->k.z};
	return (objectsrot(keys, var));
}

int			close_hook(t_var *var)
{
	free_lists(var->light, var->obj);
	mlx_destroy_image(var->mlx_ptr, var->img_ptr);
	mlx_destroy_window(var->mlx_ptr, var->win_ptr);
	free(var->scene);
	free(var);
	exit(0);
	return (0);
}

int		ft_hook_add(int keys, t_var *var)
{
	if (var->selection == 1)
	{
		if (keys == 53)
			close_hook(var);
		parameters(keys, var);
		ft_draw(var);
		ft_string_put(var);
		SP(var->mlx_ptr, var->win_ptr, 550, 735, 0x00FEDC, var->pos);
		free(var->pos);
		(OBJ->type != 4) ? free(var->rot) : NULL;
		return (-1);
	}
	if (keys == 78)
	{
		var->cam_rot = (t_vec){var->cam_rot.x - 10.0 * var->k.x,
							   var->cam_rot.y - 10.0 * var->k.y, var->cam_rot.z - 10.0 * var->k.z};
		var->cam_pos = (t_vec){var->cam_pos.x - 10.0 * var->k.x,
							   var->cam_pos.y - 10.0 * var->k.y, var->cam_pos.z - 10.0 * var->k.z};
	}
	return (0);
}

int			keys(int key, t_var *var)
{
	float	tmp_pos;

//	if (ft_hook_add(key, var) == -1)
//		return (0);
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
	render(var);
	if (OBJ != NULL)
	{
		strput(var);
		SP(var->mlx_ptr, var->win_ptr, 800, 735, 0x0B2F9B, var->pos);
	}
//	return (ft_translation(key, var));
}