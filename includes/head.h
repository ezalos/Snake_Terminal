/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:21:20 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/08 23:33:32 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H


# define FAILURE				0
# define SUCCESS				1

# define ERROR					-1
# define VALID					0

# define PTR_ERROR				NULL

# define EMPTY					0
# define BODY					1
# define FOOD					2
# define DEAD					3


# define REFRESH_TIME			300 //milliseconds

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#define BAUDRATE				B38400
#define MODEMDEVICE				"/dev/ttyS1"
#define _POSIX_SOURCE			1 /* code source conforme à POSIX */

#define FALSE					0
#define TRUE					1

# define S_RIGHT					"\033[C"
# define S_DOWN						"\033[B"
# define S_LEFT						"\033[D"
# define S_UP						"\033[A"

# include "../../libft/includes/libft.h"
# include <sys/ioctl.h>
# include <stdio.h>


typedef int* 					t_ints;

typedef struct					s_point
{
	int							row;
	int							col;
}								t_point;

typedef struct							s_snake
{
			char						**board;
			int							rows;
			int							cols;
			t_ints						row_history;
			t_ints						col_history;
			t_point						first;
			t_point						food;
			int							dir_col;
			int							dir_row;

}										t_snake;

typedef enum 							e_state
{
			INPUT,
			CHECK,
			ACTIO,
}										t_state;

/*
******************************************************************************
**																			**
**								----------									**
**								PROTOTYPES									**
**								----------									**
**																			**
******************************************************************************
*/

/*
**************
**   INIT	**
**************
*/
t_snake		*init(int ac, char **av);
void 		print_it(t_snake *snake);
void 		new_food(t_snake *snake);
void		snake_grow(t_snake *snake, int row, int col);
void		snake_move(t_snake *snake, int row, int col);
int 		kbhit();
void 		set_conio_terminal_mode();
void 		reset_terminal_mode();
int 		get_input(t_snake *snake);
void		got_food(t_snake *snake);
void		print_pixel(t_snake *snake, int row, int col, int type);
int 		big_loop(t_snake *snake);
void		color_screen(t_snake *snake);
void		terminal_setup(void);
int			is_it_legal_move(t_snake *snake);




#endif
