TODO

# mise a jour de la doc
# mise a jour de l'aide en ligne

# ajouter les options de lancement :
    - modification des repertoires 
      - src (-s)
      - inc (-i)
      - obj (-o)
      - bin (-b)

# prevoir un fichier de conf pour prendre en compte les options par default
    - nom des variables definissables dans le fichier de conf :
      - SRC_DIR (src par default)
      - INC_DIR (inc par default)
      - OBJ_DIR (obj par default)
      - BIN_DIR (bin par default)
      - INSTALL_DIR (~/bin par default)
      - MAKEFILE_NAME (makefile.result par default)
      - COMPILER (C++ par default)
    - La syntaxe de definition est la suivante :
      - NOM_VARIABLE = valeur
    - en cas d'erreur détectée dans le fichier de conf => fin de programme
    - Si une variable n'est pas présente dans le fichier de conf, c'est sa valeur par default qui est prise en compte
