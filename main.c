/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/31 15:29:58 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"
#include <termcap.h>

void	print_env(char **str)
{
	while (*str)
	{
		printf("[%s]\n", *str);
		str++;
	}
}

static int	put_char(int c)
{
	write(1, &c, 1);
	return (1);
}

void	reset_prompt(t_shell **ghost)
{
	signal(SIGINT, ctrl);
	signal(SIGQUIT, SIG_IGN);
	(*ghost)->first_command = TRUE;
	(*ghost)->red_in = -42;
	(*ghost)->red_out = -42;
	ft_putstr_fd("\e[1;34mghostshell$> \e[0m", STDERR_FILENO);
}

void	exec_shell(t_shell **ghost, t_list *head, char *line)
{
	while ((*ghost)->status != INTERNAL_ERROR)
	{
		reset_prompt(ghost);
		line = read_line(ghost);
		(*ghost)->tokens = lexer(ghost, line, " ><|;");
		head = (*ghost)->tokens;
		free(line);
		while ((*ghost)->tokens)
		{
			(*ghost)->commands = parser(ghost);
			if (!(*ghost)->commands)
				break ;
			if ((*ghost)->commands && !(*ghost)->error)
				if (shell_exec((*ghost)->commands, ghost) == 0)
					return ;
			(*ghost)->error = 0;
		}
		(*ghost)->tokens = head;
		tputs(tgetstr("ke", NULL), 1, &put_char);
		restart_shell(ghost);
	}
	reins_destroy((*ghost)->reins);
}

int	main(int argc, char *args[], char *envp[])
{
	t_shell	*ghost;
	t_list	*head;
	char	*line;

	head = NULL;
	line = NULL;
	(void)argc;
	(void)args;
	ghost = init_shell(envp);
	if (!ghost)
		error_handler(&ghost, INIT_ERROR, "failed to initialize structs", NULL);
	init_reins(&ghost);
	exec_shell(&ghost, head, line);
	return (0);
}
