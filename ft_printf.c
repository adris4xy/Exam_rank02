/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:40:52 by aortega-          #+#    #+#             */
/*   Updated: 2020/02/04 15:39:04 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_putchar(char c, int n)
{
	while(n-- > 0)
		write(1, &c, 1);
}

int	ft_strlen(char *s)
{
	int i = 0;
	while(*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

int	ft_prints(int wid, int po, int prec, char *str)
{
	int lon = str == NULL ? 6 : ft_strlen(str);
	if(po > 0)
		lon = lon > prec ? prec : lon;
	wid = wid > lon ? wid : lon;
	ft_putchar(' ', wid - lon);
	write(1, str == NULL ? "(null)" : str, lon);
	return (wid);
}

char	*ft_itoa(int n)
{
	long int n2 = n < 0 ? (long int)n * -1 : n;
	long int na = n2;
	int	len = n <= 0 ? 1 : 0;
	char *str;
	while (na > 0)
	{
		na = na / 10;
		len++;
	}
	if (!(str = malloc(sizeof (char) * (len + 1))))
		return (NULL);
	*(str + len) = '\0';
	if (n < 0)
		*str = '-';
	if (n == 0)
		*str = '0';
	while (n2 > 0)
	{
		str[--len] = n2 % 10 + '0';
		n2 = n2 / 10;
	}
	return (str);
}

int	ft_printd(int wid, int po, int prec, int n)
{
	char *str = ft_itoa(n);
	int lon = po == 1 && prec == 0 && n == 0 ? 0 : ft_strlen(str);
	if (n < 0)
		prec = prec > lon - 1 ? prec + 1 : lon;
	else
		prec = prec > lon ? prec : lon;
	wid = wid > prec ? wid : prec;
	ft_putchar(' ', wid - prec);
	ft_putchar('-', n < 0 ? 1 : 0);
	ft_putchar('0', prec - lon);
	write(1, str + (n < 0 ? 1: 0), lon - (n < 0 ? 1 : 0));
	return (wid);
}

char	*ft_itoax(unsigned int n)
{
	char *str;
	long int na = n;
	int len = 0;
	while (na > 0)
	{
		na = na / 16;
		len++;
	}
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	*(str + len) = '\0';
	if (n == 0)
		*str = '0';
	while (n > 0)
	{
		str[--len] = n % 16 + (n % 16 > 9 ? 'W' : '0');
		n = n / 16;
	}
	return (str);
}

int	ft_printx(int wid, int po, int prec, unsigned int n)
{
	char *str = ft_itoax(n);
	int lon = po == 1 && prec == 0 && n == 0 ? 0 : ft_strlen(str);
	prec = prec > lon ? prec : lon;
	wid = wid > prec ? wid : prec;
	ft_putchar(' ', wid - prec);
	ft_putchar('0', prec - lon);
	write(1, str, lon);
	return (wid);
}

int	ft_printf(const char *s, ...)
{
	int	len = 0;
	int	width = 0;
	int	point = 0;
	int	precision = 0;
	va_list	ap;
	va_start(ap, s);
	while (*s != '\0')
	{
		if (*s == '%')
		{
			s++;
			while (*s >= '0' && *s <= '9')
			{
				width = width * 10 + (*s - '0');
				s++;
			}
			if (*s == '.')
			{
				s++;
				point = 1;
				while (*s >= '0' && *s <= '9')
				{
					precision = precision * 10 + (*s - '0');
					s++;
				}
			}
			if (*s == 's')
			{
				len = len + ft_prints(width, point, precision, va_arg(ap, char *));
				s++;
			}
			else if (*s == 'd')
			{
				len = len + ft_printd(width, point, precision, va_arg(ap, int));
				s++;
			}
			else if (*s == 'x')
			{
				len = len + ft_printx(width, point, precision, va_arg(ap, unsigned int));
				s++;
			}
			width = 0;
			point = 0;
			precision = 0;
		}
		else
		{
			write(1, s, 1);
			len++;
			s++;
		}
	}
	va_end(ap);
	return (len);
}

int main()
{	
	int x;
	int y;

	x = ft_printf("Hola %2.8s %3.5d %6.4x %x\n", "perro", 242321,2343, 15);
	printf("%d\n", x);
	y = printf("Hola %2.8s %3.5d %6.4x %x\n", "perro", 242321 ,2343, 15);
	printf("%d\n", y);
	return (0);
}
