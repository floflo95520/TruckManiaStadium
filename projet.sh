#!/bin/bash
nb_arguments=$#
help=0

if [ $nb_arguments -eq 0 ];
then
	echo "Erreur. Aucun argument detecte."
	exit 1
fi



#On vérifie avant tout si l'option -h est présente dans les arguments passés par l'utilisateur
for (( i=1 ; i<=nb_arguments ; i++ )) do
if [ "${!i}" == "-h" ];
then
	help=1
fi
done
#Si le dossier existe alors on le vide
if [ -e fichierstemporaires ];
then
	cd fichierstemporaires
	rm * -r 2> fichiertempdéjàvide.txt # si le dossier est déjà vide alors on redirige l'erreur standart dans un fichier texte qu'on supprime aussitôt
	rm fichiertempdéjàvide.txt
	cd ..
else #si le dossier n'existe pas alors on le crée
	echo "Dossier 'fichierstemporaires' créé"
	mkdir fichierstemporaires
fi

#si le dossier images n'existe pas alors on le crée
if [ ! -e images ];
then
	echo "Dossier 'images' créé"
	mkdir images
fi


#si la variable help=1 alors cela veut dire que le programme a détecté l'option -h et va donc afficher le message d'aide et ignorer les autres options
if [ $help -eq 1 ];then
	cat Aide.txt
else 
	if [ ! -f $1 ]; then
		echo "Erreur. Le premier argument n'est pas un fichier ou n'existe pas."
	else 
	for (( k=2 ; k<=nb_arguments ; k++ )) do
		case ${!k} in
-d1) 
echo "Option -d1 :"
AVANT=$(date +%s)
#la commande awk sert à compter le nombre de trajets pour chaque conducteur en évitant de reprendre les lignes qui ont le meme routeid et le meme conducteur
awk -F';' '!seen[$1,$6]++ { count[$6]++ } END {for (name in count) print count[name],";" name}' $1 | sort -r -n -k1,1 | head -n10 > fichierstemporaires/data_d1.csv 
APRES=$(date +%s)
TEMPS=$(echo "$APRES - $AVANT" | bc)
echo "Le temps de traitement est de $TEMPS seconde(s)"
#programme pour générer le graphique
gnuplot << EOF
reset
set terminal pngcairo size 800,1200 enhanced font "arial,12"
set output "images/Résultats_d1tmp.png"
set boxwidth 0.75
set xlabel "Conducteurs"
set y2label "Nombre de trajets"
set ylabel "Option (-d1) : Nb routes = f(conducteur)"
set style data histogram
set style fill solid 1.0 border
set style histogram rowstacked
set xtics rotate 
set ytics rotate
set autoscale y
set yrange [0:*]
set datafile separator ";"
plot for [COL=1:1] "fichierstemporaires/data_d1.csv" using COL:xticlabel(2) linecolor 2 title "Nombre de trajets par conducteur"
EOF
convert images/Résultats_d1tmp.png -rotate 90 images/Résultats_d1.png

;;


-d2)
echo "Option -d2 :"
AVANT=$(date +%s)
#la commande awk compte la distance totale pour chaque conducteur
#Ce code permet d'éviter l'arrondissement des valeurs lors de l'additionnement avec la commande Awk (ChatGpt)
LC_NUMERIC=en_US.UTF-8 awk -F';' '{ count[$6] += $5 } END {for (name in count) print count[name],";" name}' $1 | sort -r -n -k1,1 | head -n10 > fichierstemporaires/data_d2.csv 
APRES=$(date +%s)
TEMPS=$(echo "$APRES - $AVANT" | bc)
echo "Le temps de traitement est de $TEMPS seconde(s)"
#programme pour générer le graphique
gnuplot << EOF
reset
set terminal pngcairo size 800,1200 enhanced font "arial,12"
set output "images/Résultats_d2tmp.png"
set boxwidth 0.75
set xlabel "Conducteurs"
set y2label "Distance"
set ylabel "Option (-d2) : Distance = f(conducteur)"
set style data histogram
set style fill solid 1.0 border
set style histogram rowstacked
set xtics rotate 
set ytics rotate
set autoscale y
set yrange [0:*]
set datafile separator ";"
plot for [COL=1:1] "fichierstemporaires/data_d2.csv" using COL:xticlabel(2) linecolor 2 title "Distance pour chaque conducteur"
EOF
convert images/Résultats_d2tmp.png -rotate 90 images/Résultats_d2.png

;;

