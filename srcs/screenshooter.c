/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:52 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 21:26:19 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	this_picture_save_free(t_sdl *win, png_structp *png,
		png_byte **row_pointers, FILE *fp)
{
	size_t	y;

	y = 0;
	while (y < win->scene.y_win)
	{
		png_free(*png, row_pointers[y]);
		y++;
	}
	png_free(*png, row_pointers);
	fclose(fp);
}

static void	this_picture_save_write(t_sdl *win, png_structp *png,
		png_byte **row_pointers, uint32_t *pixel)
{
	size_t		x;
	size_t		y;
	png_byte	*row;

	y = 0;
	while (y < win->scene.y_win)
	{
		row_pointers[y] = png_malloc(*png, win->scene.x_win * 3);
		row = row_pointers[y];
		x = 0;
		while (x < win->scene.x_win)
		{
			*row++ = *((char*)(pixel + x + y * win->scene.x_win) + 3);
			*row++ = *((char*)(pixel + x + y * win->scene.x_win) + 2);
			*row++ = *((char*)(pixel + x + y * win->scene.x_win) + 1);
			++x;
		}
		++y;
	}
}

void		rt_picture_save_stable(t_sdl *win, uint32_t *pixel, char *filename)
{
	FILE			*fp;
	png_structp		png;
	png_infop		info;
	png_byte		**row_pointers;

	if (!(fp = fopen(filename, "wb")))
		rt_error(ERROR_OPEN_PICTURE, filename, 0, 0);
	if (!(png = png_create_write_struct(PNG_LIBPNG_VER_STRING,
					NULL, NULL, NULL)))
		rt_error(ERROR_OPEN_PICTURE, filename, 0, 0);
	if (!(info = png_create_info_struct(png)))
		rt_error(ERROR_OPEN_PICTURE, filename, 0, 0);
	png_set_IHDR(png, info, win->scene.x_win, win->scene.y_win, 8,
		PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);
	row_pointers = png_malloc(png, win->scene.y_win * sizeof(png_byte*));
	this_picture_save_write(win, &png, row_pointers, pixel);
	png_init_io(png, fp);
	png_set_rows(png, info, row_pointers);
	png_write_png(png, info, PNG_TRANSFORM_IDENTITY, NULL);
	this_picture_save_free(win, &png, row_pointers, fp);
	png_destroy_write_struct(&png, &info);
}

static void	rt_fix_color_negativ(float *x, float *y, float *z)
{
	*x = *x < 0 ? 0 : *x;
	*y = *y < 0 ? 0 : *y;
	*z = *z < 0 ? 0 : *z;
	*x = *x > 2 ? 2 : *x;
}

void		fix_color(float *x, float *y, float *z)
{
	t_float3	c;

	if (*x <= 1 && *y <= 1 && *z <= 1)
		return ;
	rt_fix_color_negativ(x, y, z);
	c.x = 1;
	c.y = *y < 1 ? *y + (1 - *y) * (*x - 1) : 1;
	c.z = *z < 1 ? *z + (1 - *z) * (*x - 1) : 1;
	if (*y >= *x && *y >= *z)
	{
		*y = *y > 2 ? 2 : *y;
		c.x = *x < 1 ? *x + (1 - *x) * (*y - 1) : 1;
		c.y = 1;
		c.z = *z < 1 ? *z + (1 - *z) * (*y - 1) : 1;
	}
	else if (*z >= *x && *z >= *y)
	{
		*z = *z > 2 ? 2 : *z;
		c.x = *x < 1 ? *x + (1 - *x) * (*z - 1) : 1;
		c.y = *y < 1 ? *y + (1 - *y) * (*z - 1) : 1;
		c.z = 1;
	}
	*x = c.x;
	*y = c.y;
	*z = c.z;
}
