# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/17 23:46:04 by cempassi          #+#    #+#              #
#    Updated: 2019/07/09 07:47:59 by cempassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
COMPILE = $(CC) -c
DEBUG = $(CC) -g3 -c #-fsanitize=address,undefined

# Reset
NC = \033[0m

# Regular Colors
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

# One Line Output
ONELINE =\e[1A\r

NAME = libft.a
DBNAME = libftdb.a
CLEANUP = rm -rf
MKDIR = mkdir -p

PATHO = objs/
PATHI = includes/

INCS += libft.h
INCS += ft_printf.h
INCS += conversion.h
INCS += output.h
INCS += memory.h
INCS += list.h
INCS += test.h
INCS += other.h
INCS += hashmap.h
INCS += vector.h
INCS += get_next_line.h

#--------------------Memory--------------------#
SRCS += ft_bzero.c
SRCS += ft_memalloc.c
SRCS += ft_memmove.c
SRCS += ft_memchr.c
SRCS += ft_memcmp.c
SRCS += ft_memcpy.c
SRCS += ft_memccpy.c
SRCS += ft_memdel.c
SRCS += ft_memset.c

#--------------------Vectors---------------------#
SRCS += vct_new.c
SRCS += vct_len.c
SRCS += vct_size.c
SRCS += vct_reset.c
SRCS += vct_set_scale.c
SRCS += vct_scale.c
SRCS += vct_resize.c
SRCS += vct_getstring.c
SRCS += vct_sub.c
SRCS += vct_getcopy.c
SRCS += vct_ncpy.c
SRCS += vct_ncat.c
SRCS += vct_insert_char.c
SRCS += vct_delchar.c
SRCS += vct_insert_string.c
SRCS += vct_del_string.c
SRCS += vct_replace_char.c
SRCS += vct_replace_string.c
SRCS += vct_add.c
SRCS += vct_push.c
SRCS += vct_pop.c
SRCS += vct_cut.c
SRCS += vct_del.c
SRCS += vct_scpy.c
SRCS += vct_scat.c
SRCS += vct_shift_tool.c
SRCS += vct_dups.c
SRCS += vct_dup.c
SRCS += vct_charat.c

#--------------------Strings---------------------#
SRCS += ft_strbeginswith.c
SRCS += ft_strendswith.c
SRCS += ft_isnumeric.c
SRCS += ft_isalnum.c
SRCS += ft_isalpha.c
SRCS += ft_isascii.c
SRCS += ft_isdigit.c
SRCS += ft_isprint.c
SRCS += ft_strcat.c
SRCS += ft_strchr.c
SRCS += ft_strcmp.c
SRCS += ft_strcpy.c
SRCS += ft_strdup.c
SRCS += ft_strlcat.c
SRCS += ft_strlen.c
SRCS += ft_strncat.c
SRCS += ft_strncmp.c
SRCS += ft_strncpy.c
SRCS += ft_strnstr.c
SRCS += ft_strrchr.c
SRCS += ft_strstr.c
SRCS += ft_strclr.c
SRCS += ft_strdel.c
SRCS += ft_strequ.c
SRCS += ft_striter.c
SRCS += ft_striteri.c
SRCS += ft_strjoin.c
SRCS += ft_strmap.c
SRCS += ft_strmapi.c
SRCS += ft_strnequ.c
SRCS += ft_strnew.c
SRCS += ft_strsub.c
SRCS += ft_strtrim.c
SRCS += ft_tolower.c
SRCS += ft_toupper.c
SRCS += ft_strupper.c
SRCS += ft_strlower.c
SRCS += ft_strinsert.c
SRCS += ft_strcspn.c
SRCS += ft_strspn.c
SRCS += ft_strrev.c
SRCS += ft_strcheck.c

#--------------------Conversion------------------#
SRCS += ft_atoi.c
SRCS += ft_itoa.c
SRCS += ft_ullitoa.c
SRCS += ft_llitoa.c
SRCS += ft_atoll_base.c
SRCS += ft_atoull_base.c
SRCS += ft_convert_base.c
SRCS += ft_abs.c

#----------------------Tab-----------------------#
SRCS += ft_strsplit.c
SRCS += ft_freetab.c
SRCS += ft_getargstab.c
SRCS += ft_showtab.c
SRCS += ft_taboneach.c
SRCS += ft_tabsize.c

#--------------------Lists-----------------------#
SRCS += ft_mergesort.c
SRCS += ft_lstadd.c
SRCS += ft_lstdelone.c
SRCS += ft_lstdelnext.c
SRCS += ft_lstdel.c
SRCS += ft_lstiter.c
SRCS += ft_lstiter_ctx.c
SRCS += ft_lstmap.c
SRCS += ft_lstnew.c
SRCS += ft_lstrev.c
SRCS += ft_lstaddback.c
SRCS += ft_lstmerge.c
SRCS += ft_lstfind.c
SRCS += ft_lstlen.c
SRCS += ft_lstfilter.c
SRCS += ft_lstremove_if.c
SRCS += ft_tabtolst.c
SRCS += ft_stckpop.c
SRCS += ft_stckpopnode.c
SRCS += ft_stckpush.c
SRCS += ft_stckpushnode.c
SRCS += ft_stckinit.c
SRCS += ft_stckdestroy.c
SRCS += ft_stcksize.c
SRCS += ft_stcktop.c
SRCS += ft_lstcmp.c
SRCS += ft_lsttotab.c
SRCS += ft_lstdelfirst.c
SRCS += ft_lstsplit_if.c

#--------------------Output----------------------#
SRCS += ft_putchar.c
SRCS += ft_putchar_fd.c
SRCS += ft_putendl.c
SRCS += ft_putendl_fd.c
SRCS += ft_putnbr.c
SRCS += ft_putnbr_fd.c
SRCS += ft_putstr.c
SRCS += ft_putnstr.c
SRCS += ft_putstr_fd.c
SRCS += ft_ringbuffer.c
SRCS += ft_getopt.c
SRCS += ft_getdelim.c
SRCS += ft_getargslst.c

#--------------------ft_printf-------------------#
SRCS += ft_printf.c
SRCS += format.c
SRCS += extract.c
SRCS += type.c
SRCS += widthprec.c
SRCS += output.c
SRCS += digit.c
SRCS += unsigned.c
SRCS += doubles.c
SRCS += other.c

#--------------------Hashmap-------------------#
SRCS += ft_hash_str.c
SRCS += ft_hmap_getdata.c
SRCS += ft_hmap_init.c
SRCS += ft_hmap_insert.c
SRCS += ft_hmap_print.c
SRCS += ft_hmap_remove.c
SRCS += ft_hmap_resize.c
SRCS += ft_hmap_free_content.c
SRCS += ft_hmap_collision.c
SRCS += ft_hmap_hits.c

#--------------------test------------------------#
SRCS += framework.c
SRCS += display_test.c
SRCS += setup_test.c

#--------------------directory--------------------#
SRCS += ft_dirlist.c
SRCS += ft_dirdel.c
SRCS += ft_checkstat.c

#------------------get_next_line------------------#
SRCS += get_next_line.c

DSYM += $(NAME).dSYM
DSYM += $(DBNAME).dSYM

OBJS = $(patsubst %.c, $(PATHO)%.o, $(SRCS))
OBJD = $(patsubst %.c, $(PATHO)db%.o, $(SRCS))

WFLAGS += -Wall
WFLAGS += -Werror
WFLAGS += -Wextra
IFLAGS = -I$(PATHI)
CFLAGS = $(WFLAGS)

vpath %.c srcs/conversion
vpath %.c srcs/get_next_line
vpath %.c srcs/garbage_collector
vpath %.c srcs/directory
vpath %.c srcs/ft_printf
vpath %.c srcs/list
vpath %.c srcs/memory
vpath %.c srcs/other
vpath %.c srcs/output
vpath %.c srcs/string
vpath %.c srcs/tab
vpath %.c srcs/test
vpath %.c srcs/hashmap
vpath %.c srcs/vector
vpath %.h includes

all : $(PATHO) $(NAME)

debug : $(PATHO) $(DBNAME)

$(NAME): $(OBJS)
	ar rus $@ $^
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(DBNAME): $(OBJD)
	ar rus $@ $^
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJS): $(PATHO)%.o : %.c $(INCS) Makefile
	$(COMPILE) $(CFLAGS) $(IFLAGS) $< -o $@
	printf "$(ONELINE)$(BLUE)Compiling $<                \n$(NC)"

$(OBJD): $(PATHO)db%.o : %.c $(INCS) Makefile
	$(DEBUG) $(DFLAGS) $(CFLAGS) $(IFLAGS) $< -o $@
	printf "$(ONELINE)$(BLUE)Compiling $< for debug                     \n$(NC)"

$(PATHO) :
	$(MKDIR) $(PATHO)

clean:
	$(CLEANUP) $(PATHO)*.o
	printf "$(RED)All *.o files from libft removed\n$(NC)"
	$(CLEANUP) $(DSYM)
	printf "$(RED)All $(DSYM) removed\n$(NC)"

cleandb :
	$(CLEANUP) $(DBNAME)
	printf "$(RED)$(DBNAME) deleted\n$(NC)"

fclean: clean cleandb
	$(CLEANUP) $(NAME)
	$(CLEANUP) $(PATHO)
	printf "$(RED)$(NAME) deleted\n$(NC)"

re : fclean all

.PHONY: all clean fclean debug cleandb
.SILENT:
