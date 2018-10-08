/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:40:03 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:40:06 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*
** define pour les calculs
*/

# define EPSILON	(0.0005f)

# define FALSE		(0)
# define TRUE		(1 << 0)
# define K1			(1 << 1)
# define K2			(1 << 2)
# define LIMIT_X	(1 << 3)
# define LIMIT_Y	(1 << 4)
# define LIMIT_Z	(1 << 5)

# define FD_ERROR	(2)
# define NUM_ITER	(10)
# define NUM_THREAD	(8)

enum			e_objects
{
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	DISK,
	OBJECTS_ALL
};

enum			e_lights
{
	L_AMBIENT,
	L_SPOT,
	L_DIRECTIONAL,
	LIGHTS_ALL
};

enum			e_movment
{
	NONE,
	T_LEFT,
	T_RIGHT,
	T_UP,
	T_DOWN,
	T_FORWARD,
	T_BACKWARD,
	TRANSLATE,
	R_LEFT,
	R_RIGHT,
	R_UP,
	R_DOWN,
	R_ROLL_LEFT,
	R_ROLL_RIGHT,
	ROTATE,
	RESET,
	MUSIC,
	MOVMENT_ALL
};

enum			e_error
{
	NO_ERROR,
	ERROR_UNKNOW_VALUE,
	ERROR_NO_PROPERTY,
	ERROR_UNKNOW_TYPE,
	ERROR_NO_TAG,
	ERROR_UNKNOW_FILE,
	ERROR_OPEN_PICTURE,
	ERROR_DEF_SAVE,
	ERROR_OPEN_SAVE,
	ERROR_OPEN_IMG,
	ERROR_FATAL_PARSE,
	ERROR_INIT_IMG,
	ERROR_INIT_TTF,
	ERROR_CREATE_SDL,
	ERROR_SCN,
	ERROR_EXIT,
	ERROR_UNKNOW_TAG,
	ERROR_UNKNOW_PROPERTY,
	ERROR_PATH,
	ERROR_MALLOC,
	ERROR_NO_PATH,
	ERROR_ALL
};

static const char	*g_error[ERROR_ALL] = {
	": dev error : that cannot happen i am too good :",
	": parser error : Unknown value in property : ",
	": parser error : Missing property : ",
	": parser error : Unknow type : ",
	": parser error : Missing tag :",
	": parser error : Bad file format :",
	": picture saving error : opening fail",
	": xml saving error : define errror :",
	": xml saving error : opening fail",
	": image loading : opening fail",
	": parsing error : fatal error",
	": sdl image : init error",
	": sdl ttf : init error",
	": sdl : create error :",
	": parser error : Some scene stuff is missing :",
	": dev error : that cannot happen i am too good :",
	": parser error : Unknown tag : ",
	": parser error : Unknown property : ",
	": parser error : Invalid path : ",
	": malloc error : ",
	": parser error : Path missing :"
};

enum			e_textures
{
	TEXTURE_COLOR,
	TEXTURE_PERTU,
	TEXTURE_ALL
};

enum			e_color_state
{
	CS_SINGLE,
	CS_CHECKER,
	CS_TEXTURE,
	CS_PERLIN,
	CS_ALL
};

enum			e_normal_state
{
	NS_NATURAL,
	NS_TEXTURE,
	NS_ALL
};

enum			e_color
{
	R,
	G,
	B
};

#endif
