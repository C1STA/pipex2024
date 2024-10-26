RED		=\033[0;31m
CYAN	=\033[0;36m
GREEN	=\033[0;32m
YELLOW	=\033[0;33m
WHITE	=\033[0;37m

CC		= cc
RM		= rm -rf
NAME	= pipex
NAME_BONUS	= pipex_bonus
INC		= -I inc/ -I lib/libft/
LIBFT	= -L lib/libft -lft
CFLAGS	= -Wall -Wextra -Werror -g

SRCPATH	= src/
SRC	=	main.c \
		pipex.c \
		free.c \
		error.c \
		ft_split_args.c

SRC_BONUS_PATH = src_bonus/
SRC_BONUS = main.c \
						pipex.c \
						error.c \
						free.c \
						ft_split_args.c \
						lonely.c

all: $(NAME)

OBJDIR	= .config/obj/
OBJ		= $(addprefix $(OBJDIR), $(SRC:.c=.o))

DEPDIR	= .config/dep/
DEP		= $(addprefix $(DEPDIR), $(SRC:.c=.d))

$(NAME): $(OBJ)
		@echo "$(CYAN)Linking $(NAME)...$(WHITE)"
		@$(MAKE) --no-print-directory -C lib/libft
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
		@echo "$(GREEN)Done$(WHITE)"

$(OBJDIR)%.o: $(SRCPATH)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(DEPDIR)%.d: $(SRCPATH)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(INC) -MM $< -MT $(@:.d=.o) -MF $@ -MP

-include $(DEP)

bonus: $(NAME_BONUS)

OBJDIR_BONUS	= .config/obj_bonus/
OBJ_BONUS		= $(addprefix $(OBJDIR_BONUS), $(SRC_BONUS:.c=.o))

DEPDIR_BONUS	= .config/dep_bonus/
DEP_BONUS		= $(addprefix $(DEPDIR_BONUS), $(SRC_BONUS:.c=.d))

$(NAME_BONUS): $(OBJ_BONUS)
	@echo "$(CYAN)Linking $(NAME_BONUS)...$(WHITE)"
	@$(MAKE) --no-print-directory -C lib/libft
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME_BONUS)
	@echo "$(GREEN)Done$(WHITE)"

$(OBJDIR_BONUS)%.o: $(SRC_BONUS_PATH)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(DEPDIR_BONUS)%.d: $(SRC_BONUS_PATH)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(INC) -MM $< -MT $(@:d=.o) -MF $@ -MP

-include $(DEP_BONUS)

clean:
		@echo "$(RED)Cleaning $(NAME)...$(WHITE)"
		@$(MAKE) --no-print-directory fclean -C lib/libft
		@$(RM) .config
		@echo "$(GREEN)Done$(WHITE)"

fclean: clean
		@$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

norm:
	@echo "$(YELLOW)Executing norminette...$(WHITE)"
	@norminette inc/*
	@norminette src/*

.PHONY: all clean fclean re norm