/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktan <ktan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:53:41 by ktan              #+#    #+#             */
/*   Updated: 2023/02/03 13:20:36 by ktan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

typedef struct print
{
	int		left;
	int		sign;
	int		zero;
	int		blank;
	int		hash;
	int		negative;
	int		intwidth;
	int		dot;
	int		intpreci;
	int		sig;
	int		isfloatg;
	int		point;
	int		power;
	int		size;
	int		len;
	char	*print;
	char	c;
	int		widthpad;
	int		precipad;
	int		null;
	int		printed;
	va_list	args;
}	t_print;

void	leftfmtprint(t_print *p);
void	rightfmtprint(t_print *p);
void	prefixprint(t_print *p);
void	widthreduce(t_print *p);
void	fmtprint(t_print *p);
char	*checkflagwidth(char *c, t_print *p, char *i);
char	*checkpreci(char *c, t_print *p, char *i);
char	*checksize(char *c, t_print *p, char *i);
char	*checkfloat(char *c, t_print *p);
char	*checktype(char *c, t_print *p);
void	structreset(t_print *p);
char	*fmtconvert(char *c, t_print *p);
int		ft_printf(const char*c, ...);
//char	*ft_strncat(char *dest, char *src, size_t nb);
//size_t	ft_strlcpy(char	*dst, const char *src, size_t size);
//char	*ft_strdup(const char *s);
//size_t	ft_strlen(const char *s);
void	ft_putstr_count_fd(char *s, int fd, t_print *p);
//int		ft_isdigit(int c);
void	ft_putchar_count_fd(char c, int fd, t_print *p);
//char	*ft_strchr(const char *s, int c);
int		ft_numlen_u(size_t n, int base);
char	*ft_itoa_printf(size_t n, t_print *p);
char	*ft_putnbr_u(size_t n, t_print *p, int *i, size_t base);

#endif
