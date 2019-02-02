# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/30 14:00:12 by hben-yah          #+#    #+#              #
#    Updated: 2019/02/02 14:30:06 by hben-yah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLI		=	client
NAME_SER		=	server

COMP			=	clang
FLAG			=	-Wall -Wextra -Werror -g3

# Sources paths Client
FILES_C_CLI		=   client.c
FILES_O_CLI		=	$(FILES_C_CLI:.c=.o)

# Sources paths Server
FILES_C_SER		=   server.c
FILES_O_SER		=	$(FILES_C_SER:.c=.o)

FILES_H			=	minitalk.h

# Directories
SRCS_D			=	./srcs/
OBJS_D			=   ./objs/
INCL_D 			=	./includes/

# Paths
SRCS_CLI		=	$(addprefix $(SRCS_D), $(FILES_C_CLI))
OBJS_CLI		=	$(addprefix $(OBJS_D), $(FILES_O_CLI))

SRCS_SER		=	$(addprefix $(SRCS_D), $(FILES_C_SER))	
OBJS_SER		=	$(addprefix $(OBJS_D), $(FILES_O_SER))

INCL			=	$(addprefix $(INCL_D), $(FILES_H))

# Libft
LFT_D			=	./libft/
LFT_P			=	$(addprefix $(LFT_D), libft.a)
LFT_I			=	./libft/includes/
LFT_L			=	./libft
LFT_H			=	libft.h

# Rules

all				:	$(LFT_P) $(OBJS_D) $(NAME_CLI) $(NAME_SER)

$(OBJS_D)		:	
					mkdir -p $(OBJS_D)

$(NAME_CLI)		:	$(OBJS_CLI)
					@echo "\nAssemblage et création de l'exécutable $(NAME_CLI)"
					@$(COMP) $(FLAG) $(OBJS_CLI) $(LFT_P) -o $(NAME_CLI)
					@echo "Terminé"

$(NAME_SER)		:	$(OBJS_SER)
					@echo "\nAssemblage et création de l'exécutable $(NAME_SER)"
					@$(COMP) $(FLAG) $(OBJS_SER) $(LFT_P) -o $(NAME_SER)
					@echo "Terminé"

$(LFT_P)		:	force
					@echo "Vérification de la librairie Libft"
					@make -C $(LFT_D)

$(OBJS_D)%.o	:	$(SRCS_D)%.c $(addprefix $(LFT_I), $(LFT_H)) $(INCL)
					@echo -e "\033[2K\c"
					@echo "\rCréation de l'objet $@\c"
					@mkdir -p $(OBJS_D)
					@$(COMP) $(FLAG) -I $(LFT_I) -I $(INCL_D) -o $@ -c $<

clean			:
					@make -C $(LFT_D) clean
					@echo "Nettoyage des objets $(OBJS_D)"
					@rm -rf $(OBJS_D)

fclean			:
					@make -C $(LFT_D) fclean
					@echo "Nettoyage des objets $(OBJS_D)"
					@rm -rf $(OBJS_D)
					@echo "Nettoyage de l'exécutable $(NAME_CLI)"
					@rm -f $(NAME_CLI)
					@echo "Nettoyage de l'exécutable $(NAME_SER)"
					@rm -f $(NAME_SER)

re				:	fclean all

force			:
					@true

.PHONY			:	all clean fclean re force

