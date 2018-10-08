/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:10:43 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:10:45 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		create_thread(t_sdl *win)
{
	win->thread_test = SDL_CreateThread(&infinity_thread, "Test", win);
	if (NULL == win->thread_test)
		ft_putendl("\nSDL_CreateThread failed");
	return (0);
}

void	initialize(t_sdl *win)
{
	win->coord.x_win = 1920;
	win->coord.y_win = 1080;
	win->coord.x_wini = X_WIN_I;
	win->coord.y_wini = Y_WIN_I;
	win->init.init_interface = init_interface(win);
	win->init.init = create_win_scene1(win);
}

void	rt_error(int error, const char *file, const int line, const char *str)
{
	if (error > 0 && error < ERROR_ALL)
	{
		system("killall afplay");
		if (file)
			ft_putstr_fd(file, FD_ERROR);
		if (line)
			ft_putnbr_fd(line, FD_ERROR);
		ft_putstr_fd(g_error[error], FD_ERROR);
		if (str)
			ft_putstr_fd(str, FD_ERROR);
		ft_putchar_fd('\n', FD_ERROR);
		if (error < ERROR_EXIT)
			exit(-1);
	}
}
