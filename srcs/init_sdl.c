/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 22:31:15 by arguerin          #+#    #+#             */
/*   Updated: 2018/07/24 22:51:22 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Surface	*rt_get_surface(int type, const char *path)
{
	SDL_Surface *tmp;

	tmp = NULL;
	if (type & (TYPE_SVG | TYPE_PNG))
		tmp = IMG_Load(path);
	else if (type & TYPE_BMP)
		tmp = SDL_LoadBMP(path);
	if (!tmp)
		rt_error(ERROR_OPEN_IMG, path, 0, "get surface");
	return (tmp);
}

SDL_Surface	*rt_get_text(char *path, char *text, int size)
{
	SDL_Color	black;
	TTF_Font	*font;
	SDL_Surface	*texture;

	black = (SDL_Color){.a=0, .r=20, .g=20, .b=20};
	font = TTF_OpenFont(path, size);
	texture = TTF_RenderText_Blended(font, text, black);
	TTF_CloseFont(font);
	return (texture);
}

SDL_Texture	*rt_get_texture(int type, const char *path, SDL_Renderer *renderer)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;

	surface = rt_get_surface(type, path);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		rt_error(ERROR_OPEN_IMG, path, 0, "get texture");
	return (texture);
}

void		rt_parse_button(t_sdl *win)
{
	int		i;

	i = 0;
	while (i < BUTTON_ALL)
	{
		win->button[i].normal = rt_get_texture(g_button[i].n_type,
				g_button[i].n_path, win->rndr_i);
		win->button[i].hover = rt_get_texture(g_button[i].h_type,
				g_button[i].h_path, win->rndr_i);
		i++;
	}
}

int			init_sdl(t_sdl *win)
{
	if (win)
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		{
			ft_putendl("Error SDL");
			return (-1);
		}
		win->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, win->coord.x_win,
		win->coord.y_win, SDL_WINDOW_RESIZABLE);
		if (win->win == NULL)
		{
			ft_putendl("Error SDL Window");
			return (-1);
		}
		win->rndr = SDL_CreateRenderer(win->win, -1, SDL_RENDERER_ACCELERATED |
				SDL_RENDERER_PRESENTVSYNC);
		if (win->rndr == NULL)
		{
			ft_putendl("Error SDL Renderer");
			return (-1);
		}
	}
	return (0);
}
