#############################################################
#                   M a k e f i l e 
# 
#         généré automatiquement avec bin/buildMakefile
#              le 27/04/2022 à 23:46:16
#              (c) B. Froger 2022
# 
#############################################################

#------------------------------------------------------------
# Définition des variables
#------------------------------------------------------------
CC=gcc
CCFLAGS=-Wall -Werror
LDFLAGS=

SRCDIR=src
INCDIR=inc
OBJDIR=obj
BINDIR=bin
INSTALLDIR=~/bin

SRCCPP=$(wildcard $(SRCDIR)/*.cpp)
SRCC=$(wildcard $(SRCDIR)/*.c)
TMPCPP=$(patsubst %.cpp, %.o, $(SRCCPP))
TMPC=$(patsubst %.c, %.o, $(SRCC))
TMP=$(TMPCPP) $(TMPC)
OBJ=$(patsubst $(SRCDIR)/%.o, $(OBJDIR)/%.o, $(TMP))
EXEC = $(BINDIR)/buildMakefile

#------------------------------------------------------------
# Définition des règles génériques
#------------------------------------------------------------
ALL : $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(LDFLAGS) $(OBJ) -o $@
	@echo "Edition de lien de $@ OK"

#------------------------------------------------------------
# Définition des règles pour chaque fichier source
#------------------------------------------------------------
$(OBJDIR)/analyseParametres.o: $(SRCDIR)/analyseParametres.cpp \
	$(INCDIR)/main.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/analyseSrc.o: $(SRCDIR)/analyseSrc.cpp \
	$(INCDIR)/analyseSrc.hpp \
	$(INCDIR)/main.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/fichierConfig.o: $(SRCDIR)/fichierConfig.cpp \
	$(INCDIR)/main.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp \
	$(INCDIR)/main.hpp \
	$(INCDIR)/analyseParametres.hpp \
	$(INCDIR)/fichierConfig.hpp \
	$(INCDIR)/analyseSrc.hpp
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

$(OBJDIR)/test.o: $(SRCDIR)/test.c
	@$(CC) $(CCFLAGS) $< -c -o $@
	@echo "Compilation de $< OK"

#------------------------------------------------------------
# Définition des règles utilitaires
#------------------------------------------------------------
clean: 
	@rm -f $(OBJDIR)/* $(BINDIR)/*
	@echo "Clean OK"

info: 
	@echo "affichage des variables de makefile"
	@echo "SRCCPP = " $(SRCCPP)
	@echo "SRCC   = " $(SRCC)
	@echo "TMPCPP = " $(TMPCPP)
	@echo "TMPC   = " $(TMPC)
	@echo "TMP    = " $(TMP)
	@echo "OBJ    = " $(OBJ)
	@echo "EXEC   = " $(EXEC)

install: 
	@make
	@rm -f $(INSTALLDIR)/buildMakefile
	@cp -f $(BINDIR)/buildMakefile ~/bin
	@chmod +x $(INSTALLDIR)/buildMakefile
	@echo "installation de buildMakefile dans ~/bin OK"
