#include "push_swap.c"

void	ft_sa(t_env *env)
{
	t_list *tmp;

	tmp = NULL;
	if (!env->st_a || !env->st_a->next)
		return ;
	tmp = env->st_a->next;
	env->st_a->next = env->st_a;
	env->st_a = tmp;
	write(1, "sa ", 3);
}

void	ft_sb(t_env *env)
{
	t_list *tmp;

	tmp = NULL;
	if (!env->st_b || !env->st_b->next)
		return ;
	tmp = env->st_b->next;
	env->st_b->next = env->st_b;
	env->st_b = tmp;
	write(1, "sb ", 3);
}

void	ft_ss(t_env *env)
{
	ft_sa(env);
	ft_sb(env);
	write(1, "(equiv. to ss)", 15);
}

void 	ft_pa(t_env *env)
{
	t_list *tmp;

	tmp = NULL;
	if (!env->st_b)
		return ;
	tmp = env->st_b->next;
	ft_lstadd_front(&env->st_a, env->st_b);
	env->st_b = tmp;
	write (1, "pa ", 3);
}

void 	ft_pb(t_env *env)
{
	t_list *tmp;

	tmp = NULL;
	if (!env->st_a)
		return ;
	tmp = env->st_a->next;
	ft_lstadd_front(&env->st_b, env->st_a);
	env->st_a = tmp;
	write (1, "pb ", 3);
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
	write (1, "ra ", 3);
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
	write (1, "rb ", 3);
}

void	ft_rr(t_env *env)
{
	ft_ra(env);
	ft_rb(env);
	write(1, "(equiv. to rr)", 15);
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
	write (1, "rra ", 4);
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
	write (1, "rrb ", 4);
}

void	ft_rrr(t_env *env)
{
	ft_rra(env);
	ft_rrb(env);
	write(1, "(equiv. to rrr)", 16);
}