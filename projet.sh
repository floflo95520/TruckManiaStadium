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

if [ ! -e fichierstemporaires ];
then
	mkdir fichierstemporaires
fi

if [ ! -e images ];
then
	mkdir images
fi



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
awk -F';' '!seen[$1,$6]++ { count[$6]++ } END {for (name in count) print count[name],";" name}' $1 | sort -r -n -k1,1 | head -n10 > fichierstemporaires/datad1_sorted.csv 
/usr/bin/time -f "%e" awk -F';' '!seen[$1,$6]++ { count[$6]++ } END {for (name in count) print count[name],";" name}' $1 data.csv | sort -r -n -k1,1 | head -n10 > /dev/null 
gnuplot << EOF
reset
set terminal pngcairo size 800,1200 enhanced font "arial,12"
set output "images/Résultats_d1tmp.png"
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
plot for [COL=1:1] "fichierstemporaires/datad1_sorted.csv" using COL:xticlabel(2) linecolor 2
EOF
convert images/Résultats_d1tmp.png -rotate 90 images/Résultats_d1.png
rm images/Résultats_d1tmp.png
#rm fichierstemporaires/datad1_sorted.csv
;;


-d2) 
echo "Option -d2 :"
awk -F';' '{ count[$6] += $5 } END {for (name in count) print count[name],";" name}' $1 | sort -r -n -k1,1 | head -n10 > fichierstemporaires/datad2_sorted.csv 
/usr/bin/time -f "%e" awk -F';' '{ count[$6] += $5 } END {for (name in count) print count[name],";" name}' $1 | sort -r -n -k1,1 | head -n10 > /dev/null 
gnuplot << EOF
reset
set terminal pngcairo size 800,1200 enhanced font "arial,12"
set output "images/Résultats_d2tmp.png"
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
plot for [COL=1:1] "fichierstemporaires/datad2_sorted.csv" using COL:xticlabel(2) linecolor 2
EOF
convert images/Résultats_d2tmp.png -rotate 90 images/Résultats_d2.png
rm images/Résultats_d2tmp.png
#rm fichierstemporaires/datad2_sorted.csv
;;

-l) 
echo "Option -l :"
awk -F';' '{ count[$1] += $5 } END {for (num in count) print count[num],";" num}' $1 | sort -r -n -k1,1 | head -n10 | sort -r -n -t';' -k2,2 > fichierstemporaires/datal_sorted.csv
/usr/bin/time -f "%e" awk -F';' '{ count[$1] += $5 } END {for (num in count) print count[num],";" num}' $1 | sort -r -n -k1,1 | head -n10 | sort -r -n -t';' -k2,2 > /dev/null
gnuplot << EOF
reset
set terminal pngcairo size 800,1200 enhanced font "arial,12"
set output "images/Résultats_l.png"
set boxwidth 0.75
set xlabel "ID Route"
set ylabel "Longueur pour chaque trajet"
set style data histogram
set style fill solid 1.0 border
set style histogram rowstacked
set yrange [0:3000]
set datafile separator ";"
plot for [COL=1:1] "fichierstemporaires/datal_sorted.csv" using COL:xticlabel(2) linecolor 2
EOF
#rm fichierstemporaires/datal_sorted.csv
;;

-s) 
echo "Option -s :"
cat data.csv | cut -d';' -f1,5 | sed 's/;/ /g' | tail -n +2 > fichierstemporaires/data_s.txt
t=`wc -l fichierstemporaires/data_s.txt`
if [ ! -e ProgS ];
then
	gcc -o ProgS Prog_S.c -lm
fi
/usr/bin/time -f "%e" ./ProgS $t
./Gnuplot_s.sh
#rm fichierstemporaires/data_s.txt
#rm fichierstemporaires/data_s.csv
;;
			
-t) echo "Option -t :" 
;;
			
*) echo "Option -${!k} non reconnue." 
;; 
		esac
	done
	fi
fi
