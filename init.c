/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:06:55 by vsusol            #+#    #+#             */
/*   Updated: 2019/06/11 18:06:59 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/rtv1.h"

int		ft_cline(char *buf, int k)
{
	int	c;

	c = 0;
	while (buf[k] != '\n' && buf[k] != '\0')
	{
		k++;
		c++;
	}
	return (++c);
}

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
	char	*buf2;
	char	*s1;

	buf = ft_strnew(1);
	if (ft_open(s, &fd) == -1)
		return (NULL);
	while (get_next_line(fd, &line) > 0 && (*nbl)++ > -1)
	{
		buf2 = buf;
		s1 = ft_strjoin(line, "\n");
		buf = ft_strjoin(buf2, s1);
		free(buf2);
		free(line);
		free(s1);
	}
	if (close(fd) == -1)
	{
		ft_putendl(ft_strjoin("error: ", strerror(errno)));
		return (NULL);
	}
	free(line);
	return (buf);
}

char	**ft_getscene(char *buf, int nbl, int k)
{
	int		i;
	int		j;
	char	**sc;

	j = 0;
	if (!buf)
		return (NULL);
	if (!(sc = (char **)malloc(sizeof(char *) * (nbl))))
		return (NULL);
	while (buf[j] != '\0' && k < nbl)
	{
		i = 0;
		if (!(sc[k] = (char *)malloc(sizeof(char) * ft_cline(buf, j))))
			return (NULL);
		while (buf[j] != '\n' && buf[j] != '\0')
			sc[k][i++] = buf[j++];
		sc[k][i] = '\0';
		k++;
		j++;
	}
	free(buf);
	return (sc);
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
		return (free_arg(var, buf, 0));
	if ((var->scene = ft_getscene(buf, var->nbl, 0)) == NULL)
		return (free_arg(var, NULL, 1));
	system("leaks rtv1");
	init_var(var);
	if (parser(var) == -1)
		return (free_arg(var, NULL, 2));
	return (0);
}
