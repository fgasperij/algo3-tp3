set terminal jpeg size 800,600
set key top left
set key box
set output "ejercicio-3-complejidad.jpg"
set xlabel "Cantidad de vértices (n)"
set ylabel "Tiempo"
set title 'Tiempos de ejecución de la heurística golosa'
plot 'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:2 title "k = 10", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:3 title "k = 20", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:4 title "k = 30", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:5 title "k = 40", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:6 title "k = 50", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:7 title "k = 60", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:8 title "k = 70", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:9 title "k = 80", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:10 title "k = 90", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:11 title "k = 100"

set output "ejercicio-3-complejidad-dividida-n.jpg"
#set xrange [0:200]
set yrange [0:]
set xtics 10
set ytics 1
set xlabel "Cantidad de vértices (n)"
set ylabel "Tiempo / n"
set title 'Comprobación de complejidad teórica de la heurística golosa'
plot 'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:($2 / $1) title "k = 10", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:($3 / $1) title "k = 20", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:($4 / $1) title "k = 30", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:($5 / $1) title "k = 40", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:($6 / $1) title "k = 50", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:($7 / $1) title "k = 60", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:($8 / $1) title "k = 70", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:($9 / $1) title "k = 80", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:($10 / $1) title "k = 90", \
'tiemposPorCantidadDeVerticesParaCadaK.txt' using 1:($11 / $1) title "k = 100"


