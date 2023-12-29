#!/bin/bash

nb_arguments=$#
help=0

if [ $nb_arguments -eq 0 ];
then
	echo "Aucun argument detecte."
	exit 1
fi




for (( i=1 ; i<=nb_arguments ; i++ )) do
if [ "${!i}" == "-h" ];
then
	help=1
fi
done


if [ $help -eq 1 ];then
	echo "Message d'aide."
else 
	if [ ! -f $1 ]; then
		echo "Erreur. Le premier argument n'est pas un fichier."
	else 
	for (( k=2 ; k<=nb_arguments ; k++ )) do
		case ${!k} in
			-d1) echo "option d1" ;;
			-d2) echo "option d2" ;;
			-l) echo "option l";;
			-t) echo "option t";;
			-s) echo "option s";;
			*) echo "opérateur ${!k} non reconnu.";; 
		esac
	done
	fi
fi
