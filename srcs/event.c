/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:11:05 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:11:06 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	this_window_event(t_sdl *win)
{
	int size_x;
	int size_y;

	SDL_GetWindowSize(win->win, &size_x, &size_y);
	if (!win->b_event && size_x > 10 && size_y > 10
			&& (win->coord.x_win != (size_t)size_x
				|| win->coord.y_win != (size_t)size_y))
	{
		win->coord.x_win = (size_t)size_x;
		win->coord.y_win = (size_t)size_y;
		win->event_pov = SWITCH_WIN_SIZE;
		win->b_event = SDL_TRUE;
	}
	if (win->event.type == SDL_WINDOWEVENT)
		if (win->event.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			if (win->song == 1)
			{
				system("killall afplay");
				win->song = 0;
			}
			win->event_exit = SDL_TRUE;
		}
}

static void	this_render_norm(t_sdl *win)
{
	this_window_event(win);
	SDL_UnlockTexture(win->tex);
	SDL_RenderClear(win->rndr);
	SDL_RenderCopy(win->rndr, win->tex, NULL, NULL);
	SDL_RenderPresent(win->rndr);
	SDL_LockTexture(win->tex, NULL, (void *)&win->pixel, &win->coord.line);
	SDL_RenderClear(win->rndr_i);
}

static void	this_render(t_sdl *win, int pos_x, int pos_y, Uint32 m_state)
{
	static int id = I_HOME;

	this_render_norm(win);
	if (rt_display_interface((t_idisplay){.win = win, .background
				= win->interface[id], .button = g_interface[id].button, .len
				= g_interface[id].s_button, .id = &id, .x = pos_x, .y = pos_y,
				.click = m_state}))
	{
		rt_display_interface((t_idisplay){.win = win, .background
				= win->interface[id], .button = g_interface[id].button, .len
				= g_interface[id].s_button, .id = &id, .x = pos_x, .y = pos_y,
				.click = 0});
	}
	SDL_RenderPresent(win->rndr_i);
	if (win->b_event)
		SDL_CondSignal(win->c_event);
	SDL_UnlockMutex(win->m_event);
}

static void	this_keyboard_state(Uint8 *state, int i, t_sdl *win)
{
	if (state[g_keyboard[i].key])
	{
		*((int*)((uint64_t)win + g_keyboard[i].offset)) = g_keyboard[i].value;
		win->b_event = SDL_TRUE;
	}
}

int			init_event(t_sdl *win, t_events *action)
{
	int		i;
	int		pos_x;
	int		pos_y;
	Uint32	m_state;
	Uint8	*state;

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	(void)action;
	win->event_exit = SDL_FALSE;
	while (!win->event_exit)
	{
		init_event_norm(win, &pos_x, &pos_y, &m_state);
		SDL_LockMutex(win->m_event);
		i = 0;
		while (!win->b_event && i < KB_EVENT_ALL)
			this_keyboard_state(state, i++, win);
		this_render(win, pos_x, pos_y, m_state);
	}
	if (win->song == 1)
	{
		system("killall afplay");
		win->song = 0;
	}
	exit(0);
	return (0);
}
