#color
GREEN = \e[32m
RED = \e[31m
WHITE = \e[39m
YELLOW = \e[33m
HIDDEN = \e[8m
RESET = \e[0m
#philosophers
NAME = philo
CC = gcc
RM = rm -rf
S = src/
O = obj/
I = inc/
SRC = $Sphilo.c
CFLAGS = -Werror -Wall -Wextra
CFLAGS += -g -fsanitize=address
CFLAGS += -I$I

OBJ = $(SRC:$S.c=$O.o)

.PHONY: all clean fclean re

all: $(NAME)

$O:
	@printf "$(GREEN)🚀 Creating $(O)$(RESET)\n"
	@mkdir -p $@

$(NAME): $(OBJ) | $O
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@printf "$(GREEN)🚀 Creating $(NAME)$(RESET)\n"

clean:
	@$(RM) $(O)
	@printf "$(YELLOW)♻️  Clean $(NAME)$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "\r$(RED)🗑️  Remove $(NAME)$(RESET)\n"

re: fclean all

