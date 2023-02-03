/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktan <ktan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 00:26:06 by ktan              #+#    #+#             */
/*   Updated: 2023/02/03 13:43:55 by ktan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

int	ft_numlen_u(size_t n, int base)
{
	while (!(n / base))
		return (1);
	return (ft_numlen_u(n / base, base) + 1);
}

char	*ft_putnbr_u(size_t n, t_print *p, int *i, size_t base)
{
	char	*basechar;

	if (base == 16 && p->c != 'X')
		basechar = "0123456789abcdef";
	else if (base == 16 && p->c == 'X')
		basechar = "0123456789ABCDEF";
	if (base == 10)
		basechar = "0123456789";
	if (base == 8)
		basechar = "01234567";
	if (n / base)
		ft_putnbr_u((n / base), p, i, base);
	p->print[(*i)++] = basechar[(n % base)];
	return (p->print);
}

void	ft_itoa_int(size_t n, t_print *p, int *i, int base)
{
	if (ft_strchr("di", p->c))
	{
		if (p->size == -1 && (short int)n < 0 && ++p -> negative)
			n = (size_t)((short int)n * -1);
		if (p->size == 0 && (int)n < 0 && ++p -> negative)
			n = (size_t)((int)n * -1);
		if (p->size == 1 && (long long int)n < 0 && ++p -> negative)
			n = (size_t)((long long int)n * -1);
	}
	if (ft_strchr("diuoxXp", p->c))
		p->print = malloc (sizeof(char) * (ft_numlen_u(n, base) + 1));
	if (p->size == -1 && ft_strchr("diuoxX", p->c))
		ft_putnbr_u((short unsigned int)n, p, i, base);
	if (p->size == 0 && ft_strchr("diuoxX", p->c))
		ft_putnbr_u((unsigned int)n, p, i, base);
	if (p->size == 1 && ft_strchr("diuoxX", p->c))
		ft_putnbr_u((long long unsigned int)n, p, i, base);
	if (p->c == 'p')
		ft_putnbr_u((size_t)n, p, i, base);
}

char	*ft_itoa_printf(size_t n, t_print *p)
{
	int		i;
	int		base;

	if (ft_strchr("diufFeEgG", p->c))
		base = 10;
	if (p->c == 'o')
		base = 8;
	else if (ft_strchr("pxXaA", p->c))
		base = 16;
	i = 0;
	if (ft_strchr("diuopxX", p->c) && (!n && p->dot && p->c != 'o'))
		return (ft_strdup(""));
	else if (ft_strchr("diuopxX", p->c))
		ft_itoa_int(n, p, &i, base);
	p->print[i] = 0;
	return (p->print);
}
