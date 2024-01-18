#!/bin/bash

gnuplot << EOF
reset
set terminal pngcairo size 1200,800 enhanced font "arial,12"
set output "images/Résultats_s.png"
set xlabel "Route Id"
set ylabel "Distance (Km)"
set yrange [0:1000]
set xtics rotate by 45 right
set datafile separator ';'
plot 'fichierstemporaires/data_s.csv' using 0:3:5:xticlabel(2) with filledcurves linecolor 2 lt 1 title 'Distance (Km)',\
''using 0:4 with lines linecolor 0 title 'Distance moyenne (Km)'
EOF
