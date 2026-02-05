NAME        = philo
CC          = cc
CFLAGS      = -Wall -Werror -Wextra
OBJ_DIR     = obj
SRC_DIR     = src
UTILS_DIR   = utils

# 1. Corretto: usa spazi per indentare e rimuovi l'ultima backslash
SRC         = $(UTILS_DIR)/validate.c \
              $(SRC_DIR)/main.c \
			  $(UTILS_DIR)/init.c  \
			  $(UTILS_DIR)/time.c \
			  $(SRC_DIR)/routine.c \
			  $(SRC_DIR)/monitor.c \

# 2. Definiamo gli oggetti (mappa i file .c nella cartella obj)
OBJ         = $(SRC:%.c=$(OBJ_DIR)/%.o)

GREEN       = \033[1;32m
RED         = \033[1;31m
RESET       = \033[0m
RM          = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)🔧 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)✅ Build completata con successo!$(RESET)"

# Regola per compilare i file .o dentro la cartella obj
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)🛠 Compilazione:$(RESET) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(GREEN)🧹 Pulizia oggetti...$(RESET)"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(GREEN)🧹 Pulizia completa...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re