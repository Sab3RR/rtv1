#include "inc/rtv1.h"

t_o	*add_ol(t_var *var, t_o *obj)
{
	t_o	*obj2;

	obj2 = var->obj;
	if (var->obj == NULL)
		return (obj);
	while (var->obj->next != NULL)
		var->obj = var->obj->next;
	var->obj->next = obj;
	return (obj2);
}

t_o	*add_ll(t_var *var, t_o *obj)
{
	t_o	*obj2;

	obj2 = var->light;
	if (var->light == NULL)
		return (obj);
	while (var->light->next != NULL)
		var->light = var->light->next;
	var->light->next = obj;
	return (obj2);
}

int	parse_objects(t_var *var, int i)
{
	int	res;

	while (i < var->nbl - 1)
	{
		if (ft_strcmp(var->scene[i], "	object(light)") == 0)
			res = add_l(var, &i, 6);
		else if (ft_strcmp(var->scene[i], "	object(cone)") == 0)
			res = add_cc(var, &i, 1, 6);
		else if (ft_strcmp(var->scene[i], "	object(cylinder)") == 0)
			res = add_cc(var, &i, 2, 6);
		else if (ft_strcmp(var->scene[i], "	object(plane)") == 0)
			res = add_pl(var, &i, 6);
		else if (ft_strcmp(var->scene[i], "	object(sphere)") == 0)
			res = add_sp(var, &i, 7);
		else
			return (ft_free_lists(var->light, var->obj));
		if (res == -1)
			return (ft_free_lists(var->light, var->obj));
	}
	return (0);
}

int	checkscene(t_var *var, int i)
{
	if (ft_strcmp(var->scene[0], "scene") != 0)
		return (-1);
	if (ft_strcmp(var->scene[1], "{") != 0 || \
			ft_strcmp(var->scene[4], "}") != 0)
		return (-1);
	if (ft_strncmp(var->scene[2], "	cam_pos(", 9) != 0)
		return (-1);
	var->cam_pos.x = (float)ft_atoi(var->scene[2], &i);
	var->cam_pos.y = (float)ft_atoi(var->scene[2], &i);
	var->cam_pos.z = (float)ft_atoi(var->scene[2], &i);
	if (var->scene[2][i] != ')')
		return (-1);
	if (ft_strncmp(var->scene[3], "	cam_dir(", 9) != 0)
		return (-1);
	i = 9;
	var->cam_rot.x = (float)ft_atoi(var->scene[3], &i);
	var->cam_rot.y = (float)ft_atoi(var->scene[3], &i);
	var->cam_rot.z = (float)ft_atoi(var->scene[3], &i);
	if (var->scene[3][i] != ')')
		return (-1);
	if (ft_strlen(var->scene[5]) != 0)
		return (-1);
	return (0);
}

int	parser(t_var *var)
{
	t_o		*obj;

	if (checkscene(var, 9) == -1)
		return (-1);
	if (ft_strcmp(var->scene[6], "content") != 0 || \
			ft_strcmp(var->scene[7], "{") != 0 || \
			ft_strcmp(var->scene[var->nbl - 1], "}") != 0)
		return (-1);
	if (parse_objects(var, 8) == -1)
		return (-1);
	if (ft_check_objects(var, (obj = NULL)) == -1)
	{
		ft_putendl("error: incorrect values for color/size");
		return (-1);
	}
	return (0);
}
