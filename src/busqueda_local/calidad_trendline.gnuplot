set term png
set xrange[0:24]
set yrange[0:16000]
set title "Peso promedio"
set output "calidad_trendline.png"
set xlabel "n"
set ylabel "Peso de la partición"
plot 'pesos_local.out' using 2 title 'exacto', 'pesos_local.out' using 3 title 'vecindad B (swap)', 'pesos_local.out' using 5 title 'vecindad A (subset jump)'
