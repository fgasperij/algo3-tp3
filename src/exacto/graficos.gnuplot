set terminal jpeg size 800,600
set key top left
set key box
set output "comparacion-podas.jpg"
set xlabel "Cantidad de vértices (n)"
set ylabel "Tiempo"
#set xrange [0:12]
#set yrange [0:]
set title 'Tiempos de ejecución del algoritmo exacto'
#plot 'test_individuales.out' using 1:2 title "sin podas", \
#plot 'test_individuales.out' using 1:3 title "k subconjuntos", \
plot 'test_individuales.out' using 1:4 title "peso mínimo", \
'test_individuales.out' using 1:5 title "hay mejora", \
'test_individuales.out' using 1:6 title "todas"


