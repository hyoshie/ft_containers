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
	awk '{ratio = $4/$8} {printf "%s%13s [ratio]%5.2f [ft]%6.4f [stl]%6.4f\n", $1, $2,  ratio, $4, $8}' $TMP_LOG  > $RESULT_LOG
}

validate_ratio(){
	over_flag=0;
	while read line ; do
		ratio=$(echo $line | cut -d "]" -f 2 | cut -d "[" -f 1)
		result=$(echo "$ratio > 20" | bc)
		if [ $result -eq 1 ]; then
			over_flag=1;
		fi
	done  < $RESULT_LOG

	cat $RESULT_LOG
	if [ $over_flag -eq 0 ]; then
		printf  "\033[32mGood Performance:)\033[m\n"
	else
		printf  "\033[33mOver 20 times, OH MY GOD:()\033[m\n"
	fi

}


# $1 = binary_ft
# $2 = binary_stl
# -----main script-----
make_log $1 $2
validate_ratio
