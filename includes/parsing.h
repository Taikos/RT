/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:40:32 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:40:33 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"
# include "fcntl.h"
# include "define.h"
# include <libxml/xmlmemory.h>
# include <libxml/parser.h>
# define SCENE_PARAM		(9)
# define OBJECT_PARAM		(20)
# define CAM_PARAM			(3)
# define LIGHT_PARAM		(5)
# define USED_AMBIENT		(1 << 0)
# define USED_SPOT			(1 << 1)
# define USED_DIRECTIONAL	(1 << 2)
# define USED_CONE			(1 << 3)
# define USED_CYLINDER		(1 << 4)
# define USED_DISK			(1 << 5)
# define USED_PLANE			(1 << 6)
# define USED_SPHERE		(1 << 7)

/*
** Names of values in Xml
*/

# define PARSE_TYPE			"type"
# define PARSE_NAME 		"name"
# define PARSE_VALUE		"value"
# define PARSE_COLOR		"rgb"
# define PARSE_FLOAT3		"xyz"
# define PARSE_FLOAT4		"wxyz"

typedef struct	s_type
{
	int		type;
	char	*name;
}				t_type;

/*
** Usefull to stock totals numbers of objects,
** lights and cameras
*/

typedef struct	s_num
{
	size_t		amb;
	size_t		cam;
	size_t		obj;
	size_t		lum;
}				t_num;

/*
** Prototypes of functions pointers
*/

typedef void(*t_get_parser)(xmlNode*, void*, char*);
typedef void(*t_fill_parser)(xmlNode*, t_scene*, t_num*, char*);

/*
** Struct for identify and stock xml tags
*/

typedef struct	s_tag
{
	const char			*text;
	t_fill_parser		f_tag;
	t_get_parser		f_prop;
	char				*type;
	uint64_t			offset;
	uint64_t			used;
}				t_tag;

/*
** Fonctions pointed
*/

void			rt_get_string(xmlNodePtr cur, void *ptr, char *name);
void			rt_get_float(xmlNodePtr cur, void *ptr, char *name);
void			rt_get_float3(xmlNodePtr cur, void *ptr, char *name);
void			rt_get_float4(xmlNodePtr cur, void *ptr, char *name);
void			rt_get_int(xmlNodePtr cur, void *ptr, char *name);
void			rt_get_path(xmlNodePtr cur, void *ptr, char *name);
void			rt_fill_camera(xmlNodePtr cur, t_scene *scene, t_num *num,
			char *filename);
void			rt_fill_ambient(xmlNodePtr cur, t_scene *scene, t_num *num,
			char *filename);
void			rt_fill_spot(xmlNodePtr cur, t_scene *scene, t_num *num,
			char *filename);
void			rt_fill_directional(xmlNodePtr cur, t_scene *scene, t_num *num,
			char *filename);
void			rt_fill_plane(xmlNodePtr cur, t_scene *scene, t_num *num,
			char *filename);
void			rt_fill_sphere(xmlNodePtr cur, t_scene *scene, t_num *num,
			char *filename);
void			rt_fill_cylinder(xmlNodePtr cur, t_scene *scene, t_num *num,
			char *filename);
void			rt_fill_cone(xmlNodePtr cur, t_scene *scene, t_num *num,
			char *filename);
void			rt_fill_disk(xmlNodePtr cur, t_scene *scene, t_num *num,
			char *filename);
void			rt_fill_object(xmlNodePtr ptr, t_object *object, uint64_t used,
			char *filename);
void			rt_fill_light(xmlNodePtr ptr, t_light *light, uint64_t used,
			char *filename);

/*
** Normal fonctions
*/
void			call_parser(t_sdl *win, t_stock *stock);
void			rt_fill_scene(t_scene *scene, xmlNodePtr cur, char *filename);
void			rt_check_scene(t_num *num, xmlNodePtr cur, char *filename);
void			rt_default_scene(t_stock *stock);
void			rt_default_object(t_object *object);
void			rt_default_light(t_light *light);
void			rt_default_camera(t_cam *camera);
void			rt_post_computing(t_stock *stock, char *filename);
void			rt_open_xml(xmlDocPtr *doc, xmlNodePtr *cur, char *filename);
void			rt_malloc(t_stock **stock, xmlNodePtr cur, char *filename);
void			rt_fill(xmlNodePtr cur, t_stock **stock, char *filename);

