#set terminal jpeg size 800,600
#set output "ejercicio-5-configuracion-conjunto-2.jpg"
#set xrange[3:100]
#set yrange[0:110]
#set xtics 5
#set ytics 500
#set ytics add ("10" 10)
#set ytics add ("35" 35)
#set ytics add ("50" 50)
#set ytics add ("70" 70)
#set ytics add ("100" 100)
#set xlabel "Cantidad de vértices (n)"
#set ylabel "Configuración de parada por iteraciones"
#set title "Resultados de criterio de parada ganador \n (10,35,50,70 = por iteraciones sin mejora, 100 = por maximo de iteraciones)"
#plot 'resultadosTestConfiguracion-conjunto-2.txt' using 1:2 pt 7 notitle
#
#reset
#set terminal jpeg size 800,600
#set output "ejercicio-5-configuracion-profundidad-conjunto-2.jpg"
#set xrange[1:103]
#set yrange[0:10]
#set xtics 5
#set ytics 500
#set grid ytics
#set style line 100 lt 1 lc rgb "red" lw 2
#set ytics add ("(1,1)" 1)
#set ytics add ("(1,2)" 2)
#set ytics add ("(1,4)" 3)
#set ytics add ("(2,1)" 4)
#set ytics add ("(2,2)" 5)
#set ytics add ("(2,4)" 6)
#set ytics add ("(4,1)" 7)
#set ytics add ("(4,2)" 8)
#set ytics add ("(4,4)" 9)
#set xlabel "Cantidad de vértices (n)"
#set ylabel "Configuración de profundidad vértice-conjunto"
#set title "Resultados de profundidad vértice-conjunto ganadora para cada n"
#plot 'resultadosTestConfiguracion-conjunto-2.txt' using 1:4 pt 7 notitle
#
#reset
#set terminal jpeg size 800,600
#set output "ejercicio-5-histograma-rcl-conjunto-2.jpg"
## Select histogram data
#set style data histogram
## Give the bars a plain fill pattern, and draw a solid line around them.
#set style histogram clustered
#set style fill solid border
#set xlabel "Profundidad de elección vértice-conjunto"
#set ylabel "Cantidad de veces que ganó en calidad"
#set yrange[0:]
#set ytics 1
#set grid ytics
#set title "Resultados de configuraciones de RCL ganadoras"
#plot for [COL=2:2] 'histograma-rcl-conjunto-2.txt' using COL:xticlabels(1) notitle

#reset
#set terminal jpeg size 800,600
#set output "ejercicio-5-tiempos-grasp-conjunto-2.jpg"
#set key top left
#set xrange[3:]
#set yrange[0:]
#set xtics 5
#set xlabel "Cantidad de vértices (n)"
#set ylabel "Tiempo promedio en microsegundos"
#set title "Tiempos de ejecución de GRASP en función de n"
#plot 'tiemposGrasp-conjunto-2.txt' using 1:2 title "Max. iter. = 100 | prof. vértice-conjunto = 2 2", \
#     'tiemposGrasp-conjunto-2.txt' using 1:3 title "Max. iter. = 100 | prof. vértice-conjunto = 4 4", \
#     'tiemposGrasp-conjunto-2.txt' using 1:4 title "Iter. sin mejora = 70 | prof. vértice-conjunto = 2 2", \
#     'tiemposGrasp-conjunto-2.txt' using 1:5 title "Iter. sin mejora = 70 | prof. vértice-conjunto = 4 4"
#
#reset
#set terminal jpeg size 800,600
#set output "ejercicio-5-tiempos-grasp-primeros-nodos-conjunto-2.jpg"
#set key top left
#set yrange[0:]
#set xrange[2:15]
#set xtics 1
#set xlabel "Cantidad de vértices (n)"
#set ylabel "Tiempo promedio en microsegundos"
#set title "Tiempos de ejecución de GRASP en función de n"
#plot 'tiemposGrasp-conjunto-2.txt' using 1:3 title "Max. iter. = 100 | prof. vértice-conjunto = 4 4", \
#     'tiemposGrasp-conjunto-2.txt' using 1:5 title "Iter. sin mejora = 70 | prof. vértice-conjunto = 4 4"
     
reset
set terminal jpeg size 800,600
set output "ejercicio-5-calidad-todos-conjunto-2.jpg"
set key top left
set yrange[0:]
set xtics 1
set ytics 1
set grid ytics
set xlabel "Cantidad de vértices (n)"
set ylabel "Error relativo en porcentaje"
set title "Calidad de GRASP en función de n y del límite de iteraciones\nTodos los límites"
plot 'calidadVsExacto-conjunto-2.txt' using 1:2 with lines title "Límite = 1", \
     'calidadVsExacto-conjunto-2.txt' using 1:3 with lines title "Límite = 2", \
     'calidadVsExacto-conjunto-2.txt' using 1:4 with lines title "Límite = 4", \
     'calidadVsExacto-conjunto-2.txt' using 1:5 with lines title "Límite = 8", \
     'calidadVsExacto-conjunto-2.txt' using 1:6 with lines title "Límite = 16", \
     'calidadVsExacto-conjunto-2.txt' using 1:7 with lines title "Límite = 32", \
     'calidadVsExacto-conjunto-2.txt' using 1:8 with lines title "Límite = 64", \
     'calidadVsExacto-conjunto-2.txt' using 1:9 with lines title "Límite = 128", \
     'calidadVsExacto-conjunto-2.txt' using 1:10 with lines title "Límite = 256", \
     'calidadVsExacto-conjunto-2.txt' using 1:11 with lines title "Límite = 512"
     
reset
set terminal jpeg size 800,600
set output "ejercicio-5-calidad-mejores-conjunto-2.jpg"
set key top left
set yrange[0:]
set xtics 1
set ytics 0.1
set grid ytics
set xlabel "Cantidad de vértices (n)"
set ylabel "Error relativo en porcentaje"
set title "Calidad de GRASP en función de n y del límite de iteraciones\nMejores límites"
plot 'calidadVsExacto-conjunto-2.txt' using 1:7 with lines title "Límite = 32", \
     'calidadVsExacto-conjunto-2.txt' using 1:8 with lines title "Límite = 64", \
     'calidadVsExacto-conjunto-2.txt' using 1:9 with lines title "Límite = 128", \
     'calidadVsExacto-conjunto-2.txt' using 1:10 with lines title "Límite = 256", \
     'calidadVsExacto-conjunto-2.txt' using 1:11 with lines title "Límite = 512"

