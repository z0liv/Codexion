NAME = codexion

CC = cc
FLAGS = -pthread -Wall -Wextra -Werror
OBJS_DIR = ./objs

SRCS = src/codexion.c src/data_initializer.c src/data_validator.c
		
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(FLAGS) -o $@ $^

run: $(NAME)
	clear
	./codexion

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
