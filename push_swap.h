#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "./libft/libft.h"

typedef struct s_env
{
	t_list	*group;
	t_list	*st_a;
	t_list	*st_b;
	int		nexti;
}				t_env;

typedef struct s_group
{
	int	max;
	int	min;
	int	mid;
}				t_group;

typedef struct s_number
{
	t_group	*group;
	int		number;
	int		index;
}				t_number;

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

void	ft_littlsort(t_env *env, int argc);
void	ft_get_position(t_env *env, t_list *tmp1);
void	ft_littlsearch(t_env *env, t_list *tmp1, t_list *tmp2);
int		ft_condition(t_env *env, t_list *tmp1, t_list *tmp2);

void	ft_btoa(t_env *env);
void	ft_sort(t_env *env, int index);
void	ft_addnewgroup(t_list *stack);
int		ft_calcmax(t_list *stack);
int		ft_calcmin(t_list *stack);
void	ft_atob(t_env *env);
void	ft_pop(t_env *env);
void	ft_makelems(t_env *anb, int argc, char **args);
t_group	*ft_create_group(t_env *env, int max, int min);
void	ft_indexmaker(t_number *n1, int counter);
int		ft_cmp(t_number *n1, t_number *n2);
void	ft_exit(t_env *env);
void	ft_free(t_env *env);

#endif