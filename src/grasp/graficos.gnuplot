set terminal jpeg size 800,600
set output "ejercicio-5-configuracion.jpg"
set xrange[3:100]
set yrange[0:100]
set xtics 5
set ytics 5
set xlabel "Cantidad de vértices (n)"
set ylabel "Configuración de parada por iteraciones"
plot 'resultadosTestConfiguracion.txt' using 1:2 with lines notitle
