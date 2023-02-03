/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktan <ktan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:19:36 by ktan              #+#    #+#             */
/*   Updated: 2023/02/03 13:44:26 by ktan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

void	rightfmtprint(t_print *p)
{
	if ((!ft_strchr("cs", p->c) && p->zero) || (p->c == '%' && p->dot))
	{
		prefixprint(p);
		while (p->widthpad-- > 0)
			ft_putchar_count_fd('0', 1, p);
	}
	else
	{
		while (p->widthpad-- > 0)
			ft_putchar_count_fd(' ', 1, p);
		prefixprint(p);
	}
	if (!ft_strchr("cs", p->c))
		while (p->precipad-- > 0)
			ft_putchar_count_fd('0', 1, p);
	else
		while (p->precipad-- > 0)
			ft_putchar_count_fd(' ', 1, p);
	if (p->c == 'c' && !p->len)
		ft_putchar_count_fd('\0', 1, p);
	else
		ft_putstr_count_fd(p->print, 1, p);
}

void	leftfmtprint(t_print *p)
{
	prefixprint(p);
	if (!ft_strchr("cs", p->c))
		while (p->precipad-- > 0)
			ft_putchar_count_fd('0', 1, p);
	else
		while (p->precipad-- > 0)
			ft_putchar_count_fd(' ', 1, p);
	if (p->c == 'c' && !p->len)
		ft_putchar_count_fd('\0', 1, p);
	else
		ft_putstr_count_fd(p->print, 1, p);
	while (p->widthpad-- > 0)
		ft_putchar_count_fd(' ', 1, p);
}

void	prefixprint(t_print *p)
{
	if (p->c == 's' || p->c == 'c')
		return ;
	if (p->c == 'p')
		ft_putstr_count_fd("0x", 1, p);
	if (p->hash && p->c == 'o' && *p->print && *p->print != '0')
		ft_putstr_count_fd("0", 1, p);
	if (p->hash && p->c == 'x' && *p->print && *p->print != '0')
		ft_putstr_count_fd("0x", 1, p);
	if (p->hash && p->c == 'X' && *p->print && *p->print != '0')
		ft_putstr_count_fd("0X", 1, p);
	if (p->negative)
		ft_putstr_count_fd("-", 1, p);
	else if (p->sign)
		ft_putstr_count_fd("+", 1, p);
	else if (p->blank)
		ft_putstr_count_fd(" ", 1, p);
}

void	widthreduce(t_print *p)
{
	if (p->c == 'c' && !p->len && p->widthpad)
		--(p->widthpad);
	if (p->c == 's' || p->c == 'c')
		return ;
	if (p->c == 'p')
		p->widthpad -= 2;
	if (*p->print)
		if (p->hash && (p->c == 'X' || p->c == 'x') && *p->print != '0')
			p->widthpad -= 2;
	if (*p->print)
		if (p->hash && p->c == 'o' && *p->print != '0')
			--(p->widthpad);
	if (p->negative || p->sign || p->blank)
		--(p->widthpad);
}

void	fmtprint(t_print *p)
{
	if (p->print)
	{
		if (p->c == 's' && p->dot && p->intpreci < (int)ft_strlen(p->print))
			*(p->print + p->intpreci) = '\0';
		p->len = (int)ft_strlen(p->print);
		if (p->len < (p->intpreci) && p->c != 's' && p->c != '%')
		{
			p->precipad = p->intpreci - p->len;
			if (p->intpreci < p->intwidth)
				p->widthpad = p->intwidth - p->intpreci;
		}
		else if (p->len < p->intwidth)
			p->widthpad = p->intwidth - ft_strlen(p->print);
		widthreduce(p);
		if (p->left)
			leftfmtprint(p);
		else
			rightfmtprint(p);
		free(p->print);
	}
	structreset(p);
}
