# HackathonInfoLog2023
## Présentation du projet
Notre entrée au [Hackathon GIGL 2023 de Polytechnique Montréal](https://github.com/MathieuPCorbeil/HackathonGIGL2023/tree/main)[0] réalisée du 17 au 21 novembre 2023. Le thème du Hackathon est "Rêve d'enfance", alors nous avons décidé de recréer le jouet pour enfant du crocodile qui mord les doigts quand on pèse sur la mauvaise dent. Évidemment, on a adapté les graphiques "à notre sauce" pour rendre le jeu plus représentatif de la terreur ressentie par un jeune enfant alors qu'il y joue.

### Photo du jouet qu'on recrée
![Photo du jouet qu'on recrée](http://i2.cdscdn.com/pdt2/0/6/5/1/700x700/gee2009815369065/rw/jouet-crocodile-dentiste-mord-doigts-jeu-enfants-k.jpg "Le jouet qu'on veut recréer")
[Image du jouet dans la réalité](http://i2.cdscdn.com/pdt2/0/6/5/1/700x700/gee2009815369065/rw/jouet-crocodile-dentiste-mord-doigts-jeu-enfants-k.jpg)[1]

## Équipe et séparation du travail
Notre équipe est composée de 3 personnes: [Clément Jevardat de Fombelle](https://github.com/clemdef), [Maya Forest](https://github.com/bacondelicorne) et [Clément Lebeau](https://github.com/clemlebeau).

Voici comment nous nous sommes séparé les tâches:
- Clément Jevardat de Fombelle : Tâches pointues entourant l'implémentation des nombres aléatoires et implémentation du mode plein écran (qui ne s'est malheureusement pas rendu dans la version finale du projet par manque de temps)
- Maya Forest : Textures du projet, design graphique, brainstorming
- Clément Lebeau : Intégration de l'aléatoire et des textures au jeu, affichage et logique interne du jeu.

## Technologies utilisées
Le jeu est programmé en C++ et l'affichage se fait avec la librairie graphique [SDL2](https://www.libsdl.org/)[2]. Le PRNG (pseudo random number generator) du jeu est initialisé avec un [API qui génère des nombres aléatoires à l'aide de la mécanique quantique](https://qrng.anu.edu.au/)[3] puis on utilise ensuite des librairies cryptographiques pour maximiser la qualité de nos nombres aléatoires.

Pour le positionnement des dents du crocodile dans la scène GameScene, nous avons chargé les positions depuis un fichier.

## Apprentissages réalisés
Participer à ce Hackathon nous a permis d'apprendre et développer plusieurs habiletés. Nous n'avions jamais fait de projet qui demandait à ce qu'on *link* nous-même nos librairies aux compilateur, ce fut donc l'occasion parfaite d'apprendre à mieux le gérer et l'utiliser, même si ce n'est pas encore parfait. Nous avons pu utiliser des librairies que nous n'avions jamais utilisé auparavant, comme `curl` pour envoyer une requête à un API externe. Évidemment, nous avons du laisser tomber quelques idées que nous voulions implémenter dans notre jeu, étant donné que nous n'avions pas beaucoup de temps pour le réaliser. Nous avons aussi appris à travailler avec des coéquipiers n'ayant pas les mêmes expérience que nous, ce qui pouvait parfois être limitant dans l'entre-aide et rendre plus difficile le debugging. Évidemment, pour remettre ce projet, il fallait apprendre à faire fonctionner notre programme sur d'autres ordinateurs que le nôtre (nous avons fait de notre mieux, espérons que ça fonctionne sur le vôtre). Finalement, nous avons appris à réutiliser du code et l'adapter à nos besoins (voir [sous-section Notes](#notes)).

## Notes 
Les classes ajoutées au [commit 52fd109](https://github.com/clemlebeau/HackathonInfoLog2023/commit/52fd109c2d51bb1aad5395281e43e4db0d0ebb52) font partie d'un petit cadriciel que j'ai (Clément Lebeau) développé dans le cadre d'un projet au cégep avec 2 personnes (Louis-Philippe Dalmont et Mikaël Bureau) [4]. Le but de ce cadriciel dans notre projet actuel était de faciliter l'utilisation de la librairie graphique SDL avec un paradigme orienté-objet. Ces classes contiennent d'ailleurs l'ancienne documentation qui était demandée dans notre projet du cégep, c'est pourquoi certains fichiers ont un attribut `@author` qui ne semble pas venir d'un membre de l'équipe du Hackathon. 

## Utiliser le projet
Les librairies suivantes sont requises pour compiler le projet: 
- SDL2
- SDL2_image
- SDL2_mixer
- SDL2_ttf
- curl
- openssl 
- cstdlib

Le projet a été configuré avec g++ comme compilateur, mais un autre peut être utilisé si vous le souhaitez. (Voir `tasks.json` dans le dossier `source/.vscode` pour une idée des flags à utiliser.) 

Ce projet a été conçu pour Windows 64 bit et n'a pas été testé ou compilé pour d'autres systèmes d'exploitation.

### Exemple d'installation des librairies avec MinGW

#### Installation de MSYS2
Visiter [le site de MSYS2](https://www.msys2.org/)[5] et cliquer sur "Download the installer".
Suivre les étapes d'installation par défaut.

Entrer les prochaines commandes dans un terminal MSYS2.

#### Installation du compilateur et du debugger
```bash
pacman -Sy mingw-w64-x86_64-gcc
```
```bash
pacman -Sy mingw-w64-x86_64-gdb
```

#### Installation des librairies
```bash
pacman -Sy mingw-w64-x86_64-SDL2
```
```bash
pacman -Sy mingw-w64-x86_64-SDL2_image
```
```bash
pacman -Sy mingw-w64-x86_64-SDL2_mixer
```
```bash
pacman -Sy mingw-w64-x86_64-SDL2_ttf
```
```bash
pacman -Sy mingw-w64-x86_64-openssl
```
```bash
pacman -Sy mingw-w64-x86_64-curl
```

#### Tout installer d'un coup: le pactol
```bash
pacman -Sy mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-openssl mingw-w64-x86_64-curl
```

## Références
[0]Hackathon GIGL 2023 de Polytechnique Montréal (https://github.com/MathieuPCorbeil/HackathonGIGL2023/tree/main)<br>
[1]Image du crocodile (http://i2.cdscdn.com/pdt2/0/6/5/1/700x700/gee2009815369065/rw/jouet-crocodile-dentiste-mord-doigts-jeu-enfants-k.jpg)<br>
[2]Librairie SDL2 (https://www.libsdl.org/)<br>
[3]API QRNG (https://qrng.anu.edu.au/)<br>
[4]Travail d'équipe `WormsQQCH` réalisé au Cégep Régional de Lanaudière à Joliette par Louis-Philippe Dalmont, Mikaël Bureau et Clément Lebeau (Git repo privé)<br>
[5]Site de MSYS2 (https://www.msys2.org/)<br>
