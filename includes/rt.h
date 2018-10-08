/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <arguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 01:43:41 by arguerin          #+#    #+#             */
/*   Updated: 2018/09/03 16:25:13 by yokartou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <SDL2/SDL.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_ttf/SDL_ttf.h>
# include <SDL2/SDL_thread.h>
# include "../libft/libft.h"
# include <math.h>
# include <struct.h>
# include <define.h>
# include <parsing.h>
# include <filter.h>
# include <events.h>
# include <texture.h>
# include <interface.h>
# include <libxml/xmlmemory.h>
# include <libxml/parser.h>
# include <png.h>

# include <sched.h>

/*
**                            #######  #####    ###      ######
**                           ###      ##  ###  ###          ###
** Fonctions proto          #######  ##   ##  ###        #####
**                            ###  ##   ##  ###       ####
**                       #######  #####    #######  #######
*/

/*
** -----------------------FONCTIONS INIT-----------------------
*/

int				init_all(t_sdl *win, t_events *action);
int				init_all1(t_sdl *win, t_events *action);
int				init_event(t_sdl *win, t_events *action);
int				init_interface(t_sdl *win);
void			initialize(t_sdl *win);

/*
** -------------------FONCTIONS THREAD----------------
*/

void			ft_multi_norme(t_thread *data, t_sdl *win,
	t_lidl *dia, SDL_Thread *recurse[NUM_THREAD]);
int				create_thread(t_sdl *win);
int				infinity_thread(void *data);

/*
** -------------------FONCTIONS EVENT----------------
*/

void			event_all(t_sdl *win, t_events *action);
void			event_main_side(t_sdl *win, t_float3 **screen);
void			event_main_side_wait(t_sdl *win);
int				rt_display_interface_2(t_idisplay *norm,
					int *cur_obj, int *cur_light);
int				rt_display_interface_3(t_idisplay *norm,
					int *cur_obj, int *cur_light);
int				rt_display_interface_4(t_idisplay *norm, int *cur_obj);
void			init_event_norm(t_sdl *win, int *pos_x,
					int *pos_y, Uint32 *m_state);

/*
** Fonctions d'initialisation
*/

t_view			**rt_init_projection(size_t x_win, size_t y_win, float fov);
t_float3		*rt_init_origin(t_float3 *ori, t_object *obj, size_t num_obj);
void			rt_update_buffer(t_scene *env, t_cam *cam);

/*
** Fonctions calculs
*/

void			rt_look_lights(t_refl_refr *ref, const t_scene *scene,
					const t_visible *v, const t_float3 *vector);

void			rt_translate_screen(t_float3 *vector, t_view **screen,
					size_t x, size_t y);
void			rt_rotate_screen(t_float4 *quaternion, t_view **screen,
					size_t x, size_t y);

void			rt_origin_object(const t_float3 *origin,
					const t_object *object, t_float3 *const new_origin);
int				rt_scene_pixels(t_sdl *win, int thread, t_float3 *screen);
void			rt_scene_camera(size_t order, t_cam *cam);

void			rt_vector_normalize(t_float3 *vector);
void			rt_vector_reverse(t_float3 *vector);

float			rt_vector_length(t_float3 *v);
float			rt_vector_angle(t_float3 *v1, t_float3 *v2);
t_float3		rt_vector_impact(t_float3 *origin, t_float3 *vector, float k);
void			rt_vector_cam(size_t xwin, size_t ywin, t_view **screen,
					float fov);
float			rt_vector_dot_p(t_float3 *v1, t_float3 *v2);
t_float3		rt_vector_cross_p(t_float3 *v1, t_float3 *v2);

void			rt_quaternion_create(t_float3 *axis, float alpha,
					t_float4 *quaternion);
void			rt_quaternion_multiply(t_float4 q1, t_float4 q2,
					t_float4 *result);
void			rt_quaternion_to_euler(float *alpha, float *beta,
					float *omega, t_float4 *quaternion);
