/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:25:34 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 12:11:14 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "enum.h"
# include "define.h"
# include "libft.h"

/*
*****************************************************
********************** COMMON ***********************
*****************************************************
*/

typedef uint64_t				t_option;

typedef struct					s_opt
{
	char						*command_str;
	t_option					option;
}								t_opt;

typedef struct					s_variable
{
	char						*name;
	char						*data;
	t_option					flag;
}								t_variable;

typedef	struct					s_hashmap
{
	t_hash						bin;
	t_hash						blt;
}								t_hashmap;

typedef struct					s_registry
{
	const char					**grammar;
	const char					**grammar_m;
	t_list						*intern;
	t_opt						option;
	t_hashmap					hash;
	pid_t						pid;
	t_list						*job_list;
	uint64_t					active_jobs;
	uint8_t						job_notified;
	t_list						*current_plus;
	t_list						*current_minus;
	uint8_t						sigint;

	struct termios				*sle_ios;
	struct termios				*orig_ios;
	struct termios				*exe_ios;
}								t_registry;

extern t_registry				*g_shell;

/*
*****************************************************
*********************** LEXER ***********************
*****************************************************
*/

typedef struct					s_token
{
	char						*data;
	int							type;
}								t_token;

typedef struct					s_lexer
{
	t_list						*tokens;
	t_vector					*buffer;
	t_vector					*input;
	size_t						index;
	enum e_lexer_state			state;
	enum e_mtype				last_token_mtype;
	enum e_type					token_type;
	enum e_type					last_token_type;
	enum e_mtype				token_mtype;
	uint8_t						assignation;
}								t_lexer;

/*
*****************************************************
********************** PARSER ***********************
*****************************************************
*/

typedef struct					s_graph
{
	enum e_type					*good_type;
}								t_graph;

/*
*****************************************************
********************** ANALYZER *********************
*****************************************************
*/

typedef struct s_analyze		t_analyze;
typedef void					(*t_analyzing)(t_analyze *);
typedef t_analyzing				t_analyzer[ANALYZER_STATES][NB_OF_TOKENS];
typedef struct s_redirect		t_redirect;
typedef struct s_action			t_action;

typedef int						(*t_set_redirect)(t_redirect *, t_action *);
typedef t_set_redirect			t_redirection[REDIRECT_ACTION];

struct							s_redirect
{
	int32_t						from;
	int32_t						to;
	uint16_t					type;
};

struct							s_action
{
	enum e_actions				type;
	t_list						*data;
};

typedef	struct					s_command
{
	t_list						*av;
	t_list						*actions;
	uint8_t						type;
}								t_command;

typedef struct					s_group
{
	uint8_t						type;
	t_list						*command_list;
}								t_group;

typedef struct					s_process
{
	char						**av;
	t_list						*env;
	t_list						*pipe;
	t_list						*redirects;
	uint32_t					type;
	uint32_t					id;
	pid_t						pid;
	pid_t						*pgid;
	uint16_t					status;
	uint8_t						completed;
	uint8_t						stopped;
}								t_process;

typedef struct					s_job
{
	pid_t						pgid;
	t_list						*processes;
	uint8_t						state;
	uint8_t						type;
	uint32_t					signo;
	uint64_t					id;
	char						current;
	struct termios				*term_modes;
}								t_job;

struct							s_analyze
{
	t_list						**tokens;
	t_stack						stack;
	t_stack						tree_node;
	t_token						token;
	unsigned int				special_case;
	enum e_analyzer_state		last_state;
	enum e_analyzer_state		state;
	int							valid;
};

/*
*****************************************************
************************ SLE ************************
*****************************************************
*/

typedef struct					s_coord
{
	uint64_t					x;
	uint64_t					y;
}								t_coord;

typedef struct					s_termcaps
{
	char						*clear_line;
	char						*clear_screen;
	char						*standout_on;
	char						*standout_off;
	char						*clear;
	char						*down;
	char						*right;
	char						*left;
	char						*up;
	char						*hidden_cursor;
	char						*normal_cursor;
}								t_termcaps;

typedef struct					s_prompt
{
	uint64_t					length;
	char						*state;
	char						*missing_char;
}								t_prompt;

typedef struct					s_cursor
{
	uint64_t					x;
	uint64_t					y;
	uint64_t					x2;
	uint64_t					y2;
	uint64_t					x3;
	uint64_t					y3;
	uint64_t					index;
}								t_cursor;

