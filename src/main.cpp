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
#include <time.h>

#include "../inc/main.hpp"
#include "../inc/analyseParametres.hpp"
#include "../inc/fichierConfig.hpp"

extern int analyseSrc(char *filename);

char tblSrcFiles[NB_FILES_MAX][FILENAME_MAX_LENGTH];
char filename[FILENAME_MAX_LENGTH];
char appName[FILENAME_MAX_LENGTH]="";
FILE *srcFile;
FILE *ficMakefile;
char makefile[FILENAME_MAX_LENGTH]="makefile.result";
char configFilename[FILENAME_MAX_LENGTH];
char repertoireInstallation[FILENAME_MAX_LENGTH]="~/bin";
int nbSrcFiles=0;
char ligne[LINE_MAX_LENGTH];
char compilateur[10]="c++";
char ligneCompilation[100];
char ligneLink[100];
char srcDir[100];
char incDir[100];
char objDir[100];
char binDir[100];

int main(int argc, char**argv){

	//printf("Repertoire d'installation par defaut = %s \n", repertoireInstallation);

	// recuperation de la date de génération
	time_t rawtime;
	struct tm * timeinfo;
	char bufferDate [100];
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	strftime (bufferDate,100,"le %d/%m/%Y à %T",timeinfo);

	strcpy(srcDir, "src");
	strcpy(incDir, "inc");
	strcpy(objDir, "obj");
	strcpy(binDir, "bin");
	char *tmp = strrchr(argv[0], '/');
	if (tmp == NULL){
		tmp = &argv[0][0];
	} else {
		tmp+=1;
	}

	sprintf(configFilename,"%s.cfg", tmp);

	litFichierConfig(configFilename);

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
	if (ficMakefile == NULL){
		printf("fichier makefile (%s) n'existe pas\n", makefile);
		exit(-1);
	}
	fprintf(ficMakefile,"#############################################################\n");
	fprintf(ficMakefile,"#                   M a k e f i l e \n");
	fprintf(ficMakefile,"# \n");
	fprintf(ficMakefile,"#         généré automatiquement avec %s\n", argv[0]);
	fprintf(ficMakefile,"#              %s\n", bufferDate);
	fprintf(ficMakefile,"#              (c) B. Froger 2022\n");
	fprintf(ficMakefile,"# \n");
	fprintf(ficMakefile,"#############################################################\n");
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	fprintf(ficMakefile,"# Définition des variables\n");
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	fprintf(ficMakefile,"CC=%s\n", compilateur);
	fprintf(ficMakefile,"CCFLAGS=-Wall -c -o $@\n");
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"SRCDIR=%s\n", srcDir);
	fprintf(ficMakefile,"INCDIR=%s\n", incDir);
	fprintf(ficMakefile,"OBJDIR=%s\n", objDir);
	fprintf(ficMakefile,"BINDIR=%s\n", binDir);
	fprintf(ficMakefile,"INSTALLDIR=%s\n", repertoireInstallation);
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"SRC=$(wildcard $(SRCDIR)/*.cpp)\n");
	fprintf(ficMakefile,"TMP=$(patsubst %%.cpp, %%.o, $(SRC))\n");
	fprintf(ficMakefile,"OBJ=$(patsubst $(SRCDIR)/%%.o, $(OBJDIR)/%%.o, $(TMP))\n");
	fprintf(ficMakefile,"EXEC = $(BINDIR)/%s\n", appName);
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	fprintf(ficMakefile,"# Définition des règles génériques\n");
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	fprintf(ficMakefile,"ALL : $(EXEC)\n");
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"$(EXEC): $(OBJ)\n");
	fprintf(ficMakefile,"\t%s\n", ligneLink);
	fprintf(ficMakefile,"\t@echo \"Edition de lien de $@ OK\"\n");
	fprintf(ficMakefile,"\n");
	///std::cout << "nombre de fichiers trouves " << nbSrcFiles << "\n";
	int i=0;
	// analyse des fichiers sources
	strcpy(filename, tblSrcFiles[i++]);
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	fprintf(ficMakefile,"# Définition des règles pour chaque fichier source\n");
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	while (i <= nbSrcFiles){
		// on traite ce fichier
		analyseSrc(filename);
		strcpy(filename, tblSrcFiles[i++]);
	}
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	fprintf(ficMakefile,"# Définition des règles utilitaires\n");
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	fprintf(ficMakefile,"clean: \n");
	fprintf(ficMakefile,"\t@rm -f $(OBJDIR)/* $(BINDIR)/*\n");
	fprintf(ficMakefile,"\t@echo \"Clean OK\"\n");
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"install: \n");
	fprintf(ficMakefile,"\t@make\n");
	fprintf(ficMakefile,"\t@rm -f $(INSTALLDIR)/%s\n", appName);
	fprintf(ficMakefile,"\t@cp -f $(BINDIR)/%s %s\n", appName, repertoireInstallation);
	fprintf(ficMakefile,"\t@chmod +x $(INSTALLDIR)/%s\n", appName);
	fprintf(ficMakefile,"\t@echo \"installation de %s dans %s OK\"\n", appName, repertoireInstallation);

	printf("fichier %s généré avec succès \n", makefile);
}