/*
** Table for objects identification
*/

static const t_tag	g_object[OBJECT_PARAM] = {
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "pos", .type = PARSE_FLOAT3, .f_prop = rt_get_float3,
		.offset = offsetof(t_object, pos)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "color", .type = PARSE_COLOR, .f_prop = rt_get_float3,
		.offset = offsetof(t_object, kd)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "color_ambient", .type = PARSE_COLOR, .f_prop = rt_get_float3,
		.offset = offsetof(t_object, ka)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "color_specular", .type = PARSE_COLOR, .f_prop = rt_get_float3,
		.offset = offsetof(t_object, ks)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "rotate", .type = PARSE_FLOAT3, .f_prop = rt_get_float3,
		.offset = offsetof(t_object, rotate.rot)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "transparency", .type = PARSE_VALUE, .f_prop = rt_get_float,
		.offset = offsetof(t_object, transparency)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "shininess", .type = PARSE_VALUE, .f_prop = rt_get_float,
		.offset = offsetof(t_object, ns)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "limit_min", .type = PARSE_FLOAT3, .f_prop = rt_get_float3,
		.offset = offsetof(t_object, limit_min)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "limit_max", .type = PARSE_FLOAT3, .f_prop = rt_get_float3,
		.offset = offsetof(t_object, limit_max)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_SPHERE,
		.text = "ray", .type = PARSE_VALUE, .f_prop = rt_get_float,
		.offset = offsetof(t_object, ray)},
(t_tag){.used = USED_CONE,
		.text = "alpha", .type = PARSE_VALUE, .f_prop = rt_get_float,
		.offset = offsetof(t_object, alpha)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "texture", .type = PARSE_NAME, .f_prop = rt_get_path,
		.offset = offsetof(t_object, texture_path)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "checker_A", .type = PARSE_COLOR, .f_prop = rt_get_float3,
		.offset = offsetof(t_object, checkerdata.color1)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "checker_B", .type = PARSE_COLOR, .f_prop = rt_get_float3,
		.offset = offsetof(t_object, checkerdata.color2)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "checker_width", .type = PARSE_VALUE, .f_prop = rt_get_int,
		.offset = offsetof(t_object, checkerdata.w)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "checker_length", .type = PARSE_VALUE, .f_prop = rt_get_int,
		.offset = offsetof(t_object, checkerdata.l)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "noise_A", .type = PARSE_COLOR, .f_prop = rt_get_float3,
		.offset = offsetof(t_object, noisedata.color1)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "noise_B", .type = PARSE_COLOR, .f_prop = rt_get_float3,
		.offset = offsetof(t_object, noisedata.color2)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "noise_octaves", .type = PARSE_VALUE, .f_prop = rt_get_int,
		.offset = offsetof(t_object, noisedata.octaves)},
(t_tag){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "noise_persistence", .type = PARSE_VALUE,
		.f_prop = rt_get_float,
		.offset = offsetof(t_object, noisedata.persistence)},
};

/*
** Table for cameras identification
*/

static const t_tag	g_cam[CAM_PARAM] = {
(t_tag){.text = "fov", .type = PARSE_VALUE, .f_prop = rt_get_float,
		.offset = offsetof(t_cam, fov)},
(t_tag){.text = "origin", .type = PARSE_FLOAT3, .f_prop = rt_get_float3,
		.offset = offsetof(t_cam, origin)},
(t_tag){.text = "rotate", .type = PARSE_FLOAT4, .f_prop = rt_get_float4,
		.offset = offsetof(t_cam, rotate_start)},
};

/*
** Table for lights identification
*/

