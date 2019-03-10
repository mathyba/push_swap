# !/bin/bash

echo "\n\033[01;37m>>>>>>>>>>  Lists of 4 elements  <<<<<<<<<<\033[0m\n"
for i in `seq 1 5`; do
	for j in `seq 1 5`; do
		for k in `seq 1 5`; do
			for l in `seq 1 5`; do
				if [ $j -ne $i ] && [ $j -ne $k ] && [ $i -ne $k ] && [ $l -ne $i ] && [ $l -ne $j ] && [ $l -ne $k ] ; then
					ARG="$i $j $k $l"; echo "Input = $ARG";
					../push_swap $ARG | ../checker -cvn $ARG
				fi
			done
		done
	done
done
