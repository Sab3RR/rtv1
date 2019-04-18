#include "inc/rtv1.h"

int 	init_mlx(t_mlx *mlx, char *s)
{}

int		main(int argc, char **argv)
{
	t_var	*var;

	(void)argv;
	if (argc != 2)
	{
		ft_putstr("usage: ./RTv1 input_file\n");
		return (0);
	}
	if (!(var = (t_var *)malloc(sizeof(t_var))))
		return (0);
	if (init_mlx(var, argv[1]) == -1)
	{
		free(var);
		return (0);
	}
	ft_instructions();
	if (ft_draw(var) == -1)
		return (0);
	mlx_mouse_hook(var->win_ptr, ft_mouse, var);
	mlx_hook(var->win_ptr, 17, (1L << 17), close_hook, var);
	mlx_hook(var->win_ptr, 2, (1L << 17), key_hook, var);
	mlx_loop(var->mlx_ptr);
	return (0);
}