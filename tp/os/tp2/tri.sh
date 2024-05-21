cat "@a" | {
   
   while IFS='\n' read line
   do   if [ $line = 1:* ]
         then echo "$line cut -c 1,2"
   done

}

# marche pas