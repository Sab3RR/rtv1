#include "inc/rtv1.h"

int		check_obj(t_var *var, t_o *obj)
{
	obj = var->light;
	while (obj != NULL)
	{
		if (!(obj->col.red >= 0 && obj->col.red <= 255) ||
			!(obj->col.green >= 0 && obj->col.green <= 255) ||
			!(obj->col.blue >= 0 && obj->col.blue <= 255))
			return (-1);
		obj = obj->next;
	}
	obj = var->obj;
	while (obj != NULL)
	{
		if (!(obj->col.red >= 0 && obj->col.red <= 255) ||
			!(obj->col.green >= 0 && obj->col.green <= 255) ||
			!(obj->col.blue >= 0 && obj->col.blue <= 255))
			return (-1);
		if (obj->type == 2 || obj->type == 4)
		{
			if (obj->size < 0)
				return (-1);
		}
		obj = obj->next;
	}
	return (0);
}