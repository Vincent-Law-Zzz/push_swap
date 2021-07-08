#include "push_swap.h"

int	ft_calcmin(t_list *stack)
{
	t_list	*tmp;
	int		min;

	min = ((t_number *)stack->content)->index;
	tmp = stack;
	while (tmp)
	{
		if (min > ((t_number *)tmp->content)->index)
			min = ((t_number *)tmp->content)->index;
		tmp = tmp->next;
	}
	return (min);
}

int	ft_calcmax(t_list *stack)
{
	t_list	*tmp;
	int		max;

	max = ((t_number *)stack->content)->index;
	tmp = stack;
	while (tmp)
	{
		if (max < ((t_number *)tmp->content)->index)
			max = ((t_number *)tmp->content)->index;
		tmp = tmp->next;
	}
	return (max);
}

void	ft_addnewgroup(t_list *stack)
{
	t_list	*tmp;
	t_group	*g;
	t_group	*nextg;
	int		min;

	tmp = stack;
	g = ((t_number *)tmp->content)->group;
	if (!g)
		return ;
	nextg = ((t_number *)tmp->next->content)->group;
	min = g->mid;
	while (((t_number *)tmp->content)->group != NULL && g == nextg)
	{
		g->min = min;
		g->mid = (g->max - g->min) / 2 + g->min;
		tmp = tmp->next;
		g = ((t_number *)tmp->content)->group;
		nextg = ((t_number *)tmp->next->content)->group;
	}
}

void	ft_sort(t_env *env, int index)
{
	if (index == env->nexti)
	{
		((t_number *)env->st_b->content)->group = NULL;
		ft_pa(env);
		ft_ra(env);
		env->nexti = env->nexti + 1;
	}
	else
		ft_rb(env);
}

void	ft_btoa(t_env *env)
{
	t_group		*tmp;
	t_number	*number;
	int			count;

	while (env->st_b)
	{
		tmp = ft_create_group(env, ft_calcmax(env->st_b), \
			ft_calcmin(env->st_b));
		count = ft_lstsize(env->st_b);
		while (count-- && env->st_b)
		{
			number = ((t_number *)env->st_b->content);
			if (number->index > tmp->mid)
			{
				number->group = tmp;
				ft_pa(env);
			}
			else if (number->index <= tmp->mid)
				ft_sort(env, number->index);
		}
	}
}
