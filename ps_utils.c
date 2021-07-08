#include "push_swap.h"

void	ft_pa(t_env *env)
{
	t_list	*tmp;

	tmp = NULL;
	if (!env->st_b)
		return ;
	if (!env->st_b->next)
	{
		ft_lstadd_front(&env->st_a, env->st_b);
		env->st_b = NULL;
	}
	else
	{
		tmp = env->st_b;
		env->st_b = env->st_b->next;
		ft_lstadd_front(&env->st_a, tmp);
	}
	write(1, "pa\n", 3);
}

void	ft_pb(t_env *env)
{
	t_list	*tmp;

	tmp = NULL;
	if (!env->st_a)
		return ;
	if (!env->st_a->next)
	{
		ft_lstadd_front(&env->st_b, env->st_a);
		env->st_a = NULL;
	}
	else
	{
		tmp = env->st_a;
		env->st_a = env->st_a->next;
		ft_lstadd_front(&env->st_b, tmp);
	}
	write(1, "pb\n", 3);
}

void	ft_sa(t_env *env)
{
	t_list	*tmp;

	tmp = NULL;
	if (!env->st_a || !env->st_a->next)
		return ;
	tmp = env->st_a->next->next;
	ft_lstadd_front(&env->st_a, env->st_a->next);
	env->st_a->next->next = tmp;
	write(1, "sa\n", 3);
}

void	ft_sb(t_env *env)
{
	t_list	*tmp;

	tmp = NULL;
	if (!env->st_b || !env->st_b->next)
		return ;
	tmp = env->st_b->next->next;
	ft_lstadd_front(&env->st_b, env->st_b->next);
	env->st_b->next->next = tmp;
	write(1, "sb\n", 3);
}

void	ft_ss(t_env *env)
{
	ft_sa(env);
	ft_sb(env);
	write(1, "(equiv. to ss)\n", 16);
}
