reset
set autoscale x
set autoscale y
set ytics 0.02
set xlabel " n [-]"
set ylabel " t [s]"
set key top left
set title "Laufzeitvergleich der Sortieralgorithmen"

plot \
"quicksort.txt" with linespoints title 'Quicksort',\
"mergesort.txt" with linespoints title 'Mergesort',\
"shellsort.txt" with linespoints title 'Shellsort',\
"heapsort.txt" with linespoints title  'Heapsort',\