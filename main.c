/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:44:31 by vsusol            #+#    #+#             */
/*   Updated: 2019/06/11 17:44:35 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/rtv1.h"

int		main(int argc, char **argv)
{
	t_var	*var;

	argv[1] = "scene1.rt";
	argc = 2;
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
	if (render(var) == -1)
		return (0);
	mlx_mouse_hook(var->win_ptr, mouse, var);
	mlx_hook(var->win_ptr, 17, (1L << 17), ft_close, var);
	mlx_hook(var->win_ptr, 2, (1L << 17), keys, var);
	mlx_loop(var->mlx_ptr);
	return (0);
}
