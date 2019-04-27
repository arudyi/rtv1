/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:17 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/27 19:03:11 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <pthread.h>
# include "../frameworks/SDL2/SDL.h"
# include "../frameworks/SDL2/SDL_thread.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../lib/libft/includes/libft.h"
# define WIDTH 1000
# define HEIGHT 1000
# define THREADS 20
typedef double	t_vector __attribute__((ext_vector_type(4)));

typedef struct s_plane
{
    t_vector normal;
    t_vector point;
}              t_plane;

typedef struct s_cone
{
    t_vector p1;
    t_vector p2;
    double angle;
    double height;
    double radius;
}               t_cone;

typedef struct s_cylinder
{
    t_vector p1;
    t_vector p2;
    double height;
    double radius;
}              t_cylinder;

typedef struct s_sphere
{
    t_vector center;
    double radius;
}               t_sphere;

typedef struct s_object3d
{
    double  reflective;
    double  specular;
    int     color;
    int     type_of_data;
    void    *data;
}               t_object3d;

typedef struct s_player
{
    t_vector    position;
    double      d;
    int rotate_left;
    int rotate_right;
    double angle_gor;
    double angle_ver;
    t_vector pov;
}               t_player;

typedef struct s_keys
{
    int         but1_press;
    int         but2_press;
    int         but4_press;
    int         but5_press;
}               t_keys;

typedef struct s_skybox
{
    int         type_of_skybox;
}               t_skybox;

typedef struct s_light
{
    int type_of_light;
    double intensity;
    t_vector position;
}               t_light;


typedef struct		s_elem
{
    SDL_Window      *window;
	SDL_Renderer    *renderrer;
    SDL_Event       event;
    SDL_Surface     *surface;
    int             is_reflect;
    int             is_shadow;
    int             is_specular;
    char            *text;
    int             figure_now;
    double          t_min;
    double          t_max;
    int             i;
    int             depth_recursive;
    //int             color_now;
    int             obj_now;
    int             is_intersect;
    t_vector        intersect;
    t_player        player;
    int             nbr_of_obj;
    int             nbr_of_light;
    t_object3d      arr_object3d[100];
    t_light         arr_light[10];
    t_keys          keys;
    t_vector        normal_now;
}					t_elem;




void        ft_check_key(t_elem *s_pixel);
void        ft_main_draw(t_elem *s_pixel);
void        ft_validate_input(char *line, t_elem *s_pixel);
void        ft_refresh(t_elem *s_pixel);
t_vector    ft_canvas_to_viewport(double x, double y);
double      ft_intersect_ray_sphere(t_vector position, t_elem *s_pixel, t_vector direction, int i);
double      ft_intersect_ray_plane(t_vector position, t_elem *s_pixel, t_vector direction, int i);
void        ft_after_mouse(t_elem *s_pixel, int x, int y, int key);
int         ft_get_object(t_elem *s_pixel, int x, int y);
double      ft_intersect_ray_cone(t_vector position, t_elem *s_pixel, t_vector direction, int i);
double      ft_intersect_ray_cylinder(t_vector position, t_elem *s_pixel, t_vector direction, int i);
t_vector    ft_normalize_vector(t_vector vec);
int         ft_check_size(t_vector vec, int type_of_object, t_elem *s_pixel);
double      ft_dot_product(t_vector vec1, t_vector vec2);
int         ft_lighting(int color, int t, t_elem *s_pixel, t_vector direction);
unsigned    ft_change_color(unsigned color, double k);
double      ft_vector_len(t_vector vec);
int         ft_is_shadow(t_elem *s_pixel, double t, t_vector direction, int i);
void        ft_change_light(t_elem *s_pixel);
t_vector    ft_reflect_ray(t_vector r, t_vector normal);
unsigned    ft_add_color(unsigned color1, unsigned color2);
t_vector    ft_rotate_camera(t_vector direction, t_elem *s_pixel);
void        ft_image_on_screen(t_elem *s_pixel);
void        mouse_press(t_elem *s_pixel);
void        mouse_release(t_elem *s_pixel);
void        ft_validate_light(t_elem *s_pixel, int i, int k);
int         ft_check_if_equal(t_vector vec1, t_vector vec2);
void        ft_change_obj_size(t_elem *s_pixel);
#endif