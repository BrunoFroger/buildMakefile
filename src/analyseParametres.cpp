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
    printf("    appName : nom de l'application qui sera générée par le makefile\n");
    printf("    options : \n");
    printf("        -h : cette aide\n");
    printf("        -c : change le nom du compilateur (c++ par défault)\n");
    printf("        -e : change la variable CCFLAGS (-Wall par défault)\n");
    printf("        -l : change la variable LDFLAGS (\"\" par défault)\n");
    printf("        -f : change le nom du makefile généré (makefile.result par défault)\n");
    printf("        -d : change le repertoire de déploiement (~/bin par défaul)\n");
    printf("        -s : change le repertoire ou vous avez stocké vos fichiers source (src par défaul)\n");
    printf("        -i : change le repertoire ou vous avez stocké vos fichiers include (inc par défaul)\n");
    printf("        -o : change le repertoire ou sont générés les fichiers objet (obj par défaul)\n");
    printf("        -b : change le repertoire ou est généré le fichier executable (bin par défaul)\n");
    printf("        -v : mode verbose\n");
    printf(" Architecture des répertoires de votre projet pour une utilisation standard :\n");
    printf("        Racine du projet :\n");
    printf("            makefile\n");
    printf("            src : repertoire contenant vos fichiers source (.cpp)\n");
    printf("            inc : repertoire contenant vos fichiers include (.h*)\n");
    printf("            obj : repertoire contenant les fichiers objet générés (.o)\n");
    printf("            bin : repertoire contenant l'exécutable généré\n");
    printf("\n");
    printf("Pour une aide plus complète consulter la doc sur GitHub : https://github.com/BrunoFroger/buildMakefile/blob/main/README.md\n");
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
    /*
    if (argc < 2) {
		printf("ERROR : manque parametre\n");
        aide(argv[0]);
		exit(-1);
    }*/
    if (argc >= 2){
        // il y a des parametres a analyser
        do {
            if (modeVerbose) printf("traitement du parametre numero %d\n", i);
            strcpy(param, argv[i]);
            //printf("analyse de %s\n", param);
            if (param[0] != '-'){
                sprintf(appName,"%s", argv[i]);
            } else {
                //printf("gestion d'une option %s\n", param);
                switch(param[1]){
                    case 'b' : // change repertoire des fichiers binaire
                        checkNbParametres(i, argc);
                        sprintf(binDir, "%s", argv[++i]);
                        break;
                    case 'c' : // change nom du compilateur
                        checkNbParametres(i, argc);
                        sprintf(compilateur, "%s", argv[++i]);
                        break;
                    case 'd' : // change repertoire d'installation
                        checkNbParametres(i, argc);
                        sprintf(repertoireInstallation, "%s", argv[++i]);
                        //printf("nouveau repertoire d'installation : %s \n", repertoireInstallation);
                        break;
                    case 'e' : // change ccFlags
                        checkNbParametres(i, argc);
                        sprintf(ccFlags, "%s", argv[++i]);
                        break;
                    case 'f' : // change nom du fichier makefile généré
                        checkNbParametres(i, argc);
                        sprintf(makefile, "%s", argv[++i]);
                        break;
                    case 'h' : // aide
                        aide(argv[0]);
                        break;
                    case 'i' : // change repertoire des fichiers include
                        checkNbParametres(i, argc);
                        sprintf(incDir, "%s", argv[++i]);
                        break;
                    case 'l' : // change ldFlags
                        checkNbParametres(i, argc);
                        sprintf(ldFlags, "%s", argv[++i]);
                        break;
                    case 'o' : // change repertoire des fichiers objet
                        checkNbParametres(i, argc);
                        sprintf(objDir, "%s", argv[++i]);
                        break;
                    case 's' : // change repertoire des fichiers source
                        checkNbParametres(i, argc);
                        sprintf(srcDir, "%s", argv[++i]);
                        break;
                    case 'v' : // active mode verbose
                        modeVerbose=true;
                        break;
                    default :
                        printf("option inconnue %s\n", param);
                        exit(-1);
                }
            }
        } while (++i < argc);
    }
	if (strcmp(appName,"") == 0){
		printf("ERROR : manque parametre (nom de l'application)\n");
		printf( "	%s [AppName]\n",  argv[0]);
		exit(-1);
	}
    //printf("Analyse des parametres => fin\n");
}