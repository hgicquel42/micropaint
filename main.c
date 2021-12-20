/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:14:51 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/20 12:11:02 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
	int		w;
	int		h;
	char	b;
	FILE	*f;
	char	*p;
}	t_data;

typedef	struct t_line
{
	char	t;
	float	x;
	float	y;
	float	w;
	float	h;
	char	c;
}	t_line;

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

int	ft_argerr(void)
{
	ft_putstr("Error: argument\n");
	return (1);
}

int	ft_ioerr(void)
{
	ft_putstr("Error: Operation file corrupted\n");
	return (1);
}

int	ft_header(t_data *d)
{
	int	l;
	int	i;

	if (fscanf(d->f, "%d %d %c\n", &d->w, &d->h, &d->b))
		return (0);
	if (!d->w || d->w > 300)
		return (0);
	if (!d->h || d->h > 300)
		return (0);
	l = d->w * d->h;
	if (!(d->p = malloc(l)))
		return (0);
	i = 0;
	while (i < l)
		d->p[i++] = d->b;
	return (1);
}

int	ft_body(FILE *file, t_data *d)
{
	t_line	l;

	while (1)
	{
		if (fscanf(d->f, "%c %f %f %f %f %c\n", &l.t, &l.x, &l.y, &l.w, &l.h, &l.c))
			return (0);
		
	}	
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_argerr());
	if (!(data.f = fopen(argv[1], "r")))
		return (ft_ioerr());
	if (!ft_header(&data))
		return (ft_ioerr());
	return (0);
}