# TP 3/4

Ce TP sera à réaliser sur deux séances. Merci d'aller aussi loin que possible dans le TP3!

# Prérequis

- [CMake](https://cmake.org) (Déjà installé sur les serveurs de l'isima)
- Un compilateur C (Déjà installé sur les serveurs de l'isima)
- Une machine linux (Possible de faire le TP sur Windows pour les aventureux, mais pour simplifier le TP est écrit pour une machine linux!)

# Compiler

## Cmake

Très rapidement: CMake est un "meta buildsystem", et permet de générer des fichier de build (pour ensuite être utilisé par `make`, Visual Studio, XCode, ...).
Vous pourrez vous contenter de suivre les 3 commandes utilisées plus bas pour compiler le projet.
Le projet est décrit par le fichier `CMakeLists.txt` (pour les curieux).

## Configuration

CMake nécessite une étape dite de "configuration". On va pour le moment garder les options par défaut:

`cmake -B build .`

Une fois cette dernière réalisée, il n'y a plus besoin de la relancer (sauf si vous voulez changer la configuration du build!).

Vous constaterez que cmake va vous générer des fichier (notamment un makefile dans notre cas) dans le dossier `build/`. Ce dossier peut être supprimé ou recréé (via la même commande) sans problème.


## Compiler le programme

Pour compiler vous avez le choix entre:
- lancer `make` depuis le dossier `build`
- lancer `cmake --build build` depuis le dossier courant

## Lancer le programme

Le programme va être généré sous le nom `imageconvert` dans le dossier de `build`.
Vous pouvez:
- Le lancer à la main
- Pour simplifier, j'ai préconfiguré l'execution de certaines commandes en tant que tests. Vous pouvez les lancer (après avoir recompilé si besoin) via:
  - Soit `make test` depuis le dossier `build`
  - Soit `cmake --build build --target test` depuis le dossier courant
  - Pour voir la sortie des tests, rajouter `ARGS=-V` à la fin de la commande (`make test ARGS=-V`)

## Clean

Pour nettoyez le dossier de build, utilisez `make clean` ou `cmake --build build --target clean`. Si vous voulez vraiment tout remettre à zéro, supprimez le dossier `build` complètement.

## TL;DR

Lancez (une fois) `cmake -B build .`.

Puis quand vous faites des changements:

Depuis le dossier `build`:
- `make && make test`

Depuis le dossier courant:
- `cmake --build build && cmake --build build --target test`

# Le programme

Nous allons aujourd'hui convertir des images d'un format vers un autre et tenter d'optimiser un peu !

L'objectif est de faire cela le plus rapidement possible, le tout en utilisant les fonctionnalités de votre système d'exploitation bien entendu.

Pour commencer, le programme prend simplement en parametre des chemins de fichiers, qui sont les images a convertir. Celles-ci seront automatiquement mises dans le dossier `.out`.

Examples: 
- `imageconvert images/chat.jpg` va lire le fichier `images/chat.jpg` et la convertir en fichier `out/chat.png`.
- `imageconvert images/chat.jpg images/chien.jpg` idem pour les deux images.

A noter que le programme vous affichera les durées de chacune des étapes.

## Les sources

- [`src/main.c`](src/main.c): C'est là que vous aller travailler !
- [`inlcude/utils.h`](inlcude/utils.h): Quelques fonctions utilitaires
- `include/stb_image*.h`: Deux petites librairies qui permettent de lire/écrire des images.
- [`workingdir`](workingdir): Le répertoire de travail, c'est là que sont lancés les tests. Contient des images à convertir dans le sous-dossier [`images`](workingdir/images/).
- [`CMakeLists.txt`](CMakeLists.txt): Décrit comment compiler le projet et comment lancer les tests.

## Constatez que c'est lent

Lancez les tests, ils sont configurés pour convertir les images.
Chaque test lance le programme avec une commande du type `imageconvert images/chat.jpg`. (Vous pouvez les consulter dans le fichier [`CMakeLists.txt`](CMakeLists.txt))
Sur ma machine j'obtient les résultats suivants:

```sh
Running tests...
Test project /home/lectem/tests/tp3/build
    Start 1: IC.furet
1/4 Test #1: IC.furet .........................   Passed    2.08 sec
    Start 2: IC.pandaroux
2/4 Test #2: IC.pandaroux .....................   Passed    0.72 sec
    Start 3: IC.lionsrock
3/4 Test #3: IC.lionsrock .....................   Passed    4.23 sec
    Start 4: IC.chat_et_chien
4/4 Test #4: IC.chat_et_chien .................   Passed   10.26 sec

100% tests passed, 0 tests failed out of 4

Total Test time (real) =  17.29 sec
```

# Le TP - Partie 1

1. Essayez d'imaginer les opérations système nécessaires pour faire la conversion d'image.
    - Compiler le programme si ce n'est pas déjà fait
    - Depuis le dossier `workingdir`, lancer `strace ../build/imageconvert images/chat.jpg`
    - Confirmez que les opérations imaginées sont bien présentes.
    - Avez vous remarqué des traces du buffering de la librairie standard ?
      - Il est inutile ici de le désactiver, le gain serait ici négligeable par rapport à la conversion des images!
        Si vous êtes de nature à douter (c'est bien quand on parle de performance!), le programme peut désactiver le buffering de la librairie standard lorsqu'il trouve la variable d'environnement `NO_STDIO_BUFFERING`.
        Vous pouvez essayer la commande `NO_STDIO_BUFFERING=1 strace ../build/imageconvert images/chat.jpg` pour vous en convaincre !

2. On distingue généralement deux types d'opérations: calcul et entrées/sorties. Caractériser les différentes étapes (celles qui listées la sortie du programme) dans l'une des deux catégories.

3. Selon vous et sans inspecter le code (et en partant du principe que le code de conversion d'image est déjà optimisé), que pourrait-on faire pour que le programme aille plus vite ?
    - Noter que vos machines ont plusieurs cores
    - Noter qu'il est possible de faire du travail CPU pendant le chargement d'un fichier

4. Faisons un test rapide, CMake permet de lancer les tests en parallèle via la variable d'environnement `CTEST_PARALLEL_LEVEL`
    - lancer `CTEST_PARALLEL_LEVEL=4 make test` (ou son équivalent CMake)
    - La durée individuelle des tests a-t-elle changée ?
    - L'ordre des résultats des tests a-t-il changé ?
    - La durée totale perçue par l'utilisateur a-t-elle changée ?
    - Quelle technique utilise CMake pour faire son parallèlisme ?
    - Si l'on écrivait les logs dans le même fichier, quels problèmes pourraient apparaitre ?

5. Certains se seront peut-être rendus compte que l'on compile sans les flags d'optimisation...
    - C'est le premier truc à vérifier quand vous voulez optimiser ! Sinon, ça sert à rien.
    - CMake fourni plusieurs configurations de compilation, dont deux qui nous intéressent particulièrement
         - `Debug`: C'est celle à utiliser quand vous voulez vraiment faire du dev & debugging. Pas (ou presque pas) d'optimisation + génération des symboles de debug.
         - `RelWithDebInfo`: C'est celle à utiliser si vous voulez developper avec les optimisations. Les optimisations ne sont pas aussi poussées qu'avec `Release`, mais vous aurez les symboles de debug, sinon impossible de profiler. (Idéalement, il faudrait la configuration `Release` + symboles, mais c'est hors-scope pour ce TP)
    - Pour changer la configuration de CMake, utilisez le paramètre `-DCMAKE_BUILD_TYPE=`. Ici, on génère un dossier différent par configuration:
        - `cmake -B build-debug -DCMAKE_BUILD_TYPE=Debug`
        - `cmake -B build-rel -DCMAKE_BUILD_TYPE=RelWithDebInfo`
    - Pour les besoins de ce TP, vous pouvez utiliser la configuration que vous voulez, mais n'oubliez pas que profiler (mesurer les performances de) votre application sans activer les optimisations du compilateur est une grossière erreur en temps normal !


# Le TP - Partie 2

Maintenant que nous avons confirmé qu'il est possible de gagner du temps en exécutant le code en parallèle, faisont en sorte de pouvoir traiter plusieurs images de cette façon.

## En créant des processus

1. En adéquation avec ce qui a été dit dans le cours n°2, utilisez `posix_spawn` pour créer un sous-process par image si vous avez plus d'une image à convertir. Le process principal ne fera qu'orchestrer et attendre le travail des enfants.
Vous pouvez consulter le manuel: [`man posix_spawn`](https://www.man7.org/linux/man-pages/man3/posix_spawn.3.html).
    - > Rappel: le parametre `argv` attendu doit contenir le nom de la commande (`argv[0]`), les paramètres, mais aussi un dernier élément à `NULL` pour que la fonction détecte la taille du tableau (un peu comme les chaînes de caractères).
    - Il est possible que la sortie des différents programmes soit dans le désordre. N'hésitez pas à logger (par exemple argv) avec le pid en début de programme via `printf` et `getpid`!

2. Il y a quelque chose d'important à faire avec le PID, ne l'oubliez pas !

3. Si vous ne le faites pas, que se passe-t-il ?

4. Faites en sorte (si pas déjà fait) que le programme principal renvoie un code de retour `-1` si l'un de ses enfants crash ou ne renvoie pas un code de retour `0`;

5. Mesurez le temps de création d'un processus
    - Prenez un timestamp juste avant l'appel à `posix_spawn`, puis affichez le avec `utils_print_timestamp(stdout, montimestamp)`. (après `posix_spawn`, pour ne pas fausser le résultat ! Ecrire sur la sortie standard a un coût.)
    - Prenez un timestamp en début de conversion pour les processus enfants et affichez le.
    - Souvenez-vous que cette durée peut dépendre de plusieurs paramètres, comme par exemple le nombre de file descriptors du process parents (car on peut les partager). Les durées observées ici sont globalement la durée minimale. De plus, sur windows on est en général plus dans l'ordre de 10-20ms par appel a CreateProcess, si ce n'est plus ! (Attention, on mesure ici la différence entre début creation de processus et le début du travail dans le processus enfant. Ce qui veut dire que sur windows la durée peut être différente que celle de l'appel à CreateProcess. En effet un processus commence bien avant de rentrer dans la fonction `main` de la librairie standard.)

6. Mesurez le temps d'éxécution en lancant votre programme avec la commande `time` 
    - Quels sont les trois durées affichées par `time` ? Aidez vous du manuel [man 1 time](https://www.man7.org/linux/man-pages/man1/time.1.html)
    - Le temps entre le début et fin de la commande a-t-il changé ?
    - Si non, corrigez votre code !
    - Le temps où le CPU est actif a-t-il changé ?

7. Il serait bien pratique de pouvoir renseigner uniquement un dossier plutôt que des fichiers un à un
    - Vous pourriez utiliser `stat` et `S_ISDIR` pour détecter si le parametre est un dossier, mais celà fait un aller retour inutile dans le système de fichiers. Preférez rajouter un parametre de commande (par exemple `-d`).
    - Utilisez `opendir`, `readdir` sans oublier `closedir ` pour lister les fichiers à ouvrir.
    - Vous pouvez rajouter un test dans le [CMakeLists.txt](CMakeLists.txt) pour lancer votre nouvelle commande

8. Quel(s) problème(s) peut-on rencontrer avec cette méthode ? Pensez au fait que l'on va peut être vouloir convertir des albums avec plus de 10000 photos !
    - Faites en sortes de pouvoir limiter le parallelisme. On choisira la valeur par défaut avec [`get_nprocs`](https://linux.die.net/man/3/get_nprocs_conf)

## En utilisant des threads

La même chose, mais avec des threads !
N'oubliez pas de nommer vos threads. Par exemple avec le numéro du fichier, ou bien avec son nom.

Voir [`man pthread_create`](https://linux.die.net/man/3/pthread_create).
Vous noterez qu'il y à un paramètre `void* arg` qui sera passé en paramètre de votre point d'entrée. Vous pouvez ainsi transférer le chemin du fichier à convertir à votre thread. (Attention, il y a tout de même un petit piège par rapport à la version processus !)

Etant donné que nous n'avons pas une vraie gestion d'erreur (c'est mal! basée sur `assert`...), il est difficile de gérer celle-ci comme lorsque l'on crée des process enfants. En effet il suffit qu'un thread crash pour que le programme complet se termine. Ne vous occupez donc pas d'essayer de les détecter.

# Le TP - Partie 3

Faites en sorte que ce soit le thread principal qui affiche les durées cummulées des opérations. 

- On commencera par renvoyer une structure allouée par le thread, que l'on récupérera via `pthread_join` puis dont on fait la somme.
- Dans un deuxième temps, on référencera une seule et même structure, dans laquelle on accumulera les resultats.
    - Quels problèmes peut-on avoir avec cette approche ?
    - Utilisez un [mutex](https://linux.die.net/man/3/pthread_mutex_init) pour protéger les accès à votre structure.
    - Lorsque que vous [lockez](https://linux.die.net/man/3/pthread_mutex_lock) un mutex, il y à deux possibilités:
        - soit personne n'a déjà acquis le mutex, et la fonction se terminera pour vous laisser exécuter le code.
        - Soit le mutex est déjà acquis, et il y aura une attente (le thread va "dormir") tant que le thread l'ayant acquis ne le libère via `pthread_mutex_unlock`. Au plus un seul thread à la fois peut avoir acquis le mutex, et donc exécuter le code protégé par celui-ci. D'où le nom: "Mutual exclusion"

# Le TP - Partie 4

Afin d'éviter le coût de création d'un thread ainsi que de faire de l'oversubscription (plus de threads que de cores), nous allons vouloir faire une Threadpool.

L'idée est la suivante: plutôt que créer des threads à chaque tâche que l'on souhaite réaliser, nous allons les créer au démarrage et leur envoyer des tâches à exécuter. Chaque thread aura une boucle dans laquelle il attendra une tâche, l'exécutera, puis attendra la prochaine.

1. Ecrire une fonction qui sera votre point d'entrée du thread. Elle devra:
    - avoir pour signature `void utils_task_routineptr (void * pUserArg)`. Vous pouvez partir du principe que `pUserArg` sera en réalité une structure `threadpool` de votre choix contenant au moins une `utils_tasklist`.
    - Boucler tant qu'un booléen `shouldStop` dans la structure `threadpool` n'est pas à `true`
    - Appeler `utils_try_pop_task` pour essayer de récupérer une tache à éxecuter. S'il y en a une, l'exécuter (`(*ptTaskRoutine)(pUserData)`).
2. Quels sont les problèmes que vous allez avoir si plus de deux threads tournent en parallèle avec cette technique ?
    - Comme pour la partie 3, utiliser un mutex pour protéger les accès à la liste de tâches.
         - > **Attention**: pensez à libérer le mutex avant de lancer la tâche, sinon vous aurez au plus une tâche exécutée à la fois. Autant ne pas avoir de threads à ce moment là!
    - Pour le booléen controllant l'arrêt du thread, utilisez plutôt un [`atomic_bool`](https://en.cppreference.com/w/c/language/atomic). 
        - Pour les types de taille 1,2,4,8 octets, vos processeurs peuvent effectuer des opérations dites "atomiques". C'est à dire que les opérations que vous effectuez dessus ne peuvent pas créer de valeur "invalide" car l'opération ne peut être observée comme plusieurs opérations. Cela ne signifie pas que vous n'aurez pas de soucis de race conditions avec, mais cela vient avec certaines garanties. 
        Par exemple si deux threads font un incrément `i++`, cette opération bien qu'équivalente à une lecture et écriture ne sera considérée que comme une opération. On ne pourra jamais avoir lecture|lecture|ecriture|ecriture, ce sera toujours lecture|ecriture suivi de lecture|ecriture. 
        - L'avantage de ces variable est qu'il n'y a pas besoin d'utiliser des primitives de synchronisation potentiellement lourdes comme un mutex. Ce sont en réalité ces opérations qui sont utilisées par l'OS pour implémenter des mutex, mais ici pas besoin de passer par le kernel.
        - > Note: mettez à jour votre `CMakeLists.txt` pour qu'il compile en C11 (asssurez vous qu'il contienne la ligne `target_compile_features(imageconvert PUBLIC c_std_11)` s'il n'y est pas déjà). Sinon il ne sera pas possible d'inclure `<stdatomic.h>`
3. Lancer autant de threads que de cores, et utiliser `utils_push_task` pour lancer les conversions.
    - Ces threads sont généralement appelés des **Worker threads**. (On peut les nommer *WorkerThread##*, avec leur numéro de core).
    - Ajoutez un compteur de tâches réalisées (par exemple un `atomic_int`) à la structure `threadpool`. Le thread principal pourra ainsi attendre que toutes les tâches soient réalisées, puis `shouldStop = false` pour demander aux threads de s'arrêter. (N'oubliez pas ensuite de `pthread_join` vos threads).
4. Que se passe-t-il si vous n'avez pas de tâches mais que le thread principal mets du temps à demander la sortie ? Ou inversement si on attends longtemps la fin des tâches du côtéé du thread principal ?
    - Si vous n'avez pas d'idée, mettez un `sleep(20);` avant de mettre le booléen `shouldStop` à false et ouvrez `top`. Constatez le problème.
    - Plutôt que faire tourner les threads dans la boucle pour "ne rien faire d'autre qu'attendre" (et faire brûler votre CPU pour rien), il est plus intéressant de le faire s'endormir tant qu'aucune tâche n'est disponible.
    - On pourrait mettre un `usleep(1)` lorsque l'on attend, mais cela tromperait grandement le scheduler. De plus, cela rajouterait une latence potentiellement plus grande que la tache à réaliser !
    - On utilisera en général plutôt une *condition variable*.
        - La condition variable permet au thread de s'endormir tant qu'on ne le reveille pas depuis un autre thread
        - On l'associe toujours à une condition (pour les workers threads, on se contentera du fait qu'`utils_try_pop_task` ne fasse rien s'il n'y a pas de tâches à réaliser.). La raison pour laquelle on associe toujours une condition, est parce qu'il est possible d'avoir ce qu'on appelle un **spurious wakeup**, où le thread se réveille même si personne ne l'a demandé.
        - Chaque condition variable nécessite d'avoir un mutex. Le principe est le suivant:
            - On lock le mutex
            - On boucle en checkant la condition. Tant qu'elle est fausse, on fait des wait (`pthread_cond_wait`) à l'intérieur de la boucle.
            - le wait va libérer de façon sécurisée le mutex (pour que d'autres threads puissent eux aussi attendre)
            - Lorsque l'on sort du wait, le mutex est de nouveau acquis (locké), on peut donc utiliser la mémoire protégée par ce mutex.
    - Utilisez une condition variable pour faire en sorte de ne réveiller les threads que s'ils ont du travail ou doivent s'arrêter. Côté thread principal, appelez `pthread_cond_signal`/`pthread_cond_broadcast` après avoir pushé des tâches pour reveiller un/vos threads. Si votre programme ne se termine jamais, c'est que vous avez oublié de réveiller vos threads à un moment!







