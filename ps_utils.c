#include "push_swap.h"

void	ft_pa(t_env *env)
{
	t_list *tmp;

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
	t_list *tmp;

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
	t_list *tmp;

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
	t_list *tmp;

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

void	ft_ra(t_env *env)
{
	t_list *tmp;

	tmp = NULL;
	if (!env->st_a || !env->st_a->next)
		return ;
	tmp = env->st_a;
	env->st_a = env->st_a->next;
	tmp->next = NULL;
	ft_lstadd_back(&env->st_a,tmp);
	write (1, "ra\n", 3);
}

void	ft_rb(t_env *env)
{
	t_list *tmp;

	tmp = NULL;
	if (!env->st_b || !env->st_b->next)
		return ;
	tmp = env->st_b;
	env->st_b = env->st_b->next;
	tmp->next = NULL;
	ft_lstadd_back(&env->st_b,tmp);
	write (1, "rb\n", 3);
}

void	ft_rr(t_env *env)
{
	ft_ra(env);
	ft_rb(env);
	write(1, "(equiv. to rr)\n", 16);
}

void	ft_rra(t_env *env)
{
	t_list *tmp;
	t_list *end;

	if (!env->st_a || !env->st_a->next)
		return ;
	end = env->st_a;
	while (end->next)
	{
		tmp = end;
		end = end->next;
	}
	ft_lstadd_front(&env->st_a, end);
	tmp->next = NULL;
	write (1, "rra\n", 4);
}

void	ft_rrb(t_env *env)
{
	t_list *tmp;
	t_list *end;

	if (!env->st_b || !env->st_b->next)
		return ;
	end = env->st_b;
	while (end->next)
	{
		tmp = end;
		end = end->next;
	}
	ft_lstadd_front(&env->st_b, end);
	tmp->next = NULL;
	write (1, "rrb\n", 4);
}

void	ft_rrr(t_env *env)
{
	ft_rra(env);
	ft_rrb(env);
	write(1, "(equiv. to rrr)\n", 17);
}