#!/bin/bash
read -p "Enter a string: " str
rev=$(echo "$str" | rev)

if [ "$str" == "$rev" ]; then
    echo "The String is Palindrome✅"
else
    echo "The String is Not a Palindrome!❌"
fi
