#!/bin/bash

file_path=$1 

if [ -z "$file_path" ]; then
    echo "Erorr! No argument."
    exit 0
fi

if [ ! -f "$file_path" ]; then
echo "'$file_path' does not exist."
exit 0
fi

if [[ ! "$file_path" == *".log" ]]; then
echo "invalid file extension."
exit 0
fi

# if [ ! -s "$file_path" ]; then
# echo "'$file_path' is empty."
# exit 0
# fi

numb_records=$(wc -l < $file_path | sed -r 's/ //g')
numb_unic_files=$(awk '{print $1}' $file_path | uniq | wc -l | sed -r 's/ //g')
numb_changes=$(awk '{if ($8 != "NULL") print $8}' $file_path | sort -u | wc -l | sed -r 's/ //g')

echo $numb_records $numb_unic_files $numb_changes