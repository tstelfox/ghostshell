/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prog_launch.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:29:22 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/09 16:03:23 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	**get_path(t_cmd *cmd, t_shell *ghost)
{
	int i;
	int k;
	char **path;
	char *command;

	i = 0;
	k = 0;
	command = ft_strjoin("/", cmd->type);
	while (ghost->env[i])
	{
		if (ft_strnstr(ghost->env[i], "PATH", 4))
		{
			path = ft_split(&ghost->env[i][5], ':');
			while (path[k])
			{
				path[k] = ft_strjoin(path[k], command);
				k++;
			}
			return(path);
		}
		i++;
	}
	return (0);
}

int	prog_launch(t_cmd *cmd, t_shell *ghost)
{
	pid_t	pid;
	char **path;
	char **args;
	int k = 0;

	path = get_path(cmd, ghost);
	if (path == NULL)
		cmd_notfound(cmd);
	int i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd->type, g_builtin[i]) == 0)
			return(1);
		i++;
	}
	if (cmd->args)
	{
		t_list	*fucker = ft_lstnew(cmd->type);
		ft_lstadd_front(&cmd->args, fucker);
		args = list_to_arr(cmd->args);
	}
	else
	{
		args = (char**)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(cmd->type);
		args[1] = NULL;
	}
	pid = fork();
	if (pid == 0) //child process
	{
		while (path[k])
		{
			if (execve(path[k], args, NULL) == -1)
			{
				(void)pid;
				// printf("%s: errno %d\n", strerror(errno), errno);
			}
			k++;
		}
		cmd_notfound(cmd);
		exit(0);
	}
	else if (pid < 0)
	{
		strerror(errno);
	}
	else
	{
		waitpid(pid, &ghost->status, 0);
	}
	return (1);
}
