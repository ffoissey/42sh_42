/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:33:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/06 16:27:19 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

/*
*****************************************************
********************** BUILTIN **********************
*****************************************************
*/

enum	e_state_option
{
	E_START_OPTION,
	E_OPTION,
	E_END_OPTION,
	E_NO_OPTION
};

/*
*****************************************************
*********************** LEXER ***********************
*****************************************************
*/

enum	e_lexer_state
{
	L_PROCESS,
	L_OUT,
	L_FINISH
};

typedef enum	e_type
{
	E_PIPE,
	E_GREAT,
	E_LESS,
	E_SEMICOLON,
	E_AND,
	E_NEWLINE,
	E_DAND,
	E_OR,
	E_DLESS,
	E_DGREAT,
	E_LESSAND,
	E_GREATAND,
	E_ANDDGREAT,
	E_ANDGREAT,
	E_DLESSDASH,
	E_IO_NUMBER,
	E_ASSIGN,
	E_STRING,
	E_END,
	E_ERROR,
	E_DEFAULT
}				t_type;

typedef enum	e_mtype
{
	E_M_TIMES,
	E_M_DIVIDE,
	E_M_MODULO,
	E_M_PLUS,
	E_M_MINUS,
	E_M_OPENP,
	E_M_CLOSEP,
	E_M_LESS,
	E_M_LESSEQ,
	E_M_GREAT,
	E_M_GREATEQ,
	E_M_EQUAL,
	E_M_NEQUAL,
	E_M_AND,
	E_M_OR,
	E_M_DPLUS,
	E_M_DMINUS,
	E_M_ASSIGN,
	E_M_STRING,
	E_M_NB_DEC,
	E_M_NB_OCT,
	E_M_NB_HEX,
	E_M_DELIMITER,
	E_M_END,
	E_M_DEFAULT
}				t_mtype;

/*
*****************************************************
********************** ANALYZER *********************
*****************************************************
*/

typedef enum	e_quote
{
	QUOTE_OFF,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_BACKSLASH,
}				t_quote;

enum			e_actions
{
	A_STDOUT_TRUNCATE_FILE,
	A_STDOUT_TRUNCATE_FILE_SPECIAL,
	A_STDOUT_APPEND_FILE,
	A_STDIN_READ_FILE,
	A_STDIN_READ_FD,
	A_IO_TRUNCATE_FILE,
	A_IO_APPEND_FILE,
	A_IO_READ_FILE,
	A_IO_READ_FD,
	A_DUP,
	A_CLOSE,
	A_MOVE,
	A_HEREDOC,
	A_HEREDOC_TRIM,
	A_IO_HEREDOC,
	A_IO_HEREDOC_TRIM,
	A_AMBIGOUS_REDIRECT,
	A_BAD_FILEDESC,
	A_ARGS,
	A_ASSIGN,
	A_AND,
	A_DAND,
	A_OR,
	A_END,
};

enum	e_analyzer_state
{
	P_START,
	P_END,
	P_STOP,
	P_ERROR,
	P_STRING,
	P_STRING_FLUSH,
	P_REDIRECT,
	P_REDIRECT_AND,
	P_DUP_MOVE,
	P_REDIRECT_FLUSH,
	P_REDIRECT_FLUSH_AND,
	P_FILENAME,
	P_IO,
	P_IO_REDIRECT,
	P_IO_REDIRECT_AND,
	P_IO_FILENAME,
	P_IO_DUP_MOVE,
	P_IO_FLUSH,
	P_IO_FLUSH_AND,
	P_PIPE,
	P_HEREDOC,
	P_HEREDOC_REDIRECT,
	P_HEREDOC_DELIMITER,
	P_IO_HEREDOC,
	P_IO_HEREDOC_REDIRECT,
	P_IO_HEREDOC_DELIMITER,
	P_ASSIGN_NAME,
	P_ASSIGN_DATA,
	P_ASSIGN_FLUSH,
};

/*
*****************************************************
************************ SLE ************************
*****************************************************
*/

enum	e_prompt_type
{
	PRINT_PIPE,
	PRINT_QUOTE,
	PRINT_DQUOTE,
	PRINT_BQUOTE,
	PRINT_NL,
	PRINT_AND,
	PRINT_OR,
	PRINT_BRACE,
	PRINT_MATHS
};

enum	e_action_keys
{
	AK_ARROW_UP,
	AK_ARROW_DOWN,
	AK_ARROW_RIGHT,
	AK_ARROW_LEFT,
	AK_HOME,
	AK_END,
	AK_CTRL_A,
	AK_CTRL_E,
	AK_BACKSPACE,
	AK_DELETE,
	AK_CTRL_LEFT,
	AK_CTRL_RIGHT,
	AK_CTRL_DOWN,
	AK_CTRL_UP,
	AK_CTRL_D,
	AK_CTRL_L,
	AK_ESCAPE,

	AK_ALT_V,
	AK_ALT_C,
	AK_ALT_X,
	AK_ALT_P,

	AK_CTRL_R,
	AK_CTRL_T,
	AK_TABULATION,
};

/*
*****************************************************
******************** AUTOCOMPLETION *****************
*****************************************************
*/

enum	e_result_type
{
	CMD_TYPE,
	VARIABLE_TYPE,
	VARIABLE_BRACKET_TYPE,
	FILE_TYPE
};

/*
*****************************************************
*********************** EXPANSION *******************
*****************************************************
*/

enum	e_mathstate
{
	MATH_START,
	MATH_NUMBER,
	MATH_UNARY,
	MATH_OPERATOR,
	MATH_LOGICAL_OPERATOR,
	MATH_PREFFIX,
	MATH_SUFFIX,
	MATH_VARIABLE,
	MATH_VARIABLE_FLUSH,
	MATH_OPEN_PARENT,
	MATH_CLOSE_PARENT,
	MATH_ERROR,
	MATH_END
};

enum	e_rpn
{
	RPN_OPERATOR,
	RPN_PARENT_OPEN,
	RPN_PARENT_CLOSE,
	RPN_NUMBER,
};

enum	e_paramexp
{
	PEX_PARAM,
	PEX_DELIM,
	PEX_WORD,
	PEX_END
};

#endif
