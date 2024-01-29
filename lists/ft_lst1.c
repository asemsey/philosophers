/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:00:55 by asemsey           #+#    #+#             */
/*   Updated: 2024/01/29 15:10:58 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_list
{
	int				content;
	int				pos;
	int				moves;
	struct s_list	*target;
	struct s_list	*next;
}	t_list;

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	node = *lst;
	node = ft_lstlast(node);
	node->next = new;
}

t_list	*ft_lstnew(int content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	if (!content)
	{
		node->content = 0;
		node->next = NULL;
		return (node);
	}
	node->content = content;
	node->next = NULL;
	return (node);
}

t_list	*ft_lst(int *n, unsigned int len)
{
	t_list			*lst;
	unsigned int	i;

	i = 0;
	if (len >= 1)
		lst = ft_lstnew(n[i++]);
	while (i < len)
		ft_lstadd_back(&lst, ft_lstnew(n[i++]));
	return (lst);
}

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		ft_putnbr(lst->content);
		write(1, " ", 1);
		lst = lst->next;
	}
	write(1, "\n", 1);
}

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	free_lst(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}
