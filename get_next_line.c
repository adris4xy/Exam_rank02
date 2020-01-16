/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:31:46 by aortega-          #+#    #+#             */
/*   Updated: 2020/01/16 17:49:09 by aortega-         ###   ########.fr       */
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

void	ft_bzero(void *s, size_t n)
{
	unsigned char *ptr;

	ptr = (unsigned char*)s;
	while (n-- > 0)
		*(ptr++) = 0;
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

int					ft_putline(char *s, char **line)
{
	int		size;
	char	*tmp;

	size = 0;
	while (s[size] != '\n')
		size++;
	*line = ft_substr(s, 0, size);
	tmp = ft_strdup(&s[size + 1]);
	free(s);
	s = tmp;
	return (1);
}

int					output(int ret, char *s, char **line)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (s == NULL || s[0] == '\0'))
	{
		*line = ft_strdup("");
		ft_strdel(&s);
		return (0);
	}
	else if (ft_strchr(s, '\n'))
		return (ft_putline(s, line));
	else
	{
		*line = ft_strdup(s);
		ft_strdel(&s);
		return (0);
	}
}

int					get_next_line(char **line)
{
	int				ret;
	static char		*s;
	char			*buff;
	char			*tmp;

	if (BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if (!(buff = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while ((ret = read(0, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (s == NULL)
			s = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(s, buff);
			free(s);
			s = tmp;
		}
		if (ft_strchr(s, '\n'))
			break ;
	}
	free(buff);
	return (output(ret, s, line));
}

int main(int argc, char **argv)
{
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
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("-----------\nEnd of stdin\n");
		free(buff);
	}
	return (0);
}
/*
Assignment name  : get_next_line
Expected files   : get_next_line.c get_next_line.h
Allowed functions: read, free, malloc
--------------------------------------------------------------------------------

Escriba una función que almacene en el parámetro "line" una línea leída desde el "file descriptor" 0.

El prototipo de la función será el siguiente: int get_next_line(char **line);

Su función no puede provocar fugas de memoria (memory leak).

Lo que llamamos una "línea leída" es una sucesión de 0 a n caracteres que termina con un '\n' (código ASCII 0x0a) o un Final De Archivo (EOF).

La cadena de caracteres almacenada en "line" no debe contener '\n'.

El parámetro de la función es la dirección de un puntero a carácter y servirá para guardar la línea leída.

El valor de retorno será 1, 0 o -1 en función de si se ha leído una línea, se ha terminado de leer (lo que significa que read ha devuelto 0) o ha ocurrido algún error, respectivamente.

Si su función llega al "final del archivo" (EOF), debe almacenar el "buffer" actual en "line". Si el "buffer" está vacío, "line" tendría que apuntar hacia una cadena de caracteres vacía.

Si su función llega al "final del archivo" (EOF), salvo el último "buffer" almacenado en "line", no debería conservar ningún espacio de memoria reservado por malloc.

El contenido de "line" tendrá que poder ser liberado con la función free.

Una llamada en bucle de get_next_line le permitirá leer la totalidad del texto disponible a través de un "file descriptor", línea por línea. Todo esto, independientemente del tamaño del texto o de una de sus líneas.

Asegúrese de que su función funciona correctamente si hace la lectura desde un archivo, la entrada estándar, una redirección, etc.

Tenga en cuenta que, entre 2 llamadas a su función get_next_line, no se realizará ninguna otra llamada al "file descriptor".

Por último, el comportamiento de su get_next_line será indeterminado si lo utilizamos sobre un contenido binario.

Le animamos a que utilice el archivo test.sh para probar su get_next_line.
*/