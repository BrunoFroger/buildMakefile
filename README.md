# buildMakefile

buildMakefile permet de générer automatiquement vos makefiles

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
   

dans le makefile généré, les options suivantes sont disponibles :
* clean : efface les fichiers objet et l'executable
* ALL : genere l'ensemble des fichiers
* install : build et copie l'executable dans le repertoire d'installation (~/bin par default) ce répertoire doit etre dans votre path pour que l'application soit utilisable partout sur votre ordinateur.