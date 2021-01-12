/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 05:07:30 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/20 02:09:56 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_thread
{
	int				fd;
	char			*buf;
	struct s_thread *next;
}					t_thread;

t_thread			*search_thread(int fd, t_thread **threads);
t_thread			*push_thread(int fd, t_thread **threads);
void				delete_element(t_thread **threads, t_thread *current);
void				reallocate(t_thread *current, char *arg1, char *arg2);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				clean_buffer(char *buf);
char				*ft_strjoin(char *s1, char *s2);
int					get_next_line(int fd, char **line);

#endif
