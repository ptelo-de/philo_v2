/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_logs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:00:51 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/11/25 23:48:16 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//returns time in milisec
size_t my_getime(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
