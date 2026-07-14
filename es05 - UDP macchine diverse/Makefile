# Colori per i log
GREEN = \033[0;32m
CYAN = \033[0;36m
YELLOW = \033[0;33m
NC = \033[0m

# Variabili per compilatore C
CC = gcc
CFLAGS = -Wall -Iinc -pthread
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = inc

# File oggetto condivisi (librerie, moduli senza main)
COMMON_OBJS = $(OBJ_DIR)/network.o

# Obiettivo principale: compila tutti gli eseguibili
all: $(BIN_DIR)/serverUDP $(BIN_DIR)/clientUDP

# Regole per ogni eseguibile C
$(BIN_DIR)/serverUDP: $(OBJ_DIR)/serverUDP.o $(COMMON_OBJS)
	@printf "$(CYAN)Generazione eseguibile $@...$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "$(GREEN)Completato: $@$(NC)\n"

$(BIN_DIR)/clientUDP: $(OBJ_DIR)/clientUDP.o $(COMMON_OBJS)
	@printf "$(CYAN)Generazione eseguibile $@...$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "$(GREEN)Completato: $@$(NC)\n"

# Regola generica per i file oggetto C
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "$(YELLOW)Compilazione oggetto $<...$(NC)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

# Pulizia dei file compilati
clean:
	@printf "$(YELLOW)Pulizia $(CURDIR)...$(NC)\n"
	@rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/* $(BIN_DIR)/*.class
