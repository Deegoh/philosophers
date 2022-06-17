#color
GREEN = \e[32m
RED = \e[31m
WHITE = \e[39m
YELLOW = \e[33m
HIDDEN = \e[8m
RESET = \e[0m
#philosophers
NAME = philo
CC = cc
RM = rm -rf
S = src/
O = obj/
I = inc/
SRC =	$Smain.c\
		$Sphilo.c\
		$Serror.c\
		$Sinit.c\
		$Sutils.c
CFLAGS = -Werror -Wall -Wextra
CFLAGS += -g #-fsanitize=address #-fsanitize=leak
CFLAGS += -I./$I

ifeq ($(shell uname),Linux)
	CFLAGS += -pthread
endif

OBJ = $(SRC:$S.c=$O.o)

.PHONY: all clean fclean re

all: $(NAME)

$O:
	@mkdir -p $@
	@printf "$(GREEN)🚀 Creating $(O)$(RESET)\n"
	@sleep 0.2

$(NAME): $(OBJ) | $O
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "$(GREEN)🚀 Creating $(NAME)$(RESET)\n"
	@sleep 0.2

clean:
	@$(RM) $(O)
	@printf "$(YELLOW)♻️ Clean $(O)$(RESET)\n"
	@sleep 0.2

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)🗑️ Remove $(NAME)$(RESET)\n"
	@sleep 0.2

valgrind: all
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	./$(NAME) 5 410 200 200

re: fclean all

