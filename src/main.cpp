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
#include "../inc/analyseSrc.hpp"


structFichierSource tblSrcFiles[NB_FILES_MAX];
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
char ccFlags[100];
char ldFlags[100];
bool modeVerbose=false;
char buildDate[15]=__DATE__;
char buildDay[5];
char buildMonth[5];
char buildYear[10];

int main(int argc, char**argv){

	//printf("Repertoire d'installation par defaut = %s \n", repertoireInstallation);
	// definition de la date de compilation
	strncpy(buildDay, &buildDate[4], 2); 
	strncpy(buildMonth, buildDate, 3); 
	strncpy(buildYear, &buildDate[7], 4); 

	// recuperation de la date de génération
	time_t rawtime;
	struct tm * timeinfo;
	char bufferDate [100];
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	strftime (bufferDate,100,"%d/%m/%Y à %T",timeinfo);

	strcpy(srcDir, "src");
	strcpy(incDir, "inc");
	strcpy(objDir, "obj");
	strcpy(binDir, "bin");
	strcpy(ccFlags, "-Wall");
	strcpy(ldFlags, "");
	char *tmp = strrchr(argv[0], '/');
	if (tmp == NULL){
		tmp = &argv[0][0];
	} else {
		tmp+=1;
	}

	sprintf(configFilename,"%s.cfg", tmp);

	// detection du mode verbose
	for (int i = 0 ; i < argc ; i++){
		if (strcmp(argv[i], "-v") == 0) modeVerbose=true;
	}

	litFichierConfig(configFilename);

	analyseParametres(argc, argv);
	nbSrcFiles=0;
	// recuperation de la liste des fichiers sources
	//if (modeVerbose) printf("debut analyse liste des fichiers sources\n");
	system("ls src/*.c* > listesrc.txt");
	if (modeVerbose) system("cat listesrc.txt");
	srcFile = fopen("listesrc.txt", "r");
	if (srcFile == NULL){
		printf("Impossible de creer de fichiers temporaires dans ce projet\n");
		exit(-1);
	}
	if (modeVerbose) printf("construction de la liste des fichiers a traiter\n");
	while (!feof(srcFile)){
		fgets(ligne,FILENAME_MAX_LENGTH,srcFile);
		//if (modeVerbose) printf("detection du fichier à traiter : %s", ligne);
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
		strcpy(tblSrcFiles[nbSrcFiles].ext,&tmp[1]);
		// suppression du RC dans extension
		tblSrcFiles[nbSrcFiles].ext[strlen(tblSrcFiles[nbSrcFiles].ext)-1] = '\0';
		tmp[1]='\0';
		// suppression du retour chariot dans le nom de fichier
		if (strlen(ligne) > 0){
			ligne[strlen(ligne)-1]='\0';
			//std::cout << "ajout de " << ligne << " au makefile \n";
			strcpy(tblSrcFiles[nbSrcFiles].name, ligne);
			if (modeVerbose) printf("fichier <%s> avec extention <%s> trouvé\n", tblSrcFiles[nbSrcFiles].name, tblSrcFiles[nbSrcFiles].ext);
			nbSrcFiles++;
		}
	}
	if (modeVerbose) printf("fin analyse liste des fichiers sources\n");
	fclose(srcFile);
	system("rm listesrc.txt");
	if (nbSrcFiles == 0){
		printf("ERROR : aucun fichier source trouves dans src/...\n");
		return -1;
	}
	sprintf(ligneCompilation, "@$(CC) $(CCFLAGS) $< -c -o $@");
	sprintf(ligneLink, "@$(CC) $(LDFLAGS) $(OBJ) -o $@");
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
	fprintf(ficMakefile,"#     généré automatiquement le %s\n", bufferDate);
	fprintf(ficMakefile,"#         avec %s (version du %s %s %s)\n", argv[0], buildDay, buildMonth, buildYear);
	fprintf(ficMakefile,"#                 (c) B. Froger \n");
	fprintf(ficMakefile,"# \n");
	fprintf(ficMakefile,"#############################################################\n");
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	fprintf(ficMakefile,"# Définition des variables\n");
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	fprintf(ficMakefile,"CC=%s\n", compilateur);
	fprintf(ficMakefile,"CCFLAGS=%s\n", ccFlags);
	fprintf(ficMakefile,"LDFLAGS=%s\n", ldFlags);
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"SRCDIR=%s\n", srcDir);
	fprintf(ficMakefile,"INCDIR=%s\n", incDir);
	fprintf(ficMakefile,"OBJDIR=%s\n", objDir);
	fprintf(ficMakefile,"BINDIR=%s\n", binDir);
	fprintf(ficMakefile,"INSTALLDIR=%s\n", repertoireInstallation);
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"SRCCPP=$(wildcard $(SRCDIR)/*.cpp)\n");
	fprintf(ficMakefile,"SRCC=$(wildcard $(SRCDIR)/*.c)\n");
	fprintf(ficMakefile,"TMPCPP=$(patsubst %%.cpp, %%.o, $(SRCCPP))\n");
	fprintf(ficMakefile,"TMPC=$(patsubst %%.c, %%.o, $(SRCC))\n");
	fprintf(ficMakefile,"TMP=$(TMPCPP) $(TMPC)\n");
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
	//strcpy(filename, tblSrcFiles[i].name);
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	fprintf(ficMakefile,"# Définition des règles pour chaque fichier source\n");
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	while (i < nbSrcFiles){
		// on traite ce fichier
		analyseSrc(tblSrcFiles[i++]);
		//strcpy(filename, tblSrcFiles[i++].name);
	}
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	fprintf(ficMakefile,"# Définition des règles utilitaires\n");
	fprintf(ficMakefile,"#------------------------------------------------------------\n");
	fprintf(ficMakefile,"clean: \n");
	fprintf(ficMakefile,"\t@rm -f $(OBJDIR)/* $(BINDIR)/*\n");
	fprintf(ficMakefile,"\t@echo \"Clean OK\"\n");
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"info: \n");
	fprintf(ficMakefile,"\t@echo \"affichage des variables de makefile\"\n");
	fprintf(ficMakefile,"\t@echo \"SRCCPP = \" $(SRCCPP)\n");
	fprintf(ficMakefile,"\t@echo \"SRCC   = \" $(SRCC)\n");
	fprintf(ficMakefile,"\t@echo \"TMPCPP = \" $(TMPCPP)\n");
	fprintf(ficMakefile,"\t@echo \"TMPC   = \" $(TMPC)\n");
	fprintf(ficMakefile,"\t@echo \"TMP    = \" $(TMP)\n");
	fprintf(ficMakefile,"\t@echo \"OBJ    = \" $(OBJ)\n");
	fprintf(ficMakefile,"\t@echo \"EXEC   = \" $(EXEC)\n");
	fprintf(ficMakefile,"\n");
	fprintf(ficMakefile,"install: \n");
	fprintf(ficMakefile,"\t@make\n");
	fprintf(ficMakefile,"\t@rm -f $(INSTALLDIR)/%s\n", appName);
	fprintf(ficMakefile,"\t@cp -f $(BINDIR)/%s %s\n", appName, repertoireInstallation);
	fprintf(ficMakefile,"\t@chmod +x $(INSTALLDIR)/%s\n", appName);
	fprintf(ficMakefile,"\t@echo \"installation de %s dans %s OK\"\n", appName, repertoireInstallation);

	printf("fichier %s généré avec succès \n", makefile);
}