/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:00:51 by ezalos            #+#    #+#             */
/*   Updated: 2019/09/08 21:10:18 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void 	print_it(t_snake *snake)
{
	int		last_color;
	int		row;
	int		col;

	color_screen(snake);
	// ft_press_any_key();
	_C_RESET;
	_C_CURSOR_RESET;
	last_color = EMPTY;
	row = -1;
	while (++row < snake->rows)
	{
		col = -1;
		while (++col < snake->cols)
		{
			if (snake->board[row][col] == BODY)
				ft_rgb_bcolor(255, 255, 255);
			else if (snake->board[row][col] == FOOD)
				ft_rgb_bcolor(0, 255, 0);
			else if (snake->board[row][col] == EMPTY)
				_C_RESET;
			write(1, " ", 1);
		}
		_C_RESET;
		write(1, "\n", 1);
	}
	_C_RESET;
	_C_CURSOR_RESET;
	// ft_printf("print complete\n");
}

void	color_screen(t_snake *snake)
{
	int		row;
	int		col;

	ft_rgb_bcolor(0, 0, 0);
	_C_RESET;
	_C_CURSOR_RESET;
	row = -1;
	while (++row < snake->rows)
	{
		col = -1;
		while (++col < snake->cols)
		{
			write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	_C_RESET;
	_C_CURSOR_RESET;

}

void	print_pixel(t_snake *snake, int row, int col, int type)
{
	DEBUG_FUNC;
	if (type == BODY)
		ft_rgb_bcolor(255, 255, 255);
	else if (type == FOOD)
		ft_rgb_bcolor(0, 255, 0);
	else if (type == DEAD)
		ft_rgb_bcolor(255, 0, 0);
	else if (type == EMPTY)
		_C_RESET;
	else
		return ;
	if ((snake->first.row >= 0 && snake->first.row <= snake->rows)
	||  (snake->first.col >= 0 && snake->first.col <= snake->cols))
		snake->board[row][col] = type;
	ft_place_cursor(row, col);
	write(1, " ", 1);
	_C_RESET;
	if (type != DEAD)
		_C_CURSOR_RESET;
}