static const t_tag	g_light[LIGHT_PARAM] = {
(t_tag){.used = USED_AMBIENT | USED_DIRECTIONAL | USED_SPOT,
		.text = "color", .type = PARSE_COLOR, .f_prop = rt_get_float3,
		.offset = offsetof(t_light, color)},
(t_tag){.used = USED_DIRECTIONAL | USED_SPOT | USED_AMBIENT,
		.text = "intensity", .type = PARSE_VALUE, .f_prop = rt_get_float,
		.offset = offsetof(t_light, intensity)},
(t_tag){.used = USED_DIRECTIONAL | USED_SPOT,
		.text = "ray", .type = PARSE_VALUE, .f_prop = rt_get_float,
		.offset = offsetof(t_light, ray)},
(t_tag){.used = USED_SPOT,
		.text = "pos", .type = PARSE_FLOAT3, .f_prop = rt_get_float3,
		.offset = offsetof(t_light, pos)},
(t_tag){.used = USED_DIRECTIONAL,
		.text = "dir", .type = PARSE_FLOAT3, .f_prop = rt_get_float3,
		.offset = offsetof(t_light, pos)},
};

/*
** Table for scenes identification
*/

static const t_tag	g_scene[SCENE_PARAM] = {
(t_tag){.text = "ambient", .f_tag = rt_fill_ambient,
		.offset = offsetof(t_num, amb)},
(t_tag){.text = "spot", .f_tag = rt_fill_spot,
		.offset = offsetof(t_num, lum)},
(t_tag){.text = "soleil", .f_tag = rt_fill_directional,
		.offset = offsetof(t_num, lum)},
(t_tag){.text = "camera", .f_tag = rt_fill_camera,
		.offset = offsetof(t_num, cam)},
(t_tag){.text = "plan", .f_tag = rt_fill_plane,
		.offset = offsetof(t_num, obj)},
(t_tag){.text = "sphere", .f_tag = rt_fill_sphere,
		.offset = offsetof(t_num, obj)},
(t_tag){.text = "cylindre", .f_tag = rt_fill_cylinder,
		.offset = offsetof(t_num, obj)},
(t_tag){.text = "cone", .f_tag = rt_fill_cone,
		.offset = offsetof(t_num, obj)},
(t_tag){.text = "disque", .f_tag = rt_fill_disk,
		.offset = offsetof(t_num, obj)}
};

/*
** Table for textures identification
*/

static const t_type	g_texture[TEXTURE_ALL] = {
(t_type){.name = "color", .type = TEXTURE_COLOR},
(t_type){.name = "pertu", .type = TEXTURE_PERTU},
};

/*
**	To create a new Xml
*/

typedef void(*t_put_xml)(void*, char*, char*, int);

void			rt_put_t_float_fd(void *ptr, char *vname, char *tname, int fd);
void			rt_put_t_float3_fd(void *ptr, char *vname, char *tname, int fd);
void			rt_put_t_float4_fd(void *ptr, char *vname, char *tname, int fd);
void			rt_put_string_fd(void *ptr, char *vname, char *tname, int fd);
void			rt_put_path_fd(void *ptr, char *vname, char *tname, int fd);
void			rt_put_start_tag_name(char *type, char *name, int indent,
					int fd);
void			rt_put_end_tag(char *type, int indent, int fd);

typedef struct	s_save
{
	const char			*text;
	t_put_xml			p_prop;
	char				*type;
	uint64_t			offset;
	uint64_t			used;
}				t_save;

static const t_save	g_scene_obj_save[OBJECTS_ALL] = {
(t_save){.text = "plan", .used = USED_PLANE},
(t_save){.text = "sphere", .used = USED_SPHERE},
(t_save){.text = "cylindre", .used = USED_CYLINDER},
(t_save){.text = "cone", .used = USED_CONE},
(t_save){.text = "disque", .used = USED_DISK},
};

static const t_save	g_scene_lum_save[LIGHTS_ALL] = {
(t_save){.text = "ambient", .used = USED_AMBIENT},
(t_save){.text = "spot", .used = USED_SPOT},
(t_save){.text = "soleil", .used = USED_DIRECTIONAL},
};

# define CAMERA_NAME	"camera"

