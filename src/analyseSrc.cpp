//
//  Analyse.cpp
//  Generateur de Makefile
//
//  Created by Bruno FROGER on 19/12/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../inc/analyseSrc.hpp"  
#include "../inc/main.hpp"


int analyseSrc(structFichierSource filename){

	FILE *srcFile;
	char ligne[LINE_MAX_LENGTH];
	char tampon[LINE_MAX_LENGTH];

	// recherche de include dans le fichier source
	char ficName[FILENAME_MAX_LENGTH * 2 + 10];
	sprintf(ficName,"%s/%s.%s", srcDir, filename.name, filename.ext);
	if (modeVerbose) printf("traitement du fichier [%s]\n", ficName);
	srcFile = fopen(ficName,"r");
	if (srcFile == NULL){
		printf("ERROR : unable to open %s\n", ficName);
		return -1;
	}

	//std::cout << "creation de l'entree correspondant au fichier " << ficName << "\n";
	fprintf(ficMakefile,"$(OBJDIR)/%s.o: $(SRCDIR)/%s.%s", filename.name, filename.name, filename.ext);

	strcpy(ligne, "");
	while (!feof(srcFile)){
		fgets(ligne,FILENAME_MAX_LENGTH,srcFile);
		ligne[strlen(ligne)-1]='\0';
		char *tmp;
		// on ne prends en compte que les lignes contenant #include
		if (strstr(ligne,"#include") == &ligne[0]){
			// on ne prends pas en compte les lignes contenant "<"
			if (strstr(ligne, "<") == NULL){
				// on accepte que les lignes contenant "*.h"
				if (strstr(ligne, ".h") != NULL){
					//std::cout << "traitement de la ligne " << ligne << "\n";
					while (strchr(ligne,'/') != NULL){
						//std::cout << "\n1	ligne = " << ligne << "\n";
						tmp = strchr(ligne,'/');
						//std::cout << "2	tmp = " << tmp << "\n";
						tmp=&(tmp[1]);
						//std::cout << "3	tmp = " << tmp << "\n";
						strcpy(tampon,tmp);
						strcpy(ligne,tampon);
						//std::cout << "4	ligne = " << ligne << "\n";
					}
					// suppression de la fin de ligne (" et au dela)
					if (strstr(ligne, "\"") != NULL){
						tmp = strstr(ligne, "\"");
						tmp[0]='\0';
					}
					//printf("	tmp = %s\n", tmp);
					//printf("fichier : %s il faut inclure : %s\n", filename, ligne);
					//std::cout << " i = " << i << "\n";
					fprintf(ficMakefile," \\");
					fprintf(ficMakefile, "\n\t$(INCDIR)/%s",ligne);
				}
			}
		}
	}

	fprintf(ficMakefile,"\n\t%s\n", ligneCompilation);
	fprintf(ficMakefile,"\t@echo \"Compilation de $< OK\"\n");
	fprintf(ficMakefile,"\n");
	fflush(ficMakefile);
	return 0;
}