-l) 
echo "Option -l :"
AVANT=$(date +%s)
#la commande awk calcule la distance totale pour chaque trajet
#Ce code permet d'éviter l'arrondissement des valeurs lors de l'additionnement avec la commande Awk (ChatGpt)
LC_NUMERIC=en_US.UTF-8 awk -F';' '{ count[$1] += $5 } END {for (num in count) print count[num],";" num}' $1 | sort -r -n -t';' -k1,1 | head -n10 | sort -r -n -t';' -k2,2 > fichierstemporaires/data_l.csv
APRES=$(date +%s)
TEMPS=$(echo "$APRES - $AVANT" | bc)
echo "Le temps de traitement est de $TEMPS seconde(s)"
gnuplot << EOF
reset
set terminal pngcairo size 800,800 enhanced font "arial,12"
set output "images/Résultats_l.png"
set boxwidth 0.75
set title "Option (-l) : Distance = f(Trajet)"
set xlabel "ID Route"
set ylabel "Longueur pour chaque trajet"
set style data histogram
set style fill solid 1.0 border
set boxwidth 2
set autoscale y
set yrange [0:*]
set datafile separator ";"
plot for [COL=1:1] "fichierstemporaires/data_l.csv" using COL:xticlabel(2) linecolor 2 title "Longueur d'un trajet"
EOF
;;

-s) 
echo "Option -s :"
#si le fichier qui va stocker les fichiers.o n'existe pas alors on le crée
if [ ! -d Programme_C/Fichiers_o_S ];
then
	cd Programme_C
	mkdir Fichiers_o_S
	cd ..
fi
#si l'exécutable ProgS n'est pas présent alors on le crée
if [ ! -e Programme_C/ProgS ];
then
	cd Programme_C
 	touch make.txt
	make ProgS >> make.txt
	make clean >> make.txt
	rm make.txt
	cd ..
fi
AVANT=$(date +%s)
#à partir du fichier passé en argument, on garde uniquement les colonnes qui nous interressent tout en changeant le séparateur ce qui facilitera la lecture des données pour le programme c
cut -d';' -f1,5 $1 | sed 's/;/ /g' | tail -n +2 > fichierstemporaires/data_s.txt
#on récupère le nombre de lignes grâce à la variable t en retirant le nom du fichier qui s'affiche à côté
t=`wc -l fichierstemporaires/data_s.txt | cut -d' ' -f1`
#on exécute le programme en passant la valeur de t en argument pour que le programme C la récupère
./Programme_C/ProgS $t
APRES=$(date +%s)
TEMPS=$(echo "$APRES - $AVANT" | bc)
echo "Le temps de traitement est de $TEMPS seconde(s)"
#programme pour générer le graphique
gnuplot << EOF
reset
set terminal pngcairo size 1200,800 enhanced font "arial,12"
set output "images/Résultats_s.png"
set title "Option (-s) : Max/Min/Moyenne = f(Trajet)"
set xlabel "Route Id"
set ylabel "Distance (Km)"
set autoscale y
set yrange [0:*]
set xtics rotate by 45 right
set datafile separator ';'
plot 'fichierstemporaires/data_s.csv' using 0:3:5:xticlabel(2) with filledcurves linecolor 2 title 'Distance (Km)',\
''using 0:4 with lines linecolor 0 title 'Distance moyenne (Km)'
EOF

;;
			
-t) 
echo "Option -t :"
#si le fichier qui va stocker les fichiers.o n'existe pas alors on le crée
if [ ! -d Programme_C/Fichiers_o_T ];
then
	cd Programme_C
	mkdir Fichiers_o_T
	cd ..
fi
#si l'exécutable ProgT n'est pas présent alors on le crée
if [ ! -e Programme_C/ProgT ];
then
	cd Programme_C
 	touch make.txt
	make ProgT >> make.txt
	make clean >> make.txt
	rm make.txt
	cd ..
fi
AVANT=$(date +%s)
#à partir du fichier passé en argument, on garde uniquement les colonnes qui nous interressent tout en changeant le séparateur ce qui facilitera la lecture des données pour le programme c
cut -d';' -f1-4 $1 | sed 's/ /-/g' | sed 's/;/ /g' | tail -n +2 > fichierstemporaires/data_t.txt
#on récupère le nombre de lignes grâce à la variable t en retirant le nom du fichier qui s'affiche à côté
t=`wc -l fichierstemporaires/data_t.txt | cut -d' ' -f1`
#on exécute le programme en passant la valeur de t en argument pour que le programme C la récupère
./Programme_C/ProgT $t
sed 's/-/ /g' fichierstemporaires/data_t_temp.csv > fichierstemporaires/data_t.csv
APRES=$(date +%s)
TEMPS=$(echo "$APRES - $AVANT" | bc)
echo "Le temps de traitement est de $TEMPS seconde(s)"
#programme pour générer le graphique
gnuplot << EOF
reset
set terminal pngcairo size 800,800 enhanced font "arial,12"
set output "images/Résultats_t.png"
set title "Option (-t) : NbRoutes = f(Trajet)"
set xlabel "Villes"
set ylabel "NbRoutes"
set autoscale y
set yrange [0:*]
set xtics rotate by 45 right
set style data histogram
set style fill solid 1.0 border
set style histogram clustered gap 7
set boxwidth 4
set datafile separator ';'
plot 'fichierstemporaires/data_t.csv' using 2:xtic(1) linecolor 2 title 'Nombre de trajets', '' using 3 linecolor 9 title 'Départs trajets'
EOF
;;
			
*) echo "Option ${!k} non reconnue." 
;; 
		esac
	done
	fi
fi



