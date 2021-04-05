/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexerv2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/25 19:28:05 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/26 00:05:17 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	add_token(t_shell **ghost, char *input, int start, int len)
{
	char	*result;
	t_list	*new;
	result = ft_substr(input, start, len);
	new = ft_lstnew(ft_strdup(result));
	if (!new)
		error_handler(ghost, INTERNAL_ERROR, "something went wrong with tokenizing", NULL);
	ft_lstadd_back(&(*ghost)->tokens, new);
	free(result);
}

int		handle_colon(t_shell **ghost, char input, int i)
{
	char *line;
	int len;

	if (input != ';')
		return (0);
	len = ft_strlen((*ghost)->line);
	if (len > i)
	{
		line = ft_substr((*ghost)->line, i, len - i);
		free((*ghost)->line);
		(*ghost)->line = line;
	}
	else
		(*ghost)->status = FINISHED;
	return (1);
}

int		handle_quote(t_shell **ghost, char *input, int current)
{
	int i;
	char type;

	i = current + 1;
	type = input[current];
	while (input[i])
	{
		if (input[i] == type)
			return (i);
		i++;
	}
	error_handler(ghost, NO_MULTI_LINE, "no multiline", NULL);
	return (i);
}

int		handle_seperator(t_shell **ghost, char *input, int start, int i)
{
	int len;
	
	len = i - start;
	if (i == start) // if nothing before seperator
		len = 1;
	if (input[start] != ' ') // ignore spaces
		add_token(ghost, input, start, len); // if input before separator or esparator, tokenize it
	if (i != start && input[i] != ' ') // if input before separator, tokenize seperator
		add_token(ghost, input, i, 1);
	return (i);
}

void	lexer(t_shell **ghost)
{
	int i;
	int start;
	char *input;

	i = 0;
	start = 0;
	if (!(*ghost)->line)
		return ;
	input = (*ghost)->line;
	while (input[i])
	{
		if (handle_colon(ghost, input[i], i))
			return;
		if (ft_strchr(" ><|", input[i]))
		{
			if (input[i] == '>' && input[i + 1] == '>')
				i = handle_seperator(ghost, input, start, i);
			else
				i = handle_seperator(ghost, input, start, i);
			start = i + 1;
		}
		if (input[i] == '\"' || input[i] == '\'')
			i = handle_quote(ghost, input, i);
		i++;
	}
	if (i != start)
		add_token(ghost, input, start, i - start);
	(*ghost)->status = FINISHED;
}