/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:47:20 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/24 14:52:36 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include "libft.h"

# define ENV			t_environment
# define INS			t_inslist
# define STDOUT			1
# define STDIN			0
# define NB_INS			11
# define NB_PAT			32
# define SUCCESS		">>>>>>>> OK <<<<<<<<"
# define FAILURE		">>>>>>>> KO <<<<<<<<"
# define SWITCH_SORT	20

/*
** USER OPTIONS
*/
# define OPT_ANIM		(1 << ('a' - 'a'))
# define OPT_VERBOSE	(1 << ('v' - 'a'))
# define OPT_COLOR		(1 << ('c' - 'a'))
# define OPT_STACK		(1 << ('s' - 'a'))
# define OPT_INS		(1 << ('i' - 'a'))
# define OPT_LIST		(1 << ('l' - 'a'))
# define OPT_OPTI		(1 << ('o' - 'a'))
# define OPT_NUM		(1 << ('n' - 'a'))
# define OPT_HELP		(1 << ('h' - 'a'))
# define OPT_OFF		(1 << ('f' - 'a'))

/*
** ERRORS
*/

# define TYPE			5
# define MSG			11
# define ERR_WRNG		" --Warning-- "
# define ERR			"Error"
# define ERR_STACKA		"[STACK A]"
# define ERR_STACKB		"[STACK B]"
# define ERR_PROGRAM	"Program failure"
# define ERR_EMPTY		"Empty"
# define ERR_NUM		"Not a number"
# define ERR_UNDO		"Impossible to undo further | Back to beginning state"
# define ERR_INPUT		"Wrong input"
# define ERR_EFFECT		"Instruction without effect (not enough elements)"
# define ERR_DUP		"Duplicate value"
# define ERR_IMP		"Impossible operation"
# define ERR_ARG		"Missing argument"
# define ERR_RANGE		"Please enter number between -2147483648 and 2147843647"
# define ERR_WRONG		"This instruction does not exist"
# define ERR_ALLOC		"Failed allocation"
# define ERR_FNCTN		"Function failure"
# define ERR_OPT		"Unknown option | -h for detailed list"

/*
** SYNC PATTERNS
*/

# define PAT_SASB		"sa sb >>> ss"
# define PAT_SASB		"sa sb >>> ss"
# define PAT_SASS		"sa ss >>> sb"
# define PAT_SBSS		"sb ss >>> sa"
# define PAT_RRARR		"rra rr >>> rb"
# define PAT_RRBRR		"rrb rr >>> ra"
# define PAT_RARRR		"ra rrr >>> rrb"
# define PAT_RBRRR		"rb rrr >>> rra"

/*
** STANDARD COLORS
*/

# define COL_BLACK		"\033[22;30m"
# define COL_DRED		"\033[22;31m"
# define COL_GREEN		"\033[22;32m"
# define COL_BROWN		"\033[22;33m"
# define COL_BLUE		"\033[22;34m"
# define COL_PINK		"\033[22;35m"
# define COL_CYAN		"\033[22;36m"
# define COL_GREY		"\033[22;37m"
# define COL_DGREY		"\033[01;30m"
# define COL_LRED		"\033[01;31m"
# define COL_LGREEN		"\033[01;32m"
# define COL_YELLOW		"\033[01;33m"
# define COL_LBLUE		"\033[01;34m"
# define COL_LPINK		"\033[01;35m"
# define COL_LCYAN		"\033[01;36m"
# define COL_WHITE		"\033[01;37m"
# define COL_OFF		"\033[0m"

/*
** COLORS
*/

# define COL_STACKA		COL_WHITE
# define COL_STACKB		COL_DGREY
# define COL_OK			COL_LGREEN
# define COL_KO			COL_DRED
# define COL_WRNG		COL_YELLOW
# define COL_ERR		COL_LRED
# define COL_PAT		COL_LBLUE
# define COL_SYNC		COL_CYAN
# define COL_ROT		COL_BLUE
# define COL_MIR		COL_LCYAN
# define COL_NUM		COL_LPINK
# define COL_PLACE		COL_LGREEN
# define COL_INSERT		COL_GREEN

