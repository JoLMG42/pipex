/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 09:51:11 by jtaravel          #+#    #+#             */
/*   Updated: 2022/02/23 15:07:39 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex_bonus.h"

void	ft_exec_cmd(char *av, char **env)
{
	int		i;
	char	**cmd;
	char	*path;

	i = 0;
	cmd = ft_split(av, ' ');
	path = ft_recup_path(cmd[0], env);
	if (!path)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		ft_error(5);
	}
	if (!execve(path, cmd, env))
	{
		free(path);
		ft_error(2);
	}
}

int	ft_read_file(char *av, int i)
{
	int	fd;

	if (i == 0)
		fd = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		fd = open(av, O_RDONLY, 0777);
	if (fd == -1)
		ft_error(6);
	return (fd);
}

void	ft_pipe(char *av, char **env)
{
	int	child;
	int	pipe_fd[2];

	pipe(pipe_fd);
	child = fork();
	if (child == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_exec_cmd(av, env);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		waitpid(child, NULL, 0);
	}
}

void	ft_here_doc(char *av, int ac)
{
	int		heredoc;
	int		pipe_fd[2];
	char	*cpy;

	(void)ac;
	pipe(pipe_fd);
	heredoc = fork();
	if (heredoc == 0)
	{
		close(pipe_fd[0]);
		while (get_next_line(&cpy))
		{
			if (ft_strncmp(cpy, av, ft_strlen(av)) == 0)
				ft_error(2);
			ft_putstr_fd(cpy, pipe_fd[1]);
		}
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	file_1;
	int	file_2;

	if (ac >= 5 && env[0])
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			i = 3;
			file_2 = ft_read_file(av[ac - 1], 0);
			ft_here_doc(av[2], ac);
		}
		else
		{
			i = 2;
			file_1 = ft_read_file(av[1], 2);
			file_2 = ft_read_file(av[ac - 1], 1);
			dup2(file_1, STDIN_FILENO);
		}
		while (i < ac - 2)
			ft_pipe(av[i++], env);
		dup2(file_2, STDOUT_FILENO);
		ft_exec_cmd(av[ac - 2], env);
	}
	ft_error_arg();
}
