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

# Variabili per compilatore Java
JAVAC = javac
JFLAGS = -d $(BIN_DIR) -sourcepath $(SRC_DIR)

# Obiettivo principale: compila tutti gli eseguibili
all: $(BIN_DIR)/serverHTTP-REST $(BIN_DIR)/clientREST-POST $(BIN_DIR)/clientREST-GET $(BIN_DIR)/prime-number-interval java_classes

# Regole per ogni eseguibile C
$(BIN_DIR)/serverHTTP-REST: $(OBJ_DIR)/serverHTTP-REST.o $(COMMON_OBJS)
	@printf "$(CYAN)Generazione eseguibile $@...$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "$(GREEN)Completato: $@$(NC)\n"

$(BIN_DIR)/clientREST-POST: $(OBJ_DIR)/clientREST-POST.o $(COMMON_OBJS)
	@printf "$(CYAN)Generazione eseguibile $@...$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "$(GREEN)Completato: $@$(NC)\n"

$(BIN_DIR)/clientREST-GET: $(OBJ_DIR)/clientREST-GET.o $(COMMON_OBJS)
	@printf "$(CYAN)Generazione eseguibile $@...$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "$(GREEN)Completato: $@$(NC)\n"

$(BIN_DIR)/prime-number-interval: $(OBJ_DIR)/prime-number-interval.o $(COMMON_OBJS)
	@printf "$(CYAN)Generazione eseguibile $@...$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "$(GREEN)Completato: $@$(NC)\n"

# Regola generica per i file oggetto C
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "$(YELLOW)Compilazione oggetto $<...$(NC)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

# Regola per compilare i file Java
java_classes: $(wildcard $(SRC_DIR)/*.java)
	@printf "$(YELLOW)Compilazione classi Java in corso...$(NC)\n"
	@$(JAVAC) $(JFLAGS) $^
	@printf "$(GREEN)Classi Java compilate con successo!$(NC)\n"

# Pulizia dei file compilati
clean:
	@printf "$(YELLOW)Pulizia $(CURDIR)...$(NC)\n"
	@rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/* $(BIN_DIR)/*.class
