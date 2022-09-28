#!/bin/bash

# $1 = binary_ft
# $2 = binary_stl
diff <(./$1) <(./$2)
if [ $? == 0 ]; then
	echo -e "\e[32mOK:)\e[m"
else
	echo -e "\e[33mOH MY GOD:()\e[m"
fi
