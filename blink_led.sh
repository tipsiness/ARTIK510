#!/bin/bash

if [ "$#" -lt 1 ]; then
	echo "$# is illegal number of parameters."
	echo "Usage: $0 [r|b] [count] [interval]"
	exit 1
fi

args=("$@")

if [ "$1" == "b" ]; then
	echo 38 > /sys/class/gpio/export
	echo out > /sys/class/gpio/gpio38/direction
fi

count=0

while [ ${count} -le $2 ]; do
	count=$(( ${count}+1))
	echo 1 > /sys/class/gpio/gpio38/value
	sleep $3
	echo 0 > /sys/class/gpio/gpio38/value
	sleep $3
done

