#!/bin/bash

if [ ! -f $1 ];
then
	echo "Erreur. Le premier argument n'est pas un fichier."
fi

nb_arguments=$#
help=0
for (( i=1 ; i<=nb_arguments ; i++ )) do
if [ "${!i}" == "-h" ];
then
	help=1
fi
done


if [ $help -eq 1 ];
then
	echo "Message d'aide."
fi