typedef struct		s_inslist
{
	t_list			*lst;
	t_list			*tail;
	char			ref[NB_INS][4];
}					t_inslist;

typedef struct		s_error
{
	int				type;
	int				stack;
	int				msg;
}					t_error;

typedef struct		s_environment
{
	t_inslist		*ins;
	t_list			*a;
	t_list			*b;
	t_error			err;
	void			(*op[NB_INS])(struct s_environment *, t_list **lst);
	char			pattern[NB_PAT][10];
	t_list			*(*opti[NB_PAT])(t_list *lst, int ins1, int ins2, int ins3);
	int				options;
	int				alen;
	int				blen;
	int				checker;
	int				fd;
	int				nb_runs;
	int				*runs;
	int				max;
	int				min;
	int				nb_ext;
	int				ins_val;
	char			*color;
}					t_environment;

enum				e_instructions
{
	PA, SA, RA, RR, RB, SS, RRB, RRR, RRA, SB, PB
};

enum				e_stacks
{
	A, B
};

enum				e_error_types
{
	NO_ERR, WRNG, PROGRAM, INPUT, IMPOSSIBLE
};

enum				e_error_msg
{
	MALLOC, FUNCTION, DUP, NUMBER, EMPTY, NOEFFECT, UNDO, NOARG, RANGE, WRONG,
	OPTION
};

enum				e_part
{
	BEG, END
};

enum				e_shortcut
{
	MIN, MAX, INSERTION
};

/*
** DISPLAY
*/

void				display_commands(ENV *e);
int					display_err(ENV *e);
int					display_ins(ENV *e, char *s, int fd);
int					display_mir(ENV *e, char *ins1, char *ins2);
int					display_opti(ENV *e, char *opti);
void				display_options(ENV *e, int ins, int option);
int					display_pat(ENV *e, t_list *l, int pat);
int					display_rot(ENV *e, int ins, int n1, int n2);
int					display_sync(ENV *e, char *sync);
int					display_shortcut(ENV *e, int val, int type);
void				display_help(ENV *e);
void				exe_and_display(ENV *e, int ins);
void				printlist(ENV *e, t_list *l);
void				show_stacks(ENV *e);

/*
** ENV & MEMORY
*/

int					ft_setenv(ENV *e);
int					freeenv(ENV *e);

/*
** INSTRUCTIONS
*/

void				sa(ENV *e, t_list **lst);
void				sb(ENV *e, t_list **lst);
void				ss(ENV *e, t_list **lst);
void				pa(ENV *e, t_list **lst);
void				pan(ENV *e, t_list **lst, int n);
void				pb(ENV *e, t_list **lst);
void				pbn(ENV *e, t_list **lst, int n);
void				ra(ENV *e, t_list **lst);
void				ran(ENV *e, t_list **lst, int n);
void				rb(ENV *e, t_list **lst);
void				rbn(ENV *e, t_list **lst, int n);
void				rr(ENV *e, t_list **lst);
void				rra(ENV *e, t_list **lst);
void				rran(ENV *e, t_list **lst, int n);
void				rrb(ENV *e, t_list **lst);
void				rrbn(ENV *e, t_list **lst, int n);
void				rrr(ENV *e, t_list **lst);

/*
** INPUT
*/

int					readarg(ENV *e, int argc, char **argv, int stop);
int					read_options(ENV *e, char **argv, int argc, int *num);

/*
** LISTS
*/

void				add(ENV *e, t_list **lst, int ins_ref);
void				addn(ENV *e, t_list **lst, int n, int ins_ref);
void				rem(t_list **lst);
void				remn(t_list **lst, int n);
void				remn_add(ENV *e, t_list **lst, int n, int ins);

/*
** OPTIMIZATION
*/

