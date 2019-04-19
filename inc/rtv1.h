//
// Created by Vadim SUSOL on 2019-04-16.
//

#ifndef RTV1_H
#define RTV1_H

# include "../libft/libft.h"
# include <mlx.h>
# include <errno.h>
# include <pthread.h>
# include <fcntl.h>
# include <math.h>

# define D_WIDTH 800
# define D_HEIGHT 800

typedef struct		s_c
{
	float			red;
	float			green;
	float			blue;
}					t_c;

typedef struct		s_o
{
	int				type;
	float			size;
	t_vec			rot;
	t_vec			pos;
	t_c				col;
	struct s_o		*next;
}					t_o;

typedef struct		s_var
{
	int				bpp;
	int				nbl;
	int				endian;
	int				size_line;
	int				selection;
	int				maxref;
	int				hud;
	int				aa;
	int				pref;
	char			*pos;
	char			*img_addr;
	char			**scene;
	char			*rot;
	void			*win_ptr;
	void			*mlx_ptr;
	void			*img_ptr;
	t_vec			j;
	t_vec			i;
	t_vec			cam_pos;
	t_vec			k;
	t_vec			ray_dir;
	t_vec			cam_rot;
	t_vec			ref;
	t_vec			norm;
	t_vec			refpos;
	t_vec			dist;
	t_o				*tmp;
	t_o				*obj;
	t_o				*light;
	float			t0;
	float			spec;
	float			t;
	float			t1;
	float			b;
	float			a;
	float			c;
}					t_var;

typedef struct		s_tab_th
{
	t_var			*var;
	int				i;
}					t_tab_th;

typedef struct		s_th
{
	int				bpp;
	int				maxref;
	int				size_line;
	int				cpt;
	int				pref;
	int				tx;
	int				ty;
	int				aa;
	char			*d;
	t_vec			i;
	t_vec			j;
	t_vec			k;
	t_vec			cam_pos;
	t_vec			cam_dir;
	t_vec			ray_dir;
	t_vec			norm;
	t_vec			ref;
	t_vec			dist;
	t_vec			refpos;
	t_o				*obj;
	t_o				*light;
	float			t0;
	float			spec;
	float			t;
	float			t1;
	float			b;
	float			a;
	float			c;
}					t_th;

int					ft_free_arg(t_var *var, char *buf, int i);
void				ft_init_mlx_var(t_var *var);
t_o					*add_ll(t_var *var, t_o *obj);
int					add_l(t_var *var, int *k, int i);
int					add_cc(t_var *var, int *k, int t, int i);
t_o					*add_ol(t_var *var, t_o *obj);
int					add_pl(t_var *var, int *k, int i);
int					add_sp(t_var *var, int *k, int i);

#endif
