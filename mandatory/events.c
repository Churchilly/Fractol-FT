/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:17:47 by yusudemi          #+#    #+#             */
/*   Updated: 2025/01/31 21:16:59 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <X11/keysym.h>
#include "fractol.h"
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

static int key_handler(int key, t_data *d)
{
	if (key == XK_Escape)
		quit(d);
	if (key == XK_w || key == XK_Up)
		d->shift.im -= (0.5 * d->zoom);
	if (key == XK_s || key == XK_Down)
		d->shift.im += (0.5 * d->zoom);
	if (key == XK_a || key == XK_Left)
		d->shift.re += (0.5 * d->zoom);
	if (key == XK_d || key == XK_Right)
		d->shift.re -= (0.5 * d->zoom);
	render_image(d);
	return (0);
}

static int mouse_handler(int button, int x, int y, t_data *d)
{
	(void)x;
	(void)y;
	
	if (button == Button4)
	{
		printf("1here\n");
		d->zoom *= 1.1;
	}
	else if (button == Button5)
	{
		printf("2here\n");
		d->zoom *= 0.9;
	}
	render_image(d);
	return (0);
}

void	events_setup(t_data *d)
{
	mlx_hook(d->window, DestroyAll, StructureNotifyMask, quit, d);
	mlx_hook(d->window, KeyPress, KeyPressMask, key_handler, d);
	mlx_hook(d->window, ButtonPress, ButtonPressMask, mouse_handler, d);
}