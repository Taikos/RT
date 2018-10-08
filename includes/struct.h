/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:40:55 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:40:57 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*
** struct floats
*/

# include <stdlib.h>
# include "define.h"
# include "interface.h"

/*
** struct sdl2
*/

typedef struct	s_var
{
	int		i;
	int		j;
}				t_var;

typedef	struct	s_init
{
	int				init_event;
	int				init_bmp1;
	int				init_bmp2;
	int				init_bpm;
	int				init_bpm_pos;
	int				init_button_m_menu;
	int				init_tex_2;
	int				init_tex;
	int				init;
	int				init_all;
	int				init_interface;
	int				init_create_surfi;
	int				init_create_surfi_text;
	int				init_text_rt;
	int				init_text_scene1;
	int				init_fond_scene1;
	int				init_text_scene2;
	int				init_fond_scene2;
	int				init_text_scene3;
	int				init_fond_scene3;
	int				init_text_scene4;
	int				init_fond_scene4;
	int				init_text_scene5;
	int				init_fond_scene5;
	int				init_text_scene6;
	int				init_fond_scene6;
	int				init_button_home;
	int				init_button_add1;
	int				init_button_add2;
	int				init_button_add3;
	int				init_button_home_v;
	int				init_rndr_i;
	int				init_rndr_b;
	int				init_button_back;
	int				init_obj_add;
	int				init_light_add;
	int				init_cam_add;
}				t_init;

typedef struct	s_coord
{
	size_t			x_win;
	size_t			y_win;
	size_t			x_wini;
	size_t			y_wini;
	int				x_mouse;
	int				y_mouse;
	void			**pixel;
	int				line;
}				t_coord;

typedef struct	s_font
{
	TTF_Font	*police;
	TTF_Font	*text;
	TTF_Font	*home;
	TTF_Font	*rt;
	TTF_Font	*scene1;
	TTF_Font	*scene2;
	TTF_Font	*scene3;
	TTF_Font	*scene4;
	TTF_Font	*scene5;
	TTF_Font	*scene6;
	TTF_Font	*add_obj;
	TTF_Font	*add_light;
	TTF_Font	*add_cam;
}				t_font;

typedef struct	s_img
{
	SDL_Rect	rect;
	SDL_Texture	*text;
}				t_img;

typedef struct	s_events
{
	SDL_bool		key[SDL_NUM_SCANCODES];
	SDL_bool		quit;
	int				x;
	int				y;
	int				xrel;
	int				yrel;
	int				xwheel;
	int				ywheel;
}				t_events;

typedef struct	s_texture2
{
	SDL_Texture *normal;
	SDL_Texture *hover;
}				t_texture2;

/*
** Autres structs
*/

typedef struct	s_int2
{
	int		x;
	int		y;
}				t_int2;

typedef struct	s_float3
{
	float x;
	float y;
	float z;
}				t_float3;

typedef struct	s_float4
{
	float w;
	float x;
	float y;
	float z;
}				t_float4;

typedef struct	s_double3
{
	double x;
	double y;
	double z;
}				t_double3;

/*
** struct collisions
*/

typedef struct	s_impact
{
	int			hit;
	float		k1;
	float		k2;
}				t_impact;

typedef struct	s_visible
{
	int			visible;
	float		k;
	t_float3	ori;
	t_float3	vec;
}				t_visible;

/*
** struct lumieres
*/

typedef struct	s_light
{
	t_float3	pos;
	t_float3	color;
	float		intensity;
	t_float3	luminance;
	float		ray;
	float		alpha;
	int			type;
	char		*name;
}				t_light;

typedef struct	s_refl_refr
{
	t_float3	color;
	t_float3	ka;
	t_float3	kd;
	t_float3	ks;
	t_float3	normal;
	t_float3	normal_h;
	t_float3	light;
	t_float3	impact[2];
	float		len;
	size_t		x;
	size_t		y;
	int			visible;
}				t_refl_refr;

/*
** struct objets
*/

typedef struct	s_checker
{
	int			w;
	int			l;
	t_float3	color1;
	t_float3	color2;
}				t_checker;

typedef struct	s_noise
{
	int			octaves;
	float		persistence;
	t_float3	color1;
	t_float3	color2;
}				t_noise;

typedef struct	s_rotate
{
	t_float3	rot;
	float		mat[3][3];
	float		mat_i[3][3];
}				t_rotate;

typedef struct	s_object
{
	char		*name;
	int			type;
	t_float3	pos;

	float		ray;
	float		alpha;

	t_rotate	rotate;

	int			limit;
	t_float3	limit_min;
	t_float3	limit_max;

	int			color_state;
	int			normal_state;
	char		*texture_path[TEXTURE_ALL];
	SDL_Surface *texture[TEXTURE_ALL];
	t_noise		noisedata;
	t_checker	checkerdata;

	t_float3	ka;
	t_float3	kd;
	t_float3	ks;
	float		ns;

	float		transparency;
}				t_object;

/*
** struct init
*/

typedef struct	s_recursive
{
	size_t		iter;
	t_float3	coeff;
	uint32_t	*pixel;
	t_float3	origin;
	t_float3	vector;
	t_float3	*color;
}				t_recursive;

typedef struct	s_view
{
	t_float3	origin;
	t_float3	vector;
}				t_view;

typedef struct	s_cam
{
	t_float4	rotate_start;
	t_float4	rotate;
	t_float3	translate;
	t_float3	axis_x;
	t_float3	axis_y;
	t_float3	axis_z;
	t_float3	origin;
	float		alpha;
	float		fov;
	int			pitch;
	int			moved;
	char		*name;
}				t_cam;

