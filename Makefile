RED		=\033[0;31m
CYAN	=\033[0;36m
GREEN	=\033[0;32m
YELLOW	=\033[0;33m
WHITE	=\033[0;37m

CC		= cc
RM		= rm -rf
NAME	= pipex 
INC		= -I inc/ -I lib/libft/
LIBFT	= -L lib/libft -lft
CFLAGS	= -Wall -Wextra -Werror -g

SRCPATH	= src/
SRC	=	main.c \
		pipex.c \
		free.c \
		error.c \
		ft_split_args.c

OBJDIR	= .config/obj/
OBJ		= $(addprefix $(OBJDIR), $(SRC:.c=.o))

DEPDIR	= .config/dep/
DEP		= $(addprefix $(DEPDIR), $(SRC:.c=.d))

all: $(NAME)

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

clean:
		@echo "$(RED)Cleaning $(NAME)...$(WHITE)"
		@$(MAKE) --no-print-directory fclean -C lib/libft
		@$(RM) .config
		@echo "$(GREEN)Done$(WHITE)"

fclean: clean
		@$(RM) $(NAME)

re: fclean all

norm:
	@echo "$(YELLOW)Executing norminette...$(WHITE)"
	@norminette inc/*
	@norminette src/*

.PHONY: all clean fclean re norm