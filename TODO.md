TODO

# mise a jour de la doc
# mise a jour de l'aide en ligne

# prevoir un fichier de conf pour prendre en compte les options par default
    - nom des variables definissables dans le fichier de conf :
      - SRCDIR (src par default)
      - INCDIR (inc par default)
      - OBJDIR (obj par default)
      - BINDIR (bin par default)
      - INSTALLDIR (~/bin par default)
      - MAKEFILENAME (makefile.result par default)
      - COMPILATEUR (C++ par default)
    - La syntaxe de definition est la suivante :
      - NOM_VARIABLE = valeur
    - en cas d'erreur détectée dans le fichier de conf => fin de programme
    - Si une variable n'est pas présente dans le fichier de conf, c'est sa valeur par default qui est prise en compte
