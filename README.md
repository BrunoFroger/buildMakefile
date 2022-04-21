# Programme générateur de Makefile : buildMakefile

buildMakefile permet de générer automatiquement vos makefiles, il accepte un certain nombre de parametres en ligne de commande ainsi qu'un fichier de configuration optionnel (buildMakefile.cfg).

## Syntaxe
La syntaxe de lancement de ce programme est :

	buildMakefile [options] nomProjet [options]

* nomProjet : correspontd au nom de l'executable qui ser agénéré par le makefile ainsi généré
* Les options disponibles à l'execution sont :
	* -c : modifie le compilateur (c++ par default)
  	* -f : nom du fichier makefile généré (makefile.result par défault)
  	* -h : affichage de l'aide 
  	* -d : change le repertoire de deloiement
    * -s : change le repertoire dans lequel se situe les fichiers source
    * -i : change le repertoire dans lequel se situe les fichiers include
    * -o : change le repertoire dans lequel sont générés les fichiers objet
    * -b : change le repertoire dans lequel est généré le fichier executable

Le resultat de cette commande se trouve dans le fichier *makefile.result* (ce nom est modifiable avec l'option -f)

## Contraintes d'utilisation
Vous devez organiser votre projet de la façon suivante :
* racine du projet
    - fichier Makefile
    - fichier README.md
    - repertoire src (modifiable avec l'option -s)
    	- repertoire contenant les fichiers source que vous avez créés
    - repertoire inc (modifiable avec l'option -s)
    	- repertoire contenant les fichiers include que vous avez créés
    - repertoire obj (modifiable avec l'option -o)
    	- contient les fichiers objets généré par make
    - repertoire bin (modifiable avec l'option -b)
    	- contient l'executable *buildMakefile* généré par make
    - fichier résultat *makefile.result* généré par buildMakefile
   
## options du makefile
dans le makefile généré, les options suivantes sont disponibles :
* clean : efface les fichiers objet et l'executable
* ALL : genere l'ensemble des fichiers
* install : build et copie l'executable dans le repertoire d'installation (~/bin par default) ce répertoire doit etre dans votre path pour que l'application soit utilisable partout sur votre ordinateur.


## fichier de configuration
Le fichier de configuration optionnel doit repondre aux contraintes suivantes :
* le nom du fichier de configuration doit obliagoirement etre le même nom que l'executable buildMakefile avec l'extention '.cfg'
* une seule affectation par ligne
* lignes vides possibles
* une ligne valide d'affectation doit contenir un et un seul symbole '='
	* le texte avant '=' correspond au nom de la variable
    * le texte apres '=' correspond a la valeur que l'on souhaite affecter a cette variable
* il est possible de mettre des espaces avant et apres les noms de variables et des valeurs
* les variables disponibles sont :
	- SRCDIR (src par default)
    - INCDIR (inc par default)
    - OBJDIR (obj par default)
    - BINDIR (bin par default)
    - INSTALLDIR (~/bin par default)
    - MAKEFILENAME (makefile.result par default)
    - COMPILATEUR (C++ par default)
* les variables non definies dans ce fichier prennent leur valeur par defaut