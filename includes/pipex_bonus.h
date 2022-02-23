/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:56:25 by jtaravel          #+#    #+#             */
/*   Updated: 2022/02/23 12:52:39 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

void	ft_putstr(char *str);
void	ft_error(int i);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strfind(char *big, char *little, size_t len);
size_t	ft_strlen(char *str);
char	*ft_strfind(char *big, char *little, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_check_args(int ac, char **av);
void	ft_putstr_fd(char *str, int fd);
int		get_next_line(char **line);
char	*ft_recup_path(char *cmd, char **env);
void	ft_here_doc(char *av, int ac);
void	ft_pipe(char *av, char **env);
void	ft_error_arg(void);

#endif
