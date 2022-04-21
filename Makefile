#############################################################
#                   M a k e f i l e 
# 
#         généré automatiquement avec bin/buildMakefile
#              le 21/04/2022 à 15:09:14
#              (c) B. Froger 2022
# 
#############################################################

#------------------------------------------------------------
# Définition des variables
#------------------------------------------------------------
CC=gcc
CCFLAGS=-Wall -c -o $@

SRCDIR=src
INCDIR=inc
OBJDIR=obj
BINDIR=bin
INSTALLDIR=~/bin

SRC=$(wildcard $(SRCDIR)/*.cpp)
TMP=$(patsubst %.cpp, %.o, $(SRC))
OBJ=$(patsubst $(SRCDIR)/%.o, $(OBJDIR)/%.o, $(TMP))
EXEC = $(BINDIR)/buildMakefile

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
$(OBJDIR)/analyseParametres.o: $(SRCDIR)/analyseParametres.cpp \
	$(INCDIR)/main.hpp
	@$(CC) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/analyseSrc.o: $(SRCDIR)/analyseSrc.cpp \
	$(INCDIR)/analyseSrc.hpp \
	$(INCDIR)/main.hpp
	@$(CC) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/fichierConfig.o: $(SRCDIR)/fichierConfig.cpp \
	$(INCDIR)/main.hpp
	@$(CC) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp \
	$(INCDIR)/main.hpp \
	$(INCDIR)/analyseParametres.hpp \
	$(INCDIR)/fichierConfig.hpp
	@$(CC) $< -c -o $@
	@echo "Compilation de $< OK"

#------------------------------------------------------------
# Définition des règles utilitaires
#------------------------------------------------------------
clean: 
	@rm -f $(OBJDIR)/* $(BINDIR)/*
	@echo "Clean OK"

install: 
	@make
	@rm -f $(INSTALLDIR)/buildMakefile
	@cp -f $(BINDIR)/buildMakefile ~/bin
	@chmod +x $(INSTALLDIR)/buildMakefile
	@echo "installation de buildMakefile dans ~/bin OK"
