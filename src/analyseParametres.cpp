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
    printf("    options : \n");
    printf("        -h : cette aide\n");
    exit(0);
}

//-----------------------------------
//
//      analyseParametres
//
//-----------------------------------
void analyseParametres(int argc, char **argv){
    printf("Analyse des parametres => debut\n");
	if (argc < 2){
		printf("ERROR : manque parametre (nom de l'application)\n");
		printf( "	%s [AppName]\n",  argv[0]);
		exit(-1);
	}
    int i = 1;
    char param[50];
    do {
        //printf("traitement du parametre numero %d\n", i);
        strcpy(param, argv[i]);
        //printf("analyse de %s\n", param);
        if (param[0] != '-'){
	        sprintf(appName,"bin/%s",argv[1]);
        } else {
            //printf("gestion d'une option %s\n", param);
            switch(param[1]){
                case 'c' : // aide
                    sprintf(compilateur, "%s", argv[i++]);
                    break;
                case 'h' : // aide
                    aide(argv[0]);
                    break;
                default :
                    printf("option inconnue %s\n", param);
                    exit(-1);
            }
        }
    } while (++i < argc);
    printf("Analyse des parametres => fin\n");
}