set term png
set xrange[0:80]
set yrange[0:30]
set title "Complejidad vecindad A (subset jump)"
set output "tiempos_vecindad_a.png"
set xlabel "n"
set ylabel "Tiempo (microseconds) / n"
plot 'time_local.out' using 1:($2/$1) title 'tiempo'
