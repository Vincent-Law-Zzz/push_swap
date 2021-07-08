#include "push_swap.h"

void	ft_rr(t_env *env)
{
	ft_ra(env);
	ft_rb(env);
	write(1, "(equiv. to rr)\n", 16);
}

void	ft_ra(t_env *env)
{
	t_list	*tmp;

	tmp = NULL;
	if (!env->st_a || !env->st_a->next)
		return ;
	tmp = env->st_a;
	env->st_a = env->st_a->next;
	tmp->next = NULL;
	ft_lstadd_back(&env->st_a, tmp);
	write (1, "ra\n", 3);
}

void	ft_rb(t_env *env)
{
	t_list	*tmp;

	tmp = NULL;
	if (!env->st_b || !env->st_b->next)
		return ;
	tmp = env->st_b;
	env->st_b = env->st_b->next;
	tmp->next = NULL;
	ft_lstadd_back(&env->st_b, tmp);
	write (1, "rb\n", 3);
}
