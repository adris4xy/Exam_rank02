/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 14:26:21 by aortega-          #+#    #+#             */
/*   Updated: 2020/02/19 14:37:51 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strchr(char *s1)
{
    while (*s1 != '\0')
    {
        if (*s1 == '\n')
            return(1);
        s1++;
    }
    return(0);
}
int ft_strlen(char *s1)
{
    int len = 0;
    while (*s1 != '\0')
    {
        len++;
        s1++;
    }
    return (len);
}
char    *ft_strdup(char *s1)
{
    char *ptr;
    int len = ft_strlen(s1);
    if(!(ptr = malloc(sizeof(char) * len + 1)))
        return(NULL);
    len = 0;
    while (*s1 != '\0')
    {
        ptr[len] = *s1;
        len++;
        s1++;
    }
    ptr[len] = '\0';
    return (ptr);
}
char    *ft_strjoin(char *s1, char *s2)
{
    char *ptr;
    int len = ft_strlen(s1);
    len += ft_strlen(s2);
    if(!(ptr = malloc(sizeof(char) * len + 1)))
        return (NULL);
    len = 0;
    while (*s1 != '\0')
    {
        ptr[len] = *s1;
        len++;
        s1++;
    }
    while (*s2 != '\0')
    {
        ptr[len] = *s2;
        len++;
        s2++;
    }
    ptr[len] = '\0';
    return(ptr);
}
char    *ft_substr(char *s1, int n)
{
    char    *ptr;
    int i = 0;
    if(!(ptr = malloc(sizeof(char)*n + 1)))
        return(NULL);
    while (n > 0)
    {
        ptr[i] = *s1;
        i++;
        s1++;
        n--;
    }
    ptr[i] = '\0';
    return(ptr);
}
int get_next_line(char **line)
{
    int len =  0;
    char *aux2 = NULL;
    if (line == NULL)
        return (-1);
    static char *aux = NULL;
    char    buff[BUFFER_SIZE + 1];
    if(aux == NULL)
        aux = ft_strdup("");
    if (ft_strchr(aux) != 1)
    {
        while((len = read(0, buff, BUFFER_SIZE)) > 0)
        {
            buff[len] = '\0';
            aux2 = ft_strjoin(aux, buff);
            free(aux);
            aux = aux2;
            if (ft_strchr(aux) == 1)
                break;
        }
    }
    if (len < 0)
        return(-1);
    len = 0;
    while(aux[len] != '\n' && aux[len] != '\0')
        len++;
    if (aux[len] == '\n')
    {
        *line = ft_substr(aux, len);
        aux2 = ft_strdup(aux + (len + 1));
        free(aux);
        aux = aux2;
        return (1);
    }
    else
    {
        *line = ft_strdup(aux);
        free(aux);
        aux = NULL;
        return(0);
    }
}
