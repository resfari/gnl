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

#include "get_next_line.h"

static int		ft_howmuchspaces(char *buf)
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

static int		ft_strchrint(char *s, int c)
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
	char		*help;
	char		*sub;

	if (fd < 0 || BUFF_SIZE < 1 || !line || fd >= 1025 || read(fd, buf, 0) < 0)
		return (-1);
	str = ft_strnew(0);
	if (i == 0)
		memory = ft_strnew(0);
	if (ft_strlen(memory) != 0 && ft_howmuchspaces(memory) > 0 && i > 0)
	{
		help = ft_strnew(ft_strlen(memory));
		help = ft_strsub(memory, 0, ft_strlen(memory));
		ft_memdel((void**)&str);
		str = ft_strsub(memory, 0, ft_strchrint(memory, '\n'));
		ft_memdel((void**)&memory);
		memory = ft_strsub(help, ft_strchrint(help, '\n') + 1, ft_strlen(help) - ft_strchrint(help, '\n') + 1);
		*line = ft_strsub(str, 0, ft_strlen(str));
		ft_memdel((void**)&str);
		ft_memdel((void**)&help);
		return (1);
	}
	else
	{
		help = ft_strnew(ft_strlen(str));
		help = ft_strcpy(help, str);
		ft_memdel((void**)&str);
		str = ft_strjoin(help, memory);
		ft_memdel((void**)&memory);
		memory = ft_strnew(0);
		ft_memdel((void**)&help);
	}
	i++;
	while ((file = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[file] = '\0';
		if (ft_howmuchspaces(buf) > 0)
		{
			help = ft_strnew(ft_strlen(str));
			help = ft_strcpy(help, str);
			ft_memdel((void**)&str);
			str = ft_strjoin(help, sub = ft_strsub(buf, 0, ft_strchrint(buf, '\n')));
			ft_memdel((void**)&memory);
			memory = ft_strsub(buf, ft_strchrint(buf, '\n') + 1, ft_strlen(buf) - ft_strchrint(buf, '\n') + 1);
			*line = ft_strsub(str, 0, ft_strlen(str));
			ft_memdel((void**)&str);
			ft_memdel((void**)&sub);
			ft_memdel((void**)&help);
			return (1);
		}
		help = ft_strnew(ft_strlen(str));
		help = ft_strcpy(help, str);
		ft_memdel((void**)&str);
		str = ft_strjoin(help, buf);
		ft_memdel((void**)&help);
	}
	*line = ft_strsub(str, 0, ft_strlen(str));
	ft_memdel((void**)&str);
	return (ft_strlen(*line) > 0 ? 1 : 0);
}
