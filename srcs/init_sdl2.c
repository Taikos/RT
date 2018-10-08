/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:11 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:37:42 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			init_all1(t_sdl *win, t_events *action)
{
	int i;

	rt_parse_button(win);
	i = 0;
	while (i < INTERFACE_ALL)
	{
		win->interface[i] = rt_create_background(win,
				&g_background[g_interface[i].bg],
				g_interface[i].text, g_interface[i].s_text);
		i++;
	}
	SDL_UnlockTexture(win->tex);
	SDL_RenderCopy(win->rndr, win->tex, NULL, NULL);
	win->init.init_event = init_event(win, action);
	SDL_DestroyTexture(win->tex);
	SDL_DestroyRenderer(win->rndr);
	SDL_DestroyWindow(win->win);
	return (0);
}

int			create_win_scene1(t_sdl *win)
{
	void		*tmp;
	uint32_t	*pixel;

	if (win)
	{
		win->win = SDL_CreateWindow("RT", 100, 100,
				win->coord.x_win, win->coord.y_win, SDL_WINDOW_RESIZABLE);
		if (win->win == NULL)
			rt_error(ERROR_CREATE_SDL, __FILE__, __LINE__, "window");
		win->rndr = SDL_CreateRenderer(win->win, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (win->rndr == NULL)
			rt_error(ERROR_CREATE_SDL, __FILE__, __LINE__, "renderer");
		pixel = NULL;
		win->tex = SDL_CreateTexture(win->rndr, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, win->coord.x_win, win->coord.y_win);
		if (win->tex == NULL)
			rt_error(ERROR_CREATE_SDL, __FILE__, __LINE__, "texture");
		win->pix = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
		SDL_LockTexture(win->tex, NULL, &tmp, &win->coord.line);
		SDL_SetTextureBlendMode(win->tex, SDL_BLENDMODE_BLEND);
		pixel = (uint32_t *)tmp;
		win->pixel = pixel;
	}
	return (0);
}

int			init_interface(t_sdl *win)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		return (-1);
	}
	win->wini = SDL_CreateWindow("Interface", 1900, 300,
			win->coord.x_wini, win->coord.y_wini, SDL_WINDOW_SHOWN);
	if (win->wini == NULL)
	{
		return (-1);
	}
	win->init.init_rndr_i = (*g_rndr[RNDR_1])(win);
	if (SDL_RenderClear(win->rndr_i) < 0)
		return (-1);
	return (0);
}

int			create_rndr_i(t_sdl *win)
{
	if (!(win->rndr_i))
		win->rndr_i = SDL_CreateRenderer(win->wini, 0,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (win->rndr_i == NULL)
	{
		return (-1);
	}
	return (0);
}

SDL_Texture	*rt_create_background(t_sdl *win, const t_picture *picture,
		const t_text *tab, int len)
{
	SDL_Surface	*background;
	SDL_Surface	*text;
	SDL_Texture *bg;

	background = rt_get_surface(picture->n_type, picture->n_path);
	while (len--)
	{
		text = rt_get_text(tab[len].font, tab[len].text, tab[len].size);
		SDL_BlitSurface(text, NULL, background, (SDL_Rect*)&tab[len].rect);
		SDL_FreeSurface(text);
	}
	bg = SDL_CreateTextureFromSurface(win->rndr_i, background);
	SDL_FreeSurface(background);
	return (bg);
}
