/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeorgia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 17:35:18 by lgeorgia          #+#    #+#             */
/*   Updated: 2019/04/22 17:35:18 by lgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 4
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "./libft/libft.h"

int		get_next_line(const int fd, char **line);

#endif
