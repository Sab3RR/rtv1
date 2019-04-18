#include "inc/rtv1.h"

void	ft_init_mlx_var(t_var *var)
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


int		ft_free_lists(t_o *ob1, t_o *ob2)
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

int		ft_free_arg(t_var *var, char *buf, int i)
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
		ft_free_lists(var->light, var->obj);
	}
	return (-1);
}