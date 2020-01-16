/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:40:52 by aortega-          #+#    #+#             */
/*   Updated: 2020/01/16 18:42:03 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

void	ft_putchar(char c, int n)
{
	while (n-- > 0)
	{
		write (1, &c, 1);
	}
}

int	ft_strlen(char *s)
{
	int n = 0;
	while (*s != '\0')
	{
		n++;
		s++;
	}
	return (n);
}

int	ft_prints(int width, int p, int precision, char *s)
{
	int l = s == NULL ? 6 : ft_strlen(s);
	if (p > 0)
	{
		l = l > precision ? precision : l;
	}
	width = width > l ? width : l;
	ft_putchar(' ', width - l);
	write( 1, s == NULL ? "(null)" : s, l);
	return (width);
}

char *ft_itoa(int n)
{
	long int n2 = n < 0 ? (long int)n * -1 : n;
	long int na = n2;
	int l = n <= 0 ? 1 : 0;
	char *s;
	while ( na > 0)
	{
		na = na / 10;
		l++;
	}
	if (!(s = malloc(sizeof (char) * (l + 1))))
			return (NULL);
	*(s+l) = '\0';
	if (n < 0 )
		*s = '-';
	if (n == 0)
		*s = '0';
	while (n2 > 0)
	{
		s[--l] = n2 % 10 + '0';
		n2 /= 10;
	}
	return (s);

}

int ft_printd(int w, int f, int p, int n)
{
	char *s = ft_itoa(n);
	int l = f == 1 && p == 0 && n == 0 ? 0 : ft_strlen(s);
	if (n < 0)
		p = p > l - 1 ? p + 1 : l;
	else
		p = p > l ? p : l;
	w = w > p ?  w : p;
	ft_putchar(' ', w - p);
	ft_putchar('-', n < 0 ? 1 : 0);
	ft_putchar('0', p - l);
	write (1, s + (n < 0 ? 1:0), l - (n < 0 ? 1:0) );
   return (w);
}
char *ft_itoax(unsigned int n)
{
	long int na = n;
	int l =  0;
	char *s;
	while ( na > 0)
	{
		na = na / 16;
		l++;
	}
	if (!(s = malloc(sizeof (char) * (l + 1))))
			return (NULL);
	*(s+l) = '\0';
	if (n == 0)
		*s = '0';
	while (n > 0)
	{
		s[--l] = n % 16 + (n % 16 > 9 ? 'W':'0');
		n /= 16;
	}
	return (s);

}

int ft_printx(int w, int f, int p, unsigned int n)
{
	char *s = ft_itoax(n);
	int l = f == 1 && p == 0 && n == 0 ? 0 : ft_strlen(s);
	p = p > l ? p : l;
	w = w > p ?  w : p;
	ft_putchar(' ', w - p);
	ft_putchar('0', p - l);
	write (1, s , l);
   return (w);
}

int	ft_printf(const char *s, ...)
{
	int len = 0;
	int p = 0;
	int width = 0;
	int precision = 0;
	va_list ap;
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
				p = 1;
				while (*s >= '0' && *s <= '9')
				{
					precision = precision * 10 + (*s -'0');
					s++;
				}
			}
			if (*s == 's')
			{
				len += ft_prints(width, p, precision, va_arg(ap, char *));
				s++;
			}
			else if (*s == 'd')
			{
				len += ft_printd(width, p, precision, va_arg(ap, int));
				s++;
			}
			else if (*s == 'x')
			{
				len += ft_printx(width, p, precision, va_arg(ap, unsigned int));
				s++;
			}
			p = 0;
			width = 0;
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
