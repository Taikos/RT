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

static void		this_get_kernel(size_t *x, size_t *y, t_sdl *win, int k)
{
	if (*y != 0 && (k == K_UP_LEFT || k == K_UP_MID || k == K_UP_RIGHT))
		*y = *y - 1;
	if (*y != win->scene.y_win - 1 && (k == K_DOWN_LEFT || k == K_DOWN_MID
				|| k == K_DOWN_RIGHT))
		*y = *y + 1;
	if (*x != 0 && (k == K_UP_LEFT || k == K_MID_LEFT || k == K_DOWN_LEFT))
		*x = *x - 1;
	if (*x != win->scene.x_win - 1 && (k == K_UP_RIGHT || k == K_MID_RIGHT
				|| k == K_DOWN_RIGHT))
		*x = *x + 1;
}

static char		this_matrix_mult(const int matrix[3][3], int kernel[3][3][3],
		int color, int divi)
{
	int ret;

	ret = (int)(((unsigned char)kernel[2][2][color] * matrix[0][0]
				+ (unsigned char)kernel[2][1][color] * matrix[0][1]
				+ (unsigned char)kernel[2][0][color] * matrix[0][2]
				+ (unsigned char)kernel[1][2][color] * matrix[1][0]
				+ (unsigned char)kernel[1][1][color] * matrix[1][1]
				+ (unsigned char)kernel[1][0][color] * matrix[1][2]
				+ (unsigned char)kernel[0][2][color] * matrix[2][0]
				+ (unsigned char)kernel[0][1][color] * matrix[2][1]
				+ (unsigned char)kernel[0][0][color] * matrix[2][2])
				/ (int)divi);
	ret = ret < 0 ? 0 : ret;
	return ((unsigned char)(ret > 255 ? 255 : ret));
}

static void		this_parse_kernel(t_sdl *win, int (*kernel)[3][3][3],
		size_t xy[3], uint32_t *cp_pixel)
{
	int		i;
	size_t	tmpx;
	size_t	tmpy;

	i = 0;
	while (i < 9)
	{
		tmpx = xy[0];
		tmpy = xy[1];
		this_get_kernel(&tmpx, &tmpy, win, g_get_kernel[i].type);
		(*kernel)[g_get_kernel[i].y][g_get_kernel[i].x][0] =
			*((char*)(cp_pixel + tmpx + tmpy * win->scene.x_win) + 3);
		tmpx = xy[0];
		tmpy = xy[1];
		this_get_kernel(&tmpx, &tmpy, win, g_get_kernel[i].type);
		(*kernel)[g_get_kernel[i].y][g_get_kernel[i].x][1] =
			*((char*)(cp_pixel + tmpx + tmpy * win->scene.x_win) + 2);
		tmpx = xy[0];
		tmpy = xy[1];
		this_get_kernel(&tmpx, &tmpy, win, g_get_kernel[i].type);
		(*kernel)[g_get_kernel[i].y][g_get_kernel[i].x][2] =
			*((char*)(cp_pixel + tmpx + tmpy * win->scene.x_win) + 1);
		i++;
	}
}

static void		this_write_ret(uint32_t **pixel, size_t xy[3], t_sdl *win,
		int kernel[3][3][3])
{
	*((char*)((*pixel) + xy[0] + xy[1] * win->scene.x_win) + 3) =
		this_matrix_mult(g_filter_matrix[xy[2]].matrix, kernel, 0,
				g_filter_matrix[xy[2]].div);
	*((char*)((*pixel) + xy[0] + xy[1] * win->scene.x_win) + 2) =
		this_matrix_mult(g_filter_matrix[xy[2]].matrix, kernel, 1,
				g_filter_matrix[xy[2]].div);
	*((char*)((*pixel) + xy[0] + xy[1] * win->scene.x_win) + 1) =
		this_matrix_mult(g_filter_matrix[xy[2]].matrix, kernel, 2,
				g_filter_matrix[xy[2]].div);
}

void			rt_kernel_convolution(t_sdl *win, uint32_t *pixel, int type)
{
	uint32_t	*cp_pixel;
	int			kernel[3][3][3];
	size_t		xy[3];

	xy[2] = type;
	if (!((cp_pixel) = (uint32_t*)malloc(sizeof(uint32_t)
					* win->coord.y_win * win->coord.x_win)))
		exit(-1);
	ft_memcpy((cp_pixel), (pixel), sizeof(uint32_t)
			* win->coord.y_win * win->coord.x_win);
	xy[1] = 0;
	while (xy[1] < win->scene.y_win)
	{
		xy[0] = 0;
		while (xy[0] < win->scene.x_win)
		{
			this_parse_kernel(win, &kernel, xy, cp_pixel);
			this_write_ret(&pixel, xy, win, kernel);
			xy[0]++;
		}
		xy[1]++;
	}
	free(cp_pixel);
}
