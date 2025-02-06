/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:17:47 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/06 05:00:56 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <X11/keysym.h>
#include "fractol_bonus.h"
#include "../minilibx/mlx.h"
#include <stdlib.h>

static int	quit(t_data *d)
{
	mlx_destroy_image(d->connection, d->image);
	mlx_destroy_window(d->connection, d->window);
	mlx_destroy_display(d->connection);
	free(d->connection);
	exit(0);
}

static int	key_handler(int key, t_data *d)
{
	if (key == XK_Escape)
		quit(d);
	if (key == XK_w || key == XK_Up)
		d->shift.im -= (0.75) * d->zoom;
	if (key == XK_s || key == XK_Down)
		d->shift.im += (0.75) * d->zoom;
	if (key == XK_a || key == XK_Left)
		d->shift.re -= (0.75) * d->zoom;
	if (key == XK_d || key == XK_Right)
		d->shift.re += (0.75) * d->zoom;
	if (key == XK_p || key == XK_P)
		d->max_iter += 25;
	if (key == XK_o || key == XK_O)
		d->max_iter -= 25;
	render_image(d);
	return (0);
}

static int	mouse_handler(int button, int x, int y, t_data *d)
{
	double	mouse_re;
	double	mouse_im;
	double	zoom_factor;

	mouse_re = d->min.re + (x * (d->max.re - d->min.re) / WIDTH);
	mouse_im = d->min.im + (y * (d->max.im - d->min.im) / HEIGHT);
	if (button == Button4)
		zoom_factor = 0.7;
	else if (button == Button5)
		zoom_factor = 1.3;
	else
		return (0);
	d->min.re = mouse_re + (d->min.re - mouse_re) * zoom_factor;
	d->max.re = mouse_re + (d->max.re - mouse_re) * zoom_factor;
	d->min.im = mouse_im + (d->min.im - mouse_im) * zoom_factor;
	d->max.im = mouse_im + (d->max.im - mouse_im) * zoom_factor;
	d->zoom *= zoom_factor;
	render_image(d);
	return (0);
}

void	events_setup(t_data *d)
{
	mlx_hook(d->window, ClientMessage, StructureNotifyMask, quit, d);
	mlx_hook(d->window, KeyPress, KeyPressMask, key_handler, d);
	mlx_hook(d->window, ButtonPress, ButtonPressMask, mouse_handler, d);
}
