/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:40:08 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/10 02:26:00 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "../minilibx/mlx.h"
# include <pthread.h>


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


static void	*render_thread(void *data)
{
	t_threads_data	*td;
	int				x;
	int				y;
	double			iter;
	int				trgb;

	td = (t_threads_data *)data;
	y = td->start_y - 1;
	while (++y < td->end_y)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (td->d.set == MANDELBROT)
				iter = render_mandelbrot(x, y, &td->d);
			else if (td->d.set == JULIA)
				iter = render_julia(x, y, &td->d);
			else if (td->d.set == TRICORN)
				iter = render_tricorn(x, y, &td->d);
			trgb = get_color(iter, td->d.max_iter);
			put_pixel(x, y, trgb, &td->d);
		}
	}
	return (0);
}

void	render_image(t_data *d)
{
	pthread_t		thread[DEFAULT_THREADS];
	t_threads_data	threads_data[DEFAULT_THREADS];
	int				i;
	
	i = -1;
	while (++i < DEFAULT_THREADS)
	{
		threads_data[i].d = *d;
		threads_data[i].start_y = i * (HEIGHT / DEFAULT_THREADS);
		threads_data[i].end_y = (i == DEFAULT_THREADS - 1) ? HEIGHT : (i + 1) * (HEIGHT / DEFAULT_THREADS);
		pthread_create(&thread[i], NULL, render_thread, &threads_data[i]);
	}
	i = -1;
	while (++i < DEFAULT_THREADS)
		pthread_join(thread[i], NULL);
	mlx_put_image_to_window(d->connection, d->window, d->image, 0, 0);
}
