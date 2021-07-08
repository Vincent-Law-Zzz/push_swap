#include "push_swap.h"

int	ft_condition(t_env *env, t_list *tmp1, t_list *tmp2)
{
	if (tmp1 && ((t_number *)tmp1->content)->index == env->nexti)
		return (1);
	else if (tmp1 && tmp1->next && ((t_number *) \
		tmp1->next->content)->index == env->nexti)
		return (2);
	else if (tmp2 && ((t_number *)tmp2->content)->index == env->nexti)
		return (3);
	else if (tmp2 && tmp2->next && \
		((t_number *)tmp2->next->content)->index == env->nexti)
		return (4);
	return (0);
}

void	ft_littlsearch(t_env *env, t_list *tmp1, t_list *tmp2)
{
	if (ft_condition(env, tmp1, tmp2) == 1)
		ft_ra(env);
	else if (ft_condition(env, tmp1, tmp2) == 2)
	{
		ft_sa(env);
		ft_ra(env);
	}
	else if (ft_condition(env, tmp1, tmp2) == 3)
	{
		ft_pa(env);
		ft_ra(env);
	}
	else if (ft_condition(env, tmp1, tmp2) == 4)
	{
		ft_sb(env);
		ft_pa(env);
		ft_ra(env);
	}
	else
	{
		ft_pb(env);
		return ;
	}
	env->nexti = env->nexti + 1;
}

void	ft_get_position(t_env *env, t_list *tmp1)
{
	if (((t_number *)tmp1->content)->index == 1)
		ft_ra(env);
	else if (tmp1->next && ((t_number *)tmp1->next->content)->index == 1)
	{
		ft_sa(env);
		ft_ra(env);
	}
	else if (tmp1->next && tmp1->next->next && \
		((t_number *)tmp1->next->next->content)->index == 1)
	{
		ft_rra(env);
		ft_rra(env);
	}
	else if (tmp1->next && tmp1->next->next->next && ((t_number *) \
		tmp1->next->next->next->content)->index == 1)
		ft_rra(env);
	env->nexti = env->nexti + 1;
}

void	ft_littlsort(t_env *env, int argc)
{
	t_list	*tmp1;
	t_list	*tmp2;
	int		flag;

	flag = 0;
	tmp1 = env->st_a;
	tmp2 = env->st_b;
	ft_get_position(env, tmp1);
	while (env->nexti < argc)
	{
		tmp1 = env->st_a;
		tmp2 = env->st_b;
		ft_littlsearch(env, tmp1, tmp2);
	}
}
