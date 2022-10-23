# La Prépa dans votre terminal

## Introduction

***La prépa dans votre terminal*** est une implémentation du [jeu de la vie](https://fr.wikipedia.org/wiki/Jeu_de_la_vie) en C. \
Ce projet rentre dans le cadre du devoir "[Projet de Fin de Période 1](https://lyc-champollion.ac-grenoble.fr/moodle/mod/page/view.php?id=25053)" du cours d'informatique de la MP2I du Lycée Champollion.

## Présentation

Le Jeu de la Vie (Game Of Life) est un automate cellulaire dans lequel les cellules illustrent le chaos déterministe (l'exemple le plus connu de chaos déterministe est le double pendule). En d'autres termes, le comportement des cellules est imprévisible dans le détail car il dépend trop des conditions initiales. 

Le Jeu de la Vie a été inventé par John Conway (1937 - 2020) en 1970. Le jeu se déroule dans une grille à deux dimensions, où l'utilisateur peut définir une grille initiale. A chaque époque, le jeu met à jour la grille en respectant les règles énoncées ci-dessous : 
- Une cellule devient vivante si elle possède strictement trois voisines vivantes,
- Une cellule reste dans son état précédent si elle possède strictement deux voisins vivantes,
- Sinon, la cellule devient morte.

## Installation

## Utilisation

L'utilisateur peut choisir trois options à son arrivée :
- `h` : ouvre le menu d'aide,
- `f` : ouvre une grille créée au préalable dans un fichier texte,
- `r` : génère une grille aléatoire.
- `s` : ouvre un menu répertoriant les structures les plus connues du jeu.

La grille créée par l'utilisateur doit être un rectangle de taille `m` par `n`. Chaque cellule est matérialisée par un nombre : `0` si elle est morte, `1` si elle est vivante. Attention, il ne faut pas mettre d'espace entre les cellules, et le programme n'a pas besoin de signe distinctif pour s'arrêter.

A chaque époque, le programme affiche la grille mise à jour.
