NAME		= philo

CC 			= cc
CFLAGS 		= -Wall -Werror -Wextra

SRC_DIR 	= src
OBJ_DIR 	= obj

SRC			= \

MAIN		= main.c

OBJ_SRC     = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_MAIN    = $(OBJ_DIR)/main.o
OBJ         = $(OBJ_SRC) $(OBJ_MAIN)

GREEN		= \033[1;32m
RED			= \033[1;31m
RESET		= \033[0m

RM			= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)🔧 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME) && \
	 echo "$(GREEN)✅ Build completata con successo!$(RESET)" || \
	 echo "$(RED)❌ Errore nel linking di $(NAME)!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(GREEN)🛠 Compilazione:$(RESET) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ && \
	 echo "$(GREEN)   ✔ Creato: $@$(RESET)" || \
	 echo "$(RED)   ✘ Errore nella compilazione di: $<$(RESET)"

$(OBJ_DIR)/main.o: $(MAIN) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(GREEN)🛠 Compilazione:$(RESET) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ && \
	 echo "$(GREEN)   ✔ Creato: $@$(RESET)" || \
	 echo "$(RED)   ✘ Errore nella compilazione di: $<$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) clean -C
	@echo "$(GREEN)🧹 Pulizia oggetti...$(RESET)"
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)✅ Cartella '$(OBJ_DIR)' rimossa.$(RESET)"

fclean: clean
	@$(MAKE) fclean -C
	@echo "$(GREEN)🧹 Pulizia completa...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(GREEN)✅ Binario '$(NAME)' rimosso.$(RESET)"

re: fclean all

.PHONY: all clean fclean re