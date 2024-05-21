#renvoyer une phrase lorsque il y un argument
if test $# != 2
then
    echo "il n'y a pas 2 argument" 1>&2
else
   echo "$2 ! Vous avez dit $2?"
   echo "$1 ! Vous avez dit $1?"
fi
exit