typedef struct					s_window
{
	uint32_t					rows;
	uint32_t					cols;
	uint32_t					rd_flag;
	uint64_t					max_chars;
	uint64_t					point_cursor;
	uint64_t					point1;
	uint64_t					point2;
	t_vector					*displayed_line;
}								t_window;

typedef struct					s_redrawinfo
{
	uint64_t					line_len;
	uint64_t					disp_len;
	uint64_t					prompt_len;
}								t_redrawinfo;

typedef struct					s_intern
{
	t_vector					*ps1;
	t_vector					*ps2;
	t_vector					*ps3;
	t_vector					*pwd;
	t_vector					*username;
	t_vector					*home;
}								t_intern;

typedef struct					s_sle
{
	int64_t						vis_start;
	int64_t						vis_stop;
	uint64_t					ak_masks[AK_AMOUNT];
	uint16_t					search_type;
	uint8_t						state;
	int8_t						(*actionkeys[AK_AMOUNT])
										(t_registry *shell, struct s_sle *sle);
	t_termcaps					termcaps;
	t_window					window;
	t_prompt					prompt;
	t_cursor					cursor;
	t_redrawinfo				rd_info;
	t_intern					interns;
	t_vector					*line;
	t_vector					*sub_line;
	t_vector					*heredocln;
	t_vector					*search_hit;
	t_vector					*line_save;
	t_vector					*clip;
}								t_sle;

typedef int8_t					(*t_actionkeys)(t_registry *shell, t_sle *sle);

/*
*****************************************************
********************** BUILTIN **********************
*****************************************************
*/

typedef int						(*t_builtin) (t_list *, char **);
typedef t_option				(*t_get_option)(char *s, t_option option);
typedef uint8_t					(*t_test_cb)(void *, void *, uint8_t);

/*
*****************************************************
********************** RESOLVE **********************
*****************************************************
*/

extern t_list					*g_job_head;

/*
*****************************************************
********************** HISTORY **********************
*****************************************************
*/

typedef struct s_entry			t_entry;

typedef struct					s_param
{
	int							first;
	int							last;
	int							fd;
}								t_param;

struct							s_entry
{
	t_entry						*next;
	t_entry						*prev;
	char						*cmd;
};

typedef struct					s_history
{
	t_entry						*entry;
	t_entry						*head_ptr;
	int							nb_of_entries;
	int							first_search;
}								t_history;

/*
*****************************************************
******************** AUTOCOMPLETION *****************
*****************************************************
*/

typedef struct s_autocomplete	t_autocomplete;
typedef void					(t_completion_fct)(char *
								, t_autocomplete *, t_registry *);

struct							s_autocomplete
{
	t_list						*list;
	size_t						nb;
	size_t						max_len;
	enum e_result_type			type;
	size_t						index;
};

/*
*****************************************************
********************* EXPANSION *********************
*****************************************************
*/

typedef struct s_parameter		t_parameter;
typedef void					(*t_paramexp)(t_parameter *);
typedef int						(*t_advanced_pex)(t_list *, t_parameter *, int);

typedef struct					s_pex_token
{
	enum e_paramexp				type;
	char						*data;
}								t_pex_token;

struct							s_parameter
{
	t_vector					*buffer;
	t_list						*tokens;
	char						*expanded;
	char						*source;
	size_t						index;
	uint8_t						modifier;
	enum e_paramexp				state;
};

typedef struct s_arithmetic		t_arithmetic;
typedef void					(*t_arithmexp)(t_arithmetic *);
typedef t_arithmexp				t_ar_analyzer[MATH_STATE][MATH_TOKEN];
typedef enum e_mathstate		t_mathstate;

typedef union					u_value
{
	int64_t						digit;
	uint64_t					type;
}								t_value;

typedef struct					s_rpn_tk
{
	enum e_rpn					type;
	t_value						value;
}								t_rpn_tk;

typedef struct					s_infix
{
	uint8_t						type;
	int64_t						result;
	t_stack						calcul;
}								t_infix;

struct							s_arithmetic
{
	t_vector					*input;
	char						*expanded;
	t_list						*tokens;
	t_list						*current;
	t_token						*curr_token;
	t_stack						processing;
	t_list						*solving;
	int							parenthesis;
	t_mathstate					state;
	size_t						end;
};

typedef struct					s_math
{
	t_vector					*input;
	t_list						*tokens;
	t_token						*current_token;
	t_stack						sign;
	t_stack						operand;
	char						*expanded;
}								t_math;

#endif
