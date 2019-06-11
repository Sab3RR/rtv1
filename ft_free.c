/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:18:48 by vsusol            #+#    #+#             */
/*   Updated: 2019/06/11 18:18:51 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/rtv1.h"

int		free_lists(t_o *ob1, t_o *ob2)
{
	t_o	*fst;
	t_o	*tmp;

	fst = ob2;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
	fst = ob1;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
	return (-1);
}

t_o		*cp_obj(t_o *obj)
{
	t_o	*nl;

	if (!(nl = (t_o *)malloc(sizeof(t_o))))
		return (NULL);
	if (obj && nl)
	{
		nl->type = obj->type;
		nl->rot = (t_vec){obj->rot.x, obj->rot.y, obj->rot.z};
		nl->size = obj->size;
		nl->pos = (t_vec){obj->pos.x, obj->pos.y, obj->pos.z};
		nl->col.red = obj->col.red;
		nl->col.blue = obj->col.blue;
		nl->col.green = obj->col.green;
		nl->next = NULL;
		if (nl && obj->next)
			nl->next = cp_obj(obj->next);
		return (nl);
	}
	return (NULL);
}

void	cp_var(t_var *var, t_thr *thr)
{
	thr->maxref = var->maxref;
	thr->spec = var->spec;
	thr->cpt = 0;
	thr->pref = var->pref;
	thr->cam_rot = (t_vec){var->cam_rot.x, var->cam_rot.y, var->cam_rot.z};
	thr->cam_pos = (t_vec){var->cam_pos.x, var->cam_pos.y, var->cam_pos.z};
	thr->light = cp_obj(var->light);
	thr->ray_dir = (t_vec){var->ray_dir.x, var->ray_dir.y, var->ray_dir.z};
	thr->bpp = var->bpp;
	thr->obj = cp_obj(var->obj);
	thr->img_addr = var->img_addr;
	thr->size_line = var->size_line;
	thr->aa = var->aa;
}

void	init_var(t_var *var)
{
	var->obj = NULL;
	var->light = NULL;
	var->hud = 1;
	var->spec = 0;
	var->maxref = 0;
	var->pref = 0;
	var->selection = 0;
	var->aa = 1;
}

int		free_arg(t_var *var, char *buf, int i)
{
	if (i == 0)
		free(buf);
	else if (i == 1)
	{
		ft_putendl("error: Dynamic memory allocation failed");
		free(var->scene);
	}
	else if (i == 2)
	{
		ft_putendl("error: scene descriptor incorrect or incomplete");
		free(var->scene);
	}
	else if (i == 3)
	{
		ft_putendl("error: Dynamoc memory allocation failed");
		free(var->scene);
		free_lists(var->light, var->obj);
	}
	return (-1);
}
