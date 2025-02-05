/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:40:08 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/05 00:40:26 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "../minilibx/mlx.h"

static void	put_pixel(int x, int y, int trgb, t_data *d)
{
	char	*dest;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dest = d->addr + (y * d->line_length + x
				* (d->bits_per_pixel / 8));
		*(unsigned int *)dest = trgb;
	}
}

static int	get_color(double i, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = i / max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return (r << 16 | g << 8 | b);
}

void	render_image(t_data *d)
{
	int		x;
	int		y;
	double	iter;
	int		trgb;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (d->set == MANDELBROT)
				iter = render_mandelbrot(x, y, d);
			else if (d->set == JULIA)
				iter = render_julia(x, y, d);
			else if (d->set == TRICORN)
				iter = render_tricorn(x, y, d);
			trgb = get_color(iter, d->max_iter);
			put_pixel(x, y, trgb, d);
		}
	}
	mlx_put_image_to_window(d->connection, d->window, d->image, 0, 0);
}
