/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:28:10 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/01 19:26:01 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	print_data(void *data)
{
	char *str = data;
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("]", STDOUT_FILENO);
}

void	add_token(t_list **ptr, char *input, int start, int len)
{
	char	*result;
	t_list	*new;
	result = ft_substr(input, start, len);
	new = ft_lstnew(ft_strdup(result));
	if (!new)
		error_handler("something went wrong with tokenizing");
	ft_lstadd_back(ptr, new);
	free(result);
}

int		handle_quote(char *input, int current)
{
	int i;
	char type;

	i = current + 1;
	type = input[current];
	while (input[i])
	{
		if (input[i] == type)
			return (i + 1);
		i++;
	}
	error_handler("no multiline");
	return (i);
}

int		handle_seperator(t_list **ptr, char *input, int start, int i)
{
	int len;
	
	len = i - start;
	if (i == start) // if nothing before seperator
		len = 1;
	if (input[start] != ' ')
		add_token(ptr, input, start, len); // if input before separator or esparator, tokenize it
	if (i != start && input[i] != ' ') // if input before separator, tokenize seperator
		add_token(ptr, input, i, 1);
	return (i);
}

t_list	*split_literal_tokens(char *input)
{
	t_list *ptr = NULL;

	int i;
	int start;
	int len;
	
	i = 0;
	start = 0;
	len = 0;
	while (input[i])
	{
		if (ft_strchr(" ><|", input[i]))
		{
			i = handle_seperator(&ptr, input, start, i);
			start = i + 1;
		}
		if (input[i] == '\"' || input[i] == '\'')
			i = handle_quote(input, i);
		i++;
	}
	if (i != start)
	{
		len = i - start;
		add_token(&ptr, input, start, len);
	}
	return (ptr);
}

t_list	*lexer(char *input)
{
	t_list *literal_tokens;

	literal_tokens = split_literal_tokens(input);
	ft_lstiter(literal_tokens, print_data);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (literal_tokens);
}
