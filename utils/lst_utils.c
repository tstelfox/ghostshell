/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 13:37:13 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/17 17:55:24 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	free_list(t_list **lst, void (*del)(void *))
{
	ft_lstclear(lst, del);
	free(*lst);
}

void	*copy_data(void	*data)
{
	char	*str;

	str = data;
	return (ft_strdup(str));
}

int	ft_lstredir(t_list *lst, int (*f)(void *))
{
	t_list	*temp;
	int		fd;

	if (!lst)
		return (-1);
	temp = lst;
	while (temp)
	{
		fd = f(temp->content);
		if (temp->next)
			close(fd);
		temp = temp->next;
	}
	return (fd);
}

char	**list_to_arr(t_list *tokens)
{
	t_list	*temp;
	char	**ret;
	int		i;

	if (!tokens)
		return (NULL);
	temp = tokens;
	ret = (char **)malloc(sizeof(char *) * ft_lstsize(tokens) + 1);
	if (!ret)
		error_handler(NULL, INTERNAL_ERROR, "malloc fail", NULL);
	i = 0;
	while (temp)
	{
		ret[i] = ft_strdup(temp->content);
		temp = temp->next;
		i++;
	}
	ret[i] = 0;
	return (ret);
}
