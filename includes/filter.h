/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeckert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:40:16 by mbeckert          #+#    #+#             */
/*   Updated: 2018/09/15 18:40:18 by mbeckert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTER_H
# define FILTER_H

# define FILTER_MATRIX (9)

enum				e_kernel
{
	K_UP_LEFT,
	K_UP_MID,
	K_UP_RIGHT,
	K_MID_LEFT,
	K_MID_MID,
	K_MID_RIGHT,
	K_DOWN_LEFT,
	K_DOWN_MID,
	K_DOWN_RIGHT,
	K_ALL
};

typedef struct		s_filter
{
	const int		matrix[3][3];
	const int		div;
}					t_filter;

typedef struct		s_pkernel
{
	int			x;
	int			y;
	int			type;
}					t_pkernel;

static const t_pkernel g_get_kernel[9] = {
(t_pkernel){.y = 0, .x = 0, .type = K_UP_LEFT},
(t_pkernel){.y = 0, .x = 1, .type = K_UP_MID},
(t_pkernel){.y = 0, .x = 2, .type = K_UP_RIGHT},
(t_pkernel){.y = 1, .x = 0, .type = K_MID_LEFT},
(t_pkernel){.y = 1, .x = 1, .type = K_MID_MID},
(t_pkernel){.y = 1, .x = 2, .type = K_MID_RIGHT},
(t_pkernel){.y = 2, .x = 0, .type = K_DOWN_LEFT},
(t_pkernel){.y = 2, .x = 1, .type = K_DOWN_MID},
(t_pkernel){.y = 2, .x = 2, .type = K_DOWN_RIGHT},
};

enum				e_filter
{
	F_EDGE_LOW,
	F_EDGE_MID,
	F_EDGE_HARD,
	F_SHARPEN,
	F_BLUR_BOX,
	F_BLUR_GAUS,
	F_EDGE_LEFT,
	F_EMBOSSING,
	F_ANTIALIAZ,
	F_ALL,
	F_BLACK_WHITE,
	F_SEPIA,
	F_CARTOON,
};

static const t_filter g_filter_matrix[F_ALL] = {
	(t_filter){.matrix = {
			{1, 0, -1},
			{0, 0, 0},
			{-1, 0, 1}}, .div = 1},
	(t_filter){.matrix = {
			{0, 1, 0},
			{1, -4, 1},
			{0, 1, 0}}, .div = 1},
	(t_filter){.matrix = {
			{-1, -1, -1},
			{-1, 8, -1},
			{-1, -1, -1}}, .div = 1},
	(t_filter){.matrix = {
			{0, -1, 0},
			{-1, 5, -1},
			{0, -1, 0}}, .div = 1},
	(t_filter){.matrix = {
			{1, 1, 1},
			{1, 1, 1},
			{1, 1, 1}}, .div = 9},
	(t_filter){.matrix = {
			{1, 2, 1},
			{2, 4, 2},
			{1, 2, 1}}, .div = 16},
	(t_filter){.matrix = {
			{0, 0, 0},
			{-1, 1, 0},
			{0, 0, 0}}, .div = 1},
	(t_filter){.matrix = {
			{-2, -1, 0},
			{-1, 1, 1},
			{0, 1, 2}}, .div = 1},
	(t_filter){.matrix = {
			{2, 1, 2},
			{1, 8, 1},
			{2, 1, 2}}, .div = 15},
};

typedef struct		s_norline
{
	int fr;
	int fg;
	int fb;
	int x;
	int y;
}					t_norline;

#endif
