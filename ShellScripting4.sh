#!/bin/bash
read -p "Enter a number: " num
prime=true

if [ $num -lt 2 ]; then
    prime=false
else
    for ((i=2; i*i<=num; i++)); do
        if [ $((num % i)) -eq 0 ]; then
            prime=false
            break
        fi
    done
fi

if $prime; then
    echo "$num is Prime"
else
    echo "$num is Not Prime"
fi
