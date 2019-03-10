# !/bin/bash

make -C ..
echo "\n\033[01;37m>>>>>>>>>>  Lists of 1 element  <<<<<<<<<<\033[0m\n"
ARG="13"; echo "Input = $ARG"; ../push_swap -co $ARG | ../checker -cn $ARG
ARG="0"; echo "Input = $ARG"; ../push_swap -co $ARG | ../checker -cn $ARG
ARG="-5"; echo "Input = $ARG"; ../push_swap -co $ARG | ../checker -cn $ARG
sh 2ins.sh
sh 3ins.sh
sh 4ins.sh
sh 5ins.sh
