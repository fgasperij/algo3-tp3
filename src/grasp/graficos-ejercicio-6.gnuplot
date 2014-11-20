reset
set terminal jpeg size 800,600
set output "ejercicio-6-calidad-comparacion-n-32.jpg"
set key top left
set yrange[0:]
set xtics 1
set ytics 0.1
set grid ytics
set xlabel "Cantidad de vértices (n)"
set ylabel "Error relativo en porcentaje"
set title "Calidad de GRASP en función de n y del límite de instancias"
plot 'calidadVsExacto-conjunto-1.txt' using 1:7 with lines title "Conjunto 1 con límite = 32", \
     'calidadVsExacto-conjunto-2.txt' using 1:7 with lines title "Conjunto 2 con límite = 32"
     
reset
set terminal jpeg size 800,600
set output "ejercicio-6-calidad-comparacion-n-64.jpg"
set key top left
set yrange[0:]
set xtics 1
set ytics 0.1
set grid ytics
set xlabel "Cantidad de vértices (n)"
set ylabel "Error relativo en porcentaje"
set title "Calidad de GRASP en función de n y del límite de instancias"
plot 'calidadVsExacto-conjunto-1.txt' using 1:8 with lines title "Conjunto 1 con límite = 64", \
     'calidadVsExacto-conjunto-2.txt' using 1:8 with lines title "Conjunto 2 con límite = 64"

reset
set terminal jpeg size 800,600
set output "ejercicio-6-calidad-comparacion-n-128.jpg"
set key top left
set yrange[0:]
set xtics 1
set ytics 0.1
set grid ytics
set xlabel "Cantidad de vértices (n)"
set ylabel "Error relativo en porcentaje"
set title "Calidad de GRASP en función de n y del límite de instancias"
plot 'calidadVsExacto-conjunto-1.txt' using 1:9 with lines title "Conjunto 1 con límite = 128", \
     'calidadVsExacto-conjunto-2.txt' using 1:9 with lines title "Conjunto 2 con límite = 128"

reset
set terminal jpeg size 800,600
set output "ejercicio-6-calidad-comparacion-n-256.jpg"
set key top left
set yrange[0:]
set xtics 1
set ytics 0.1
set grid ytics
set xlabel "Cantidad de vértices (n)"
set ylabel "Error relativo en porcentaje"
set title "Calidad de GRASP en función de n y del límite de instancias"
plot 'calidadVsExacto-conjunto-1.txt' using 1:10 with lines title "Conjunto 1 con límite = 256", \
     'calidadVsExacto-conjunto-2.txt' using 1:10 with lines title "Conjunto 2 con límite = 256"

reset
set terminal jpeg size 800,600
set output "ejercicio-6-calidad-comparacion-n-512.jpg"
set key top left
set yrange[0:]
set xtics 1
set ytics 0.1
set grid ytics
set xlabel "Cantidad de vértices (n)"
set ylabel "Error relativo en porcentaje"
set title "Calidad de GRASP en función de n y del límite de instancias"
plot 'calidadVsExacto-conjunto-1.txt' using 1:11 with lines title "Conjunto 1 con límite = 512", \
     'calidadVsExacto-conjunto-2.txt' using 1:11 with lines title "Conjunto 2 con límite = 512"
