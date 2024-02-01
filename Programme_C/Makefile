CC = gcc
CHEMIN_O_S = Fichiers_o_S
CHEMIN_O_T = Fichiers_o_T
CHEMIN_T = Programme_T
CHEMIN_S = Programme_S
SRC_S = $(wildcard $(CHEMIN_S)/*.c)
OBJ_S = $(SRC_S:.c=.o)
SRC_T = $(wildcard $(CHEMIN_T)/*.c)
OBJ_T = $(SRC_T:.c=.o)
CFLAGS = -Wall -Werror




all : ProgS ProgT

$(CHEMIN_O_S)/%.o: $(CHEMIN_S)/%.c $(CHEMIN_S)/Main_S.h
	$(CC) $(CFLAGS) -c $< -o $@

$(CHEMIN_O_T)/%.o: $(CHEMIN_T)/%.c $(CHEMIN_T)/Main_T.h
	$(CC) $(CFLAGS) -c $< -o $@

ProgS: $(OBJ_S)
	$(CC) $(CFLAGS) $^ -o $@ -lm

ProgT: $(OBJ_T)
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean :
	rm -f $(CHEMIN_O_S)/*.o $(CHEMIN_O_T)/*.o $(CHEMIN_S)/*.o $(CHEMIN_T)/*.o 




