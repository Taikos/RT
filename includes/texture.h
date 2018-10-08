/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:41:03 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:41:04 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "struct.h"

typedef t_float3	(*t_get_texture)(t_object *obj,
	t_float3 *impact, int target);

# define APPLI_ALL 20

# define NS_USED 1
# define CS_USED 2

typedef struct		s_get_text
{
	t_get_texture	f_text;
	int				type;
	int				state;
	int				used;
}					t_get_text;

t_float3			get_checker_plane(t_object *obj,
						t_float3 *impact, int target);
t_float3			get_checker_sphere(t_object *obj,
						t_float3 *impact, int target);
t_float3			get_checker_cylinder(t_object *obj,
						t_float3 *impact, int target);
t_float3			get_checker_plane(t_object *obj,
						t_float3 *impact, int target);
t_float3			get_tex_value_plane(t_object *obj,
						t_float3 *impact, int target);
t_float3			get_tex_value_sphere(t_object *obj,
						t_float3 *impact, int target);
t_float3			get_tex_value_cylinder(t_object *obj,
						t_float3 *impact, int target);
t_float3			get_tex_value_plane(t_object *obj,
						t_float3 *impact, int target);
t_float3			get_noise_value_plane(t_object *obj,
						t_float3 *impact, int target);
t_float3			get_noise_value_sphere(t_object *obj,
						t_float3 *impact, int target);
t_float3			get_noise_value_cylinder(t_object *obj,
						t_float3 *impact, int target);

Uint32				getpixel(SDL_Surface *surface, int x, int y);
float				octave(float x, float y, int octaves, float persistence);
float				lerp(float a, float b, float t);
float				fade(float a);

static const		t_get_text g_apply_texture[APPLI_ALL] = {
	(t_get_text){.type = PLANE, .state = CS_CHECKER,
		.f_text = get_checker_plane, .used = CS_USED},
	(t_get_text){.type = SPHERE, .state = CS_CHECKER,
		.f_text = get_checker_sphere, .used = CS_USED},
	(t_get_text){.type = CYLINDER, .state = CS_CHECKER,
		.f_text = get_checker_cylinder, .used = CS_USED},
	(t_get_text){.type = CONE, .state = CS_CHECKER,
		.f_text = get_checker_cylinder, .used = CS_USED},
	(t_get_text){.type = DISK, .state = CS_CHECKER,
		.f_text = get_checker_plane, .used = CS_USED},

	(t_get_text){.type = PLANE, .state = CS_TEXTURE,
		.f_text = get_tex_value_plane, .used = CS_USED},
	(t_get_text){.type = SPHERE, .state = CS_TEXTURE,
		.f_text = get_tex_value_sphere, .used = CS_USED},
	(t_get_text){.type = CYLINDER, .state = CS_TEXTURE,
		.f_text = get_tex_value_cylinder, .used = CS_USED},
	(t_get_text){.type = CONE, .state = CS_TEXTURE,
		.f_text = get_tex_value_cylinder, .used = CS_USED},
	(t_get_text){.type = DISK, .state = CS_TEXTURE,
		.f_text = get_tex_value_plane, .used = CS_USED},

	(t_get_text){.type = PLANE, .state = CS_PERLIN,
		.f_text = get_noise_value_plane, .used = CS_USED},
	(t_get_text){.type = SPHERE, .state = CS_PERLIN,
		.f_text = get_noise_value_sphere, .used = CS_USED},
	(t_get_text){.type = CYLINDER, .state = CS_PERLIN,
		.f_text = get_noise_value_cylinder, .used = CS_USED},
	(t_get_text){.type = CONE, .state = CS_PERLIN,
		.f_text = get_noise_value_cylinder, .used = CS_USED},
	(t_get_text){.type = DISK, .state = CS_PERLIN,
		.f_text = get_noise_value_plane, .used = CS_USED},

	(t_get_text){.type = PLANE, .state = NS_TEXTURE,
		.f_text = get_tex_value_plane, .used = NS_USED},
	(t_get_text){.type = SPHERE, .state = NS_TEXTURE,
		.f_text = get_tex_value_sphere, .used = NS_USED},
	(t_get_text){.type = CYLINDER, .state = NS_TEXTURE,
		.f_text = get_tex_value_cylinder, .used = NS_USED},
	(t_get_text){.type = CONE, .state = NS_TEXTURE,
		.f_text = get_tex_value_cylinder, .used = NS_USED},
	(t_get_text){.type = DISK, .state = NS_TEXTURE,
		.f_text = get_tex_value_plane, .used = NS_USED},
};
#endif
