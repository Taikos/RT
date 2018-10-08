/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 22:26:41 by arguerin          #+#    #+#             */
/*   Updated: 2018/07/25 01:17:50 by arguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	apply_sizewin(t_stock *stock, t_sdl *win)
{
	size_t i;

	i = 0;
	while (i < stock->num_scn)
	{
		(stock->scene[i].x_win) = (win->coord.x_win);
		(stock->scene[i].y_win) = (win->coord.y_win);
		i++;
	}
}

void	call_parser(t_sdl *win, t_stock *stock)
{
	size_t i;

	i = 0;
	if (win->argc == 2)
	{
		if (rt_parser(stock, win->argv[1]) == 0)
			exit(-1);
	}
	else
	{
		if (rt_parser(stock, "demo/scene1.xml") == 0)
			exit(-1);
	}
	stock->cur_scn = 0;
	while (i < stock->num_scn)
		stock->scene[i++].cur_cam = 0;
	stock->feed = 1;
}

void	ft_multi_norme(t_thread *data, t_sdl *win,
	t_lidl *dia, SDL_Thread *recurse[NUM_THREAD])
{
	while (dia->thread < NUM_THREAD)
	{
		data[dia->thread] = (t_thread){.win = win, .thread = dia->thread,
		.screen = dia->screen};
		recurse[dia->thread] =
			SDL_CreateThread(&rt_recurse, "Recurse", &data[dia->thread]);
		dia->thread++;
	}
	dia->thread = 0;
	while (dia->thread < NUM_THREAD)
		SDL_WaitThread(recurse[dia->thread++], NULL);
}

void	multithreading_call(t_sdl *win, t_float3 *screen)
{
	SDL_Thread	*recurse[NUM_THREAD];
	t_thread	data[NUM_THREAD];
	t_lidl		dia;

	dia.thread = 0;
	dia.screen = screen;
	if (win->scene.num_obj == 0 || win->scene.num_lum == 0
	|| win->scene.num_cam == 0)
		rt_error(ERROR_SCN, __FILE__, __LINE__, "");
	else
	{
		if (NUM_THREAD >= 1)
			ft_multi_norme(data, win, &dia, recurse);
		else
		{
			data[dia.thread] = (t_thread){.win = win, .thread = dia.thread,
			.screen = dia.screen};
			rt_recurse(&data[dia.thread]);
		}
	}
}

int		infinity_thread(void *data)
{
	t_sdl			*win;
	static t_float3	*screen;

	win = data;
	call_parser(win, &win->stock);
	apply_sizewin(&win->stock, win);
	if (!screen)
		if (!(screen = (t_float3*)malloc(sizeof(t_float3)
		* win->coord.x_win * win->coord.y_win)))
			exit(-1);
	win->scene = win->stock.scene[win->stock.cur_scn];
	win->cam = win->scene.cam[win->scene.cur_cam];
	while (1)
	{
		event_main_side(win, &screen);
		multithreading_call(win, screen);
		if (win->filter < F_ALL)
			rt_kernel_convolution(win, win->pixel, win->filter);
		else if (win->filter > F_ALL && win->filter <= F_CARTOON)
			rt_basic_filters(win, win->pixel, win->filter);
		event_main_side_wait(win);
	}
	return (0);
}
