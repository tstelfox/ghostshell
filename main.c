/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/01 18:00:24 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	exec_shell(void)
{
	char	*input;
	t_list	*lit_input;

	input = NULL;
	while (1) // check for errors
	{
		ft_putstr_fd("ghostshell$> ", STDOUT_FILENO);
		read_line(&input);
		// lexer
		lit_input = lexer(input);
		// parser(lit_input);
		// exec  command
		// check errors
		// ft_putstr_fd("[" , STDOUT_FILENO);
		// ft_putstr_fd(input , STDOUT_FILENO);
		// ft_putstr_fd("]\n" , STDOUT_FILENO);
	}
}

int main(void)
{
	exec_shell();
	return (0);
}