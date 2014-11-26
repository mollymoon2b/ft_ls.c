NAME = ft_ls
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDE = 
SRC = ft_ls.c 					\
		ft_ls_l.c  				\
		ft_option.c				\
		ft_add.c 				\
		ft_space.c   \
		main.c
		 

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) -L libft -lft

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, fclean, clean, re 