static const t_save	g_object_save[OBJECT_PARAM] = {
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "pos", .type = PARSE_FLOAT3,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_object, pos)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "color", .type = PARSE_COLOR,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_object, kd)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "color_ambient", .type = PARSE_COLOR,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_object, ka)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "color_specular", .type = PARSE_COLOR,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_object, ks)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "rotate", .type = PARSE_FLOAT3,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_object, rotate.rot)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "transparency", .type = PARSE_VALUE,
		.p_prop = rt_put_t_float_fd,
		.offset = offsetof(t_object, transparency)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "shininess", .type = PARSE_VALUE,
		.p_prop = rt_put_t_float_fd,
		.offset = offsetof(t_object, ns)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "limit_min", .type = PARSE_FLOAT3,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_object, limit_min)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "limit_max", .type = PARSE_FLOAT3,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_object, limit_max)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_SPHERE,
		.text = "ray", .type = PARSE_VALUE,
		.p_prop = rt_put_t_float_fd,
		.offset = offsetof(t_object, ray)},
(t_save){.used = USED_CONE,
		.text = "alpha", .type = PARSE_VALUE,
		.p_prop = rt_put_t_float_fd,
		.offset = offsetof(t_object, alpha)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "texture", .type = PARSE_NAME,
		.p_prop = rt_put_path_fd,
		.offset = offsetof(t_object, texture_path)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "checker_A", .type = PARSE_COLOR,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_object, checkerdata.color1)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "checker_B", .type = PARSE_COLOR,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_object, checkerdata.color2)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "checker_width", .type = PARSE_VALUE,
		.p_prop = rt_put_t_float_fd,
		.offset = offsetof(t_object, checkerdata.w)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "checker_length", .type = PARSE_VALUE,
		.p_prop = rt_put_t_float_fd,
		.offset = offsetof(t_object, checkerdata.l)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "noise_A", .type = PARSE_COLOR,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_object, noisedata.color1)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "noise_B", .type = PARSE_COLOR,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_object, noisedata.color2)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "noise_octaves", .type = PARSE_VALUE,
		.p_prop = rt_put_t_float_fd,
		.offset = offsetof(t_object, noisedata.octaves)},
(t_save){.used = USED_CONE | USED_CYLINDER
		| USED_DISK | USED_PLANE | USED_SPHERE,
		.text = "noise_persistence", .type = PARSE_VALUE,
		.p_prop = rt_put_t_float_fd,
		.offset = offsetof(t_object, noisedata.persistence)},
};

static const t_save	g_light_save[LIGHT_PARAM] = {
(t_save){.used = USED_AMBIENT | USED_DIRECTIONAL | USED_SPOT,
		.text = "color", .type = PARSE_COLOR,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_light, color)},
(t_save){.used = USED_DIRECTIONAL | USED_SPOT | USED_AMBIENT,
		.text = "intensity", .type = PARSE_VALUE,
		.p_prop = rt_put_t_float_fd,
		.offset = offsetof(t_light, intensity)},
(t_save){.used = USED_DIRECTIONAL | USED_SPOT,
		.text = "ray", .type = PARSE_VALUE,
		.p_prop = rt_put_t_float_fd,
		.offset = offsetof(t_light, ray)},
(t_save){.used = USED_SPOT,
		.text = "pos", .type = PARSE_FLOAT3,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_light, pos)},
(t_save){.used = USED_DIRECTIONAL,
		.text = "dir", .type = PARSE_FLOAT3,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_light, pos)},
};

static const t_save	g_cam_save[CAM_PARAM] = {
(t_save){.text = "fov", .type = PARSE_VALUE,
		.p_prop = rt_put_t_float_fd,
		.offset = offsetof(t_cam, fov)},
(t_save){.text = "origin", .type = PARSE_FLOAT3,
		.p_prop = rt_put_t_float3_fd,
		.offset = offsetof(t_cam, origin)},
(t_save){.text = "rotate", .type = PARSE_FLOAT4,
		.p_prop = rt_put_t_float4_fd,
		.offset = offsetof(t_cam, rotate_start)},
};

#endif
