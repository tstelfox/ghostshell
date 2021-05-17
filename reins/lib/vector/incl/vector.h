/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:44:25 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/13 20:38:02 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <sys/types.h>

typedef struct s_vec
{
	char			*store;
	size_t			type_size;
	size_t			capacity;
	size_t			size;
}					t_vec;

int					vec_add(t_vec *vector, void *buffer, size_t n);
int					vec_insert(t_vec *vector, void *buffer, \
						size_t index, size_t n);
int					vec_new(t_vec *vector, size_t type_size);
int					vec_destroy(t_vec *vector, void (*del)(void *));
void				*vec_getref(t_vec *vector, size_t index);
int					vec_del(t_vec *vector, size_t index, size_t n);

#endif
