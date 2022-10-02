#!/bin/bash

LOGDIR=./log
FT_LOG=${LOGDIR}/output_ft.txt
STL_LOG=${LOGDIR}/output_stl.txt

# $1 = binary_ft
# $2 = binary_stl
./$1  > ${FT_LOG}
./$2  > ${STL_LOG}
diff ${FT_LOG} ${STL_LOG}
if [ $? == 0 ]; then
	echo -e "\e[32mOK:)\e[m"
else
	echo -e "\e[33mOH MY GOD:()\e[m"
fi
