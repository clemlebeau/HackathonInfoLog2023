# HackathonInfoLog2023
Notre entrée au [Hackathon GIGL 2023 de Polytechnique Montréal](https://github.com/MathieuPCorbeil/HackathonGIGL2023/tree/main). Le thème du Hackathon est "Rêve d'enfance", alors nous avons décidé de recréer le jouet pour enfant du crocodile qui mord les doigts. Évidemment, on a adapté les graphiques "à notre sauce" pour rendre le jeu plus représentatif de la terreur ressentie par un jeune enfant alors qu'il y joue.

![Photo du jouet qu'on recrée](http://i2.cdscdn.com/pdt2/0/6/5/1/700x700/gee2009815369065/rw/jouet-crocodile-dentiste-mord-doigts-jeu-enfants-k.jpg "Le jouet qu'on veut recréer")

## Technologies utilisées
Le jeu est programmé en C++ et l'affichage se fait avec la librairie graphique SDL2. Le PRNG (pseudo random number generator) du jeu est initialisé avec un [API qui génère des nombres aléatoires à l'aide de la mécanique quantique](https://qrng.anu.edu.au/).

## Utiliser le projet
Les librairies suivantes sont requises pour compiler le projet: SDL2, SDL2_image, SDL2_mixer, SDL2_ttf.
Le projet a été configuré avec gcc comme compilateur, mais un autre peut être utilisé si vous le souhaitez.

### Exemple d'installation des librairies avec MinGW
Installation du compilateur
```bash
pacman -Sy mingw-w64-x86_64-gcc
```
Installation des librairies
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
