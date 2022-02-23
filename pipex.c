/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:32:18 by jtaravel          #+#    #+#             */
/*   Updated: 2022/02/23 14:55:03 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

char	*ft_recup_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	**all_path;
	char	*path_test;

	i = 0;
	while (!ft_strfind(env[i], "PATH=", 5))
		i++;
	all_path = ft_split(env[i] + 5, ':');
	i = 0;
	while (all_path[i])
	{
		path_test = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(path_test, cmd);
		free(path_test);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (all_path[++i])
		free(all_path[i]);
	free(all_path);
	return (0);
}

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
		free(path);
		ft_error(5);
	}
	if (!execve(path, cmd, env))
		ft_error(2);
}

void	ft_pipe_1(char **av, char **env, int pipe_fd[2])
{
	int	file;

	file = open(av[1], O_RDONLY, 0777);
	if (file == -1)
		ft_error(3);
	dup2(file, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	ft_exec_cmd(av[2], env);
}

void	ft_pipe_2(char **av, char **env, int pipe_fd[2])
{
	int	file;

	file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		ft_error(4);
	dup2(file, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	ft_exec_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int	pipe_fd[2];
	int	child;

	if (ac == 5 && ft_check_args(ac, av) && env[0])
	{
		if (open(av[1], O_RDONLY) == -1)
			ft_error(3);
		pipe(pipe_fd);
		child = fork();
		if (child == -1)
			ft_error(1);
		if (child == 0)
			ft_pipe_1(av, env, pipe_fd);
		ft_pipe_2(av, env, pipe_fd);
	}
	else if (ac != 5 || !ft_check_args(ac, av) || !env[0])
		ft_putstr("Args incorrect\n./pipex file1 cmd1 cmd2 file2\n");
}
