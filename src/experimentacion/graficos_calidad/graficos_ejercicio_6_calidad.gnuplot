reset
set terminal png size 800,600
set output "ejercicio_6_comparacion_calidad.png"
set key top left
set xrange [0:25]
set xlabel "Cantidad de vértices (n)"
set ylabel "Promedio de pesos obtenidos"
set title "Comparación de pesos obtenidos por GRASP, algoritmo exacto,\nalgoritmo goloso y algoritmo goloso más la búsqueda local en función de n"
plot '../resultados-tests-ejercicio-6.txt' using 1:($2 > 0 ? $2/100 : NaN) title "Peso del algortimo exacto", \
     '../resultados-tests-ejercicio-6.txt' using 1:($1 < 24 ? $3/100 : NaN) title "Peso del algoritmo goloso", \
     '../resultados-tests-ejercicio-6.txt' using 1:($1 < 24 ? $4/100 : NaN) title "Peso del algoritmo goloso con búsqueda local", \
     '../resultados-tests-ejercicio-6.txt' using 1:($1 < 24 ? $5/100 : NaN) title "Peso del GRASP", \

reset
set terminal png size 800,600
set output "ejercicio_6_comparacion_calidad_sin_exacto.png"
set key top left
set xlabel "Cantidad de vértices (n)"
set ylabel "Promedio de pesos obtenidos"
set title "Comparación de pesos obtenidos por GRASP, algoritmo goloso y \nalgoritmo goloso con la búsqueda local en función de n"
plot '../resultados-tests-ejercicio-6.txt' using 1:($3/100) title "Peso del algoritmo goloso", \
     '../resultados-tests-ejercicio-6.txt' using 1:($4/100) title "Peso del algoritmo goloso con búsqueda local", \
     '../resultados-tests-ejercicio-6.txt' using 1:($5/100) title "Peso del GRASP", \

reset
set terminal png size 800,600
set output "ejercicio_6_comparacion_calidad_error_relativo.png"
set key top left
set yrange [0:30]
set xlabel "Cantidad de vértices (n)"
set ylabel "Error realivo con respecto al exacto"
set title "Comparación del error relativo de los pesos obtenidos por GRASP\nalgoritmo goloso y algoritmo goloso más la búsqueda local\ncon respecto al peso del exacto en función de n"
plot '../resultados-tests-ejercicio-6.txt' using 1:((($3*100)/$2)-100) title "Error relativo del algoritmo goloso", \
     '../resultados-tests-ejercicio-6.txt' using 1:((($4*100)/$2)-100) title "Error relativo del algoritmo goloso con búsqueda local", \
     '../resultados-tests-ejercicio-6.txt' using 1:((($5*100)/$2)-100) title "Error relativo del GRASP", \
