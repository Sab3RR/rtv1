#include "inc/rtv1.h"

int		ft_open(char *s, int *fd)
{
	if (BUFF_SIZE < 1)
	{
		ft_putendl("error: BUFF_SIZE must be greater than 0");
		return (-1);
	}
	if ((*fd = open(s, O_RDONLY)) == -1)
	{
		ft_putendl(ft_strjoin("error: ", strerror(errno)));
		return (-1);
	}
	return (1);
}

char	*get_buf(char *s, int *nbl)
{
	int		fd;
	char	*buf;
	char	*line;
	char 	*buf2;

	buf = ft_strnew(1);
	if (ft_open(s, &fd) == -1)
		return (NULL);
	while (get_next_line(fd, &line) > 0 && (*nbl)++ > -1)
	{
		buf2 = buf;
		buf = ft_strjoin(buf2, ft_strjoin(line, "\n"));
		free(buf2);
		free(line);
	}
	if (close(fd) == -1)
	{
		ft_putendl(ft_strjoin("error: ", strerror(errno)));
		return (NULL);
	}
	return (buf);
}

int		init_mlx(t_var *var, char *str)
{
	char	*buf;
	char	*name;

	name = ft_strjoin("RTv1: ", str);
	var->mlx_ptr = mlx_init();
	var->img_ptr = mlx_new_image(var->mlx_ptr, D_WIDTH, D_HEIGHT);
	var->win_ptr = mlx_new_window(var->mlx_ptr, D_WIDTH, D_HEIGHT, name);
	free(name);
	var->img_addr = mlx_get_data_addr(var->img_ptr, &var->bpp, &var->size_line,
							   &var->endian);
	var->nbl = 0;
	if ((buf = get_buf(str, &(var->nbl))) == NULL)
		return (ft_free_arg(var, buf, 0));
	if ((var->scene = ft_getscene(buf, var->nbl, 0)) == NULL)
		return (ft_free_arg(var, NULL, 1));
	ft_init_mlx_var(var);
	if (ft_parser(var) == -1)
		return (ft_free_arg(var, NULL, 2));
	return (0);
}

