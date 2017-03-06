#!/bin/bash

function usage ()
{
	echo "Usage: $0 [-p] [-s SIGNAL] username"
	exit 1
}

if [ $# -lt 1 ]
then
	usage
fi
if [ $# -gt 4 ]
then
	usage
fi
if [ $# -eq 1 ]
then
	ps -u $1
	exit
fi

just_PID=0
send_signal=0
username_entered=0
while [ $# -gt 0 ]
do
	case "$1" in
	-p)
		shift
		just_PID=1
		;;
	-s)
		shift
		send_signal=1
		SIGNAL=$1
		shift
		;;
	-*)
		echo "Incorrect parameter"
		usage
		;;
	*)
		if [ $username_entered -eq 1 ]
		then
			usage
		fi
		username_entered=1
		USERNAME=$1
		getent passwd $USERNAME > /dev/null 2&>1
		if [ $? -ne 0 ] 
		then
			echo "No such user"
			usage
		fi
		shift
		;;
	esac
done

if [ $username_entered -eq 0 ]
then
	usage
fi

if [ $just_PID -eq 1 ] && [ $send_signal -eq 1 ]
then
	echo "Printing with just PID end sending signal $SIGNAL"
	ps -u $USERNAME -o pid=
	ps -u $USERNAME -o pid= | xargs kill -s $SIGNAL
elif [ $just_PID -eq 1 ]
then
	echo "Printing with just PID"
	ps -u $USERNAME -o pid=
elif [ $send_signal -eq 1 ]
then
	echo "Printing and sending signal $SIGNAL"
	ps -u $USERNAME
	ps -u $USERNAME -o pid= | xargs kill -s $SIGNAL
fi