void			rt_quaternion_to_matrix(t_float4 *q, float m[3][3]);
void			rt_euler_to_quaternion(float alpha, float beta,
					float omega, t_float4 *quaternion);

void			rt_quaternion_apply(t_float4 *q, t_float3 v, t_float3 *result);
t_float3		rt_matrix_apply(t_float3 *vector, float matrix[3][3]);

/*
** fonctions de multiscene / multicam
*/
void			apply_sizewin(t_stock *stock, t_sdl *win);
void			call_parser(t_sdl *win, t_stock *stock);
void			create_multimutex(t_stock *stock);

/*
** fonctions utils (genre Fix color, etc...)
*/

void			fix_color(float *x, float *y, float *z);
double			rt_atof(char *str);
void			rt_putfloat_fd(float nb, int fd);
void			rt_error(int error, const char *file, const int line,
					const char *str);
void			rt_float3_mult(const t_float3 *v1, const t_float3 *v2,
					t_float3 *result);
void			rt_float3_mult_float(const t_float3 *v1, const float v2,
					t_float3 *result);
void			rt_float3_add(const t_float3 *v1, const t_float3 *v2,
					t_float3 *result);
void			rt_float3_min(t_float3 *value, const float min);
void			rt_float3_min_max(t_float3 *value, float min, float max);
void			rt_float_min_max(float *number, float min, float max);
void			rt_int_min_max(int *number, int min, int max);

/*
** fonctions lumieres
*/

void			rt_light(const t_object *object, const t_light *light,
					t_refl_refr *ref, const t_float3 *vector);
void			rt_light_diffuse(const t_float3 *color_obj,
					const t_float3 *lightning, const float alpha_nl,
					t_float3 *target);

int				rt_recurse(void *data);
t_float3		rt_recurse_pixel(t_recursive *iter, t_scene *scene, int thread);
t_float3		rt_recurse_reflection(t_float3 *vector, t_float3 *normal);
t_float3		rt_recurse_refraction(t_float3 *vector, t_float3 *normal,
					float n);

void			rt_add_queue(t_recursive *data, int thread);
void			rt_add_pool(t_list *elem, int thread);
t_list			*rt_get_queue(int thread);
t_list			*rt_get_pool(int thread);
t_list			**rt_list_queue(int i, int thread);
t_list			**rt_list_pool(int i, int thread);

/*
** fonctions options
*/
void			apply_options(t_scene *scene, t_visible *v, t_refl_refr *ref,
				t_float3 *dir);
t_float3		rotate_normal(t_float3 *tex_normal, t_float3 *obj_normal,
				t_float3 *dir);
t_float3		get_checker_sphere(t_object *obj, t_float3 *impact, int target);
t_float3		get_checker_plane(t_object *obj, t_float3 *impact, int target);
t_float3		get_checker_cylinder(t_object *obj, t_float3 *impact,
					int target);
t_float3		get_noise_value_sphere(t_object *obj, t_float3 *impact,
					int target);
void			get_pos_sphere(t_float3 *impact, float *longi, float *lati);
float			get_pos_cylinder(t_getpos vars, float *circular, int h, int w);
t_float3		get_noise_value_cylinder(t_object *obj, t_float3 *impact,
					int target);
t_float3		get_noise_value_plane(t_object *obj, t_float3 *impact,
					int target);

/*
** fonctions de collision
*/

void			rt_collider_delta(t_double3 *abc, t_impact *cldr);

void			rt_apply_limits(const t_object *object,
	t_impact *impact, t_float3 *ray, t_float3 *origin);

int				rt_first_noticeable(t_visible *v1, t_impact *i2, int id);
void			rt_impact_to_visible(t_impact *cldr, t_visible *view, int id);
t_float3		rt_impact_to_light_spot(const t_float3 *impact,
					const t_light *light, const t_scene *scene,
					t_refl_refr *ref);
t_float3		rt_impact_to_light_directional(const t_float3 *impact,
					const t_light *light, const t_scene *scene,
					t_refl_refr *ref);

