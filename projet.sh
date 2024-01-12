#!/bin/bash

nb_arguments=$#
help=0

if [ $nb_arguments -eq 0 ];
then
	echo "Erreur. Aucun argument detecte."
	exit 1
fi




for (( i=1 ; i<=nb_arguments ; i++ )) do
if [ "${!i}" == "-h" ];
then
	help=1
fi
done


if [ $help -eq 1 ];then
	echo "Bonjour. Vous avez demandé à obtenir de l'aide sur l'utilisation de ce programme. Pour commencer, il faut obligatoirement passer le fichier dont on veut extraire les informations en premier argument sans quoi le programme ne fonctionnera pas. Enfin, il vous faudra entrer une ou plusieurs options en fonction des informations que vous voulez obtenir. Voici les options disponibles  : 

option -d1 : trie en fonction du nombre de trajets effectués et affiche un 'histogramme horizontal' avec les 10 conducteurs qui ont le plus grand nombre de trajets effectués.

option -d2 : trie en fonction de la distance totale parcourue pour chaque conducteur et affiche un 'histogramme horizontal' avec les 10 conducteurs qui ont la plus grande distance parcourue.

option -l : trie en fonction des trajets les plus longs et affiche un 'histogramme vertical' avec les 10 trajets les plus longs.

option -t : trie en fonction des villes les plus traversées et affiche un graphique de type 'histogramme regroupé' avec les 10 villes les plus traversées.

option -s : trie en fonction de la distance minimale, maximale et moyenne de chaque étape et affiche un graphique de type 'courbe min-max-moyenne'. 

En espérant que cette aide vous ait été utile.
Bonne journée."
else 
	if [ ! -f $1 ]; then
		echo "Erreur. Le premier argument n'est pas un fichier."
	else 
	for (( k=2 ; k<=nb_arguments ; k++ )) do
		case ${!k} in
-d1) 
awk -F';' '!seen[$1,$6]++ { count[$6]++ } END {for (name in count) print count[name],";" name}' $1 data.csv | sort -r -n -k1,1 | head -n10 > datad1_sorted.csv 
/usr/bin/time -f "%e" awk -F';' '!seen[$1,$6]++ { count[$6]++ } END {for (name in count) print count[name],";" name}' $1 data.csv | sort -r -n -k1,1 | head -n10 > /dev/null 
gnuplot << EOF
reset
set terminal pngcairo size 800,1200 enhanced font "arial,12"
set output "Résultats_d1tmp.png"
set boxwidth 0.75
set xlabel "Conducteurs"
set y2label "Nombre de trajets"
set ylabel "Nombre de trajets par conducteurs"
set style data histogram
set style fill solid 1.0 border
set style histogram rowstacked
set xtics rotate 
set y2tics rotate
set yrange [0:250]
set datafile separator ";"
plot for [COL=1:2] "datad1_sorted.csv" using COL:xticlabel(2) lc rgb "blue" 
EOF
convert Résultats_d1tmp.png -rotate 90 Résultats_d1.png
;;


-d2) 
awk -F';' '{ count[$6] += $5 } END {for (name in count) print count[name],";" name}' $5 data.csv | sort -r -n -k1,1 | head -n10 > datad2_sorted.csv ;;

-l) 
awk -F';' '{ count[$1] += $5 } END {for (num in count) print count[num],";" num}' $5  data.csv | sort -r -n -k1,1 | head -n10 > datal_sorted.csv ;;
			-t) echo "option t" ;;
			-s) echo "option s" ;;
			*) echo "opérateur ${!k} non reconnu." ;; 
		esac
	done
	fi
fi
