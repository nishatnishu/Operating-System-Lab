#!/bin/bash
read -sp "Enter a password to check: " password
echo
if [[ ${#password} -ge 8 && "$password" =~ [A-Z] && "$password" =~ [a-z] && "$password" =~ [0-9] ]]; then
    echo "✅Strong password!"
else
    echo "❌Weak password! Try using uppercase,lowercase and numbers with at least 8 characters."
fi
