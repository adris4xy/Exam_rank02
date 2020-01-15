/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:12:45 by aortega-          #+#    #+#             */
/*   Updated: 2020/01/14 19:09:54 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	is_in_string(char *s2, char c)
{
	int i;

	i = 0;
	while (s2[i])
	{
		if (s2[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	is_first(char *s1, char c, int len)
{
	int i;

	i = 0;
	while (s1[i] && s1[i] != c)
		i++;
	if (i == len)
		return (1);
	return (0);
}

void		ft_inter(char *s1, char *s2)
{
	int j;

	j = 0;
	while (s1[j])
	{
		if (is_in_string(s2, s1[j]) && is_first(s1, s1[j], j))
			write(1, &s1[j], 1);
		j++;
	}
}

int         main (int argc, char **argv)
{
    if (argc == 3)
        ft_inter(argv[1], argv[2]);
}
