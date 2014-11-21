set term png
set xrange[0:80]
set yrange[0:10]
set title "Complejidad vecindad B (swap)"
set output "tiempos_vecindad_b.png"
set xlabel "n"
set ylabel "Tiempo (microseconds) / n^2"
plot 'time_local.out' using 1:($3/($1*$1)) title 'tiempo'
