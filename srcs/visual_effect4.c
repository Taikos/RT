/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_effect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:55 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 20:13:29 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	this_apply_black_and_white(float *r, float *g, float *b,
		t_float3 *color)
{
	*r = ((unsigned char)(*color).x + (unsigned char)(*color).y
			+ (unsigned char)(*color).z) / 3;
	*g = ((unsigned char)(*color).x + (unsigned char)(*color).y
			+ (unsigned char)(*color).z) / 3;
	*b = ((unsigned char)(*color).x + (unsigned char)(*color).y
			+ (unsigned char)(*color).z) / 3;
}

static void	this_apply_sepia(float *r, float *g, float *b,
		t_float3 *color)
{
	*r = ((unsigned char)(*color).x * 0.393 + (unsigned char)(*color).y * 0.769
			+ (unsigned char)(*color).z * 0.189) / 1;
	*g = ((unsigned char)(*color).x * 0.349 + (unsigned char)(*color).y * 0.686
			+ (unsigned char)(*color).z * 0.168) / 1;
	*b = ((unsigned char)(*color).x * 0.272 + (unsigned char)(*color).y * 0.534
			+ (unsigned char)(*color).z * 0.131) / 1;
}

static void	this_apply_filter(t_float3 *color, int type)
{
	float r;
	float g;
	float b;

	r = (*color).x;
	g = (*color).y;
	b = (*color).z;
	if (type == F_BLACK_WHITE)
		this_apply_black_and_white(&r, &g, &b, color);
	else if (type == F_SEPIA)
		this_apply_sepia(&r, &g, &b, color);
	(*color).x = r > 255 ? 255 : r;
	(*color).y = g > 255 ? 255 : g;
	(*color).z = b > 255 ? 255 : b;
}

static void	this_pourri(t_sdl *win, uint32_t *pixel)
{
	color_pallet(win, pixel, win->pix);
	border_line(win, pixel, win->pix);
}

void		rt_basic_filters(t_sdl *win, uint32_t *pixel, int type)
{
	size_t		x;
	size_t		y;
	t_float3	color;

	y = 0;
	if (type == F_CARTOON)
		return (this_pourri(win, pixel));
	while (y < win->scene.y_win)
	{
		x = 0;
		while (x < win->scene.x_win)
		{
			color.x = *((char*)(pixel + x + y * win->scene.x_win) + 3);
			color.y = *((char*)(pixel + x + y * win->scene.x_win) + 2);
			color.z = *((char*)(pixel + x + y * win->scene.x_win) + 1);
			this_apply_filter(&color, type);
			pixel[x + y * win->scene.x_win] = SDL_MapRGBA(win->pix,
					(int)(color.x), (int)(color.y), (int)(color.z), 0xff);
			x++;
		}
		y++;
	}
}
