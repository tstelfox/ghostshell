/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   norm_made_us_do_it.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 17:10:18 by tmullan       #+#    #+#                 */
/*   Updated: 2021/06/06 18:44:52 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	the_replacing(char *str, char *var, t_shell **ghost, int i)
{
	if (ft_strchr(str, '='))
	{
		free((*ghost)->env[i]);
		(*ghost)->env[i] = ft_strdup(str);
	}
	free(var);
}

void	twenty_five_lines_max_justifyer(t_shell **ghost)
{
	(*ghost)->out = -42;
	(*ghost)->in = -42;
	(*ghost)->red_in = -42;
	(*ghost)->red_out = -42;
	(*ghost)->pipenum = 0;
	(*ghost)->pipepid = NULL;
}

int	redirection_handle(t_shell **ghost, t_cmd *cmd)
{
	if (cmd->redirection)
	{
		if (redirect(cmd, ghost) == -1)
			return (1);
		if (!cmd->type)
		{
			if ((*ghost)->in != -42)
			{
				dup2((*ghost)->in, STDIN_FILENO);
				close((*ghost)->in);
			}
			if ((*ghost)->out != -42)
			{
				dup2((*ghost)->out, STDOUT_FILENO);
				close((*ghost)->out);
			}
			return (1);
		}
	}
	return (0);
}
