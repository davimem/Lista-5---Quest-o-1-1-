reset
set terminal pdf
set output "grafico2.pdf"
plot "saida2.dat" w l t "S", "saida2.dat" u  1:3 t "I" w l, "saida2.dat" u 1:4 t "R" w l
set terminal x11
rep