#include "inc/rtv1.h"

void		ft_hud(t_var *var)
{
	char	*s1;
	char	*s2;

	if (var->hud == 1)
	{
		if (var->aa == 1)
		{
			s1 = NULL;
			SP(var->mlx_ptr, var->win_ptr, 50, 735, 0x00FEDC, "anti-aliasing: off");
		}
		else
		{
			s1 = ft_strjoin("anti-aliasing: x", ft_itoa(var->aa));
			SP(var->mlx_ptr, var->win_ptr, 50, 735, 0x00FEDC, s1);
			free(s1);
		}
		s2 = ft_strjoin("number of reflections: ", ft_itoa(var->maxref));
		SP(var->mlx_ptr, var->win_ptr, 50, 750, 0x00FEDC, s2);
		free(s2);
		if (var->spec == 1)
			SP(var->mlx_ptr, var->win_ptr, 50, 765, 0x00FEDC, "specularity: on");
		else
			SP(var->mlx_ptr, var->win_ptr, 50, 765, 0x00FEDC, "specularity: off");
	}
}