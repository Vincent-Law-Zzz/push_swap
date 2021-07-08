#include "push_swap.h"

void	ft_indexmaker(t_number *n1, int counter)
{
	n1->index = counter + 1;
}

t_group	*ft_create_group(t_env *env, int max, int min)
{
	t_group	*group;

	group = ft_calloc(1, sizeof(t_group));
	group->max = max;
	group->min = min;
	group->mid = (max - min) / 2 + min;
	if (ft_lstadd_back_content(&env->group, group) == NULL)
		ft_exit(env);
	return (group);
}

void	ft_makelems(t_env *anb, int argc, char **args)
{
	int			i;
	t_number	*number;
	t_list		*sorted_list;

	i = 1;
	sorted_list = 0;
	ft_create_group(anb, argc - 1, 1);
	while (i < argc)
	{
		number = ft_calloc(1, sizeof(t_number));
		number->number = ft_atoi(args[i]);
		number->group = anb->group->content;
		if (ft_lstadd_back_content(&anb->st_a, number) == NULL)
			ft_exit(anb);
		if (ft_lstadd_content_by_cond(&sorted_list, number, \
			(int (*)(void *, void *))ft_cmp) == NULL)
			ft_exit(anb);
		i++;
	}
	ft_lstiteri(sorted_list, (void (*)(void *, int))ft_indexmaker);
	ft_lstclear(&sorted_list, NULL);
}

void	ft_pop(t_env *env)
{
	t_list	*lst;

	lst = env->st_a;
	while (lst && ((t_number *)lst->content)->group != NULL)
		lst = lst->next;
	while (lst && lst->next && ((t_number *)lst->content)->group == NULL)
	{
		if (((t_number *)lst->next->content)->group != NULL && \
			((t_number *)lst->next->content)->index == env->nexti)
			((t_number *)lst->next->content)->group = NULL;
		lst = lst->next;
	}
	while (((t_number *)(ft_lstlast(env->st_a))->content)->group \
		!= NULL && env->nexti > 1)
		ft_rra(env);
}

void	ft_atob(t_env *env)
{
	t_group	*tmp;
	t_group	*tmpn;
	int		i;
	int		index;

	i = 0;
	tmp = (t_group *)((t_number *)((t_list *)env->st_a)->content)->group;
	tmpn = (t_group *)((t_number *)((t_list *)env->st_a->next)->content)->group;
	while (i <= (tmp->mid - tmp->min) && tmp == tmpn && tmp && tmpn)
	{
		index = ((t_number *)env->st_a->content)->index;
		tmp = (t_group *)((t_number *)((t_list *)env->st_a)->content)->group;
		tmpn = (t_group *)((t_number *)((t_list *) \
			env->st_a->next)->content)->group;
		if (index <= tmp->mid)
		{
			ft_pb(env);
			i++;
		}
		else
			ft_ra(env);
	}
}
