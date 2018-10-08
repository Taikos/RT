/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:37:50 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 17:42:10 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	this_event_pov_p2(t_sdl *win)
{
	if (win->event_pov == SWITCH_SCENE_NEXT)
		win->stock.cur_scn += (win->stock.cur_scn < win->stock.num_scn - 1 ? 1
				: -win->stock.cur_scn);
	else if (win->event_pov == SWITCH_SCENE_PREV)
		win->stock.cur_scn -= (win->stock.cur_scn > 0 ? 1 : win->stock.cur_scn
				- (win->stock.num_scn - 1));
	else if (win->event_pov == SWITCH_CAM_NEXT)
		win->stock.scene[win->stock.cur_scn].cur_cam +=
			(win->stock.scene[win->stock.cur_scn].cur_cam <
			win->stock.scene[win->stock.cur_scn].num_cam - 1 ?
			1 : -win->stock.scene[win->stock.cur_scn].cur_cam);
	else if (win->event_pov == SWITCH_CAM_PREV)
		win->stock.scene[win->stock.cur_scn].cur_cam -=
			(win->stock.scene[win->stock.cur_scn].cur_cam > 0 ?
			1 : win->stock.scene[win->stock.cur_scn].cur_cam
			- (win->stock.scene[win->stock.cur_scn].num_cam - 1));
	else
		return (0);
	return (1);
}

static void	this_event_pov(t_sdl *win, t_float3 **screen)
{
	static SDL_Texture	*save;
	static t_float3		*save_s;
	SDL_Texture			*tmp;

	if (this_event_pov_p2(win))
		;
	else if (win->event_pov == SWITCH_WIN_SIZE)
	{
		apply_sizewin(&win->stock, win);
		if (save)
			SDL_DestroyTexture(save);
		save = win->tex;
		tmp = SDL_CreateTexture(win->rndr, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, win->coord.x_win, win->coord.y_win);
		SDL_LockTexture(tmp, NULL, (void**)&win->pixel, &win->coord.line);
		SDL_SetTextureBlendMode(tmp, SDL_BLENDMODE_BLEND);
		win->tex = tmp;
		if (save_s)
			free(save_s);
		save_s = *screen;
		if (!(*screen = (t_float3*)malloc(sizeof(t_float3)
						* win->coord.x_win * win->coord.y_win)))
			exit(-1);
	}
	win->scene = win->stock.scene[win->stock.cur_scn];
}

static void	event_main_side2(t_sdl *win)
{
	if (win->event_music)
	{
		if (win->song == 1)
		{
			system("killall afplay");
			win->song = 0;
		}
	}
	rt_update_buffer(&win->scene, &win->cam);
	SDL_UnlockMutex(win->m_event);
}

void		event_main_side(t_sdl *win, t_float3 **screen)
{
	SDL_LockMutex(win->m_event);
	if (win->event_pov)
	{
		this_event_pov(win, screen);
		win->cam = win->scene.cam[win->scene.cur_cam];
		win->cam.moved = MOVMENT_ALL;
	}
	if (win->event_cam)
	{
		rt_scene_camera((size_t)win->event_cam, &win->cam);
		win->cam.moved = MOVMENT_ALL;
	}
	if (win->event_reset)
	{
		win->filter = F_ALL;
		win->stock.feed = 0;
		rt_scene_camera((size_t)win->event_cam, &win->cam);
	}
	event_main_side2(win);
}

int			init_all(t_sdl *win, t_events *action)
{
	initialize(win);
	if (IMG_Init(IMG_INIT_WEBP) == -1)
		rt_error(ERROR_INIT_IMG, __FILE__, __LINE__, 0);
	if (TTF_Init() == -1)
		rt_error(ERROR_INIT_TTF, __FILE__, __LINE__, 0);
	win->m_event = SDL_CreateMutex();
	win->c_event = SDL_CreateCond();
	create_thread(win);
	win->init.init_all = init_all1(win, action);
	return (0);
}
