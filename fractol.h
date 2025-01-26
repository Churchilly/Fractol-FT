/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:13:01 by yusudemi          #+#    #+#             */
/*   Updated: 2025/01/26 20:38:17 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H


typedef struct	s_complex
{
	double	r;
	double	i;
}		t_complex;

typedef struct s_mlx
{
	void	*connection;
	void	*window;
	void	*image;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
} t_mlx;


typedef struct	s_fractal
{
	t_mlx		*mlx;
	t_complex	z;
	t_complex	c;
}			t_fractal;

#endif