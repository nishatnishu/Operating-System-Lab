#!/bin/bash
echo "System Tool Menu"
echo "1. Show date"
echo "2. Show calendar"
echo "3. Show uptime"
read -p "Choose an option: " opt

case $opt in
    1) date ;;
    2) cal ;;
    3) uptime ;;
    *) echo "❌ Invalid option!" ;;
esac
