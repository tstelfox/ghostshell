/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exec.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:33:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/02/16 13:33:57 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	*g_builtin[4] = {
		"echo",
		"cd",
		"pwd",
		"exit"
		// "export"
		// "unset",
		// "env",
};

int		(*g_builtin_f[4])(t_list *tokens) = {
		&run_echo,
		&run_cd,
		&run_pwd,
		&run_exit
};

int	run_echo(t_list *tokens)
{
	// Some check to see if there's a Pipe or a redirection or some shiz
	if (tokens->next == NULL)
		return (0);
	// if (ft_strcmp(tokens->next->content, "-n") == 0)
		//Don't print the newline
	// Depending on flag Do the redirecting shit
	ft_putstr_fd(tokens->next->content, STDOUT_FILENO); // Simplest case
	return (1);
}

int	run_cd(t_list *tokens)
{
	tokens = tokens->next; //Spaces are list items so need to be skipped
	tokens = tokens->next;
	// t_env	yo = *g_env->content;
	ft_putstr_fd(g_env.content->content, STDOUT_FILENO);
	if (tokens->content == NULL)
		return (0);
	//To deal with ~ need to use the env variable
	else if (ft_strcmp(tokens->content, "~") == 0)
	{
		// printf("chdir returns %d\n", chdir(tokens->content));
		if (chdir(g_env->content) != 0)
			strerror(errno);
	}
	else
	{
		// printf("chdir returns %d\n", chdir(tokens->content));
		if (chdir(tokens->content) != 0)
			strerror(errno);
		// ft_putstr_fd("In here at all lads\n", STDOUT_FILENO);
	}
	return (1);
}

int	run_pwd(t_list *tokens)
{
	char	buff[1024];

	(void)tokens;
	// if (tokens[1] != NULL)
	// {
	// 	printf("pwd doesn't accept arguments");
	// 	return (0);
	// }
	if (getcwd(buff, sizeof(buff)) == NULL)
		strerror(errno);
	else
	{
		ft_putstr_fd(buff, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (1);
	}
	return (0);
}

int	run_exit(t_list *tokens)
{
	(void)tokens;
	ft_putstr_fd("Please not here yet", STDOUT_FILENO);
	exit(1);
}

int	builtin_exec(t_list *tokens)
{
	int	i;

	i = 0;
	if (tokens->content == NULL)
		return (0);
	while (i < 7)
	{
		if (ft_strcmp(tokens->content, g_builtin[i]) == 0)
			return (*g_builtin_f[i])(tokens); // Need to integrate the parsing shit into this process
		i++;
	}
	return (1);
}
