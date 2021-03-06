/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_union.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:07:19 by aortega-          #+#    #+#             */
/*   Updated: 2020/02/06 12:47:24 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		ft_verify_char(char *str, char c, int index)
{
	int i = 0;
	while (i < index)
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

void	ft_union(char *s1, char *s2)
{
	int i = 0;
	int len = 0;
	while (s1[i])
	{
		if (ft_verify_char(s1, s1[i], i))
			write(1, &s1[i], 1);
		i++;
	}
	while (s2[len])
	{
		if (ft_verify_char(s2, s2[len], len))
			if (ft_verify_char(s1, s2[len], i))
				write(1, &s2[len], 1);
		len++;
	}
}

int main(int argc, char **argv)
{
	if (argc == 3)
		ft_union(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}

/*
Escriba un programa que se llame union, que reciba como parámetro dos cadenas de
de caracteres y muestre, sin duplicados, los caracteres que aparecen en
la una o en la otra.

Se mostrarán en el orden de aparición dentro de la línea de comandos.

La visualización irá seguida de un salto de línea.

Si el número de parámetros transmitidos es distinto de 2, el programa mostrará
\n.

Ejemplo:

$>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
zpadintoqefwjy$
$>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6vewg4thras$
$>./union "rien" "cette phrase ne cache rien" | cat -e
rienct phas$
$>./union | cat -e
$
$>
$>./union "rien" | cat -e
$
$>
*/