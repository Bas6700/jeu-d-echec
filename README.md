Peut-être compilé en faisant: make echecs
Pour supprimer les .o et le binaire: make clear
Le dossier html peut-être reproduit avec: make Doxy
Puis pour jouer au jeu il suffit d'éxecuter le fichier binaire echecs créé.

Le jeu comporte toutes les fonctionnalités demandés dans l'énnoncé.

D'un point de vue chronologique, le code du programme a été écrit suivant les étapes
donnés par l'ennoncé.

L'une des fonctions les plus difficile à codé a été la fonction déplace. En effet celle-ci
est utilisé par beaucoup d'autre fonction. Elle est notamment utilisé par danger pour tester
les cases menacés par l'adversaires, par les fonctions relatif au echec et au pat, et permet des vrai
déplacement sur l'échiquier.
Ainsi il a fallu distinguer ces cas dans la fonctions déplace et cette implémentation n'a pas été facile.

De même, la mise en place d'une fonction pour gérer la règle des trois position identique n'a pas été simple
car cela demande la gestion de l'historique de la partie. De plus cette règle demande que les coups possibles
soit identique, notamment il faut faire attention au roque et à la prise en passante.
