/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_me.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 15:42:37 by ncollie           #+#    #+#             */
/*   Updated: 2018/09/28 15:42:42 by ncollie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pheader.h"
#include "lheader.h"

void print_junk(t_data *head, int *flag)
{
	if (!(head))
		return;
	 flag[5] = 1;
	while (head->next)
	{
		b_printf("ls: %s: No such file or directory\n", head->name);
		head = head->next;
	}
	b_printf("ls: %s: No such file or directory\n", head->name);
}

// void print_files(t_data *head, t_data *tail, int *flag, t_data *other_head)
// {
// 	if (!(head))
// 		return;

// 	// flag[5] = 1;
// 	t_data *ptr = flag[3] ? tail : head;

// 	(flag[0]) ? longformat(ptr, flag) : reg (ptr, flag);
// 		// if (other_head)
// 		// 	b_printf("\n");
// }

void reg(t_data *ptr, int *flag)
{
	while (flag[3] ? ptr->last : ptr->next)
	{
		printf("%s\n", ptr->name);
		ptr = flag[3] ? ptr->last : ptr->next;
	}							 //add check if for long format and print diff
	b_printf("%s\n", ptr->name); //add free after printing??
}

void longformat(t_data *ptr, int *flag, long long total)
{
	if (total)
		printf("total %lli\n", total);
	while (flag[3] ? ptr->last : ptr->next)
	{
		printf("%s  %2u %s  %s ", ptr->mode, ptr->links, ptr->user, ptr->group);
		printf("%8lli %s %s\n",ptr->size, ptr->time, ptr->name);
		ptr = flag[3] ? ptr->last : ptr->next;
	} //add check if for long format and print diff
	  //add free after printing??
	printf("%s  %2u %s  %s ", ptr->mode, ptr->links, ptr->user, ptr->group);
	printf("%8lld %s %s\n",ptr->size, ptr->time, ptr->name);
}

void print_me(t_data *head, t_data *tail, int *flag, long long total)
{
	if (!(head))
		return;
	t_data *ptr = flag[3] ? tail : head;
	(flag[0]) ? longformat(ptr, flag, total) : reg(ptr, flag);
}

void run(t_data **node_dir, int *flag)
{
	if (!(node_dir[0]))
		return;
	t_data *ptr = flag[3] ? (node_dir[1]) : (node_dir[0]);

	while (flag[3] ? ptr->last : ptr->next)
	{
		if (flag[6])
			b_printf("\n");
		flag[6] = 1;

		b_printf("%s:\n", ptr->name);
		walk(ptr->name, flag);
		ptr = flag[3] ? ptr->last : ptr->next;
	}
	// if (flag[5] || ptr->last || ptr->next)
	// 	b_printf("\n%s:\n", ptr->name);
	//if ((flag[3] && ptr->last == NULL) || (!flag[3] && ptr->next == NULL))
	//	flag[6] += 1;
	walk(ptr->name, flag);
}