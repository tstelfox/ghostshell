/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prog_launch.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:29:22 by tmullan       #+#    #+#                 */
/*   Updated: 2021/04/19 17:09:20 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int		check_dir(t_cmd *cmd, t_shell **ghost)
{
	struct stat buf;

	lstat(cmd->type, &buf);
	if (S_ISDIR(buf.st_mode))
	{
	// 	ft_putstr_fd("ghostshell: ", 1);
	// 	ft_putstr_fd(cmd->type, 1);
	// 	ft_putstr_fd(": is a directory\n", 1);
		(*ghost)->error = DIRECTORY;
		return(0);
	}
	return (1);
}

char	**get_path(t_cmd *cmd, t_shell **ghost)
{
	int i;
	int k;
	char **path;
	char *command;

	i = 0;
	k = 0;
	if (cmd->type[0] == '.' || cmd->type[0] == '/')
	{
		if (!check_dir(cmd, ghost))
			return (0);
	}
	command = ft_strjoin("/", cmd->type);
	while ((*ghost)->env[i])
	{
		if (ft_strnstr((*ghost)->env[i], "PATH", 4))
		{
			path = ft_split(&(*ghost)->env[i][5], ':');
			while (path[k])
			{
				path[k] = ft_strjoinfree(path[k], command);
				k++;
			}
			path = arr_addback(path, cmd->type);
			// free(command);
			return(path);
		}
		i++;
	}
	// free(command);
	return (0);
}

int	prog_launch(t_cmd *cmd, t_shell **ghost)
{
	// pid_t	pid;
	char **path;
	char **args;
	int	w_status;

	int k = 0;
	// w_status = 0;
	path = get_path(cmd, ghost);
	if (path == NULL)
		cmd_notfound(cmd, (*ghost)->error, ghost); // Might need some work
	int i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd->type, g_builtin[i]) == 0)
			return(1);
		i++;
	}
	if (cmd->args)
	{
		t_list	*fucker = ft_lstnew(ft_strdup(cmd->type));
		ft_lstadd_front(&cmd->args, fucker);
		args = list_to_arr(cmd->args);
	}
	else
	{
		args = (char**)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(cmd->type);
		args[1] = NULL;
	}
	(*ghost)->pid = fork();
	if ((*ghost)->pid == 0) //child process
	{
		if (cmd->redirection)
		{
			if (redirect(cmd, ghost) == -1)
				exit(0);
		}
		while (path[k])
		{
			if (execve(path[k], args, NULL) == -1)
			{
				// ft_putnbr_fd(errno, 1);
				(*ghost)->ret_stat = 1;
				// printf("%s: errno %d\n", strerror(errno), errno);
			}
			// free(path[k]);
			k++;
		}
		// free(path);
		cmd_notfound(cmd, 0, ghost);
		exit(0);
	}
	else if ((*ghost)->pid < 0)
	{
		strerror(errno);
	}
	else
	{
		waitpid((*ghost)->pid, &w_status, WUNTRACED);
		// for (int i = 0; path[i]; i++)
		// 	free(path[i]);
		// free(path);
		for (int i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		if (WIFSIGNALED(w_status))
		{
			(*ghost)->ret_stat = WTERMSIG(w_status);
			// ft_putstr_fd("the motherfucking thing is: ", 1);
			// ft_putnbr_fd((*ghost)->ret_stat, 1);
			// ft_putstr_fd("\n", 1);
		}
		if (WIFEXITED(w_status))
		{
			(*ghost)->ret_stat = WEXITSTATUS(w_status);
		}
	}
	return (1);
}
