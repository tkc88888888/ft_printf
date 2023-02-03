/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkfmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktan <ktan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:30:11 by ktan              #+#    #+#             */
/*   Updated: 2023/02/03 14:58:15 by ktan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

char	*checkflagwidth(char *c, t_print *p, char *i)
{
	while (i != c && ft_strchr("-+0 #", *c))
	{
		if (*c == '-')
			p->left = 1;
		if (*c == '+')
			p->sign = 1;
		if (*c == '0')
			p->zero = 1;
		if (*c == ' ')
			p->blank = 1;
		if (*c == '#')
			p->hash = 1;
		++c;
	}
	if (i != c && *c == '*' && ++c)
		p->intwidth = va_arg(p->args, int);
	else
		while (i != c && ft_isdigit(*c))
			if (!(p->intwidth > ((INT32_MAX - (*c - '0')) / 10)))
				p->intwidth = (p->intwidth) * 10 + *c++ - '0';
	if (p->intwidth < 0 && ++p->left)
		p->intwidth *= -1;
	return (c);
}

char	*checkpreci(char *c, t_print *p, char *i)
{
	if (i != c && (*c == '.' && ++p->dot))
	{
		if (*++c == '*' && ++c)
		{
			p->intpreci = va_arg(p->args, int);
			if (p->intpreci < 0 && !ft_strchr("eEfFgG", *i) && p->dot--)
				p->intpreci = 0;
			else if (p->intpreci < 0 && ft_strchr("eEfFgG", *i))
				goto isdefault;
		}
		while (i != c && ft_isdigit(*c))
			if (!(p->intpreci > ((INT32_MAX - (*c - '0')) / 10)))
				p->intpreci = (p->intpreci) * 10 + *c++ - '0';
		if (p->dot && !ft_strchr("eEfFgG", *i))
			p->zero = 0;
	}
	else
	{
		isdefault:;
		if (ft_strchr("eEfFgG", *i))
			p->intpreci = 6;
		if (ft_strchr("aA", *i))
			p->intpreci = 13;
	}
	return (c);
}

char	*checksize(char *c, t_print *p, char *i)
{
	if (c != i)
	{
		if (*c == 'h' && *(c + 1) == 'h' && c + 2 == i)
			c = i;
		if (*c == 'h' && c + 1 == i && --p->size)
			c = i;
		if (ft_strchr("jtzIl", *c) && c + 1 == i && ++p->size)
			c = i;
		if (ft_strchr("L", *c) && c + 1 == i)
			c = i;
		if (*c == 'I' && *(c + 1) == '3' && *(c + 2) == '2' && c + 3 == i)
			c = i;
		if (*c == 'I' && *(c + 1) == '6' && *(c + 2) == '4' && c + 3 == i)
			if (++p->size)
				c = i;
		if (*c == 'l' && *(c + 1) == 'l' && c + 2 == i && ++p->size)
			c = i;
		if (c == ft_strchr("hlw", *c) && c + 1 == i)
			c = i;
		p->c = *i;
	}
	return (c);
}

char	*checktype(char *c, t_print *p)
{
	if (ft_strchr("di", *c) && p->size == -1)
		p->print = ft_itoa_printf((size_t)va_arg(p->args, int), p);
	else if (ft_strchr("uoxX", *c) && p->size == -1)
		p->print = ft_itoa_printf((size_t)va_arg(p->args, unsigned int), p);
	else if (ft_strchr("di", *c) && p->size == 0)
		p->print = ft_itoa_printf((size_t)va_arg(p->args, int), p);
	else if (ft_strchr("uoxX", *c) && p->size == 0)
		p->print = ft_itoa_printf((size_t)va_arg(p->args, unsigned int), p);
	else if (ft_strchr("di", *c) && p->size == 1)
		p->print = ft_itoa_printf((size_t)va_arg(p->args, long long int), p);
	else if (ft_strchr("uoxX", *c) && p->size == 1)
		p->print = ft_itoa_printf(va_arg(p->args, long long unsigned int), p);
	else if (*c == 'p')
		p->print = ft_itoa_printf((size_t)va_arg(p->args, size_t), p);
	else if (ft_strchr("c%", *c))
		p->print = ft_strdup("0");
	if (*c == 'c')
		*(p->print) = va_arg(p->args, int);
	else if (*c == '%')
		*(p->print) = *c;
	if (*c == 's')
		p->print = ft_strdup(va_arg(p->args, char *));
	if (*c == 's' && p->print == NULL && ++p->null)
		p->print = ft_strdup("(null)");
	return (++c);
}
