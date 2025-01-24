#!/bin/bash

operation=$1
interface=$2
protocol=$3
nb_args=$#

check_usage()
{
	if [[ $nb_args -lt 2 || $nb_args -gt 3 ]]; then
		echo -e "Usage:"
		echo " OUTGOING packets: ./iptables <operation> <interface> <protocol>"
		echo " INCOMING packets: ./iptables <operation> <protocol>"
		exit 1
	elif [[ $nb_args -eq 3 ]]; then
		if [[ $operation != "disable_sending" && $operation != "enable_sending" ]]; then
			echo -e "Usage:"
			echo " OUTGOING packets: ./iptables <operation> <interface> <protocol>"
			echo " INCOMING packets: ./iptables <operation> <protocol>"
			exit 1
		fi
	elif [[ $nb_args -eq 2 ]]; then
		if [[ $operation != "disable_receiving" && $operation != "enable_receiving" ]]; then
			echo -e "Usage:"
			echo " OUTGOING packets: ./iptables <operation> <interface> <protocol>"
			echo " INCOMING packets: ./iptables <operation> <protocol>"
			exit 1
		fi
	fi
}

filter_packets()
{
	if [[ $operation == "disable_sending" ]]; then
		sudo iptables -A OUTPUT -p $protocol -o $interface -j DROP
		echo "* sending disabled *"
	elif [[ $operation == "enable_sending" ]]; then
		sudo iptables -D OUTPUT -p $protocol -o $interface -j DROP
		echo "* sending enabled *"
	elif [[ $operation == "disable_receiving" ]]; then
		sudo iptables -A INPUT -p $protocol -j DROP
		echo "* receiving disabled *"
	elif [[ $operation == "enable_receiving" ]]; then
		sudo iptables -D INPUT -p $protocol -j DROP
		echo "* receiving enabled *"
	fi
}

check_usage
filter_packets
