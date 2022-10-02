#!/bin/bash

LOGDIR=./log
FT_LOG=${LOGDIR}/benchmark_ft.txt
STL_LOG=${LOGDIR}/benchmark_stl.txt
TMP_LOG=${LOGDIR}/benchmark_tmp.txt
RESULT_LOG=${LOGDIR}/benchmark_result.txt

# $1 = binary_ft
# $2 = binary_stl
make_log() {
	./$1 > $FT_LOG
	./$2 > $STL_LOG
	paste $FT_LOG $STL_LOG  > $TMP_LOG
	awk '{ratio = $3/$6} {printf "%13s [ratio]%5.2f [ft]%6.4f [stl]%6.4f\n", $1, ratio, $3, $6}' $TMP_LOG  > $RESULT_LOG
}

validate_ratio(){
	while read line ; do
		ratio=$(echo $line | cut -d "]" -f 2 | cut -d "[" -f 1)
		result=$(echo "$ratio > 20" | bc)
		if [ $result -eq 1 ]; then
			echo -e "\e[33mOver 20 times, OH MY GOD:()\e[m"
			exit 1
		fi
	done  < $RESULT_LOG
	echo -e "\e[32mPerformance is OK:)\e[m"
}


# $1 = binary_ft
# $2 = binary_stl
# -----main script-----
make_log $1 $2
validate_ratio