typedef struct	s_scene
{
	size_t		x_win;
	size_t		y_win;
	size_t		num_obj;
	size_t		num_lum;
	size_t		num_cam;
	size_t		cur_cam;
	size_t		prev_cam;

	t_cam		*cam;
	t_object	*object;
	t_light		*light;
	t_light		ambient;
	t_view		**screen;
	t_view		***buffer;
	char		*name;
	SDL_mutex	*m_picture;
}				t_scene;

typedef struct	s_stock
{
	size_t		num_scn;
	size_t		cur_scn;
	size_t		prev_scn;

	int			feed;
	t_scene		*scene;
}				t_stock;

typedef struct	s_getpos
{
	t_object	*obj;
	t_float3	*impact;
}				t_getpos;

typedef struct	s_uint8_3
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
}				t_uint8_3;

typedef struct	s_sdl
{
	t_texture2		button[BUTTON_ALL];

	SDL_Texture		*interface[INTERFACE_ALL];
	SDL_mutex		*m_event;
	SDL_cond		*c_event;
	SDL_bool		b_event;
	int				event_cam;
	int				event_pov;
	int				event_exit;
	int				event_reset;
	int				event_music;
	int				song;

	SDL_Rect		dst;
	SDL_Rect		rect;
	SDL_PixelFormat *pix;

	SDL_Texture		*tex;

	SDL_Surface		*fond;
	SDL_Surface		*screen;
	SDL_Point		*point;
	SDL_Color		color;
	SDL_Event		event;
	SDL_Window		*wini;
	SDL_Window		*win;
	SDL_Renderer	*rndr;
	SDL_Renderer	*rndr_i;

	SDL_threadID	thread_testid;
	SDL_Thread		*thread_test;

	uint32_t		*pixel;
	t_coord			coord;
	t_init			init;
	t_var			var;
	t_font			font;

	t_cam			cam;
	t_scene			scene;
	t_stock			stock;
	int				argc;
	char			**argv;
	int				test;

	SDL_Rect		dst_interface;

	SDL_Rect		rect_interface;
	SDL_Rect		rect_interface1;

	SDL_Surface		*fond_surfi;
	SDL_Surface		*fond_surfi1;
	int				filter;
}				t_sdl;

typedef struct	s_thread
{
	int			thread;
	t_sdl		*win;
	t_float3	*screen;
}				t_thread;

typedef struct	s_scnpxl
{
	int			thread;
	t_float3	*screen;
	t_recursive	loop;
	t_visible	*v;
}				t_scnpxl;

typedef struct	s_value
{
	uint64_t	offset;
	int			min_max;
}				t_value;

typedef struct	s_lidl
{
	int			thread;
	t_float3	*screen;
}				t_lidl;

typedef struct	s_idisplay
{
	t_sdl				*win;
	SDL_Texture			*background;
	const t_rectangle	*button;
	int					len;
	int					*id;
	int					x;
	int					y;
	Uint32				click;
	float				*var;
	int					*val;
	t_scene				*scene;
	t_object			*object;
	t_cam				*camera;
	t_light				*light;
	int					refresh;
	int					pouet;
}				t_idisplay;

static const t_value g_value[VALUE_ALL] = {
	(t_value){.offset = offsetof(t_object, pos.x), .min_max = MM_NONE},
	(t_value){.offset = offsetof(t_object, pos.y), .min_max = MM_NONE},
	(t_value){.offset = offsetof(t_object, pos.z), .min_max = MM_NONE},
	(t_value){.offset = offsetof(t_object, ka.x), .min_max = MM_10},
	(t_value){.offset = offsetof(t_object, ka.y), .min_max = MM_10},
	(t_value){.offset = offsetof(t_object, ka.z), .min_max = MM_10},
	(t_value){.offset = offsetof(t_object, kd.x), .min_max = MM_10},
	(t_value){.offset = offsetof(t_object, kd.y), .min_max = MM_10},
	(t_value){.offset = offsetof(t_object, kd.z), .min_max = MM_10},
	(t_value){.offset = offsetof(t_object, ks.x), .min_max = MM_10},
	(t_value){.offset = offsetof(t_object, ks.y), .min_max = MM_10},
	(t_value){.offset = offsetof(t_object, ks.z), .min_max = MM_10},
	(t_value){.offset = offsetof(t_object, transparency), .min_max = MM_10},
	(t_value){.offset = offsetof(t_object, ray), .min_max = MM_EPS},
	(t_value){.offset = offsetof(t_object, ns), .min_max = MM_1},
	(t_value){.offset = offsetof(t_object, alpha), .min_max = MM_ALPHA},
	(t_value){.offset = offsetof(t_cam, origin.x), .min_max = MM_NONE},
	(t_value){.offset = offsetof(t_cam, origin.y), .min_max = MM_NONE},
	(t_value){.offset = offsetof(t_cam, origin.z), .min_max = MM_NONE},
	(t_value){.offset = offsetof(t_cam, fov), .min_max = MM_13},
	(t_value){.offset = offsetof(t_light, pos.x), .min_max = MM_NONE},
	(t_value){.offset = offsetof(t_light, pos.y), .min_max = MM_NONE},
	(t_value){.offset = offsetof(t_light, pos.z), .min_max = MM_NONE},
	(t_value){.offset = offsetof(t_light, color.x), .min_max = MM_10_LUM},
	(t_value){.offset = offsetof(t_light, color.y), .min_max = MM_10_LUM},
	(t_value){.offset = offsetof(t_light, color.z), .min_max = MM_10_LUM},
	(t_value){.offset = offsetof(t_light, ray), .min_max = MM_EPS},
	(t_value){.offset = offsetof(t_light, intensity), .min_max = MM_10_LUM},
};

#endif
