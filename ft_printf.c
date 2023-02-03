/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktan <ktan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:29:49 by ktan              #+#    #+#             */
/*   Updated: 2023/02/03 13:44:03 by ktan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

void	ft_putchar_count_fd(char c, int fd, t_print *p)
{
	++p->printed;
	write(fd, &c, 1);
}

void	ft_putstr_count_fd(char *s, int fd, t_print *p)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_count_fd(*s++, fd, p);
}

void	structreset(t_print *p)
{
	p->left = 0;
	p->sign = 0;
	p->negative = 0;
	p->zero = 0;
	p->blank = 0;
	p->hash = 0;
	p->intwidth = 0;
	p->dot = 0;
	p->intpreci = 0;
	p->sig = 0;
	p->isfloatg = 0;
	p->point = -1;
	p->power = 0;
	p->size = 0;
	p->len = 0;
	p->print = 0;
	p->c = 0;
	p->widthpad = 0;
	p->precipad = 0;
	p->null = 0;
}

char	*fmtconvert(char *c, t_print *p)
{
	char	*i;
	int		j;

	j = 0;
	while (*(c + j))
	{
		if (ft_strchr("diuoxXpcs%naAeEfFgG", *(c + j)))
			break ;
		j++;
	}
	if (*(c + j))
		i = c + j;
	else
		return (c);
	c = checkflagwidth(c, p, i);
	c = checkpreci(c, p, i);
	c = checksize(c, p, i);
	p->c = *c;
	c = checktype(c, p);
	fmtprint(p);
	return (c);
}

int	ft_printf(const char *c, ...)
{
	t_print	*p;
	int		val;

	val = 0;
	p = malloc(sizeof(*p));
	if (!p)
		return (0);
	structreset(p);
	p->printed = 0;
	va_start(p->args, c);
	while (*c)
	{
		if (*c == '%')
			c = fmtconvert((char *)++c, p);
		else if (*c)
			ft_putchar_count_fd(*c++, 1, p);
	}
	va_end(p->args);
	val = p->printed;
	free(p);
	return (val);
}
