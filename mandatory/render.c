/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:40:08 by yusudemi          #+#    #+#             */
/*   Updated: 2025/01/31 03:22:55 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	square_complex(t_complex c) // helper 
{
	// (a + bi)^2 = a^2 - b^2 + 2abi
	t_complex	res;
	
	res.re = c.re * c.re - c.im * c.im;
	res.im = 2 * c.re * c.im;
	return (res);
}

t_complex	sum_complex(t_complex c1, t_complex c2) //helper
{
	t_complex	res;
	
	res.im = c1.im + c2.im;
	res.re = c1.re + c2.re;
	return (res);
}

int	render_pixel(t_data *d)
{
	int	i;
	d->z.re = 0;
	d->z.im = 0;
	i = -1;
	while ((d->z.re * d->z.re + d->z.im * d->z.im) < 4.0 && ++i < d->max_iter)
		d->z = sum_complex(square_complex(d->z), d->c);
	return (i);
}

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

void	render_image(t_data *d)
{
	int	x;
	int	y;
	int	trgb;
	
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			d->c.re = ((x - WIDTH / 2.0) * 4.0 / WIDTH);
			d->c.im = ((y - HEIGHT / 2.0) * 4.0 / HEIGHT);
			trgb = render_pixel(d);
			put_pixel(x, y, trgb, d);
		}
	}
}