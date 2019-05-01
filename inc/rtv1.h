/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:17 by arudyi            #+#    #+#             */
/*   Updated: 2019/05/01 14:21:44 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <pthread.h>
# include "../frameworks/SDL2/SDL.h"
# include "../lib/libft/includes/libft.h"
# define WIDTH 1000
# define HEIGHT 1000
# define THREADS 80
# define ESC (key == SDLK_ESCAPE)
# define BACKSPACE (key == SDLK_BACKSPACE)
# define ARROW_UP key == SDLK_DOWN || key == SDLK_UP
# define ARROW_LEFT key == SDLK_LEFT || key == SDLK_RIGHT
# define LIGHT (key == SDLK_1 || key == SDLK_2)
# define SPECULAR (key == SDLK_3 || key == SDLK_4)
# define REFLECT (key == SDLK_5 || key == SDLK_6)
# define SIZE (key == SDLK_KP_PLUS || key == SDLK_KP_MINUS)
# define NORMAL s_pixel->normal_now
# define P_POS s_pixel->player.position
# define TY_LI s_pixel->arr_light[i].type_of_light
# define P_L s_pixel->arr_light[i].position
# define L_INTE s_pixel->arr_light[i].intensity
# define SPECU_OBJ s_pixel->arr_object3d[s_pixel->obj_now].specular
# define LEN(vec) (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z))
# define DOT(vec1, vec2) (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z)
# define TYPE_OBJ s_pixel->arr_object3d[k].type_of_data
# define T_MAX s_pixel->obj.t_max
# define BYTE s_pixel->surface->format->BytesPerPixel
# define RADIUS_CYL ((t_cylinder *)s_pixel->arr_object3d[i].data)->radius
# define T1_CYL ((t_cylinder *)s_pixel->arr_object3d[i].data)->t1
# define T2_CYL ((t_cylinder *)s_pixel->arr_object3d[i].data)->t2
# define A_CYL ((t_cylinder *)s_pixel->arr_object3d[i].data)->a
# define B_CYL ((t_cylinder *)s_pixel->arr_object3d[i].data)->b
# define C_CYL ((t_cylinder *)s_pixel->arr_object3d[i].data)->c
# define P1_CYL ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1
# define P2_CYL ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2
# define HEIGHT_CYL ((t_cylinder *)s_pixel->arr_object3d[i].data)->height
# define A_CONE ((t_cone *)s_pixel->arr_object3d[i].data)->a
# define B_CONE ((t_cone *)s_pixel->arr_object3d[i].data)->b
# define C_CONE ((t_cone *)s_pixel->arr_object3d[i].data)->c
# define T1_CONE ((t_cone *)s_pixel->arr_object3d[i].data)->t1
# define T2_CONE ((t_cone *)s_pixel->arr_object3d[i].data)->t2
# define HEIGHT_CONE ((t_cone *)s_pixel->arr_object3d[i].data)->height
# define P1_CONE ((t_cone *)s_pixel->arr_object3d[i].data)->p1
# define P2_CONE ((t_cone *)s_pixel->arr_object3d[i].data)->p2
# define K_CONE ((t_cone *)s_pixel->arr_object3d[i].data)->k
# define PLA_POS s_pixel->player.position
# define RECURSIVE s_pixel->depth_recursive
# define IS_INTERSECT s_pixel->is_intersect

typedef double		t_vector __attribute__((ext_vector_type(4)));

typedef struct		s_plane
{
	t_vector		normal;
	t_vector		point;
}					t_plane;

typedef struct		s_cone
{
	t_vector		p1;
	t_vector		p2;
	double			angle;
	double			height;
	double			radius;
	double			a;
	double			b;
	double			c;
	double			t1;
	double			t2;
	double			k;
}					t_cone;

typedef struct		s_cylinder
{
	t_vector		p1;
	t_vector		p2;
	double			height;
	double			radius;
	double			a;
	double			b;
	double			c;
	double			t1;
	double			t2;
	t_vector		v;
}					t_cylinder;

typedef struct		s_sphere
{
	t_vector		center;
	double			radius;
	double			t1;
	double			t2;
	double			b;
	double			a;
}					t_sphere;

typedef struct		s_object3d
{
	double			reflective;
	double			specular;
	int				color;
	int				type_of_data;
	void			*data;
}					t_object3d;

typedef struct		s_player
{
	int				i;
	int				k;
	t_vector		position;
	double			d;
	int				rotate_left;
	int				rotate_right;
	double			angle_gor;
	double			angle_ver;
	t_vector		pov;
}					t_player;

typedef struct		s_keys
{
	int				but1_press;
	int				but2_press;
	int				but4_press;
	int				but5_press;
}					t_keys;

typedef struct		s_trace
{
	int				i;
	double			reflect_color1;
	t_vector		r;
	double			local_color;
	double			t;
	double			tmp;
	double			t_max;
	double			reflect;
	t_vector		normal;
	t_vector		direction;
}					t_trace;

typedef struct		s_obj
{
	double			t_max;
	int				k;
	double			t;
}					t_obj;

typedef struct		s_light
{
	int				type_of_light;
	double			intensity;
	t_vector		position;
}					t_light;

typedef struct		s_elem
{
	SDL_Window		*window;
	SDL_Renderer	*renderrer;
	SDL_Event		event;
	SDL_Surface		*surface;
	char			*text;
	int				figure_now;
	double			t_min;
	double			t_max;
	int				i;
	int				depth_recursive;
	int				obj_now;
	int				is_intersect;
	t_vector		intersect;
	t_player		player;
	int				nbr_of_obj;
	int				nbr_of_light;
	t_object3d		arr_object3d[10];
	t_light			arr_light[5];
	t_keys			keys;
	t_vector		normal_now;
	t_obj			obj;
}					t_elem;

void				ft_check_key(t_elem *s_pixel);
void				ft_validate_input(char *line, t_elem *s_pixel);
void				ft_refresh(t_elem *s_pixel);
t_vector			ft_canvas_to_viewport(double x, double y);
double				ft_intersect_ray_sphere(t_vector position, t_elem *s_pixel,
t_vector direction, int i);
double				ft_intersect_ray_plane(t_vector position, t_elem *s_pixel,
t_vector direction, int i);
void				ft_after_mouse(t_elem *s_pixel, int x, int y, int key);
int					ft_get_object(t_elem *s_pixel, int x, int y);
double				ft_intersect_ray_cone(t_vector position, t_elem *s_pixel,
t_vector direction, int i);
double				ft_intersect_ray_cylinder(t_vector position,
t_elem *s_pixel, t_vector direction, int i);
t_vector			ft_normalize_vector(t_vector vec);
int					ft_check_size(t_vector vec, int type_of_object,
t_elem *s_pixel);
double				ft_dot_product(t_vector vec1, t_vector vec2);
int					ft_lighting(int color, int t, t_elem *s_pixel,
t_vector direction);
unsigned			ft_change_color(unsigned color, double k);
double				ft_vector_len(t_vector vec);
int					ft_is_shadow(t_elem *s_pixel, double t, t_vector direction,
int i);
void				ft_change_light(t_elem *s_pixel);
t_vector			ft_reflect_ray(t_vector r, t_vector normal);
unsigned			ft_add_color(unsigned color1, unsigned color2,
unsigned new_color, unsigned r1);
t_vector			ft_rotate_camera(t_vector direction, t_elem *s_pixel);
void				ft_image_on_screen(t_elem *s_pixel);
void				mouse_press(t_elem *s_pixel);
void				mouse_release(t_elem *s_pixel);
void				ft_validate_light(t_elem *s_pixel, int i, int k);
int					ft_check_if_equal(t_vector vec1, t_vector vec2);
void				ft_change_obj_size(t_elem *s_pixel);
int					ft_trace_ray(t_vector position, t_elem *s_pixel,
t_vector direction, int depth);
void				*ft_draw_display(void *data);
void				ft_main_draw(t_elem *s_pixel, int i);
void				ft_mouse_press(t_elem *s_pixel);
void				ft_mouse_wheel(t_elem *s_pixel, int i);
void				ft_mouse_release(t_elem *s_pixel);
void				ft_mouse_move(t_elem *s_pixel, int i);
int					exit_program(t_elem *s_pixel);
void				ft_draw_pixel(t_elem *s_pixel, int x, int y, int color);
void				ft_wait_for_input(t_elem *s_pixel);
void				ft_change_position(t_elem *s_pixel, double angle1,
double angle2);
void				ft_change_object(t_elem *s_pixel, double angle_x,
double angle_z, int i);
void				ft_change_light(t_elem *s_pixel);
void				ft_change_specular(t_elem *s_pixel);
void				ft_change_reflective(t_elem *s_pixel);
void				ft_change_obj_size(t_elem *s_pixel);
void				ft_prepare_programm1(t_elem *s_pixel);
void				ft_change_obj_size_sphere(t_elem *s_pixel, int i);
void				ft_change_obj_size_cylinder(t_elem *s_pixel, int i);
void				ft_change_obj_size_cone(t_elem *s_pixel, int i);
void				ft_change_object_up_down(t_elem *s_pixel, int i,
double angle_x);
void				ft_change_object_left_right(t_elem *s_pixel, int i,
double angle_z);
void				ft_change_object_up_down1(t_elem *s_pixel, int i,
double angle_x);
void				ft_change_object_left_right1(t_elem *s_pixel, int i,
double angle_z);
void				ft_validate_sphere(t_elem *s_pixel, int i);
void				ft_validate_cylinder(t_elem *s_pixel, int i);
void				ft_validate_plane(t_elem *s_pixel, int i);
void				ft_validate_cone(t_elem *s_pixel, int i);
void				ft_validate_amb_light(t_elem *s_pixel, int k);
void				ft_get_trace(t_elem *s_pixel, t_trace *trace);
void				ft_get_t_min_max(t_elem *s_pixel);
int					ft_trace_ray1(t_elem *s_pixel, int depth, t_trace *trace,
t_vector position);
#endif
