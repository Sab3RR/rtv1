#include "inc/rtv1.h"

int				ft_mouse(int button, int x, int y, t_var *var)
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
		if ((var->tmp = ft_seek(u, v, (t_vec){var->cam_pos.x + u,
											  var->cam_pos.y + v, var->cam_pos.z}, var)) == NULL)
		{
			SP(var->mlx_ptr, var->win_ptr, 550, 720, 0x00FEDC, "no selection");
			var->selection = 0;
			return (0);
		}
		ft_string_put(mlx);
		SP(var->mlx_ptr, var->win_ptr, 550, 735, 0x00FEDC, var->pos);
		free(var->pos);
		(var->tmp->type != 4) ? free(var->rot) : NULL;
		var->selection = 1;
	}
	return (0);
}

