# !/bin/bash

make -C ..
rm output

for i in `seq 1 $1`; do ARG=`ruby -e "puts (1..$2).to_a.shuffle.join(' ')"`; echo $ARG >> output;
echo "\n-------------------------------------------------------------------------\n";
echo $ARG;
echo "\n-------------------------------------------------------------------------\n"; .././push_swap -co $ARG | .././checker -cn $ARG >> output ; done
