/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 05:13:30 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/20 02:19:18 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_thread	*search_thread(int fd, t_thread **threads)
{
	t_thread *tmp;

	tmp = *threads;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	return (push_thread(fd, threads));
}

t_thread	*push_thread(int fd, t_thread **threads)
{
	t_thread *new;
	t_thread *tmp;

	if (!(new = (t_thread *)malloc(sizeof(t_thread))))
		return (NULL);
	new->fd = fd;
	new->buf = NULL;
	new->next = NULL;
	tmp = *threads;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*threads = new;
	return (new);
}

static	int	find_new_line(char *str, char **next_line, int count)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			*next_line = &str[i + 1];
			return (1);
		}
		i++;
	}
	if (count == 0)
	{
		*next_line = NULL;
		return (1);
	}
	*next_line = str;
	return (0);
}

static int	get_line(t_thread *current, char **line, char *buf)
{
	char	*next_line;
	int		count;
	int		res;

	count = 1;
	while (count > 0)
	{
		clean_buffer(buf);
		count = read(current->fd, buf, BUFFER_SIZE);
		reallocate(current, current->buf, buf);
		if ((res = find_new_line(current->buf, &next_line, count)))
			*line = ft_strjoin(NULL, current->buf);
		reallocate(current, NULL, next_line);
		if (!next_line)
			return (0);
		if (res == 1)
			return (1);
	}
	return (count);
}

int			get_next_line(int fd, char **line)
{
	static t_thread		*threads;
	t_thread			*current;
	char				*buf;
	int					code;

	current = search_thread(fd, &threads);
	if (fd < 0 || BUFFER_SIZE <= 0 || !current || !line)
		return (-1);
	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	buf[BUFFER_SIZE] = '\0';
	code = get_line(current, line, buf);
	if (code == -1 || code == 0)
		delete_element(&threads, current);
	free(buf);
	return (code);
}
