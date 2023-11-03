# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 09:27:32 by rroussel          #+#    #+#              #
#    Updated: 2023/11/02 18:36:36 by rroussel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_CYAN=\033[0;36m
COLOUR_END=\033[0m


SRCS	=	src/main.c \
			src/dinner.c \
			src/errors.c \
			src/initialization.c \
			src/parsing.c \
			src/solo_philo.c \
			src/table.c \
			src/time_management.c

OBJS		= $(SRCS:.c=.o)

NAME		= philo

CC			= gcc

FLAGS		= -Wall -Werror -Wextra -pthread

HEADER	= inc/philo.h

RM = rm -f

################ RULES ################

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(COLOUR_CYAN)\
	██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗\n\
	██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝\n\
	██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗\n\
	██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║\n\
	██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║\n\
	╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝ by rroussel$(COLOUR_END)"    
	@$(CC) $(FLAGS) -lpthread $(INCS) $(OBJS) -o $(NAME) $(RDLINE_FLAGS)
	@echo "↪ Finished, $(COLOUR_BLUE)philisophers$(COLOUR_END) $(COLOUR_GREEN)compiled$(COLOUR_END)"

%.o: %.c $(HEADER)
	@echo "Compiling $<"
	@$(CC) $(FLAGS) -c $<  -o $(<:.c=.o)
	@sleep .033
	@printf "\033[1A"
	@printf "\033[K"

clean:
	@echo "Cleaning files..."
	@$(RM) $(OBJS)
	@echo "↪ Finished, $(COLOUR_BLUE)files$(COLOUR_END) $(COLOUR_RED)cleaned$(COLOUR_END)"

fclean: clean
	@echo "Cleaning binaries..."
	@$(RM) $(NAME)
	@echo "↪ Finished, $(COLOUR_BLUE)binaries$(COLOUR_END) $(COLOUR_RED)cleaned$(COLOUR_END)"

re: fclean all
	@echo "↪ Finished, $(COLOUR_BLUE)re-make$(COLOUR_END) $(COLOUR_GREEN)done$(COLOUR_END)"

.PHONY: all clean fclean re
