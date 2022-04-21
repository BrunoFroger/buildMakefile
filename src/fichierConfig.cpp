//
//  fichierConfig.cpp
//  Generateur de Makefile
//
//  Created by Bruno FROGER on 19/12/2017.
//  Copyright © 2022 Bruno FROGER. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../inc/main.hpp"

//-----------------------------------
//
//      setVariable
//
//-----------------------------------
void setVariable(char *varName, char *varValue){
    if (strcmp(varName, "SRCDIR") == 0){
        strcpy(srcDir, varValue);
    } else if (strcmp(varName, "INCDIR") == 0){
        strcpy(incDir, varValue);
    } else if (strcmp(varName, "OBJDIR") == 0){
        strcpy(objDir, varValue);
    } else if (strcmp(varName, "BINDIR") == 0){
        strcpy(binDir, varValue);
    } else if (strcmp(varName, "INSTALLDIR") == 0){
        strcpy(repertoireInstallation, varValue);
    } else if (strcmp(varName, "MAKEFILENAME") == 0){
        strcpy(makefile, varValue);
    } else if (strcmp(varName, "COMPILATEUR") == 0){
        strcpy(compilateur, varValue);
    } else {
        printf("nom de variable inconnu : %s \n", varName);
        exit(-1);
    }
    printf("fichier de configuration => %s = %s\n", varName, varValue);
}

//-----------------------------------
//
//      litFichierConfig
//
//-----------------------------------
void litFichierConfig(char *fichier){
    FILE *ficConfig;
    char ligne[100];
    char *tmp, *tmp1;
    char varName[100];
    char varValue[100];

    ficConfig = fopen(fichier, "r");
    if (ficConfig == NULL){
        printf("******************************************************\n");
        printf("*  Fichier de configuration %s non trouvé\n", fichier);
        printf("*  On utilise les parametres par defaut\n");
        printf("******************************************************\n");
        return;
    }
    printf("Analyse du fichier de configuration %s\n", fichier);
    while (!feof(ficConfig)){
        fgets(ligne, 100, ficConfig);
        if (ligne[strlen(ligne) - 1] == '\n') ligne [strlen(ligne) - 1] = '\0';
        //printf("------------------------------\n");
        //printf("Analyse de la ligne <%s>", ligne);
        // suppression des blancs en denbut de ligne
        tmp = ligne;
        while (tmp[0] == ' ') tmp++;
        strcpy(ligne, tmp);
        tmp = strchr(ligne, '=');
        if (tmp != NULL ){
            // traitement du nom de variable
            strcpy(varName,ligne);
            varName[strlen(ligne) - strlen(tmp)] = '\0';
            // suppression des ' ' en fin de chaine
            while (varName[strlen(varName)- 1] == ' ') varName[strlen(varName) - 1] = '\0';

            // traitement de la valeur de la variable
            // suppression des '=' et ' ' en debut de chaine
            while ((tmp[0] == '=') || (tmp[0] == ' ')) tmp++;
            // suppression des ' ' en fin de chaine
            while (tmp[strlen(tmp)- 1] == ' ') tmp[strlen(tmp) - 1] = '\0';
            strcpy(varValue, tmp);

            //printf(" => varName = <%s>, varValue = <%s>\n", varName, varValue);
            setVariable(varName, varValue);
        } else {
            //printf("\n");
        }
    }
    //printf("------------------------------\n");
}
