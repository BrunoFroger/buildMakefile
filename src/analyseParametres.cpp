//
//  analyseParametres.cpp
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

//-----------------------------------
//
//      aide
//
//-----------------------------------
void aide(char *nomProgramme){
    printf("syntaxe : %s [options] appName [options]\n", nomProgramme);
    printf("    appName : nom de l'application qui sera généré par le makefile\n");
    printf("    options : \n");
    printf("        -c : modifie le nom du compilateur (c++ par défault)\n");
    printf("        -f : modifie le nom du makefile généré (makefile.result par défault)\n");
    printf("        -h : cette aide\n");
    printf("        -i : change repertoire d'installation (~/bin par défaul)\n");
    printf("\n");
}

//-----------------------------------
//
//      checkNbParametres
//
//-----------------------------------
void checkNbParametres(int i, int argc){
    if (i >= argc - 1) {
        printf("manque un parametre\n");
        exit(-1);
    }
}

//-----------------------------------
//
//      analyseParametres
//
//-----------------------------------
void analyseParametres(int argc, char **argv){
    //printf("Analyse des parametres => debut\n");
    int i = 1;
    char param[50];
    strcpy(appName,"");
    if (argc < 2) {
		printf("ERROR : manque parametre\n");
        aide(argv[0]);
		exit(-1);
    }
    do {
        //printf("traitement du parametre numero %d\n", i);
        strcpy(param, argv[i]);
        //printf("analyse de %s\n", param);
        if (param[0] != '-'){
	        sprintf(appName,"%s", argv[i]);
        } else {
            //printf("gestion d'une option %s\n", param);
            switch(param[1]){
                case 'c' : // change nom du compilateur
                    checkNbParametres(i, argc);
                    sprintf(compilateur, "%s", argv[++i]);
                    break;
                case 'f' : // change nom du fichier makefile généré
                    checkNbParametres(i, argc);
                    sprintf(makefile, "%s", argv[++i]);
                    break;
                case 'h' : // aide
                    aide(argv[0]);
                    break;
                case 'i' : // change repertoire d'installation
                    checkNbParametres(i, argc);
                    sprintf(repertoireInstallation, "%s", argv[++i]);
                    //printf("nouveau repertoire d'installation : %s \n", repertoireInstallation);
                    break;
                default :
                    printf("option inconnue %s\n", param);
                    exit(-1);
            }
        }
    } while (++i < argc);
	if (strcmp(appName,"") == 0){
		printf("ERROR : manque parametre (nom de l'application)\n");
		printf( "	%s [AppName]\n",  argv[0]);
		exit(-1);
	}
    //printf("Analyse des parametres => fin\n");
}