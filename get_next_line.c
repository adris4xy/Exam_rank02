  
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:09:45 by aortega-          #+#    #+#             */
/*   Updated: 2019/11/26 18:19:42 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char *ptr;

	ptr = (unsigned char*)s;
	while (n-- > 0)
		*(ptr++) = 0;
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = ft_strlen(s);
	str = (char*)malloc(sizeof(*str) * size + 1);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	str[size] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (s1 && s2)
	{
		str = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
		if (str == NULL)
			return (NULL);
		while (*s1)
			str[i++] = *s1++;
		while (*s2)
			str[i++] = *s2++;
		str[i] = '\0';
		return (str);
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (s)
	{
		if (!(str = malloc(((int)len + 1) * sizeof(char))))
			return (NULL);
		ft_bzero(str, len);
		if (start <= ft_strlen(s))
		{
			while (i < len && s[i])
			{
				str[i] = s[i + start];
				i++;
			}
		}
		if (i < len + 1)
			str[i] = '\0';
		return (str);
	}
	return (0);
}

static char			*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

static void			ft_strdel(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

int					ft_putline(char **s, char **line)
{
	int		size;
	char	*tmp;

	size = 0;
	while (s[0][size] != '\n')
		size++;
	*line = ft_substr(s[0], 0, size);
	tmp = ft_strdup(&s[0][size + 1]);
	free(s[0]);
	s[0] = tmp;
	return (1);
}

int					output(int ret, char **s, char **line)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (s[0] == NULL || s[0][0] == '\0'))
	{
		*line = ft_strdup("");
		ft_strdel(&s[0]);
		return (0);
	}
	else if (ft_strchr(s[0], '\n'))
		return (ft_putline(s, line));
	else
	{
		*line = ft_strdup(s[0]);
		ft_strdel(&s[0]);
		return (0);
	}
}

int					get_next_line(char **line)
{
	int				ret;
	static char		*s[1];
	char			*buff;
	char			*tmp;

	if (BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if (!(buff = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while ((ret = read(0, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (s[0] == NULL)
			s[0] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(s[0], buff);
			free(s[0]);
			s[0] = tmp;
		}
		if (ft_strchr(s[0], '\n'))
			break ;
	}
	free(buff);
	return (output(ret, s, line));
}

int main(int argc, char **argv)
{
	int fd;
	int ret;
	int line;
	char *buff;
	int 	i;

	line = 0;
	if (argc > 1)
	{
		i = 0;
		while (++i < argc)
		{
			fd = open(argv[i], O_RDONLY);
			printf("%d- archivo: %s\n",i, argv[i]);
			while ((ret = get_next_line(&buff)) > 0)
			{
				printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
				free(buff);
			}
			printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
			if (ret == -1)
				printf("-----------\nError\n");
			else if (ret == 0)
				printf("-----------\nEnd of file\n");
			free(buff);
		}
	}
	if (argc == 1)
	{
		while ((ret = get_next_line(&buff)) > 0)
			printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
		printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("-----------\nEnd of stdin\n");
		free(buff);
		close(fd);
	}
	return (0);
}
