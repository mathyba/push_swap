# !/bin/bash

echo "\n\033[01;37m>>>>>>>>>>  Lists of 3 elements  <<<<<<<<<<\033[0m\n"
for i in `seq 1 5`; do
for j in `seq 1 5`; do
for k in `seq 1 5`; do
if [ $j -ne $i ] && [ $j -ne $k ] && [ $i -ne $k ] ; then
ARG="$i $j $k"; echo "Input = $ARG";
	../push_swap $ARG | ../checker -cn $ARG
fi
done
done
done
