#############################################################
#                   M a k e f i l e 
# 
#         généré automatiquement avec buildMakefile
#              le 21/04/2022 à 11:41:27
#              (c) B. Froger 2022
# 
#############################################################

#------------------------------------------------------------
# Définition des variables
#------------------------------------------------------------
CC=c++
CCFLAGS=-Wall -c -o $@

SRC=$(wildcard src/*.cpp)
TMP=$(patsubst %.cpp, %.o, $(SRC))
OBJ=$(patsubst src/%.o, obj/%.o, $(TMP))
EXEC = bin/buildMakefile

#------------------------------------------------------------
# Définition des règles génériques
#------------------------------------------------------------
ALL : $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(OBJ) -o $@
	@echo "Edition de lien de $@ OK"

#------------------------------------------------------------
# Définition des règles pour chaque fichier source
#------------------------------------------------------------
obj/analyseParametres.o: src/analyseParametres.cpp \
	inc/main.hpp
	@$(CC) $< -c -o $@
	@echo "Compilation de $< OK"

obj/analyseSrc.o: src/analyseSrc.cpp \
	inc/analyseSrc.hpp \
	inc/main.hpp
	@$(CC) $< -c -o $@
	@echo "Compilation de $< OK"

obj/main.o: src/main.cpp \
	inc/main.hpp \
	inc/analyseParametres.hpp
	@$(CC) $< -c -o $@
	@echo "Compilation de $< OK"

#------------------------------------------------------------
# Définition des règles utilitaires
#------------------------------------------------------------
clean: 
	@rm -f obj/* bin/*
	@echo "Clean OK"

install: 
	@make
	@rm -f ~/bin/buildMakefile
	@cp -f bin/buildMakefile ~/bin
	@chmod +x ~/bin/buildMakefile
	@echo "installation de buildMakefile dans ~/bin OK"
