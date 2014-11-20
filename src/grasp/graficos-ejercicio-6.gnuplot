reset
set terminal jpeg size 800,600
set output "ejercicio-6-comparacion-tiempos-grasp-(2,2).jpg"
set key top left
set yrange[0:]
set xrange[3:]
set xtics 5
set xlabel "Cantidad de vértices (n)"
set ylabel "Tiempo promedio en microsegundos"
set title "Comparación de tiempos de ejecución de GRASP en función de n"
plot 'tiemposGrasp-conjunto-1.txt' using 1:2 title "Conj. 1: Max. iter. = 100 , prof. = (2,2)", \
     'tiemposGrasp-conjunto-2.txt' using 1:2 title "Conj. 2: Max. iter. = 100 , prof. = (2,2)", \
     'tiemposGrasp-conjunto-1.txt' using 1:4 title "Conj. 1: It. s/mej. = 70  , prof. = (2,2)", \
     'tiemposGrasp-conjunto-2.txt' using 1:4 title "Conj. 2: It. s/mej. = 70  , prof. = (2,2)", \

reset
set terminal jpeg size 800,600
set output "ejercicio-6-comparacion-tiempos-grasp-(4,4).jpg"
set key top left
set yrange[0:]
set xrange[3:]
set xtics 5
set xlabel "Cantidad de vértices (n)"
set ylabel "Tiempo promedio en microsegundos"
set title "Comparación de tiempos de ejecución de GRASP en función de n"
plot 'tiemposGrasp-conjunto-1.txt' using 1:3 title "Conj. 1: Max. iter. = 100 , prof. = (4,4)", \
     'tiemposGrasp-conjunto-2.txt' using 1:3 title "Conj. 2: Max. iter. = 100 , prof. = (4,4)", \
     'tiemposGrasp-conjunto-1.txt' using 1:5 title "Conj. 1: It. s/mej. = 70  , prof. = (4,4)", \
     'tiemposGrasp-conjunto-2.txt' using 1:5 title "Conj. 2: It. s/mej. = 70  , prof. = (4,4)"

#reset
#set terminal jpeg size 800,600
#set output "ejercicio-6-calidad-comparacion-n-32.jpg"
#set key top left
#set yrange[0:]
#set xtics 1
#set ytics 0.1
#set grid ytics
#set xlabel "Cantidad de vértices (n)"
#set ylabel "Error relativo en porcentaje"
#set title "Calidad de GRASP en función de n y del límite de iteraciones"
#plot 'calidadVsExacto-conjunto-1.txt' using 1:7 with lines title "Conjunto 1 con límite = 32", \
#     'calidadVsExacto-conjunto-2.txt' using 1:7 with lines title "Conjunto 2 con límite = 32"
#     
#reset
#set terminal jpeg size 800,600
#set output "ejercicio-6-calidad-comparacion-n-64.jpg"
#set key top left
#set yrange[0:]
#set xtics 1
#set ytics 0.1
#set grid ytics
#set xlabel "Cantidad de vértices (n)"
#set ylabel "Error relativo en porcentaje"
#set title "Calidad de GRASP en función de n y del límite de iteraciones"
#plot 'calidadVsExacto-conjunto-1.txt' using 1:8 with lines title "Conjunto 1 con límite = 64", \
#     'calidadVsExacto-conjunto-2.txt' using 1:8 with lines title "Conjunto 2 con límite = 64"
#
#reset
#set terminal jpeg size 800,600
#set output "ejercicio-6-calidad-comparacion-n-128.jpg"
#set key top left
#set yrange[0:]
#set xtics 1
#set ytics 0.1
#set grid ytics
#set xlabel "Cantidad de vértices (n)"
#set ylabel "Error relativo en porcentaje"
#set title "Calidad de GRASP en función de n y del límite de iteraciones"
#plot 'calidadVsExacto-conjunto-1.txt' using 1:9 with lines title "Conjunto 1 con límite = 128", \
#     'calidadVsExacto-conjunto-2.txt' using 1:9 with lines title "Conjunto 2 con límite = 128"
#
#reset
#set terminal jpeg size 800,600
#set output "ejercicio-6-calidad-comparacion-n-256.jpg"
#set key top left
#set yrange[0:]
#set xtics 1
#set ytics 0.1
#set grid ytics
#set xlabel "Cantidad de vértices (n)"
#set ylabel "Error relativo en porcentaje"
#set title "Calidad de GRASP en función de n y del límite de iteraciones"
#plot 'calidadVsExacto-conjunto-1.txt' using 1:10 with lines title "Conjunto 1 con límite = 256", \
#     'calidadVsExacto-conjunto-2.txt' using 1:10 with lines title "Conjunto 2 con límite = 256"
#
#reset
#set terminal jpeg size 800,600
#set output "ejercicio-6-calidad-comparacion-n-512.jpg"
#set key top left
#set yrange[0:]
#set xtics 1
#set ytics 0.1
#set grid ytics
#set xlabel "Cantidad de vértices (n)"
#set ylabel "Error relativo en porcentaje"
#set title "Calidad de GRASP en función de n y del límite de iteraciones"
#plot 'calidadVsExacto-conjunto-1.txt' using 1:11 with lines title "Conjunto 1 con límite = 512", \
#     'calidadVsExacto-conjunto-2.txt' using 1:11 with lines title "Conjunto 2 con límite = 512"
#
