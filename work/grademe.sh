#!/bin/bash

# $1 = binary_ft
# $2 = binary_stl
# diff <(./$1) <(./$2)
./$1  > ft_log
./$2  > stl_log
diff ft_log stl_log
if [ $? == 0 ]; then
	echo -e "\e[32mOK:)\e[m"
else
	echo -e "\e[33mOH MY GOD:()\e[m"
fi
