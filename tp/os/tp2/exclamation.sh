#renvoyer une phrase lorsque il y un argument
if [ $# = 0 ]
then
   echo "Il n'y a pas d'argument"
else
   for nom in $@
      do echo -n "$nom ! Vous avez dit $nom? " 
      echo \n
   done
fi
exit