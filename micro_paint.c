/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:14:51 by hgicquel          #+#    #+#             */
/*   Updated: 2021/12/20 14:41:00 by hgicquel         ###   ########.fr       */
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

void	ft_putstr(char *s)
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

	if (fscanf(d->f, "%d %d %c\n", &d->w, &d->h, &d->b) != 3)
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

void	ft_print(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->h)
	{
		write(1, d->p + (i * d->w), d->w);
		write(1, "\n", 1);
		i++;
	}
}

int	ft_dist(t_line *l, float x, float y)
{
	if (x < l->x || x > l->x + l->w)
		return (0);
	if (y < l->y || y > l->y + l->h)
		return (0);
	if (x - l->x < 1 || l->x + l->w - x < 1)
		return (1);
	if (y - l->y < 1 || l->y + l->h - y < 1)
		return (1);
	return (2);
}

void	ft_fill(t_data *d, t_line *l)
{
	int	i;
	int	j;
	int	q;

	i = 0;
	while (i < d->w)
	{
		j = 0;
		while (j < d->h)
		{
			q = ft_dist(l, i, j);
			if (q == 1 || (q == 2 && l->t == 'R'))
				d->p[i + j * d->w] = l->c;
			j++;
		}
		i++;
	}
}

int	ft_body(t_data *d)
{
	t_line	l;
	int		r;

	while (1)
	{
		r = fscanf(d->f, "%c %f %f %f %f %c\n", &l.t, &l.x, &l.y, &l.w, &l.h, &l.c);
		if (r == -1)
			return (1);
		if (r != 6)
			return (0);
		if (l.t != 'r' && l.t != 'R')
			return (0);
		if (l.w <= 0 || l.h <= 0)
			return (0);
		ft_fill(d, &l);
	}
	return (0);
}

int	free0(void *p)
{
	free(p);
	return (0);
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
	if (!ft_body(&data))
		return (ft_ioerr() + free0(data.p));
	ft_print(&data);
	return (0 + free0(data.p));
}
