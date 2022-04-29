//
//  main.hpp
//  Generateur de Makefile
//
//  Created by Bruno FROGER on 19/12/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.

#include <iostream>

#ifndef main_hpp
#define main_hpp

#define NB_FILES_MAX			200
#define FILENAME_MAX_LENGTH		100
#define LINE_MAX_LENGTH			100

    typedef struct {
        char name[FILENAME_MAX_LENGTH];
        char ext[10];
    } structFichierSource;

    //extern char tblSrcFiles[NB_FILES_MAX][FILENAME_MAX_LENGTH];
    extern structFichierSource tblSrcFiles[NB_FILES_MAX];
    extern FILE *ficMakefile;
    extern char appName[FILENAME_MAX_LENGTH];
    extern char makefile[FILENAME_MAX_LENGTH];
    extern char repertoireInstallation[FILENAME_MAX_LENGTH];
    extern char compilateur[10];
    extern char ligneCompilation[100];
    extern char ligneLink[100];
    extern char srcDir[100];
    extern char incDir[100];
    extern char objDir[100];
    extern char binDir[100];
    extern char ccFlags[100];
    extern char ldFlags[100];
    extern bool modeVerbose;

#endif
