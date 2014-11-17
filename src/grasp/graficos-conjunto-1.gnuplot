set terminal jpeg size 800,600
set output "ejercicio-5-configuracion-conjunto-1.jpg"
set xrange[3:100]
set yrange[0:110]
set xtics 5
set ytics 5
set xlabel "Cantidad de vértices (n)"
set ylabel "Configuración de parada por iteraciones"
set title "Resultados de criterio de parada ganador \n (10,35,50,70 = por iteraciones sin mejora, 100 = por maximo de iteraciones)"
plot 'resultadosTestConfiguracion-conjunto-1.txt' using 1:2 with lines notitle

reset
set terminal jpeg size 800,600
set output "ejercicio-5-configuracion-profundidad-conjunto-1.jpg"
set xrange[1:103]
set yrange[0:10]
set xtics 5
set ytics 500
set grid ytics
set style line 100 lt 1 lc rgb "red" lw 2
set ytics add ("1-1" 1)
set ytics add ("1-2" 2)
set ytics add ("1-4" 3)
set ytics add ("2-1" 4)
set ytics add ("2-2" 5)
set ytics add ("2-4" 6)
set ytics add ("4-1" 7)
set ytics add ("4-2" 8)
set ytics add ("4-4" 9)
set xlabel "Cantidad de vértices (n)"
set ylabel "Configuración de profundidad vértice-conjunto"
set title "Resultados de profundidad vértice-conjunto ganadora para cada n"
plot 'resultadosTestConfiguracionProfundidad_para_graficar-conjunto-1.txt' using 1:2 pt 7 notitle

reset
set terminal jpeg size 800,600
set output "ejercicio-5-histograma-rcl-conjunto-1.jpg"
# Select histogram data
set style data histogram
# Give the bars a plain fill pattern, and draw a solid line around them.
set style histogram clustered
set style fill solid border
set xlabel "Profundidad de elección vértice-conjunto, cada una yendo de 1 a 4"
set ylabel "Cantidad de veces que ganó en calidad"
set yrange[0:]
set ytics 1
set grid ytics
set title "Resultados de configuraciones de RCL ganadoras"
plot for [COL=2:2] 'histograma-rcl-conjunto-1.txt' using COL:xticlabels(1) notitle

reset
set terminal jpeg size 800,600
set output "ejercicio-5-tiempos-grasp-conjunto-1.jpg"
set key top left
set yrange[0:]
set xtics 5
set xlabel "Cantidad de vértices (n)"
set ylabel "Tiempo promedio en microsegundos"
set title "Tiempos de ejecución de GRASP en función de n: T(n)"
plot 'tiemposGrasp-conjunto-1.txt' using 1:2 title "Max. iter. = 100 | prof. vértice-conjunto = 2 2", \
     'tiemposGrasp-conjunto-1.txt' using 1:3 title "Max. iter. = 100 | prof. vértice-conjunto = 4 4", \
     'tiemposGrasp-conjunto-1.txt' using 1:4 title "Iter. sin mejora = 70 | prof. vértice-conjunto = 2 2", \
     'tiemposGrasp-conjunto-1.txt' using 1:5 title "Iter. sin mejora = 70 | prof. vértice-conjunto = 4 4"

reset
set terminal jpeg size 800,600
set output "ejercicio-5-tiempos-grasp-dividido-n-conjunto-1.jpg"
set key top left
set yrange[0:]
set xtics 5
set xlabel "Cantidad de vértices (n)"
set ylabel "Tiempo promedio en microsegundos dividido n"
set title "Tiempos de ejecución de GRASP dividido por cantidad de vértices: T(n)/n"
plot 'tiemposGrasp-conjunto-1.txt' using 1:($2 / $1) title "Max. iter. = 100 | prof. vértice-conjunto = 2 2", \
     'tiemposGrasp-conjunto-1.txt' using 1:($3 / $1) title "Max. iter. = 100 | prof. vértice-conjunto = 4 4", \
     'tiemposGrasp-conjunto-1.txt' using 1:($4 / $1) title "Iter. sin mejora = 70 | prof. vértice-conjunto = 2 2", \
     'tiemposGrasp-conjunto-1.txt' using 1:($5 / $1) title "Iter. sin mejora = 70 | prof. vértice-conjunto = 4 4"
     
reset
set terminal jpeg size 800,600
set output "ejercicio-5-calidad-todos-conjunto-1.jpg"
set key top center
set yrange[0:25]
set xtics 1
set ytics 1
set grid ytics
set xlabel "Cantidad de vértices (n)"
set ylabel "Promedio de peso GRASP dividido por peso exacto convertido a porcentaje"
set title "Calidad de GRASP en función de n y del límite de instancias\nTodos los límites\n100*Peso(GRASP)/Peso(Exacto) - 100"
plot 'calidadVsExacto-conjunto-1.txt' using 1:2 with lines title "Límite = 1", \
     'calidadVsExacto-conjunto-1.txt' using 1:3 with lines title "Límite = 2", \
     'calidadVsExacto-conjunto-1.txt' using 1:4 with lines title "Límite = 4", \
     'calidadVsExacto-conjunto-1.txt' using 1:5 with lines title "Límite = 8", \
     'calidadVsExacto-conjunto-1.txt' using 1:6 with lines title "Límite = 16", \
     'calidadVsExacto-conjunto-1.txt' using 1:7 with lines title "Límite = 32", \
     'calidadVsExacto-conjunto-1.txt' using 1:8 with lines title "Límite = 64", \
     'calidadVsExacto-conjunto-1.txt' using 1:9 with lines title "Límite = 128", \
     'calidadVsExacto-conjunto-1.txt' using 1:10 with lines title "Límite = 256", \
     'calidadVsExacto-conjunto-1.txt' using 1:11 with lines title "Límite = 512"
     
reset
set terminal jpeg size 800,600
set output "ejercicio-5-calidad-mejores-conjunto-1.jpg"
set key top center
set yrange[0:]
set xtics 1
set ytics 0.1
set grid ytics
set xlabel "Cantidad de vértices (n)"
set ylabel "Promedio de peso GRASP dividido por peso exacto convertido a porcentaje"
set title "Calidad de GRASP en función de n y del límite de instancias\nMejores límites\n100*Peso(GRASP)/Peso(Exacto) - 100"
plot 'calidadVsExacto-conjunto-1.txt' using 1:7 with lines title "Límite = 32", \
     'calidadVsExacto-conjunto-1.txt' using 1:8 with lines title "Límite = 64", \
     'calidadVsExacto-conjunto-1.txt' using 1:9 with lines title "Límite = 128", \
     'calidadVsExacto-conjunto-1.txt' using 1:10 with lines title "Límite = 256", \
     'calidadVsExacto-conjunto-1.txt' using 1:11 with lines title "Límite = 512"
