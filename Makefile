# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emuckens <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 17:52:27 by emuckens          #+#    #+#              #
#    Updated: 2018/10/24 14:53:47 by emuckens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	:= both programs  
NAME_CH := checker
NAME_PS := push_swap

#==============================================================================#
#					 		 	  COMPILATION								   
#==============================================================================#

FLAGS	:= -Wall -Werror -Wextra -g
FSANI	:= -fsanitize=address
CC		:= gcc $(FLAGS)
CCF		:= $(CC) $(FSANI)

#==============================================================================#
#								    FILES									   
#==============================================================================#

_SRC_PS := display_gen.c \
	display_opti.c display_options.c \
	env.c error.c ins_list.c ins_p.c ins_r.c ins_rr.c ins_s.c \
	main_pushswap.c opti_mirror.c opti_other.c opti_pat_detect.c \
	opti_pat_mod.c opti_rot.c opti_tweak.c read_arg.c read_options.c \
	sort.c sort_merge.c sort_insert.c utils_gen.c utils_minmax.c utils_opti.c \
	utils_sort.c

_SRC_CH := display_gen.c display_opti.c display_options.c env.c error.c \
	ins_list.c ins_p.c ins_r.c ins_rr.c ins_s.c main_checker.c opti_mirror.c \
	opti_other.c opti_pat_mod.c read_arg.c read_options.c utils_gen.c \
	utils_opti.c utils_sort.c 

_HEAD	:= pushswap.h

#SRC_PS := $(addprefix $(SRC_DIR)/, $(_SRC_PS))
#SRC_CH := $(addprefix $(SRC_DIR)/, $(_SRC_CH))
SRC_CH = $(patsubst %, $(SRC_DIR)/%, $(_SRC_CH))
SRC_PS = $(patsubst %, $(SRC_DIR)/%, $(_SRC_PS))
SRC	= $(SRC_PS) \
	 $(SRC_CH)
HEAD	= $(patsubst %, $(HEAD_DIR)/$, $(_HEAD))
BIN_PS	= $(patsubst %.c, $(BIN_DIR)/%.o, $(_SRC_PS))
BIN_CH	= $(patsubst %.c, $(BIN_DIR)/%.o, $(_SRC_CH))
LIBFT	:= libft/libft.a

#==============================================================================#
#								DIRECTORIES									    
#==============================================================================#

BIN_DIR := bin
BIN_DIR_PS := $(BIN_DIR)/push_swap
BIN_DIR_CH := $(BIN_DIR)/checker
HEAD_DIR := includes
SRC_DIR := srcs
LIB_DIR := libft

#==============================================================================#
#							       MISC										    
#==============================================================================#

NB = $(words $(SRC_PS))
INDEX := 0
COL_BUILD := \033[22;35
COL_OFF := \033[0m

#==============================================================================#
#							       RULES									    
#==============================================================================#


.PHONY: all clean fclean re simple debug

all: 
	@make -C $(LIB_DIR)
	@make $(NAME_PS)
	@make $(NAME_CH)

$(NAME_CH): $(BIN_CH) $(LIBFT)
#	@echo "\033[22;35m building $(NAME_CH)... \033[0m"
	@$(CC) -o $(NAME_CH) $(BIN_CH) -lft -L $(LIB_DIR) -lncurses
	@echo "\r>>> \033[01;32m$(NAME_CH) READY              \033[0m"

$(NAME_PS): $(BIN_PS) $(LIBFT)
#	@echo "\033[22;35mbuilding $(NAME_PS)... \033[0m"
	@$(CC) -o $(NAME_PS) $(BIN_PS) -lft -L $(LIB_DIR) 
	@echo "\r>>> \033[01;32m$(NAME_PS) READY              \033[0m"

$(LIBFT):
	@make -C $(LIB_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD) Makefile | $(BIN_DIR)
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/($(NB))))))
	@$(CC) -I $(HEAD_DIR) -I $(LIB_DIR)/$(HEAD_DIR) -o $@ -c $<
	@printf "\033[22;35mgenerating binary.... [ %d%% ]\033[0m\r" $(PERCENT) 
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:
	@echo "cleaning $(NAME_CH) and $(NAME_PS) binaries..."
	@rm -f $(BIN_CH)
	@rm -f $(BIN_PS)
	@rm -rf $(BIN_DIR)
	@make clean -C $(LIB_DIR)
	@echo "\033[01;34mBinaries removed from all folders.\n\033[0m"

fclean: clean
	@echo "cleaning $(NAME_CH) and $(NAME_PS) executables..."
	@rm -f $(NAME_CH) $(NAME_PS)
	@echo "cleaning $(LIBFT) executable..."
	@rm -f $(LIBFT)
	@echo "\033[01;34mAll directories now clean.\n\033[0m"

re:
	@make -s fclean
	@make -s all

remo:
	@make all
	@rm -f $(BIN_CH) $(BIN_PS)
	@echo "\033[01;34mBinaries removed from all folders.\n\033[0m"

debug: $(BIN_CH) $(BIN_PS) $(HEAD)
	@echo "\033[01;31mbuilding $(NAME_CH) and $(NAME_PS) in DEBUG MODE...\033[0m"
	@$(CCF) -o $(NAME_CH) $(BIN_CH) -lft -L $(LIB_DIR)
	@$(CCF) -o $(NAME_PS) $(BIN_PS) -lft -L $(LIB_DIR)
	@echo "\033[01;32m$(NAME_CH) and $(NAME_PS) READY\033[0m"
