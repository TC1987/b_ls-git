/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 19:49:29 by ncollie           #+#    #+#             */
/*   Updated: 2018/09/26 12:33:11 by ncollie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pheader.h"
#include "lheader.h"
#define NAME_TIME (flag ? (temp->numtime - new_node->numtime) \
						: ft_strcmp(new_node->name, temp->name))

t_data *create_dir_node(char *current, struct stat *stats)
{
	t_data *node;

	if (!(node = malloc(sizeof(t_data))))
		return (NULL);
	if (stats)
	{
		node->path = current;
		node->numtime = stats->st_mtime;
		node->mode = get_extra(stats, get_mode(stats));
		node->time = time_clean(ft_strdup(ctime(&(stats->st_mtime))), node->numtime);
		node->links = stats->st_nlink;
		node->user = getpwuid(stats->st_uid)->pw_name;
		node->group = getgrgid(stats->st_gid)->gr_name;
		node->size = stats->st_size;
	}
	node->name = current;
	node->next = NULL;
	node->last = NULL;
	return (node);
}

char *get_mode(struct stat *stats)
{
	char *mode;
	int n;

	n = 0;
	if (!(mode = malloc(sizeof(char) * 11)))
		return (NULL);
	mode[n++] = S_ISDIR(stats->st_mode) ? 'd' : '-';
	mode[n++] = (stats->st_mode & S_IRUSR) ? 'r' : '-';
	mode[n++] = (stats->st_mode & S_IWUSR) ? 'w' : '-';
	mode[n++] = (stats->st_mode & S_IXUSR) ? 'x' : '-';
	mode[n++] = (stats->st_mode & S_IRGRP) ? 'r' : '-';
	mode[n++] = (stats->st_mode & S_IWGRP) ? 'w' : '-';
	mode[n++] = (stats->st_mode & S_IXGRP) ? 'x' : '-';
	mode[n++] = (stats->st_mode & S_IROTH) ? 'r' : '-';
	mode[n++] = (stats->st_mode & S_IWOTH) ? 'w' : '-';
	mode[n++] = (stats->st_mode & S_IXOTH) ? 'x' : '-';
	mode[n] = '\0';
	return (mode);
}

char	*get_extra(struct stat *stats, char *mode)
{
	if (!mode)
		return (NULL);
	int n;
	n = 0;
	if (stats->st_mode & S_ISUID)
		(mode[3] == '-') ? (mode[3] = 'S') : (mode[3] = 's');
	if (stats->st_mode & S_ISGID)
		(mode[6] == '-') ? (mode[6] = 'S') : (mode[6] = 's');
	if (stats->st_mode & 0001000)
		(mode[9] == '-') ? (mode[9] = 'T') : (mode[9] = 't');
	if (S_ISLNK(stats->st_mode))
		mode[0] = 'l';
	return (mode);
}

//	   		  *  HEAD  *	       *NEW*	 	*   TAIL  *	   ( -t  <-> Else lexi )
int link_me(t_data **head, t_data *new_node, t_data **tail, int flag)
{
	t_data *temp;

	if (!(*head))
	{
		*head = new_node; //*head = *tail = malloc(sizeof(t_data));
		*tail = new_node;
		return (1);
	}
	else
	{
		temp = *head;
		while (temp->next && (NAME_TIME > 0))
		{
			temp = temp->next;
		}
		if (NAME_TIME < 0)
		{
			new_node->next = temp;
			new_node->last = temp->last;
			if (!(temp->last))
				*head = new_node;
			else
				temp->last->next = new_node;
			temp->last = new_node;
		}
		else
		{
			new_node->next = temp->next;
			new_node->last = temp;
			temp->next = new_node;
			if (!(new_node->next))
				*tail = new_node;
		}
	}
	return (1);
}
