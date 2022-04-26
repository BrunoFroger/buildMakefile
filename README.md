# Générateur de Makefile : buildMakefile

buildMakefile permet de générer automatiquement vos makefiles, il accepte un certain nombre de paramètres en ligne de commande ainsi qu'un fichier de configuration optionnel (buildMakefile.cfg). 

## Syntaxe
La syntaxe de lancement de ce programme est :

    buildMakefile [options] nomProjet [options]

* nomProjet : correspond au nom de l'exécutable qui sera généré par le makefile ainsi généré
* Les options disponibles à l'exécution sont :
    * -c : modifie le compilateur (c++ par default)
    * -f : nom du fichier makefile généré (makefile.result par défaut)
    * -e : change la variable CCFLAGS (-Wall par défault)\n");
    * -l : change la variable LDFLAGS (\"\" par défault)\n");
    * -h : affichage de l'aide 
    * -d : change le répertoire de déploiement
    * -s : change le répertoire dans lequel se situe les fichiers source
    * -i : change le répertoire dans lequel se situe les fichiers include
    * -o : change le répertoire dans lequel sont générés les fichiers objet
    * -b : change le répertoire dans lequel est généré le fichier exécutable
    * -v : active le mode verbose : affichage d'informations de progression  

Le résultat de cette commande se trouve dans le fichier *makefile.result* (ce nom est modifiable avec l'option -f)

## Ordre de prise en compte des paramètres (du moins prioritaire au plus prioritaire)
* Valeurs par défault
* Fichier de configuration
* Paramètres en ligne de commande

## Contraintes d'utilisation
Vous devez organiser votre projet de la façon suivante :
* racine du projet
    - fichier Makefile
    - fichier README.md
    - répertoire src (modifiable avec l'option -s)
        - répertoire contenant les fichiers source que vous avez créés (externtion .cpp obligatoire)
    - répertoire inc (modifiable avec l'option -i)
        - répertoire contenant les fichiers include que vous avez créés
    - répertoire obj (modifiable avec l'option -o)
        - contient les fichiers objets généré par make
    - répertoire bin (modifiable avec l'option -b)
        - contient l'exécutable *buildMakefile* généré par make
    - fichier résultat *makefile.result* généré par buildMakefile
   
## options du makefile
dans le makefile généré, les options suivantes sont disponibles :
* clean : efface les fichiers objet et l'exécutable
* ALL : génère l'ensemble des fichiers
* install : build et copie l'exécutable dans le répertoire d'installation (~/bin par default) ce répertoire doit être dans votre path pour que l'application soit utilisable partout sur votre ordinateur.

## fichier de configuration
Le fichier de configuration optionnel doit répondre aux contraintes suivantes :
* il doit être dans le répertoire racine de votre projet au même niveau que le makefile.
* le nom du fichier de configuration doit obligatoirement être le même nom que l'exécutable buildMakefile avec l'extension '.cfg'
* une seule affectation par ligne
* lignes vides possibles
* une ligne valide d'affectation doit contenir un et un seul symbole '='
    * le texte avant '=' correspond au nom de la variable
    * le texte après '=' correspond à la valeur que l'on souhaite affecter à cette variable
* il est possible de mettre des espaces avant et après les noms de variables et des valeurs
* les variables disponibles sont :
    - SRCDIR (src par default) : nom du repertoire des fichiers source que vous écrivez
    - INCDIR (inc par default) : nom du repertoire des fichiers include que vous écrivez
    - OBJDIR (obj par default) : nom du repertoire des fichiers objets générés
    - BINDIR (bin par default) : nom du repertoire du fichier executable généré
    - INSTALLDIR (~/bin par default) : nom du repertoire d'installation du fichier executable (make install)
    - MAKEFILENAME (makefile.result par default) : nom du fichier makefile généré
    - APPNAME (pas de valeur par default) : nom de binaire applicatif généré
    - COMPILATEUR (C++ par default) : nom du compilateur a utiliser
* les variables non définies dans ce fichier prennent leur valeur par défaut


