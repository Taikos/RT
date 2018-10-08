/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collider_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:34:19 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 17:34:21 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int		main(int argc, char **argv)
{
	t_events	action;
	t_sdl		win;
	int			i;

	ft_memset((void*)&action, 0, sizeof(t_events));
	ft_memset((void*)&win, 0, sizeof(t_sdl));
	win.filter = F_ALL;
	win.argc = argc;
	win.argv = argv;
	win.stock.feed = 0;
	win.song = 1;
	system("afplay ./bonus/interface.mp3 & ");
	i = init_all(&win, &action);
	if (win.song == 1)
	{
		system("killall afplay");
		win.song = 0;
	}
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
