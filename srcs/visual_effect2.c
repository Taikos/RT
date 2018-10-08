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

unsigned char	get_color_pixel(t_sdl *win, int x, int y, int enu)
{
	if (enu == R)
		return (*((char*)(win->pixel + x + y * (int)win->scene.x_win) + 3));
	else if (enu == G)
		return (*((char*)(win->pixel + x + y * (int)win->scene.x_win) + 2));
	else
		return (*((char*)(win->pixel + x + y * (int)win->scene.x_win) + 1));
}

void			reprint(t_sdl *win, uint32_t *kernel)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	while (y < (int)win->scene.y_win)
	{
		while (x < (int)win->scene.x_win)
		{
			win->pixel[x + y * (int)win->scene.x_win] =
				kernel[x + y * (int)win->scene.x_win];
			x++;
		}
		x = 0;
		y++;
	}
}

void			color_pallet(t_sdl *win, uint32_t *kernel,
		SDL_PixelFormat *p_form)
{
	int x;
	int y;
	int r;
	int g;
	int b;

	x = 0;
	y = 0;
	while (y < (int)win->scene.y_win)
	{
		while (x < (int)win->scene.x_win)
		{
			r = color_r(x, y, win);
			g = color_g(x, y, win);
			b = color_b(x, y, win);
			kernel[x + y * (int)win->scene.x_win] = SDL_MapRGB(p_form,
					(int)(r), (int)(g), (int)(b));
			x++;
		}
		x = 0;
		y++;
	}
	reprint(win, kernel);
}

void			which_line(t_sdl *win, uint32_t *kernel,
		SDL_PixelFormat *p_form, t_norline *nline)
{
	if ((nline->fr <= 25 && nline->fr >= -25) && (nline->fg <= 25 &&
				nline->fg >= -25) && (nline->fb <= 25 && nline->fb >= -25))
		kernel[nline->x + nline->y * (int)win->scene.x_win] =
			win->pixel[nline->x + nline->y * (int)win->scene.x_win];
	else if ((nline->fr <= 30 && nline->fr >= -30) || (nline->fg <= 30 &&
				nline->fg >= -30) || (nline->fb <= 30 && nline->fb >= -30))
		kernel[nline->x + nline->y * (int)win->scene.x_win] =
			SDL_MapRGB(p_form, 0, 0, 0);
	else
	{
		kernel[(nline->x - 2) + nline->y * (int)win->scene.x_win] =
			SDL_MapRGB(p_form, 0, 0, 0);
		kernel[(nline->x - 1) + nline->y * (int)win->scene.x_win] =
			SDL_MapRGB(p_form, 0, 0, 0);
		kernel[nline->x + nline->y * (int)win->scene.x_win] =
			SDL_MapRGB(p_form, 0, 0, 0);
	}
}

void			border_line(t_sdl *win, uint32_t *kernel,
		SDL_PixelFormat *p_form)
{
	t_norline nline;

	nline.x = 0;
	nline.y = 0;
	while (nline.y < (int)win->scene.y_win)
	{
		while (nline.x < (int)win->scene.x_win)
		{
			nline.fr = calc_fr(win, nline.x, nline.y);
			nline.fg = calc_fg(win, nline.x, nline.y);
			nline.fb = calc_fb(win, nline.x, nline.y);
			which_line(win, kernel, p_form, &nline);
			nline.x++;
		}
		nline.x = 0;
		nline.y++;
	}
	reprint(win, kernel);
}