t_list				*gen_sync(ENV *e, t_list **lst, int *opti);
int					long_rot(ENV *e, t_list **l, int alen, int blen);
t_list				*opti_prr(t_list *lst, int ins1, int ins2, int ins3);
t_list				*opti_rs(t_list *lst, int ins1, int ins2, int ins3);
t_list				*opti_p(t_list *lst, int ins1, int ins2, int ins3);
t_list				*opti_s1(t_list *lst, int ins1, int ins2, int ins3);
t_list				*opti_s2(t_list *lst, int ins1, int ins2, int ins3);
int					relocate(t_list **lst);
t_list				*remmir(ENV *e, t_list **lst);
int					small_pattern(ENV *e, t_list *l, int mod, int pat);
int					sync_ins(ENV *e, t_list **l);
t_list				*tweak_inslist(ENV *e, t_list **lst, int *opti);
int					useless_rot(ENV *e, t_list **l, int alen, int blen);

/*
** SORTING
*/

int					sort(ENV *e);
int					full_sort(ENV *e);
int					rec_insertsorta(ENV *e, int next, int len, int beg);
int					rec_insertsortb(ENV *e, int next, int len, int beg);

/*
** UTILS
*/

void				delins(t_list **t1, t_list **t2);
int					firstany(t_list *l, int ins1, int ins2);
int					is_number(char *str);
int					index_max(t_list *l, int len);
int					index_min(t_list *l, int len);
int					getmed(t_list *l, int size);
int					list_size(t_list *lst);
int					place_min(ENV *e, t_list *l, int len, int ins);
int					place_max(ENV *e, t_list *l, int len, int ins);
int					sorted(ENV *e, t_list *s);
int					twofirst(t_list *l, int ins1, int ins2);
int					twofirstany(t_list *l, int ins1, int ins2);
int					val(t_list *lst, int pos);

/*
** ERROR
*/

int					error(ENV *e, int type, int stack, int msg);
int					check_error(ENV *e, int ins);

/*
** OPTIMIZATION PATTERNS FOR SAFE-KEEPING
**
** #define PAT_RBPARRB		"rb pa rrb >>> sb pa"
** #define PAT_RAPBRRA		"ra pb rra >>> sa pb"
** #define PAT_PBRAPA		"pb ra pa >>> sa ra"
** #define PAT_PARBPB		"pa rb pb >>> sb rb"
** #define	PAT_PBPBSB		"pb pb sb >>> sa pb pb"
** #define PAT_SAPBPB		"sa pb pb >>> pb sb sb"
** #define PAT_PBSBRB		"pb sb rb >>> rb pb"
** #define PAT_PASARA		"pa sa ra >>> ra pa"
** #define PAT_RAPARRA		"ra pa rra >>> pa sa"
** #define PAT_RBPBRRB		"rb pb rrb >>> pb sb"
** #define PAT_RAPBRRA		"ra pb rra >>> sa pb"
** #define PAT_RBPARRB		"rb pa rrb >>> sb pa"
** #define PAT_SAPBRA		"sa pb ra >>> ra pb"
** #define PAT_SBPARB		"sb pa rb >>> rb pa"
** #define PBRRAPA			"pb rra pa >>> rra sa"
** #define PARRBPB			"pa rrb pb >>> rrb sb"
** #define PARRASA			"pa rra sa >>> rra pa"
** #define PBRRBSB			"pb rrb sb >>> rrb pb"
** #define PASBPB			"pa sb pb >>> rb sb rrb"
** #define PBSAPA			"pb sa pa >>> ra sa rra"
** #define PBSBPA			"pb sb pa >>> pa sa pb"
** #define PASAPB			"pa sa pb >>> pb sb pa"
** #define RRASAPB			"rra sa pb >>> pb rra"
** #define RRBSBPA			"rrb sb pa >>> pa rrb"
** #define SARAPB			"sa ra pb >>> pb ra"
** #define SBRBPA			"sb rb pa >>> pa rb"
** #define PARRAPBPB		"pa rra pb pb >>> rra pb sb"
** #define PBRRBPAPA		"pb rrb pa pa >>> rrb pa sa"
*/
#endif
