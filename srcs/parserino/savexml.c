/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:18 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:59:11 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		this_save_object_fd(t_object *obj, int used, int fd)
{
	int		i;

	i = 0;
	rt_put_start_tag_name((char *)g_scene_obj_save[obj->type].text,
								obj->name, 2, fd);
	while (i < OBJECT_PARAM)
	{
		if (used & g_object_save[i].used)
			(*g_object_save[i].p_prop)((void*)((uint64_t)obj
				+ g_object_save[i].offset),
				g_object_save[i].type, (char*)g_object_save[i].text, fd);
		i++;
	}
	rt_put_end_tag((char *)g_scene_obj_save[obj->type].text, 2, fd);
}

static void		this_save_light(t_light *lum, int used, int fd)
{
	int		i;

	i = 0;
	rt_put_start_tag_name((char *)g_scene_lum_save[lum->type].text,
								lum->name, 2, fd);
	while (i < LIGHT_PARAM)
	{
		if (used & g_light_save[i].used)
			(*g_light_save[i].p_prop)((void*)((uint64_t)lum
				+ g_light_save[i].offset),
				g_light_save[i].type, (char*)g_light_save[i].text, fd);
		i++;
	}
	rt_put_end_tag((char *)g_scene_lum_save[lum->type].text, 2, fd);
}

static void		this_save_camera(t_cam *cam, int fd)
{
	int		i;

	i = 0;
	rt_put_start_tag_name((char *)CAMERA_NAME,
								cam->name, 2, fd);
	while (i < CAM_PARAM)
	{
		(*g_cam_save[i].p_prop)((void*)((uint64_t)cam
			+ g_cam_save[i].offset),
			g_cam_save[i].type, (char*)g_cam_save[i].text, fd);
		i++;
	}
	rt_put_end_tag((char *)CAMERA_NAME, 2, fd);
}

static void		this_save_scene_fd(t_scene *scene, int fd)
{
	size_t		cur_obj;
	size_t		cur_lum;
	size_t		cur_cam;

	rt_put_start_tag_name("scene", scene->name, 1, fd);
	cur_obj = 0;
	while (cur_obj < scene->num_obj)
	{
		this_save_object_fd(&scene->object[cur_obj],
			g_scene_obj_save[scene->object[cur_obj].type].used, fd);
		cur_obj++;
	}
	cur_lum = 0;
	while (cur_lum < scene->num_lum)
	{
		this_save_light(&scene->light[cur_lum],
			g_scene_lum_save[scene->light[cur_lum].type].used, fd);
		cur_lum++;
	}
	this_save_light(&scene->ambient,
		g_scene_lum_save[scene->ambient.type].used, fd);
	cur_cam = 0;
	while (cur_cam < scene->num_cam)
		this_save_camera(&scene->cam[cur_cam++], fd);
	rt_put_end_tag("scene", 1, fd);
}

int				rt_save_xml(t_sdl *win, char *filename)
{
	int			fd;
	size_t		cur_scn;

	unlink(filename);
	if ((fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
		rt_error(ERROR_OPEN_SAVE, filename, 0, 0);
	rt_put_start_tag_name("folder", filename, 0, fd);
	cur_scn = 0;
	while (cur_scn < win->stock.num_scn)
		this_save_scene_fd(&win->stock.scene[cur_scn++], fd);
	rt_put_end_tag("folder", 0, fd);
	close(fd);
	return (0);
}
