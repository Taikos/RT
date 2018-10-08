/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:12:18 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 19:46:32 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		rt_check_main_tags(t_stock **stock, xmlNodePtr cur,
					char *filename)
{
	while (cur)
	{
		if (!xmlStrcmp(cur->name, (xmlChar*)"scene"))
			(*stock)->num_scn++;
		cur = cur->next;
	}
	if ((*stock)->num_scn == 0)
		rt_error(ERROR_NO_TAG, filename, 0, "<scene>");
}

static void		rt_malloc_obj_lum_cam(t_num *num, t_stock **stock, int cur_scn,
					char *filename)
{
	if (num->amb != 1)
		rt_error(ERROR_NO_TAG, filename, 0,
		"<ambient> (only one ambient per scene)");
	if (!((*stock)->scene[cur_scn].num_cam = num->cam))
		rt_error(ERROR_NO_TAG, filename, 0, "<camera>");
	(*stock)->scene[cur_scn].num_lum = num->lum;
	(*stock)->scene[cur_scn].num_obj = num->obj;
	(*stock)->scene[cur_scn].cur_cam = 0;
	(*stock)->scene[cur_scn].cam =
							(t_cam*)malloc(sizeof(t_cam) * num->cam);
	(*stock)->scene[cur_scn].light =
							(t_light*)malloc(sizeof(t_light) * num->lum);
	(*stock)->scene[cur_scn].object =
							(t_object*)malloc(sizeof(t_object) * num->obj);
}

void			rt_malloc(t_stock **stock, xmlNodePtr cur,
					char *filename)
{
	int			cur_scn;
	t_num		num;

	cur_scn = 0;
	rt_check_main_tags(stock, cur, filename);
	(*stock)->scene = (t_scene*)malloc(sizeof(t_scene) * (*stock)->num_scn);
	while (cur)
	{
		if (!xmlStrcmp(cur->name, (xmlChar*)"scene"))
		{
			rt_check_scene(&num, cur->children, filename);
			rt_malloc_obj_lum_cam(&num, stock, cur_scn, filename);
			cur_scn++;
		}
		cur = cur->next;
	}
}

void			rt_open_xml(xmlDocPtr *doc, xmlNodePtr *cur, char *filename)
{
	(*doc) = xmlParseFile(filename);
	if (!(*doc))
		rt_error(ERROR_UNKNOW_FILE, filename, 0, "must be an valid XML file");
	(*cur) = xmlDocGetRootElement(*doc);
	if (!(*cur) || xmlStrcmp((*cur)->name, (xmlChar*)"folder"))
		rt_error(ERROR_NO_TAG, filename, 0, "<folder>");
	(*cur) = (*cur)->children;
}

int				rt_parser(t_stock *stock, char *filename)
{
	xmlDocPtr	doc;
	xmlNodePtr	cur;

	stock->num_scn = 0;
	rt_open_xml(&doc, &cur, filename);
	rt_malloc(&stock, cur, filename);
	rt_default_scene(stock);
	rt_fill(cur, &stock, filename);
	xmlFreeDoc(doc);
	rt_post_computing(stock, filename);
	return (1);
}
