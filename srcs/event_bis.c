/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:11:20 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:11:21 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_event_norm(t_sdl *win, int *pos_x, int *pos_y, Uint32 *m_state)
{
	SDL_PollEvent(&win->event);
	SDL_PumpEvents();
	if (win->wini == SDL_GetMouseFocus())
		(*m_state) = SDL_GetMouseState(pos_x, pos_y);
	else
	{
		(*m_state) = 0;
		(*pos_x) = 0;
		(*pos_y) = 0;
	}
}

void	event_main_side_wait(t_sdl *win)
{
	SDL_LockMutex(win->m_event);
	win->b_event = SDL_FALSE;
	win->event_pov = 0;
	win->event_cam = 0;
	win->event_reset = 0;
	while (!win->b_event)
		SDL_CondWait(win->c_event, win->m_event);
	SDL_UnlockMutex(win->m_event);
}
