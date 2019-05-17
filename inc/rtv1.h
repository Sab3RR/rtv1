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

# define P_THREADS 8
# define D_WIDTH 1000
# define D_HEIGHT 1000

# define K thr->k
# define J thr->j
# define I thr->i

# define CAMX var->cam_pos.x
# define CAMY var->cam_pos.y
# define CAMZ var->cam_pos.z

# define OBJ var->tmp

# define COND thr->spec == 1 && tmp->type != 3
# define PREF thr->pref == 1 && tmp->type != 3
# define JOINFREE (OBJ->type != 3) ? ft_strjoin("size: ", i) : NULL; free(i);

# define SP mlx_string_put

#define FOV 2.0

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

typedef struct		s_tab_thr
{
	t_var			*var;
	int				i;
}					t_tab_thr;

typedef struct		s_thr
{
	int				bpp;
	int				maxref;
	int				size_line;
	int				cpt;
	int				pref;
	int				tx;
	int				ty;
	int				aa;
	char			*img_addr;
	t_vec			i;
	t_vec			j;
	t_vec			k;
	t_vec			cam_pos;
	t_vec			cam_rot;
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
}					t_thr;

int					render(t_var *var);
int					free_arg(t_var *var, char *buf, int i);
void				init_var(t_var *var);
t_o					*add_ll(t_var *var, t_o *obj);
int					add_l(t_var *var, int *k, int i);
int					add_cc(t_var *var, int *k, int t, int i);
t_o					*add_ol(t_var *var, t_o *obj);
int					add_pl(t_var *var, int *k, int i);
int					add_sp(t_var *var, int *k, int i);
int					free_lists(t_o *ob1, t_o *ob2);
int					check_obj(t_var *var, t_o *obj);
int					parser(t_var *var);
int					init_mlx(t_var *var, char *str);
void				cp_var(t_var *var, t_thr *thr);
void				fzero(float *s, int n);
t_o					*nearest_obj(t_thr *thr, t_o *obj, t_vec ray, t_vec pos);
float				equalizer(float value, float min, float max);
double				nearest_cone(t_thr *thr, t_o *obj, t_vec ray, t_vec pos);
double				nearest_cylinder(t_thr *thr, t_o *obj, t_vec ray, t_vec pos);
double				nearest_sphere(t_thr *thr, t_o *obj, t_vec ray, t_vec pos);
double				nearest_plane(t_thr *thr, t_o *obj, t_vec ray, t_vec pos);
t_vec				norm(t_thr *thr, t_o *obj, t_vec pos);
float				*addlight(t_o *obj, t_o *light, float *tab, float d);
float				sp(t_thr *thr, t_vec dist, float d, float lambert);
float				*light(t_thr *thr, t_o *tmp, t_o *light, float *tab);
float				*fequlizer(float *r, float *tab);
float				finit_cone(t_thr *thr, t_o *obj, t_vec ray);
void				hud(t_var *var);
int					mouse(int button, int x, int y, t_var *var);
void				strput(t_var *var);
int					keys(int key, t_var *var);
#endif
