/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:26:35 by vsusol            #+#    #+#             */
/*   Updated: 2019/06/11 18:26:39 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/rtv1.h"

int			ft_close(t_var *var)
{
	free_lists(var->light, var->obj);
	mlx_destroy_image(var->mlx_ptr, var->img_ptr);
	mlx_destroy_window(var->mlx_ptr, var->win_ptr);
	free(var->scene);
	free(var);
	exit(0);
	return (0);
}
