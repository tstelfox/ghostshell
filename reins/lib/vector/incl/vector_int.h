/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_int.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tishj <tishj@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/06 19:32:37 by tishj         #+#    #+#                 */
/*   Updated: 2021/03/11 20:33:23 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_INT_H
# define VECTOR_INT_H

# include "vector.h"

int					vec_realloc(t_vec *vector, size_t n);
void				*util_memcpy(void *dst, void *src, size_t n);
void				util_memmove(void *dst, void *src, size_t n);

#endif
