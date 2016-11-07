#!/bin/bash
DIRNAME="`dirname $0`"
. $DIRNAME/config.sh
FILENAME="`ssh s bin/dl "$1"|tail -2|head -1|cut -d \  -f 3-|tr '\n' ' '|sed -r 's/[[:space:]]*$//g'`"
FILENAME_ESCAPED="`printf '%q' "$FILENAME"`"
#FILENAME_ESCAPED="`printf '%q' "$FILENAME_ESCAPED"`"
#bash -c "scp s:$FILENAME_ESCAPED $HOME/zene/youtube"
scp s:*"$1"* $MUSIC_DIRECTORY
echo $FILENAME
mpc update &>/dev/null
sleep 1
mpc ls youtube|grep "$1"|mpc add
mpc rm list
mpc save list
killall sonata
#sleep 1
#DISPLAY=:0 sonata &
exit 0
