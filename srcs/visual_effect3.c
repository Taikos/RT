/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_effect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:13:55 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:47:54 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				color_r(int x, int y, t_sdl *win)
{
	int r;

	r = (int)(get_color_pixel(win, x, y, R) / 64 * 64);
	r = r < 0 ? 0 : r;
	return (r);
}

int				color_g(int x, int y, t_sdl *win)
{
	int g;

	g = (int)(get_color_pixel(win, x, y, G) / 64 * 64);
	g = g < 0 ? 0 : g;
	return (g);
}

int				color_b(int x, int y, t_sdl *win)
{
	int b;

	b = (int)(get_color_pixel(win, x, y, B) / 64 * 64);
	b = b < 0 ? 0 : b;
	return (b);
}

int				calc_fr(t_sdl *win, int x, int y)
{
	int r1;
	int r2;
	int fr;

	r1 = (get_color_pixel(win, x, y, R));
	r2 = (get_color_pixel(win, (x + 1 >
					(int)win->scene.x_win ? x : x + 1), y, R));
	fr = r1 - r2;
	return (fr);
}

int				calc_fg(t_sdl *win, int x, int y)
{
	int g1;
	int g2;
	int fg;

	g1 = (get_color_pixel(win, x, y, G));
	g2 = (get_color_pixel(win, (x + 1 >
					(int)win->scene.x_win ? x : x + 1), y, G));
	fg = g1 - g2;
	return (fg);
}
