#afficher en premier le dixième argument avant les autres

echo " $10 $1 $2 $3 $4 $5 $6 $7 $8 $9 "

#dans le cas ou on execute ./rotate.sh $(rotate.sh $(seq 10)) cela renvoit que rotate.sh command not found puis un 0
