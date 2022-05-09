#color
GREEN = \e[32m
RED = \e[31m
WHITE = \e[39m
YELLOW = \e[33m
HIDDEN = \e[8m
RESET = \e[0m
#philosophers
NAME = philosophers
CC = gcc
CFLAGS = -Werror -Wall -Wextra -g -fsanitize=address
SRC = philosophers.c
RM = rm -f
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re run 

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@printf "$(GREEN)🚀 Creating $(NAME)$(RESET)\n"
	@sleep 0.5

clean:
	@$(RM) $(NAME)
	@$(RM) $(OBJ)
	@printf "$(YELLOW)♻️  Clean $(NAME)$(RESET)\n"
	@sleep 0.5

fclean: clean
	@printf "\r$(RED)🗑️  Remove $(NAME)$(RESET)\n"
	@sleep 0.5

re: fclean all

run: all
	./$(NAME) $(ARG)

