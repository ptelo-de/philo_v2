/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:17:23 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/11/25 23:05:15 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
    t_info info;

    if (argc == 5 || argc == 6)
    {
        check_args(argv);
        init(&info);
        create_philo(&info);
    }
    else
    {
        printf("error");
        return(1);
    }
}