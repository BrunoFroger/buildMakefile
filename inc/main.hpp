//
//  main.hpp
//  Generateur de Makefile
//
//  Created by Bruno FROGER on 19/12/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.

#include <iostream>

#ifndef main_hpp
#define main_hpp

#define NB_FILES_MAX			100
#define FILENAME_MAX_LENGTH		100
#define LINE_MAX_LENGTH			100


    extern char tblSrcFiles[NB_FILES_MAX][FILENAME_MAX_LENGTH];
    extern FILE *ficMakefile;
    extern char appName[FILENAME_MAX_LENGTH];
    extern char makefile[FILENAME_MAX_LENGTH];
    extern char compilateur[10];
    extern char ligneCompilation[100];
    extern char ligneLink[100];

#endif