t_float3		rt_collider_normal(t_object *object, t_float3 *origin,
					t_float3 *vector, float k);

typedef void(*t_collider)(t_float3*, t_float3*, const t_object*, t_impact*);

void			rt_collider_plane(t_float3 *origin,
					t_float3 *vector, const t_object *plane, t_impact *i);
void			rt_collider_sphere(t_float3 *origin,
					t_float3 *vector, const t_object *sphere, t_impact *i);
void			rt_collider_cylinder(t_float3 *origin,
					t_float3 *vector, const t_object *cylinder, t_impact *i);
void			rt_collider_cone(t_float3 *origin,
					t_float3 *vector, const t_object *sphere, t_impact *i);
void			rt_collider_disk(t_float3 *origin,
					t_float3 *vector, const t_object *disk, t_impact *i);

static const t_collider	g_colliders[OBJECTS_ALL] = {
	rt_collider_plane,
	rt_collider_sphere,
	rt_collider_cylinder,
	rt_collider_cone,
	rt_collider_disk
};

typedef	int(*t_rndr)(t_sdl*);

int				create_rndr_i(t_sdl *win);

static const t_rndr g_rndr[RNDR_ALL] = {
	create_rndr_i,
};

int				create_win_scene1(t_sdl *win);

/*
**	fonctions de sauvegarde
*/

void			rt_picture_save_stable(t_sdl *win, uint32_t *pixel,
					char *filename);

int				rt_parser(t_stock *stock, char *filename);

int				rt_save_xml(t_sdl *win, char *filename);

/*
**	Global permutation table
*/

static const int g_permutation[32] =
{ 9, 1, 6, 10, 0, 2, 13, 7, 14, 11, 3, 4, 12, 8, 5, 15, 9, 1,
	6, 10, 0, 2, 13, 7, 14, 11, 3, 4, 12, 8, 5, 15};

static const t_float3 g_gradients[8] = {
	{.x = 0, .y = 1, .z = 0},
	{.x = 1, .y = 1, .z = 0},
	{.x = 1, .y = 0, .z = 0},
	{.x = 1, .y = -1, .z = 0},
	{.x = 0, .y = -1, .z = 0},
	{.x = -1, .y = -1, .z = 0},
	{.x = -1, .y = 0, .z = 0},
	{.x = -1, .y = 1, .z = 0},
};

/*
** Filters
*/

void			rt_stereoscopy(t_sdl *win);
void			rt_kernel_convolution(t_sdl *win, uint32_t *pixel, int type);
void			rt_basic_filters(t_sdl *win, uint32_t *pixel, int type);

unsigned char	get_color_pixel(t_sdl *win, int x, int y, int enu);
void			color_pallet(t_sdl *win, uint32_t *kernel,
						SDL_PixelFormat *p_form);
void			border_line(t_sdl *win, uint32_t *kernel,
						SDL_PixelFormat *p_form);
int				calc_fr(t_sdl *win, int x, int y);
int				calc_fg(t_sdl *win, int x, int y);
int				calc_fb(t_sdl *win, int x, int y);
int				color_r(int x, int y, t_sdl *win);
int				color_g(int x, int y, t_sdl *win);
int				color_b(int x, int y, t_sdl *win);
void			reprint(t_sdl *win, uint32_t *kernel);
void			which_line(t_sdl *win, uint32_t *kernel,
					SDL_PixelFormat *p_form, t_norline *nline);

/*
** fonction lib graph
*/

SDL_Surface		*rt_get_surface(int type, const char *path);
SDL_Surface		*rt_get_text(char *path, char *text, int size);
SDL_Texture		*rt_get_texture(int type, const char *path,
				SDL_Renderer *renderer);
SDL_Texture		*rt_create_background(t_sdl *win, const t_picture *picture,
					const t_text *tab, int len);
void			rt_parse_button(t_sdl *win);
void			multithreading_call(t_sdl *win, t_float3 *screen);
int				rt_display_interface(t_idisplay norm);

#endif
