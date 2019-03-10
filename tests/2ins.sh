# !/bin/bash

echo "\n\033[01;37m>>>>>>>>>>  Lists of 2 elements  <<<<<<<<<<\033[0m\n"
for i in {1..5}; do
	for j in {1..5}; do
		if [ $j -ne $i ] ; then
			ARG="$i $j"; echo "Input = $ARG";
			../push_swap $ARG | ../checker -cn $ARG
		fi
	done
done
