/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:58:33 by vsusol            #+#    #+#             */
/*   Updated: 2019/06/11 17:58:37 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/rtv1.h"

void		hud_next(t_var *var)
{
	char *s1;
	char *s2;

	s1 = ft_itoa(var->maxref);
	s2 = ft_strjoin("number of reflections: ", s1);
	SP(var->mlx_ptr, var->win_ptr, 50, 750, 0xFFFF00, s2);
	free(s2);
	free(s1);
	if (var->spec == 1)
		SP(var->mlx_ptr, var->win_ptr, 50, 765, 0xFFFF00, "specularity: on");
	else
		SP(var->mlx_ptr, var->win_ptr, 50, 765, 0xFFFF00, "specularity: off");
}

void		hud(t_var *var)
{
	char	*s1;
	char	*s2;

	if (var->hud == 1)
	{
		if (var->aa == 1)
		{
			s1 = NULL;
			SP(var->mlx_ptr, var->win_ptr, 50, 735, 0xFFFF00, AAOFF);
		}
		else
		{
			s2 = ft_itoa(var->aa);
			s1 = ft_strjoin("anti-aliasing: x", s2);
			SP(var->mlx_ptr, var->win_ptr, 50, 735, 0xFFFF00, s1);
			free(s1);
			free(s2);
		}
		s1 = ft_itoa(var->maxref);
		s2 = ft_strjoin("number of reflections: ", s1);
		free(s1);
		free(s2);
		hud_next(var);
	}
}
