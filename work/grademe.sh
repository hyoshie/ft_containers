#!/bin/bash

# $1 = binary_ft
# $2 = binary_stl
diff <(./$1) <(./$2)
if [ $? == 0 ]; then
	echo OK
else
	echo NG
fi
