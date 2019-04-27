/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeorgia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:53:52 by lgeorgia          #+#    #+#             */
/*   Updated: 2019/04/27 15:53:52 by lgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
# define BUFF_SIZE 1

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
char	*ft_strnew(size_t size)
{
	char	*s;
	size_t	i;

	i = size;
	if (i + 1 == 0)
		return (NULL);
	if (!(s = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i > 0)
	{
		s[i] = '\0';
		i--;
	}
	s[0] = '\0';
	return (s);
}
char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int		i;
	char				*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	return (str);
}
char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		str[i] = s2[k];
		i++;
		k++;
	}
	return (str);
}
int		ft_end(char *buf)
{
	int i;

	i = 0;
	while (i < BUFF_SIZE)
	{
		if (buf[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		ft_howmuchspaces(char *buf)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

int		ft_strchrint(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if ((s[i] == (char)c) && (char)c == '\0')
		return (i);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	char 		buf[BUFF_SIZE + 1];
	int			file;
	static int	i;
	char		*str;
	static char *memory;
	if (fd < 0 || !(*line) || BUFF_SIZE < 1)
		return (-1);
	str = ft_strnew(0);
	if (i == 0)
		memory = ft_strnew(0);
	if (ft_strlen(memory) != 0 && ft_howmuchspaces(memory) > 0 && i > 0)
	{
		str = ft_strsub(memory, 0, ft_strchrint(memory, '\n'));
		memory = ft_strsub(memory, ft_strchrint(memory, '\n') + 1, ft_strlen(memory) - ft_strchrint(memory, '\n') + 1);
		*line = ft_strsub(str, 0, ft_strlen(str));
		return (1);
	}
	else
	{
		str = ft_strjoin(str, memory);
		memory = ft_strnew(0);
	}
	i++;
	while ((file = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[file] = '\0';
		if (ft_howmuchspaces(buf) > 0)
		{
			str = ft_strjoin(str, ft_strsub(buf, 0, ft_strchrint(buf, '\n')));
			memory = ft_strsub(buf, ft_strchrint(buf, '\n') + 1, ft_strlen(buf) - ft_strchrint(buf, '\n') + 1);
			*line = ft_strsub(str, 0, ft_strlen(str));
			return (file == 0 ? 0 : 1);
		}
		str = ft_strjoin(str, buf);
	}
	*line = ft_strsub(str, 0, ft_strlen(str));
	return (0);
}

int        main(int argc, char **argv)
{
	int        fd;
	char    *line;
	int        i;
	int        ret;

	i = 0;
	(void)argc;
	fd = open((argv[1]), O_RDONLY);
	while (i < 3)
	{
		line = (char *)malloc(sizeof(*line)* 1);
		printf("%d\n",get_next_line(fd, &line));
		printf("|%s|\n", line);
		i++;
	}
}