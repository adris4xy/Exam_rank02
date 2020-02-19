/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:49:13 by egarcia-          #+#    #+#             */
/*   Updated: 2020/02/19 16:52:14 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *s;

	if (!(s = malloc(sizeof(char)* ft_strlen(s1) + ft_strlen(s2)+ 1)))
		return(NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s[i] = s2[j];
		i++;
		j++;
	}
	s[i] = 0;
	return (s);
}

char	*ft_strchr(char *s)
{
	while (*s && *s != '\n')
		s++;
	if (*s == '\n')
		return(s);
	return (NULL);
}

char	*ft_strdup(char *s)
{
	int i = 0;
	char	*str;

	if (!(str = malloc(sizeof(char) * ft_strlen(s)+ 1)))
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}


int		get_next_line(char **line)
{
	static char *stc;
	char		*tmp;
	int			len;
	char		buff[512];

	if (!line)
		return (-1);
	if (stc == NULL)
		stc = ft_strdup("");
	while (!(ft_strchr(stc)))
	{
		len = read(0, buff, 511);
		if (len < 0)
			return (-1);
		if (!len)
			break;
		buff[len] = 0;
		tmp = ft_strjoin(stc, buff);
		//printf("%s\n", tmp);
		free(stc);
		stc = tmp;
	}
	if ((tmp = ft_strchr(stc)))
	{
		*tmp = 0;
		*line = ft_strdup(stc);
		tmp = ft_strdup(++tmp);
		free(stc);
		stc = tmp;
		return (1);
	}
	else
	{
		*line = ft_strdup(stc);
		free(stc);
		stc = NULL;
		return (0);
	}
	
}