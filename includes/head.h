/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:21:20 by ldevelle          #+#    #+#             */
/*   Updated: 2019/07/14 19:29:21 by ezalos           ###   ########.fr       */
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
#endif
