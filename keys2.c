#include "inc/rtv1.h"

void	cam_rot(int key, t_var *var,float tmp_pos)
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
int 	rot_hook(int key, t_var *var)
{
	float	tmp_rot;

	if (key == 121 && var->tmp->type != 4 && (tmp_rot = var->tmp->rot.x) < 6000.0)
	{
		var->tmp->rot.x = var->tmp->rot.x * cosf(0.5) + var->tmp->rot.y * (-sinf(0.5));
		var->tmp->rot.y = tmp_rot * sinf(0.5) + var->tmp->rot.y * cosf(0.5);
	}
	if (key == 116 && var->tmp->type != 4 && (tmp_rot = var->tmp->rot.x) > -6000.0)
	{
		var->tmp->rot.x = var->tmp->rot.x * cosf(-0.5) + var->tmp->rot.y * (-sinf(-0.5));
		var->tmp->rot.y = tmp_rot * sinf(-0.5) + var->tmp->rot.y * cosf(-0.5);
	}
	return (0);
}

static int	ft_translation(int keycode, t_mlx *mlx)
{
	K = ft_vectorsub(&mlx->cam_dir, &mlx->cam_pos);
	ft_vectornorm(&K);
	I = ft_vectorcross(&K, &(t_vec){0.0, 1.0, 0.0});
	ft_vectornorm(&I);
	J = ft_vectorcross(&I, &K);
	(keycode == 53) ? close_hook(mlx) : 0;
	if (keycode == 0)
	{
		mlx->cam_dir = (t_vec){mlx->cam_dir.x + 10.0 * I.x,
							   mlx->cam_dir.y + 10.0 * I.y, mlx->cam_dir.z + 10.0 * I.z};
		mlx->cam_pos = (t_vec){mlx->cam_pos.x + 10.0 * I.x,
							   mlx->cam_pos.y + 10.0 * I.y, mlx->cam_pos.z + 10.0 * I.z};
	}
	else if (keycode == 2)
	{
		mlx->cam_dir = (t_vec){mlx->cam_dir.x - 10.0 * I.x,
							   mlx->cam_dir.y - 10.0 * I.y, mlx->cam_dir.z - 10.0 * I.z};
		mlx->cam_pos = (t_vec){mlx->cam_pos.x - 10.0 * I.x,
							   mlx->cam_pos.y - 10.0 * I.y, mlx->cam_pos.z - 10.0 * I.z};
	}
	else if (keycode == 5)
		mlx->spec = (mlx->spec == 0) ? 1 : 0;
	else if (keycode == 48)
		mlx->hud = (mlx->hud == 0) ? 1 : 0;
	return (ft_translation_add(keycode, mlx));
}

static int	ft_translation_add(int keycode, t_mlx *mlx)
{
	if (keycode == 1)
	{
		mlx->cam_dir = (t_vec){mlx->cam_dir.x - 10.0 * J.x,
							   mlx->cam_dir.y - 10.0 * J.y, mlx->cam_dir.z - 10.0 * J.z};
		mlx->cam_pos = (t_vec){mlx->cam_pos.x - 10.0 * J.x,
							   mlx->cam_pos.y - 10.0 * J.y, mlx->cam_pos.z - 10.0 * J.z};
	}
	else if (keycode == 13)
	{
		mlx->cam_dir = (t_vec){mlx->cam_dir.x + 10.0 * J.x,
							   mlx->cam_dir.y + 10.0 * J.y, mlx->cam_dir.z + 10.0 * J.z};
		mlx->cam_pos = (t_vec){mlx->cam_pos.x + 10.0 * J.x,
							   mlx->cam_pos.y + 10.0 * J.y, mlx->cam_pos.z - 10.0 * J.z};
	}
	else if (keycode == 69)
	{
		mlx->cam_dir = (t_vec){mlx->cam_dir.x + 10.0 * K.x,
							   mlx->cam_dir.y + 10.0 * K.y, mlx->cam_dir.z + 10.0 * K.z};
		mlx->cam_pos = (t_vec){mlx->cam_pos.x + 10.0 * K.x,
							   mlx->cam_pos.y + 10.0 * K.y, mlx->cam_pos.z + 10.0 * K.z};
	}
	ft_pref_key(keycode, mlx);
	return (ft_draw(mlx));
}
int		ft_pref_key(int keycode, t_mlx *mlx)
{
	(keycode == 15 && mlx->maxref < 15) ? mlx->maxref++ : mlx->maxref;
	(keycode == 3 && mlx->maxref > 0) ? mlx->maxref-- : mlx->maxref;
	if (keycode == 14)
		mlx->pref = (mlx->pref == 0) ? 1 : 0;
	if (keycode == 7)
	{
		if (mlx->aa == 1 || mlx->aa == 2 || mlx->aa == 4 || mlx->aa == 8)
			mlx->aa *= 2;
	}
	if (keycode == 6)
	{
		if (mlx->aa == 2 || mlx->aa == 4 || mlx->aa == 8 || mlx->aa == 16)
			mlx->aa /= 2;
	}
	return (0);
}