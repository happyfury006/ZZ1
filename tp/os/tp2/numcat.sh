#!/usr/bin/bash

cat "$@" | {
    let i=0
    while IFS='\n' read line
    do
        printf '%i:%s\n' $i "$line"
        let i++
    done
}

#la commande read lit le fichier qui lui est passer en commentaire et le met dans le buffer ?
#la commande read est de type shell builtin
#la commande renvoie 0 si on arrve a la fin du fichier 
#sinon en ca d'erreur elle renvoie 1
#la commande let i++ incremente de 1 la variable i a chaque itération de la boucle
#si le script est appelée sans argument il ne revoie rien et il continue de tourner a l'infini
#s'il le script est appelée avec un ou des argument qui existe alors il les lit jusqu'a avoir terminer et ne renvoie rien
#la commande cat -n affiche le numero de ligne a chaque ligne du fichier



#lorsque ecrit la commande cut -d -f2- tout ce qu'on met en entrée et en sortie aussi

#la commande num="$(echo "$PATH" |cut -d -f1-) 
# puis la commande echo num nous renvoi donc le chemin vers num ?