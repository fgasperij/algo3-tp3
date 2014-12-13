reset
set terminal png size 800,600
set output "ejercicio_6_comparacion_tiempos.png"
set key top right
set xlabel "Cantidad de vértices (n)"
set ylabel "Tiempo promedio en microsegundos"
set title "Comparación de tiempos de ejecución de GRASP, algoritmo exacto,\nalgoritmo goloso y algoritmo goloso más la búsqueda local en función de n"
plot '../resultados-tests-ejercicio-6.txt' using 1:($6/100) title "Tiempo del algortimo exacto", \
     '../resultados-tests-ejercicio-6.txt' using 1:($7/100) title "Tiempo del algoritmo goloso", \
     '../resultados-tests-ejercicio-6.txt' using 1:($8/100) title "Tiempo del algoritmo goloso con búsqueda local", \
     '../resultados-tests-ejercicio-6.txt' using 1:($9/100) title "Tiempo del GRASP", \

reset
set terminal png size 800,600
set output "ejercicio_6_tiempos_menos_exacto.png"
set key top left
set xlabel "Cantidad de vértices (n)"
set ylabel "Tiempo promedio en microsegundos"
set title "Comparación de tiempos de ejecución de GRASP, algoritmo goloso y \nalgoritmo goloso más la búsqueda local en función de n"
plot '../resultados-tests-ejercicio-6.txt' using 1:($7/100) title "Tiempo del algoritmo goloso", \
     '../resultados-tests-ejercicio-6.txt' using 1:($8/100) title "Tiempo del algoritmo goloso con búsqueda local", \
     '../resultados-tests-ejercicio-6.txt' using 1:($9/100) title "Tiempo del GRASP", \

reset
set terminal png size 800,600
set output "ejercicio_6_tiempos_menos_grasp.png"
set key top left
set xlabel "Cantidad de vértices (n)"
set ylabel "Tiempo promedio en microsegundos"
set title "Comparación de tiempos de ejecución de algoritmo goloso y \nalgoritmo goloso más la búsqueda local en función de n"
plot '../resultados-tests-ejercicio-6.txt' using 1:($7/100) title "Tiempo del algoritmo goloso", \
     '../resultados-tests-ejercicio-6.txt' using 1:($8/100) title "Tiempo del algoritmo goloso con búsqueda local", \
