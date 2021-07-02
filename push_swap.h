#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include "./libft/libft.h"


typedef struct  s_env
{
    t_list *group;
    t_list *st_a;
    t_list *st_b;
	int	nexti;
}               t_env;

typedef struct  s_group
{
    int max;
    int min;
    int mid;
}               t_group;

typedef struct s_number
{
	t_group *group;
    int number;
    int index;
}               t_number;

void	ft_pa(t_env *env);
void	ft_pb(t_env *env);
void	ft_sa(t_env *env);
void	ft_sb(t_env *env);
void	ft_ss(t_env *env);
void	ft_ra(t_env *env);
void	ft_rb(t_env *env);
void	ft_rr(t_env *env);
void	ft_rra(t_env *env);
void	ft_rrb(t_env *env);
void	ft_rrr(t_env *env);

#endif