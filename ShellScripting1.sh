#!/bin/bash
read -p "Enter a number: " n

if [ $n -gt 0 ]; then
    echo "$n is Positive"
elif [ $n -lt 0 ]; then
    echo "$n is Negative"
else
    echo "$n is Zero"
fi
