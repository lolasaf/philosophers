# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 22:34:00 by wel-safa          #+#    #+#              #
#    Updated: 2024/11/26 23:47:05 by wel-safa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

#--- DIRECTORIES ---
SRCDIR := src
INCDIR := inc
OBJDIR := obj

#--- SOURCES ---
SRCS := $(addprefix $(SRCDIR)/, $(addsuffix .c, main init matrix utils mutex \
escape))

#--- OBJECTS ---
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

#--- HEADERS ---
HEADERS := $(addprefix $(INCDIR)/, philo.h)

#--- FLAGS ---
CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INCDIR) -g -pthread 
#-fsanitize=thread

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) -f $(OBJS)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) -rf $(NAME)

re: fclean all
