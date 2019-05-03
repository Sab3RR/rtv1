#include "inc/rtv1.h"

int	c_n_p(t_var *var, t_o *obj, int k)
{
	int	i;

	i = 6;
	if (ft_strncmp(var->scene[k + 2], "		col(", 6) != 0 || \
			ft_strncmp(var->scene[k + 3], "		pos(", 6) != 0)
		return (-1);
	obj->col.red = ft_atoi(var->scene[k + 2], &i);
	obj->col.green = ft_atoi(var->scene[k + 2], &i);
	obj->col.blue = ft_atoi(var->scene[k + 2], &i);
	if (var->scene[k + 2][i] != ')')
		return (-1);
	i = 6;
	obj->pos.x = ft_atoi(var->scene[k + 3], &i);
	obj->pos.y = ft_atoi(var->scene[k + 3], &i);
	obj->pos.z = ft_atoi(var->scene[k + 3], &i);
	if (var->scene[k + 3][i] != ')')
		return (-1);
	return (0);
}

int			add_sp(t_var *var, int *k, int i)
{
	t_o	*obj;

	if (!(obj = (t_o *)malloc(sizeof(t_o))))
		return (-1);
	obj->type = 4;
	if (ft_strcmp(var->scene[*k + 1], "	{") != 0 || \
			ft_strcmp(var->scene[*k + 5], "	}") != 0)
		return (-1);
	if (c_n_p(var, obj, *k) == -1)
		return (-1);
	if (ft_strncmp(var->scene[*k + 4], "		size(", 7) != 0)
		return (-1);
	obj->size = ft_atoi(var->scene[*k + 4], &i);
	if (var->scene[*k + 4][i] != ')')
		return (-1);
	obj->next = NULL;
	var->obj = add_ol(var, obj);
	*k += 6;
	return (0);
}

int			add_pl(t_var *var, int *k, int i)
{
	t_o	*obj;

	if (!(obj = (t_o *)malloc(sizeof(t_o))))
		return (-1);
	obj->type = 3;
	if (ft_strcmp(var->scene[*k + 1], "	{") != 0 || \
			ft_strcmp(var->scene[*k + 5], "	}") != 0)
		return (-1);
	if (c_n_p(var, obj, *k) == -1 || \
			ft_strncmp(var->scene[*k + 4], "		rot(", 6) != 0)
		return (-1);
	obj->rot.x = (float)ft_atoi(var->scene[*k + 4], &i);
	obj->rot.y = (float)ft_atoi(var->scene[*k + 4], &i);
	obj->rot.z = (float)ft_atoi(var->scene[*k + 4], &i);
	if (var->scene[*k + 4][i] != ')')
		return (-1);
	obj->next = NULL;
	var->obj = add_ol(var, obj);
	*k += 6;
	return (0);
}

int	add_l(t_var *var, int *k, int i)
{
	t_o	*obj;

	if (!(obj = (t_o *)malloc(sizeof(t_o))))
		return (-1);
	if (ft_strcmp(var->scene[*k + 1], "	{") != 0 || \
			ft_strcmp(var->scene[*k + 4], "	}") != 0)
		return (-1);
	if (ft_strncmp(var->scene[*k + 2], "		col(", 6) != 0 || \
			ft_strncmp(var->scene[*k + 3], "		pos(", 6) != 0)
		return (-1);
	obj->col.red = ft_atoi(var->scene[*k + 2], &i);
	obj->col.green = ft_atoi(var->scene[*k + 2], &i);
	obj->col.blue = ft_atoi(var->scene[*k + 2], &i);
	if (var->scene[*k + 2][i] != ')')
		return (-1);
	i = 6;
	obj->pos.x = ft_atoi(var->scene[*k + 3], &i);
	obj->pos.y = ft_atoi(var->scene[*k + 3], &i);
	obj->pos.z = ft_atoi(var->scene[*k + 3], &i);
	if (var->scene[*k + 3][i] != ')')
		return (-1);
	obj->next = NULL;
	var->light = add_ll(var, obj);
	*k += 5;
	return (0);
}

int	add_cc(t_var *var, int *k, int t, int i)
{
	t_o	*obj;

	if (!(obj = (t_o *)malloc(sizeof(t_o))))
		return (-1);
	if (ft_strcmp(var->scene[*k + 1], "	{") != 0 || \
			ft_strcmp(var->scene[*k + 6], "	}") != 0 || (obj->type = t) != t)
		return (-1);
	if (c_n_p(var, obj, *k) == -1 || \
			ft_strncmp(var->scene[*k + 4], "		rot(", 6) != 0)
		return (-1);
	obj->rot.x = (float)ft_atoi(var->scene[*k + 4], &i);
	obj->rot.y = (float)ft_atoi(var->scene[*k + 4], &i);
	obj->rot.z = (float)ft_atoi(var->scene[*k + 4], &i);
	if (var->scene[*k + 4][i] != ')')
		return (-1);
	if (ft_strncmp(var->scene[*k + 5], "		size(", 7) != 0)
		return (-1);
	i = 7;
	obj->size = ft_atoi(var->scene[*k + 5], &i);
	if (var->scene[*k + 5][i] != ')')
		return (-1);
	obj->next = NULL;
	var->obj = add_ol(var, obj);
	*k += 7;
	return (0);
}