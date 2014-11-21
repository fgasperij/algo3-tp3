set term png
set xrange[0:21]
set title "Instancias ganadas por cantidad de vértices"
set output "calidad_histograma.png"
set xlabel "n"
set ylabel "Instancias ganadas"
set style data histogram 
set style histogram cluster gap 2
set style fill solid
set boxwidth 0.9
plot 'ganador_local.out' using 2 title 'vecindad B (swap)', 'ganador_local.out' using 3 title 'vecindad A (subset jump)'
