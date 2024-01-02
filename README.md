# Voyageur de commerce (TSP : The Traveling Salesman Problem)

Ceci est la résolution d’un TP fil rouge sur le voyageur de commerce. Le code est implémenté est C.

Module : Résolution de problèmes difficiles, ING3 Mineure IA, 2023/2024, Calais. 

## Structure du projet

### Code source
Le projet est composé de 4 pairs de fichier (.c et .h):

- `initialisation` : Réponses aux questions de la Partie 1
- `descentes`: Réponses aux questions de la Partie 2
- `local_search`: Réponses aux questions de la Partie 3 (ILS et SW)
- `execution_comparison` : Protocole expérimental, partie 4

L'entêtes des fonctions implémentées se trouvent dans les fichiers .h. Les fonctions de certaines parties utilisent celles des parties précedentes. 

#### Fichier execution_comparison(.h et .c)
Ici nous avons les fonctions `execute_descentes`, `execute_ILS`, `execute_SW` qui lancent les éxécutions des algos de descentes, ILS et SW respectivement et enregistrent le rapports dans des fichiers csv dans les dossiers execution_results*.

Ces fonctions sont appellées dans la fonction `execution` où les differents arguments sont initialisés. On peut appeler seulement l'une ou deux d'entre elles selon ce qu'on souhaite lancer (c'est plus simple de commenter).

La variable `instances_path` de la fonction `execution` peut être adapté pour référer de nouvelles instances. Ne pas oublier d'adapter aussi l' rgument `nb_instances` en appelant `execute_descentes`, `execute_ILS` ou `execute_SW` selon le nombre d'instances.
On peut d'ailleurs jouer sur cet argument pour ne lancer que quelques instances. Si `nb_instances=2`, même si  `instances_path` a plus de 2 instances, seulement les deux premiers seront traités. C'est aussi applicable pour la liste des algos.

La fonction execution peut alors être appelé dans la fonction main : `main.c`.

#### Fichier main.c
Ici plusieurs fonctions sont testées separemment. On peut commenter ou decommenter certains selon ce qu'on veut voir.


## Compilation et éxécution
Ce projet contient un `makefile`.

- Pour compiler
```bash
    make
```

- Pour exécuter
```bash
    make run
```
ou

```bash
    ./prog
```

- Pour exécuter en mode debug
```bash
    make debug
```
ou

```bash
    gdb ./prog
```
