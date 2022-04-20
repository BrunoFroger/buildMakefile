# Makefile genere automatiquement avec le generateur de makefile

CC=c++
CCFLAGS=-Wall -c -o $@

SRC=$(wildcard src/*.cpp)
TMP=$(patsubst %.cpp, %.o, $(SRC))
OBJ=$(patsubst src/%.o, obj/%.o, $(TMP))
EXEC = bin/buildMakefile

ALL : $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(OBJ) -o $@
	@echo "build executable OK"

obj/analyseParametres.o: src/analyseParametres.cpp \
	inc/main.hpp
	@$(CC) $< -c -o $@
	@echo "build $@ OK"

obj/analyseSrc.o: src/analyseSrc.cpp \
	inc/analyseSrc.hpp \
	inc/main.hpp
	@$(CC) $< -c -o $@
	@echo "build $@ OK"

obj/main.o: src/main.cpp \
	inc/main.hpp \
	inc/analyseParametres.hpp
	@$(CC) $< -c -o $@
	@echo "build $@ OK"

clean: 
	@rm -f obj/* bin/*
	@echo "Clean OK"

install: 
	@make
	@rm -f ~/bin/buildMakefile
	@cp -f bin/buildMakefile ~/bin
	@chmod +x ~/bin/buildMakefile
	@echo "installation de buildMakefile dans ~/bin OK"
