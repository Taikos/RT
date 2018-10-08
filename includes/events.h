/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:40:10 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:40:11 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include <stdlib.h>
# include "struct.h"

# include <SDL2/SDL.h>

typedef struct	s_state
{
	int			key;
	int			value;
	uint64_t	offset;
}				t_state;

enum			e_switch
{
	SWITCH_NO,
	SWITCH_SCENE_NEXT,
	SWITCH_SCENE_PREV,
	SWITCH_CAM_NEXT,
	SWITCH_CAM_PREV,
	SWITCH_WIN_SIZE,
	SWITCH_ALL
};

enum			e_kb_event
{
	KB_ESCAPE,
	KB_MOVE_UP,
	KB_MOVE_DOWN,
	KB_MOVE_LEFT,
	KB_MOVE_RIGHT,
	KB_MOVE_FORWARD,
	KB_MOVE_BACKWARD,
	KB_ROTATE_UP,
	KB_ROTATE_DOWN,
	KB_ROTATE_LEFT,
	KB_ROTATE_RIGHT,
	KB_ROTATE_ROLL_LEFT,
	KB_ROTATE_ROLL_RIGHT,
	KB_SWITCH_SCENE_NEXT,
	KB_SWITCH_SCENE_PREV,
	KB_SWITCH_CAM_NEXT,
	KB_SWITCH_CAM_PREV,
	KB_RESET,
	KB_MUSIC,
	KB_EVENT_ALL
};

static const t_state g_keyboard[KB_EVENT_ALL] = {
	(t_state){.key = SDL_SCANCODE_ESCAPE, .value = SDL_TRUE,
		.offset = offsetof(t_sdl, event_exit)},
	(t_state){.key = SDL_SCANCODE_LSHIFT, .value = T_UP,
		.offset = offsetof(t_sdl, event_cam)},
	(t_state){.key = SDL_SCANCODE_LCTRL, .value = T_DOWN,
		.offset = offsetof(t_sdl, event_cam)},
	(t_state){.key = SDL_SCANCODE_LEFT, .value = T_LEFT,
		.offset = offsetof(t_sdl, event_cam)},
	(t_state){.key = SDL_SCANCODE_RIGHT, .value = T_RIGHT,
		.offset = offsetof(t_sdl, event_cam)},
	(t_state){.key = SDL_SCANCODE_UP, .value = T_FORWARD,
		.offset = offsetof(t_sdl, event_cam)},
	(t_state){.key = SDL_SCANCODE_DOWN, .value = T_BACKWARD,
		.offset = offsetof(t_sdl, event_cam)},
	(t_state){.key = SDL_SCANCODE_W, .value = R_UP,
		.offset = offsetof(t_sdl, event_cam)},
	(t_state){.key = SDL_SCANCODE_S, .value = R_DOWN,
		.offset = offsetof(t_sdl, event_cam)},
	(t_state){.key = SDL_SCANCODE_A, .value = R_LEFT,
		.offset = offsetof(t_sdl, event_cam)},
	(t_state){.key = SDL_SCANCODE_D, .value = R_RIGHT,
		.offset = offsetof(t_sdl, event_cam)},
	(t_state){.key = SDL_SCANCODE_Q, .value = R_ROLL_LEFT,
		.offset = offsetof(t_sdl, event_cam)},
	(t_state){.key = SDL_SCANCODE_E, .value = R_ROLL_RIGHT,
		.offset = offsetof(t_sdl, event_cam)},
	(t_state){.key = SDL_SCANCODE_KP_7, .value = SWITCH_SCENE_PREV,
		.offset = offsetof(t_sdl, event_pov)},
	(t_state){.key = SDL_SCANCODE_KP_8, .value = SWITCH_SCENE_NEXT,
		.offset = offsetof(t_sdl, event_pov)},
	(t_state){.key = SDL_SCANCODE_KP_4, .value = SWITCH_CAM_PREV,
		.offset = offsetof(t_sdl, event_pov)},
	(t_state){.key = SDL_SCANCODE_KP_5, .value = SWITCH_CAM_NEXT,
		.offset = offsetof(t_sdl, event_pov)},
	(t_state){.key = SDL_SCANCODE_R, .value = RESET,
		.offset = offsetof(t_sdl, event_reset)},
	(t_state){.key = SDL_SCANCODE_M, .value = MUSIC,
		.offset = offsetof(t_sdl, event_music)},
};

#endif
