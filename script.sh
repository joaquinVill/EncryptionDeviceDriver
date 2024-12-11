#!/bin/bash

MONITOR_USB="/media/joaquin/usb"
MONITOR_DESKTOP="/home/joaquin/Desktop"
ENCRYPT="/home/joaquin/Documents/Project/encrypt"
DECRYPT="/home/joaquin/Documents/Project/decrypt"
INOTIFYWAIT="/usr/bin/inotifywait"

usb_monitoring(){
$INOTIFYWAIT -m "$MONITOR_USB" -e create|
while read -r directory event filename; do

    full_file_path="$directory$filename"
    if [[ $event == "CREATE" ]]; then
        bash -c "$ENCRYPT $full_file_path; exec bash"
    fi

done
}

desktop_monitoring(){
$INOTIFYWAIT -m "$MONITOR_DESKTOP" -e create|
while read -r directory event filename; do

    full_file_path="$directory$filename"
    if [[ $event == "CREATE" ]]; then
        bash -c "$DECRYPT $full_file_path; exec bash"
    fi
    
done
}

usb_monitoring &
desktop_monitoring &
wait
