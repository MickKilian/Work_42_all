/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/26 01:42:21 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_H
# define FT_LEXER_H

//# define EXIT_FAILURE "ft_Malloc failed"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <fcntl.h>
# include "get_next_line.h"

# define ERR_MALLOC "Error! Malloc"
# define ERR_NULLELEM "Error! List elem is NULL"
# define ERR_SYNTAX "Error! Syntax"
# define ERR_STRNULL "Error! String is NULL"
# define ERR_TESTFILE "Error! Reading file lexer.test"

typedef struct s_lex			t_lex;
typedef struct s_token			t_token;
typedef struct s_lex_proc		t_lex_proc;
typedef enum e_char_ascii		t_char_ascii;
typedef enum e_char_types		t_char_types;
typedef enum e_read_modes		t_read_modes;
typedef enum e_lex_actions		t_lex_actions;
typedef enum e_token_types		t_token_types;
typedef int						(*t_func)(t_lex *);

enum e_token_types
{
	NEW,
	WORD,
	//ASSIGNMENT_WORD,
	//NAME,
	NEW_LINE,
	SPL,
	DBL,
	LSS,
	GRT,
	GGRT,
	HEREDOC,
	PIPE,
	AMP,
	OP_OR,
	OP_AND,
	END_OF_INPUT,
	LEN_TOKEN_TYPES
};

enum e_char_types
{
	SEP_CHAR,
	STD_CHAR,
	SPL_CHAR,
	DBL_CHAR,
	ESCP_CHAR,
	PIPE_CHAR,
	AMP_CHAR,
	LT_CHAR,
 	GT_CHAR,
	END_CHAR,
	LEN_CHAR_TYPES
};

enum e_lex_actions
{
	CATCH,
	KEEP,
	DROP,
	TAKE,
	SKIP,
	END,
	SYNT_ERR,
	LEN_LEX_ACTIONS
};

enum e_read_modes
{
	NEW_MODE,
	STD_MODE,
	SPL_MODE,
	DBL_MODE,
	ESCP_MODE,
	PIPE_MODE,
	AMP_MODE,
	LT_MODE,
	GT_MODE,
	OR_MODE,
	AND_MODE,
	HEREDOC_MODE,
	GGRT_MODE,
	SYNT_ERR_MODE,
	LEN_READ_MODES
};

enum e_char_ascii
{
	NUL = 0,
	HTAB = 9,
	NL = 10,
	VTAB = 11,
	FFEED = 12,
	CRET = 13,
	SP = 32,
	EXCL = 33,
	QUOT = 34,
	POUND = 35,
	DOLLAR = 36,
	PERCNT = 37,
	COMAND = 38,
	APOS = 39,
	LPAR = 40,
	RPAR = 41,
	AST = 42,
	PLUS = 43,
	COMMA = 44,
	MINUS = 45,
	PERIOD = 46,
	SOL = 47,
	DIGIT_0 = 48,
	DIGIT_1 = 49,
	DIGIT_2 = 50,
	DIGIT_3 = 51,
	DIGIT_4 = 52,
	DIGIT_5 = 53,
	DIGIT_6 = 54,
	DIGIT_7 = 55,
	DIGIT_8 = 56,
	DIGIT_9 = 57,
	COLON = 58,
	SEMI = 59,
	LT = 60,
	EQUALS = 61,
	GT = 62,
	QUEST = 63,
	COMMAT = 64,
	CAPITAL_A = 65,
	CAPITAL_B = 66,
	CAPITAL_C = 67,
	CAPITAL_D = 68,
	CAPITAL_E = 69,
	CAPITAL_F = 70,
	CAPITAL_G = 71,
	CAPITAL_H = 72,
	CAPITAL_I = 73,
	CAPITAL_J = 74,
	CAPITAL_K = 75,
	CAPITAL_L = 76,
	CAPITAL_M = 77,
	CAPITAL_N = 78,
	CAPITAL_O = 79,
	CAPITAL_P = 80,
	CAPITAL_Q = 81,
	CAPITAL_R = 82,
	CAPITAL_S = 83,
	CAPITAL_T = 84,
	CAPITAL_U = 85,
	CAPITAL_V = 86,
	CAPITAL_W = 87,
	CAPITAL_X = 88,
	CAPITAL_Y = 89,
	CAPITAL_Z = 90,
	LSBQ = 91,
	ESCP = 92,
	RSQB = 93,
	CIRC = 94,
	LOWBAR = 95,
	GRAVE = 96,
	SMALL_A = 97,
	SMALL_B = 98,
	SMALL_C = 99,
	SMALL_D = 100,
	SMALL_E = 101,
	SMALL_F = 102,
	SMALL_G = 103,
	SMALL_H = 104,
	SMALL_I = 105,
	SMALL_J = 106,
	SMALL_K = 107,
	SMALL_L = 108,
	SMALL_M = 109,
	SMALL_N = 110,
	SMALL_O = 111,
	SMALL_P = 112,
	SMALL_Q = 113,
	SMALL_R = 114,
	SMALL_S = 115,
	SMALL_T = 116,
	SMALL_U = 117,
	SMALL_V = 118,
	SMALL_W = 119,
	SMALL_X = 120,
	SMALL_Y = 121,
	SMALL_Z = 122,
	LCUB = 123,
	VERBAR = 124,
	RCUB = 125,
	TILDE = 126,
	DELETE = 127,
};

