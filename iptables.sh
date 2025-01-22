#!/bin/bash

operation=$1
interface=$2
protocol=$3

if [ $# -lt 3 ]; then
	echo "Usage: ./iptables <operation> <interface> <protocol>"

else
	if [ $operation = "disable_sending" ]; then
		sudo iptables -A OUTPUT -p $protocol -o $interface -j DROP
		echo "* sending disabled *"
	elif [ $operation = "enable_sending" ]; then
		sudo iptables -D OUTPUT -p $protocol -o $interface -j DROP
		echo "* sending enabled *"
	elif [ $operation = "disable_receiving" ]; then
		sudo iptables -A INPUT -p $protocol -j DROP
		echo "* receiving disabled *"
	elif [ $operation = "enable_receiving" ]; then
		sudo iptables -D INPUT -p $protocol -j DROP
		echo "* receiving enabled *"
	fi
fi
