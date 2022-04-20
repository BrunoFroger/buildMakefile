//
//  main.cpp
//  Generateur de Makefile
//
//  Created by Bruno FROGER on 19/12/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>

#include "../inc/main.hpp"
#include "../inc/analyseParametres.hpp"

extern int analyseSrc(char *filename);

char tblSrcFiles[NB_FILES_MAX][FILENAME_MAX_LENGTH];
char filename[FILENAME_MAX_LENGTH];
char appName[FILENAME_MAX_LENGTH];
FILE *srcFile;
FILE *ficMakefile;
char makefile[FILENAME_MAX_LENGTH]="makefile.result";
char repertoireInstallation[FILENAME_MAX_LENGTH]="~/bin";
int nbSrcFiles=0;
char ligne[LINE_MAX_LENGTH];
char compilateur[10]="c++";
char ligneCompilation[100];
char ligneLink[100];

int main(int argc, char**argv){

	//printf("Repertoire d'installation par defaut = %s \n", repertoireInstallation);

	analyseParametres(argc, argv);
	nbSrcFiles=0;
	// recuperation de la liste des fichiers sources
	system("ls src/* > listesrc.txt");
	srcFile = fopen("listesrc.txt", "r");
	while (!feof(srcFile)){
		fgets(ligne,FILENAME_MAX_LENGTH,srcFile);
		if (feof(srcFile)){
			//std::cout << "fin de fichier on continue\n";
			continue;
		}
		// extract filename
		char *tmp;
		tmp = ligne;
		while (strchr(tmp,'/') != NULL){
			strcpy(tmp, strchr(tmp,'/'));
			tmp=&(tmp[1]);
			//std::cout << "	tmp = " << tmp << "\n";
		}
		// suppression de l'extention de fichier
		strcpy(ligne, tmp);
		tmp=strchr(ligne,'.');
		tmp[1]='\0';
		// suppression du retour chariot dans le nom de fichier
		if (strlen(ligne) > 0){
			ligne[strlen(ligne)-1]='\0';
			//std::cout << "ajout de " << ligne << " au makefile \n";
			sprintf(tblSrcFiles[nbSrcFiles++],"%s",ligne);
		}
	}
	//std::cout << "fin analyse liste des fichiers sources\n";
	fclose(srcFile);
	system("rm listesrc.txt");
	if (nbSrcFiles == 0){
		printf("ERROR : aucun fichier source trouves dans src/...\n");
		return -1;
	}
	sprintf(ligneCompilation, "@$(CC) $< -c -o $@");
	sprintf(ligneLink, "@$(CC) $(OBJ) -o $@");
	// ecriture de l'entete du fichier makefile
	//std::cout << "creation entete du makefile \n";
	ficMakefile = fopen(makefile,"w");
	fprintf(ficMakefile,"# Makefile genere automatiquement avec le generateur de makefile\n");
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"CC=%s\n", compilateur);
	fprintf(ficMakefile,"CCFLAGS=-Wall -c -o $@\n");
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"SRC=$(wildcard src/*.cpp)\n");
	fprintf(ficMakefile,"TMP=$(patsubst %%.cpp, %%.o, $(SRC))\n");
	fprintf(ficMakefile,"OBJ=$(patsubst src/%%.o, obj/%%.o, $(TMP))\n");
	fprintf(ficMakefile,"EXEC = bin/%s\n", appName);
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"ALL : $(EXEC)\n");
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"$(EXEC): $(OBJ)\n");
	fprintf(ficMakefile,"\t%s\n", ligneLink);
	fprintf(ficMakefile,"\t@echo \"build executable OK\"\n");
	///std::cout << "nombre de fichiers trouves " << nbSrcFiles << "\n";
	int i=0;
	// analyse des fichiers sources
	strcpy(filename, tblSrcFiles[i++]);
	while (i <= nbSrcFiles){
		// on traite ce fichier
		analyseSrc(filename);
		strcpy(filename, tblSrcFiles[i++]);
	}
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"clean: \n");
	fprintf(ficMakefile,"\t@rm -f obj/* bin/*\n");
	fprintf(ficMakefile,"\t@echo \"Clean OK\"\n");
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"install: \n");
	fprintf(ficMakefile,"\t@make\n");
	fprintf(ficMakefile,"\t@rm -f %s/%s\n", repertoireInstallation, appName);
	fprintf(ficMakefile,"\t@cp -f bin/%s %s\n", appName, repertoireInstallation);
	fprintf(ficMakefile,"\t@chmod +x %s/%s\n", repertoireInstallation, appName);
	fprintf(ficMakefile,"\t@echo \"installation de %s dans %s OK\"\n", appName, repertoireInstallation);
}