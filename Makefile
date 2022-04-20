#Makefile genere avec le generateur de makefile

CC=c++
CCFLAGS=-Wall -c -o $@

OBJ=obj/analyseSrc.o obj/main.o obj/analyseParametres.o
EXEC=bin/buildMakefile

all: $(EXEC)

$(EXEC): $(OBJ)
	@echo "---------------"
	@$(CC) $(OBJ) -o $@
	@echo "build de l'executable $@ OK"
	@echo "---------------"


clean: 
	@echo "---------------"
	@rm -f obj/* bin/*
	@ echo "clean OK"
	@echo "---------------"
	@echo "build de l'objet $@ OK"


obj/analyseParametres.o: src/analyseParametres.cpp \
	inc/main.hpp
	@$(CC) $< -c -o $@
	@echo "build de l'objet $@ OK"


obj/analyseSrc.o: src/analyseSrc.cpp \
	inc/analyseSrc.hpp \
	inc/main.hpp
	@$(CC) $< -c -o $@
	@echo "build de l'objet $@ OK"


obj/main.o: src/main.cpp \
	inc/main.hpp\
	inc/analyseParametres.hpp
	@$(CC) $< -c -o $@
	@echo "build de l'objet $@ OK"

install:
	make
	rm -f ~/bin/buildMakefile
	cp -f bin/buildMakefile ~/bin
	chmod +x ~/bin/buildMakefile