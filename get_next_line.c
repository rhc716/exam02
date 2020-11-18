/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 23:26:29 by hroh              #+#    #+#             */
/*   Updated: 2020/11/18 15:33:48 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t s;

	s = 0;
	while (str[s] != 0)
		s++;
	return (s);
}

void	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t s;
	size_t src_len;

	s = 0;
	if (!dest || !src || size == 0)
		return ;
	while (src[s] && s < size - 1)
	{
		dest[s] = src[s];
		s++;
	}
	dest[s] = 0;
}

char	*ft_strdup(const char *str)
{
	char	*re;
	size_t	len;

	len = ft_strlen(str);
	if (!(re = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(re, str, len + 1);
	return (re);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*re;
	size_t	s1_len;
	size_t	s2_len;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup(s2) : ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(re = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	ft_strlcpy(re, s1, s1_len + 1);
	free(s1);
	ft_strlcpy(re + s1_len, s2, s2_len + 1);
	return (re);
}

static void	assign_next_line(char **appended, char **line, int n_pos)
{
	char	*temp;

	(*appended)[n_pos] = 0;
	*line = ft_strdup(*appended);
	if (ft_strlen(*appended + n_pos + 1) == 0)
	{
		free(*appended);
		*appended = 0;
	}
	else
	{
		temp = ft_strdup(*appended + n_pos + 1);
		free(*appended);
		*appended = temp;
	}
}

static int	check_newline(char *appended)
{
	int i;

	i = 0;
	while (appended[i])
	{
		if (appended[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int			get_next_line(char **line)
{
	static char		*appended;
	char			buf[128];
	int				read_i;
	int				n_pos;

	while ((read_i = read(0, buf, 127)) > 0)
	{
		buf[read_i] = 0;
		appended = ft_strjoin(appended, buf);
		if ((n_pos = check_newline(appended)) >= 0)
		{
			assign_next_line(&appended, line, n_pos);
			return (1);
		}
	}
	if (read_i < 0)
		return (-1);
	if (appended && (n_pos = check_newline(appended)) >= 0)
	{
		assign_next_line(&appended, line, n_pos);
		return (1);
	}
	else if (appended)
	{
		line = &appended;
		appended = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

#include <stdio.h>
int main(void)
{
	int		r;
	char	*line;

	line = NULL;
	while ((r = get_next_line(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
}
