/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 03:05:37 by aurban            #+#    #+#             */
/*   Updated: 2024/02/28 14:44:34 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// Circular include, but parsing.h is the last one to be included, so it's fine
# include "forward_declaration.h"
# include "miniRt.h"

// Not needed anymore

# define ERROR_PARSE_RGB			1
# define ERROR_PARSE_POS 			2
# define ERROR_PARSE_ROT			3
# define ERROR_PARSE_WRONG_COUNT	4
# define ERROR_DUPLICATE_AMBIANT	5
# define ERROR_DUPLICATE_CAM		6
# define ERROR_PARSE_FOV			7
# define ERROR_PARSE_LINTESITY		8
# define ERROR_PARSE_INT			9
# define ERROR_PARSE_FLOAT			10

/* Parsing : Public*/

int					parse_map(t_glob *glob, char *path);

/* Parsing : Private*/

float				parse_float(char *str);
int					parse_int(char *str);

void				parse_error_msg(int error);
void				parse_rgb(t_rgb *color, char *str_color);
void				parse_position(t_vector *vector, char *str_pos);
void				parse_orientation(t_vector *vector, char *str_rot);

void				parse_ambiant(t_glob *glob, char **line_tokens);
void				parse_camera(t_glob *glob, char **line_tokens);
void				parse_light(t_glob *glob, char **line_tokens);

#endif