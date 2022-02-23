/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:33:24 by jtaravel          #+#    #+#             */
/*   Updated: 2022/02/23 15:04:09 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(int i)
{
	if (i == 1)
		ft_putstr("Error\nFork Error\n");
	else if (i == 2)
		ft_putstr("Error\nExec Error\n");
	else if (i == 3)
		ft_putstr("Error\nFile 1 Error\n");
	else if (i == 4)
		ft_putstr("Error\nFile 2 Error\n");
	else if (i == 5)
		perror("Error\nCommand not found or ");
	else if (i == 6)
		ft_putstr("Error\nFile 1 or 2\n");
	exit(127);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5)
		return (0);
	while (i < ac)
	{
		if (ft_strlen(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_error_arg(void)
{
	ft_putstr("Error\n./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n");
	ft_putstr("./pipex here_doc LIMITER cmd cmd1 file\n");
}
