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
	cat Aide.txt
else 
	if [ ! -f $1 ]; then
		echo "Erreur. Le premier argument n'est pas un fichier."
	else 
	for (( k=2 ; k<=nb_arguments ; k++ )) do
		case ${!k} in
-d1) 
echo "Option -d1 :"
awk -F';' '!seen[$1,$6]++ { count[$6]++ } END {for (name in count) print count[name],";" name}' $1 | sort -r -n -k1,1 | head -n10 > datad1_sorted.csv 
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
set ytics rotate
set yrange [0:250]
set datafile separator ";"
plot for [COL=1:1] "datad1_sorted.csv" using COL:xticlabel(2) lc rgb "blue" 
EOF
convert Résultats_d1tmp.png -rotate 90 Résultats_d1.png
;;


-d2) 
echo "Option -d2 :"
awk -F';' '{ count[$6] += $5 } END {for (name in count) print count[name],";" name}' $1 | sort -r -n -k1,1 | head -n10 > datad2_sorted.csv 
/usr/bin/time -f "%e" awk -F';' '{ count[$6] += $5 } END {for (name in count) print count[name],";" name}' $1 | sort -r -n -k1,1 | head -n10 > /dev/null 
gnuplot << EOF
reset
set terminal pngcairo size 800,1200 enhanced font "arial,12"
set output "Résultats_d2tmp.png"
set boxwidth 0.75
set xlabel "Conducteurs"
set y2label "Distance"
set ylabel "Distance pour chaque conducteur"
set style data histogram
set style fill solid 1.0 border
set style histogram rowstacked
set xtics rotate 
set ytics rotate
set yrange [0:160000]
set datafile separator ";"
plot for [COL=1:1] "datad2_sorted.csv" using COL:xticlabel(2) lc rgb "blue" 
EOF
convert Résultats_d2tmp.png -rotate 90 Résultats_d2.png
;;

-l) 
echo "Option -l :"
awk -F';' '{ count[$1] += $5 } END {for (num in count) print count[num],";" num}' $1 | sort -r -n -k1,1 | head -n10 | sort -r -n -t';' -k2,2 > datal_sorted.csv
/usr/bin/time -f "%e" awk -F';' '{ count[$1] += $5 } END {for (num in count) print count[num],";" num}' $1 | sort -r -n -k1,1 | head -n10 | sort -r -n -t';' -k2,2 > /dev/null
gnuplot << EOF
reset
set terminal pngcairo size 800,1200 enhanced font "arial,12"
set output "Résultats_ltmp.png"
set boxwidth 0.75
set xlabel "ID Route"
set y2label "Longueur"
set ylabel "Longueur pour chaque trajet"
set style data histogram
set style fill solid 1.0 border
set style histogram rowstacked
set yrange [0:3000]
set datafile separator ";"
plot for [COL=1:1] "datal_sorted.csv" using COL:xticlabel(2) lc rgb "blue" 
EOF
;;

-s) cat data.csv | cut -d';' -f1,5 | sed > data_t.txt
			;;
			-t) echo "option t" ;;
			*) echo "opérateur ${!k} non reconnu." ;; 
		esac
	done
	fi
fi
