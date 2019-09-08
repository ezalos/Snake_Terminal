/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:00:47 by ezalos            #+#    #+#             */
/*   Updated: 2019/09/08 23:34:22 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void 		new_food(t_snake *snake)
{
	DEBUG_FUNC;
	print_pixel(snake, snake->food.row, snake->food.col, BODY);
	snake->food.row = ft_rand(snake->rows, 0);
	snake->food.col = ft_rand(snake->cols, 0);
	print_pixel(snake, snake->food.row, snake->food.col, FOOD);
}

void		snake_grow(t_snake *snake, int row, int col)
{
	DEBUG_FUNC;
	snake->col_history[++snake->col_history[0]] = col;
	snake->row_history[++snake->row_history[0]] = row;
	ft_place_cursor(0, snake->cols - ft_strlen("SNAKE LVL XXXX"));
	ft_printf("SNAKE LVL %d\n", snake->col_history[0]);
	print_pixel(snake, row, col, BODY);
}
void		snake_move(t_snake *snake, int row, int col)
{
	DEBUG_FUNC;
	int i;

	i = 0;
	while (++i < snake->col_history[0])
		snake->col_history[i] = snake->col_history[i + 1];
	snake->col_history[snake->col_history[0]] = col;
	i = 0;
	while (++i < snake->row_history[0])
		snake->row_history[i] = snake->row_history[i + 1];
	snake->row_history[snake->row_history[0]] = row;
}

void	got_food(t_snake *snake)
{
	DEBUG_FUNC;
	snake->board[snake->food.row][snake->food.col] == BODY;
	snake_grow(snake, snake->first.row, snake->first.col);
	new_food(snake);
}

void	calculate_head_pos(t_snake *snake)
{
	if (snake->dir_row == 0 && snake->dir_col == 0)
		snake->dir_row = 1;

	snake->first.col += snake->dir_col;
	snake->first.row += snake->dir_row;
	ft_printf("[%d/%d;%d/%d]\n", snake->first.col, snake->cols, snake->first.row, snake->rows);


	if (snake->first.col < 0)
		snake->first.col = snake->cols + snake->first.col;
	if (snake->first.row < 0)
		snake->first.row = snake->rows + snake->first.row;
	snake->first.col = ft_abs((snake->first.col )) % snake->cols;
	snake->first.row = ft_abs((snake->first.row )) % snake->rows;

	ft_printf("[%d/%d;%d/%d]\n", snake->first.col, snake->cols, snake->first.row, snake->rows);
}

int		is_it_legal_move(t_snake *snake)
{
	return (snake->first.row < 0 || snake->first.row >= snake->rows
		||  snake->first.col < 0 || snake->first.col >= snake->cols);
}

int 	big_loop(t_snake *snake)
{
	int end;
	// char buffer[7];
	char *buffer;
	int	r_v;

	snake->dir_row = 1;
	end = 0;
	while (!end)
	{
		ft_printf("%~{?}%s\n", __func__);
		get_input(snake);

		calculate_head_pos(snake);

		if (ft_printf("1\n") && is_it_legal_move(snake))
		{
			ft_printf("%s\n", "OUT");
			ft_press_any_key();
			// print_pixel(snake, snake->row_history[snake->row_history[0] - 1], snake->col_history[snake->col_history[0] - 1], DEAD);
			end = 1;
		}
		else if (ft_printf("2\n") && snake->board[snake->first.row][snake->first.col] == BODY && ft_printf("2.5\n"))
		{
			ft_printf("%s\n", "DEAD");
			print_pixel(snake, snake->first.row, snake->first.col, DEAD);
			ft_press_any_key();
			end = 1;
		}
		else if (ft_printf("3\n") && snake->first.col == snake->food.col
			 &&  snake->first.row == snake->food.row)
			got_food(snake);
		else
		{
			ft_printf("%s\n", "MOVE");
			print_pixel(snake, snake->row_history[1], snake->col_history[1], EMPTY);
			snake_move(snake, snake->first.row, snake->first.col);
		}
		ft_printf("loop end\n");
		if (!end)
			print_pixel(snake, snake->first.row, snake->first.col, BODY);
		// ft_wait_pls(0);
	}
}