struct s_lex_proc
{
	t_lex_actions	buffer_action;
	t_lex_actions	char_action;
	t_read_modes	read_mode;
	t_token_types	token_type;
};

struct s_lex
{
	char		*temp;
	int			nb_taken_char;
	char		*user_input;
	t_lex_proc	prev_decision;
	t_lex_proc	new_decision;
	t_lex_proc	decision[LEN_READ_MODES][LEN_CHAR_TYPES];
	char		*token_types[LEN_TOKEN_TYPES];
	t_func		ft[LEN_LEX_ACTIONS];
	int			nb_of_tokens;
	t_token		*token;
};

struct s_token
{
	char			*id;
	t_token_types	type;
	t_token			*prev;
	t_token			*next;
};

/* ************************************************************************** */
/*                                  lexer_main.c                              */
/* ************************************************************************** */
int				main(void);
int				ft_read_prompt(void);
int				ft_lexer(t_lex *lex);
int				ft_print_lexer_content(t_lex *lex);

/* ************************************************************************** */
/*                               initializations.c                            */
/* ************************************************************************** */
const char		*ft_getlabel_token_types(const t_token_types index);
int				ft_init_decisions(t_lex *lex);
/* ************************************************************************** */
/*                            lexer_memory.c                                  */
/* ************************************************************************** */
void			ft_bzero(void *s, size_t n);
int				ft_mallocator(void *ptr, size_t size);
int				ft_freeall(t_lex *lex);

/* ************************************************************************** */
/*                             lexer_error.c                                  */
/* ************************************************************************** */
int				ft_msgerr(char	*str);

/* ************************************************************************** */
/*                               list.c                                      */
/* ************************************************************************** */
t_token			*ft_new_token(char *str);
t_token			*ft_token_addnext(t_token *current, t_token *new);
t_token			*ft_token_jumpcurrent(t_token *prev, t_token *next);
int				ft_free_tokenlist(t_lex *lex);

/* ************************************************************************** */
/*                         lexer_init_decisions.c                             */
/* ************************************************************************** */
int				ft_init_decision_1(t_lex *lex);
int				ft_init_decision_2(t_lex *lex);
int				ft_init_decision_3(t_lex *lex);
int				ft_init_decision_4(t_lex *lex);
int				ft_init_decision_5(t_lex *lex);
int				ft_init_decision_6(t_lex *lex);
int				ft_init_decision_7(t_lex *lex);

/* ************************************************************************** */
/*                         lexer_apply_decision.c                            */
/* ************************************************************************** */
int				ft_apply_decision(t_lex *lex);
int				ft_print_lex_proc(t_lex_proc proc);

/* ************************************************************************** */
/*                            lexer_actions.c                                 */
/* ************************************************************************** */
int				ft_init_lex_actions(t_lex *lex);
int				ft_lex_catch(t_lex *lex);
int				ft_lex_keep(t_lex *lex);
int				ft_lex_drop(t_lex *lex);
int				ft_lex_take(t_lex *lex);
int				ft_lex_skip(t_lex *lex);
int				ft_lex_record(t_lex *lex);
int				ft_lex_end(t_lex *lex);
int				ft_lex_synt_err(t_lex *lex);

/* ************************************************************************** */
/*                              lexer_utils.c                                 */
/* ************************************************************************** */
size_t			ft_strlen(const char *s);
char			*ft_strndup(const char *s, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);

/* ************************************************************************** */
/*                              lexer_ascii.c                                 */
/* ************************************************************************** */
int				ft_char_type(char c);

#endif
