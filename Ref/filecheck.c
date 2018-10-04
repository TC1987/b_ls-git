/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filecheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 14:02:24 by ncollie           #+#    #+#             */
/*   Updated: 2018/09/25 14:02:26 by ncollie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pheader.h"
#include "lheader.h"

char *time_clean(char *the_time, long numtime)
{
    char *temp;

    if ((temp = malloc(sizeof(char) * 13)) == NULL)
        return (NULL);
    temp[12] = '\0';
    if ((time(NULL) - numtime) > 15780000)
    {
        ft_strncpy(temp, (the_time + 4), 7);
        ft_strncpy((temp + 7), (the_time + 19), 5);
    }
    else
        temp = ft_strncpy(temp, (the_time + 4), 12);
    free(the_time);
    the_time = NULL;
    return (temp);
}

t_data **t_datamaker()
{
    t_data **array;
    t_data *head;
    t_data *tail;

    head = NULL;
    tail = NULL;
    array = malloc(sizeof(t_data) * 2);
    array[0] = head;
    array[1] = tail;
    return (array);
}

t_data ***t_datafinal()
{
    t_data ***array;
    t_data **junk;
    t_data **file;
    t_data **dir;

    junk = t_datamaker();
    file = t_datamaker();
    dir = t_datamaker();
    array = malloc(sizeof(t_data) * 3);
    array[0] = junk;
    array[1] = file;
    array[2] = dir;
    return (array);
}
